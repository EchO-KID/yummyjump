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

local util = require 'util'

print 'Loading package ScrollSprite...'

-- The package table
local ScrollSprite = {}; ScrollSprite.__index = ScrollSprite

setmetatable(ScrollSprite,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            sprites = {}
        }, ScrollSprite)
    end
})

function ScrollSprite:insert(p,position)
    local sprite = p.frame and CCSprite:createWithSpriteFrameName(p.frame)
                            or CCSprite:create(p.sprite)
    if p.opacity then sprite:setOpacity(p.opacity) end
    if p.color then sprite:setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    if p.flip then sprite:setFlipX(p.flip[1]); sprite:setFlipY(p.flip[2]) end
    sprite:setPosition(position)
    self.node:addChild(sprite)
    table.insert(self.sprites,sprite)
    return sprite
end

-- Public package functions
function ScrollSprite:init(p)
    -- The node container
    self.node = CCNode:create()
    -- Create a dummy sprite to get the sprite's size
    local size = p.frame and CCSprite:createWithSpriteFrameName(p.frame):getContentSize()
                          or CCSprite:create(p.sprite):getContentSize()
    local dir = ccpSub(p.endPos,p.startPos)
    local len = ccpDistance(p.startPos,p.endPos)
    -- offset is either the sprite's width or height depending the direction
    local offset = (math.abs(dir.x) > math.abs(dir.y) and size.width or size.height) / len
    -- Create sprite from start position minus offset to end position plus offset
    for i = -offset, 1.0 + offset, offset do
        self:insert(p,ccpLerp(p.startPos,p.endPos,i))
    end
    -- Move the container node by one offset
    local move = ccpSub(p.startPos,ccpLerp(p.startPos,p.endPos,offset))
    self.node:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCMoveBy:create(p.time * offset,ccp(-move.x,-move.y)),
        CCMoveTo:create(0,ccp(0,0)))))
    return self
end

-- Return this package
return ScrollSprite
-- EOF
