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

local mediator = require 'mediator'


print 'Loading package Season2...'

-- The package table
local Season2 = {}; Season2.__index = Season2

setmetatable(Season2,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
        }, Season2)
    end
})

function Season2:onLevelLoaded()
    -- Add sun animation
    local sun = CCNode:create()
    sun:setPosition(ccp(pix2d.VisibleRect:pointAt(0.1,0.7)))
    sun:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCMoveTo:create(22,ccp(pix2d.VisibleRect:pointAt(0.4,0.7))),
        CCMoveTo:create(22,ccp(pix2d.VisibleRect:pointAt(0.1,0.7))))))
    self.level.backgroundLayer:addChild(sun,self.level.zorder.background.behindBackgroundImage)
    -- Circle 1
    local circle = CCSprite:createWithSpriteFrameName('circle_128.png')
    circle:setColor(ccc3(252,244,79))
    circle:setOpacity(84)
    circle:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCScaleTo:create(1,1.8),CCScaleTo:create(1,1.3))))
    sun:addChild(circle)
    -- Circle 2
    circle = CCSprite:createWithSpriteFrameName('circle_128.png')
    circle:setColor(ccc3(252,244,79))
    circle:setOpacity(144)
    circle:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCScaleTo:create(1,1.4),CCScaleTo:create(1,1.2))))
    sun:addChild(circle)
    -- Circle 3
    circle = CCSprite:createWithSpriteFrameName('circle_128.png')
    circle:setColor(ccc3(255,212,42))
    circle:setOpacity(128)
    sun:addChild(circle)
    -- Sun's face
    local face = CCSprite:createWithSpriteFrameName('sun_face.png')
    face:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCRotateTo:create(1,-5),CCRotateTo:create(1,5))))
    sun:addChild(face)
end

-- Public package functions
function Season2:init(level)
    self.level = level
    -- Lose if touch the upper world boundary
    mediator:subscribe(mediator.ns.contactTopBoundary,function()
        mediator:publish(mediator.ns.lose)
    end)
    return self
end

-- Return this package
return Season2
-- EOF
