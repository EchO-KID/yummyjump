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

-- Packages dependencies
local class = require 'class'
local util = require 'util'
local mediator = require 'mediator'

print 'Loading package Grid...'

-- The package table
local Grid = {}; Grid.__index = Grid

setmetatable(Grid,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            -- package variables
            layer = nil,
            drawNode = nil,
            render = nil,
            size = nil, -- CCSize
            origin_x = 0.0,
            origin_y = 0,0,
            spacing_x = 10.0,
            spacing_y = 10.0,
            downsample = 1.0,
            color = ccc4f(1.0,1.0,1.0,1.0),
            focus = {
                x = nil, -- focuse index positions
                y = nil,
                fillcolor = ccc4f(0,1,0,0.6),
                sprite = nil,
            },
            cancelFocus = { x = nil, y = nil, fillcolor = ccc4f(1,0,0,0.6), sprite = nil },
            radius = 1.0,
            dots = false, -- Show dots instead of lines
        }, Grid)
    end
})

-- Set the focus to a new position. The x,y coord are grid's index (not pixels).
function Grid:setFocus(x,y)
    if self.focus.x ~= x or self.focus.y ~= y then
        local cx = self.spacing_x * x
        local cy = self.spacing_y * y
        self.focus.x = x
        self.focus.y = y
        self.focus.sprite:setPosition(cx,cy)
        self.cancelFocus.x = x
        self.cancelFocus.y = y
        self.cancelFocus.sprite:setPosition(cx,cy)
    end
end

function Grid:drawGrid()
    local width = self.size.width
    local height = self.size.height
    -- Clean up
    self.drawNode:clear()
    -- Draw the actual grid
    local from = ccp(0,0)
    local to = ccp(0,height)
    for x=self.origin_x, width, self.spacing_x do
        from.x = x
        to.x = x
        self.drawNode:drawSegment(from,to,self.radius,self.color)
    end
    from.x = 0
    to.x = width
    for y=self.origin_y, height, self.spacing_y do
        from.y = y
        to.y = y
        self.drawNode:drawSegment(from,to,self.radius,self.color)
    end
    -- Draw intersect corners
    --[[
    local cw = self.spacing_x * 0.1 -- corner width
    local ch = self.spacing_y * 0.1 -- corner height
    local p = vector_CCPoint_:new_local()
    for y=self.origin_y, height, self.spacing_y do
        for x=self.origin_x, width, self.spacing_x do
            p:push_back(ccp(x-cw,y)); p:push_back(ccp(x,y+ch)); p:push_back(ccp(x+cw,y)); p:push_back(ccp(x,y-ch))
            self.drawNode:drawPolygon(p,self.color,0,self.color)
            p:clear()
        end
    end
    --]]
end

-- Init must be called once after creating a package instance
function Grid:init()
    -- Create the gird's layer
    self.layer = CCLayer:create()
    -- Create the "focus" sprite
    local render = CCRenderTexture:create(self.spacing_x,self.spacing_y,kCCTexture2DPixelFormat_RGBA4444)
    render:begin()
    ccDrawSolidRect(ccp(0,0),ccp(self.spacing_x,self.spacing_y),self.focus.fillcolor)
    render:endToLua()
    self.focus.sprite = CCSprite:createWithTexture(render:getSprite():getTexture())
    self.focus.sprite:setVisible(false)
    self.focus.sprite:setAnchorPoint(ccp(0,0))
    self.layer:addChild(self.focus.sprite)
    -- Create the "cancel focus" sprite
    -- local trashSprite = CCSprite:createWithSpriteFrameName('trash.png')
    -- trashSprite:setColor(ccc3(0,0,0))
    -- trashSprite:setPosition(self.spacing_x/2,self.spacing_y/2)
    -- Need to create a new render
    render = CCRenderTexture:create(self.spacing_x,self.spacing_y,kCCTexture2DPixelFormat_RGBA4444)
    render:begin()
    ccDrawSolidRect(ccp(0,0),ccp(self.spacing_x,self.spacing_y),ccc4f(1,0,0,06))
    -- trashSprite:visit()
    render:endToLua()
    self.cancelFocus.sprite = CCSprite:createWithTexture(render:getSprite():getTexture())
    -- self.cancelFocus.sprite:setBlendFunc(util.blend(GL_ZERO,GL_SRC_ALPHA))
    self.cancelFocus.sprite:setVisible(false)
    self.cancelFocus.sprite:setAnchorPoint(ccp(0,0))
    self.layer:addChild(self.cancelFocus.sprite)
    -- Create the CCDrawNode and draw the grid
    self.drawNode = pix2d.DrawNode:create()
    self.layer:addChild(self.drawNode)
    self:drawGrid()
    -- grid is not visible by default
    self.layer:setVisible(false)
    -- Register to events
    local oldstate = false
    mediator:subscribe(mediator.ns.pauseGameplay,function()
        oldstate = self.layer:isVisible(); self.layer:setVisible(false)
    end)
    mediator:subscribe(mediator.ns.resumeGameplay,function()
        self.layer:setVisible(oldstate)
    end)
    mediator:subscribe(mediator.ns.tool_focus_began,function(_,name,x,y)
        self.layer:setVisible(true)
        self.drawNode:setVisible(true)
        self.focus.sprite:setVisible(true)
        self.cancelFocus.sprite:setVisible(false)
        self:setFocus(x,y)
    end)
    mediator:subscribe(mediator.ns.tool_focus_changed, function(_,name,x,y)
        self.drawNode:setVisible(false)
        self.focus.sprite:setVisible(true)
        self.cancelFocus.sprite:setVisible(false)
        self:setFocus(x,y)
    end)
    mediator:subscribe(mediator.ns.tool_selected,function()
        self.drawNode:setVisible(true)
        self.focus.sprite:setVisible(false)
        self.cancelFocus.sprite:setVisible(false)
        self.layer:setVisible(true)
    end)
    mediator:subscribe(mediator.ns.tool_focus_cancel,function(_,name,x,y)
        self.focus.sprite:setVisible(false)
        self.cancelFocus.sprite:setVisible(true)
        self:setFocus(x,y)
    end)
    mediator:subscribe(mediator.ns.tool_focus_ended,function()
        -- self.layer:setVisible(false)
    end)
    mediator:subscribe(mediator.ns.tool_unselected,function()
        self.layer:setVisible(false)
    end)
    mediator:subscribe(mediator.ns.lose,function()
        self.layer:setVisible(false)
    end)
    return self
end

-- Render the grid into a sprite
function Grid:createSprite()
    local r = CCRenderTexture:create(self.size.width,self.size.height,kCCTexture2DPixelFormat_RGBA8888)
    r:begin()
    self.layer:visit()
    r:endToLua()
    r:setScale(self.downsample)
    return r
end

-- Return this package
return Grid
-- EOF
