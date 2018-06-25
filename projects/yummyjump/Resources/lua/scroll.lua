-- Copyright (C) 2012-2015 Laurent Zubiaur - voodoocactus.com
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.

local class = require 'class'
local util = require 'util'

local visible = pix2d.VisibleRect

local Scroll = {
    size = nil, -- size of the scroll area
    scrolled = false, -- false if it's the first time the container scroll
    touchDown = false,
    direction = nil, -- Scrolling direction: vertical or horizontal
    startSwipe = {}
}
Scroll.__index = Scroll
-- We don't want new assigment to be done in Scroll
-- Scroll.__newindex = Scroll

function Scroll:touchHandler(e,x,y)
    if e == 'began' then
        if not self.touchDown then
            self.direction = nil
            self.startTime = os.clock()
            self.touchDown = true
            self.scrolled = false
            self.startSwipe.x = x
            self.startSwipe.y = y
            return true
        end
        -- no multi-touch. avoid this extra touch
        return false
    elseif e == 'moved' then
        local dx = x - self.startSwipe.x
        local dy = y - self.startSwipe.y
        if not self.direction then
            -- check scrolling direction
            local adx = math.abs(dx)
            local ady = math.abs(dy)
            if ady > adx + 5 then
                self.direction = 'vertical'
            elseif ady < adx - 5 then
                self.direction = 'horizontal'
            else
                self.direction = nil
            end
        else
            -- first call with scrolled == false
            self.container:didScroll(self.direction,dx,dy,self.scrolled,x,y,self)
            -- now we start scrolling
            self.scrolled = true
        end
    else -- 'ended' and 'canceled'
        self.touchDown = false
        if self.direction == 'vertical' then
            local dy = y - self.startSwipe.y
            local ady = math.abs(dy)
            local v = ady / (os.clock() - self.startTime)
            if dy > 0 and (v > 500 or ady > self.size.height * 0.15) then
                self.container:didPreviousPage(self.direction,v)
            elseif dy < 0 and (v > 500 or ady > self.size.height * 0.15) then
                self.container:didNextPage(self.direction,v)
            else
                self.container:movePageCanceled(self.direction)
            end
        elseif self.direction == 'horizontal' then
            local dx = x - self.startSwipe.x
            local adx = math.abs(dx)
            local v = adx / (os.clock() - self.startTime)
            if dx > 0 and (v > 500 or adx > self.size.width * 0.15) then
                self.container:didPreviousPage(self.direction,v)
            elseif dx < 0 and (v > 500 or adx > self.size.height * 0.15) then
                self.container:didNextPage(self.direction,v)
            else
                self.container:movePageCanceled(self.direction)
            end
        end
    end
end

function Scroll:create(size,container)
    -- Create the layer instance
    local layer = CCLayer:create()
    -- extend (derive) CCLayer with Scroll. We can now call Scroll
    -- functions with the CCLayer instance. e.g. layer:scrollTo
    t = tolua.getpeer(layer) or {}
    t = setmetatable(t,self)
    tolua.setpeer(layer,t)

    layer.container = container
    layer.size = size
    layer.direction = direction
    -- Though instance.direction = 'vertical' will update the instance's field `direction`
    -- instance.startSwipe.x = 1 will actually update Scroll.startSwipe.x because
    -- instance.startSwipe.x is evaluated twice. First instance.startSwipe is evaluated
    -- which returns Scroll.startSwipe.
    -- Then it evaluate instance.startSwipe.x = 1 which updates Scroll.startSwipe.x
    -- Therefore we muse create a new startSwipe table for the instance
    layer.startSwipe = {}

    -- Note: the anonymous function must return the value returned by touchHandler
    -- to swallow or not the touch began event
    layer:registerScriptTouchHandler(
        function(e,x,y) return layer:touchHandler(e,x,y) end, -- touch handler
        false, -- no multi-touch (process touches one by one)
        kCCMenuHandlerPriority - 2, -- touch priority higher than CCMenu
        false) -- don't swallow touches
    layer:setTouchEnabled(true)

    return layer
end

-- Create a scolling container.
-- directiom: either 'vertical' or 'horizontal'
-- layers: an array of CCLayers
-- size: the page size (CCSize)
-- startIdx: the index of the initial page
-- didScrollCallback: callback function called every time the container is scrolled. First two parameters are the x,y offset and
-- the third parameter is a flag to indicate if it's the new scrolling starting (touch begin) or the same scrolling (touch move)
-- pageChangedCallback(idx): callback function called when the current page has changed. the parameters is the new page index
-- You can call moveToPreviousPage or moveToNextPage to move the current page backward or forward
function Scroll:createContainer(direction,layers,size,startIdx,didScrollCallback,pageChangedCallback)
    local Container = {
        direction = direction,
        size = size, -- screen size in point
        nScreens = 0, -- number of screens
        cScreen = 0, -- current screen number
        startpos = {},
        didScrollCallback = didScrollCallback, -- Must use a self.didScrollCallback because of forwardToSubContainer
        isContainer = true,
        isScrolling = false,
        scrollTo = function(self,x,y,t)
            self.isScrolling = true
            self:stopAllActions()
            self:runAction(CCSequence:createWithTwoActions(
                CCEaseSineOut:create(CCMoveTo:create(t,ccp(x,y))),
                CCCallFunc:create(function() self.isScrolling = false end)))
        end,
        forwardToSubContainer = function(self,f,...)
            local sub = layers[self.cScreen + 1]
            if sub.isContainer then
                f(sub,...)
            end
        end,
        didScroll = function(self,e,dx,dy,s,x,y,scroll)
            if e == self.direction then
                self.isScrolling = true
                if s == false then
                    -- first time `didScroll` is called
                    self.startpos.x,self.startpos.y = self:getPosition()
                end
                if e == 'horizontal' then
                    local px = -(dx + self.startpos.x)
                    -- TODO add an option to enable/disable bounce
                    if px < self.size.width * (self.nScreens - 1) and px > 0 then
                        self:setPositionX(dx + self.startpos.x)
                        if self.didScrollCallback then self.didScrollCallback(dx,dy,s) end
                    else
                        scroll.startSwipe.x = x
                    end
                else
                    local py = -(dy + self.startpos.y)
                    if py < self.size.height * (self.nScreens - 1) and py > 0 then
                        self:setPositionY(dy + self.startpos.y)
                        if self.didScrollCallback then self.didScrollCallback(dx,dy,s) end
                    else
                        scroll.startSwipe.y = y
                    end
                end
            else
                self:forwardToSubContainer(self.didScroll,e,dx,dy,s,x,y,scroll)
            end
        end,
        didPreviousPage = function(self,e,v)
            if e == self.direction then
                if self.cScreen - 1 >= 0 then
                    self:moveToPage(self.cScreen - 1,true,v)
                else
                    self:movePageCanceled(e)
                end
            else
                self:forwardToSubContainer(self.didPreviousPage,e,v)
            end
        end,
        didNextPage = function(self,e,v)
            if e == self.direction then
                if self.cScreen + 1 < self.nScreens then
                    self:moveToPage(self.cScreen + 1,true,v)
                else
                    self:movePageCanceled(e)
                end
            else
                self:forwardToSubContainer(self.didNextPage,e,v)
            end
        end,
        movePageCanceled = function(self,e)
            if e == self.direction then
                self:moveToPage(self.cScreen,true)
            else
                self:forwardToSubContainer(self.movePageCanceled,e)
            end
        end,
        moveToPreviousPage = function(self,animate)
            -- Check that the page is not currently scrolling
            if self.isScrolling == false and self.cScreen - 1 >= 0 then
                self:moveToPage(self.cScreen - 1,animate)
            end
        end,
        moveToNextPage = function(self,animate)
            if self.isScrolling == false and self.cScreen + 1 < self.nScreens then
                self:moveToPage(self.cScreen + 1,animate)
            end
        end,
        moveToPage = function(self,idx,animate,v)
            local time = 0.8 -- default scrolling animation time
            if self.direction == 'horizontal' then
                local p = idx * self.size.width
                if animate then
                    if v ~= nil then
                        local t = math.abs((p - self.cScreen * self.size.width) / v) -- time = distance / velocity
                        time = math.min(math.max(t,0.3),time) -- max/min time
                    end
                    self:scrollTo(-p,self:getPositionY(),time)
                else
                    self.isScrolling = false
                    self:setPositionX(-p)
                end
            else
                local p = idx * self.size.height
                if animate then
                    if v ~= nil then
                        local t = math.abs((p - self.cScreen * self.size.height) / v) -- time = distance / velocity
                        time = math.min(math.max(t,0.3),time) -- max/min time
                    end
                    self:scrollTo(self:getPositionX(),-p,time)
                else
                    self.isScrolling = false
                    self:setPositionY(-p)
                end
            end
            -- update the current screen position
            self.cScreen = idx
            if pageChangedCallback then pageChangedCallback(idx) end
        end
    }
    Container.__index = Container

    local layer = CCLayer:create()
    -- extend (derive) CCLayer with Scroll. We can now call Scroll
    -- functions with the CCLayer instance. e.g. layer:scrollTo
    local t = tolua.getpeer(layer) or {}
    t = setmetatable(t,Container)
    tolua.setpeer(layer,t)

    -- Set the page's position
    for idx, v in ipairs(layers) do
        if direction == 'vertical' then
            v:setPositionY(layer.nScreens * size.height)
        else
            v:setPositionX(layer.nScreens * size.width)
        end
        layer:addChild(v)
        layer.nScreens = layer.nScreens + 1
    end

    -- Set the starting page
    if startIdx then
        layer:moveToPage(startIdx,false)
    end

    return layer
end

return Scroll
-- EOF
