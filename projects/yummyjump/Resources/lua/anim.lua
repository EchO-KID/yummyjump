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

local Anim = {}
Anim.__index = Anim

local framecache = CCSpriteFrameCache:sharedSpriteFrameCache()

-- Create and run an animate action (CCAnimate) on a sprite.
-- If no sprite is provided then a new one is created.
-- Paramters: a table with the following keys.
-- p = {
--     sprite = mysprite, -- if nil a new sprite is created
--     repeatForever = true, -- Should the animation repeat forever?
--     frames = { 'framename1.png','framename2.png' }, -- frame names to add to this animation
--     delay = 0.5 -- animation delay per unit
-- }
-- Returns the sprite (or the new sprite if nil) and the new animation action (CCAnimate or CCRepeatForever)
function Anim:runAnimation(p)
    -- create the animation  object
    local anim = CCAnimation:create()
    anim:setRestoreOriginalFrame(true)
    anim:setDelayPerUnit(p.delay)
    for _,v in ipairs(p.frames) do
        local spriteFrame = framecache:spriteFrameByName(v)
        assert(spriteFrame)
        anim:addSpriteFrame(spriteFrame)
    end
    -- create the sprite
    if not p.sprite then
        p.sprite = CCSprite:create()
    end
    -- run the animation action
    local action = CCAnimate:create(anim)
    if p.repeatForever then
        action = CCRepeatForever:create(action)
    end
    p.sprite:runAction(action)
    return p.sprite, action
end

local function dancingTweenHandler(sprite,quad,value,key)
    -- dancingTweenHandler is called too much time for the
    -- garbage collector to release the value returned by getQuad.
    -- Even if some of the memory is released by the garbage collector,
    -- the application eventually runs out of memory and crashes.
    -- quad = sprite:getQuad()
    if key == 'tl.x' then
        quad.tl.vertices.x = value
    elseif key == 'tl.y' then
        quad.tl.vertices.y = value
    elseif key == 'tr.x' then
        quad.tr.vertices.x = value
    elseif key == 'tr.y' then
        quad.tr.vertices.y = value
    elseif key == 'bl.x' then
        quad.bl.vertices.x = value
    elseif key == 'bl.y' then
        quad.bl.vertices.y = value
    elseif key == 'br.x' then
        quad.br.vertices.x = value
    elseif key == 'br.y' then
        quad.br.vertices.y = value
    end
    sprite:setQuad(quad)
end

function Anim:blinkFade()
    return CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCEaseOut:create(CCFadeTo:create(0.6,0),0.3),
        CCFadeTo:create(0.4,255)))
end

function Anim:skew(time,x,y,x2,y2)
    x2 = x2 or -x
    y2 = y2 or -y
    return CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCSkewTo:create(time,x,y),
        CCSkewTo:create(time,x2,y2)))
end

function Anim:repeatForever(target,actionA,actionB)
    local action = CCRepeatForever:create(CCSequence:createWithTwoActions(actionA,actionB))
    target:runAction(action)
    return action
end

-- Run an "dancing" action on the sprite `sprite`. The sprite must be an instance of CustomSprite.
function Anim:dance(sprite)
    -- Call getQuad once to init an upvalue to fix a memory issue
    local quad = sprite:getQuad()
    sprite:registerTweenActionHandler(function(value,key) dancingTweenHandler(sprite,quad,value,key) end)
    local s = sprite:getContentSize()
    local ox = -8
    local ox2 = 8
    local ox3 = -8
    local ox4 = 8
    local oy = -1
    local oy2 = 4
    local oy3 = 4
    local oy4 = -1
    local d = 0.5
    actions = CCArray:create()
    actions:addObject(CCActionTween:create(d,'tl.x',0,ox))
    actions:addObject(CCActionTween:create(d,'tl.x',ox,0))
    actions:addObject(CCActionTween:create(d,'tl.x',0,ox2))
    actions:addObject(CCActionTween:create(d,'tl.x',ox2,0))
    sprite:runAction(CCRepeatForever:create(CCSequence:create(actions)))

    actions:removeAllObjects()
    actions:addObject(CCActionTween:create(d,'tr.x',s.width,s.width+ox3))
    actions:addObject(CCActionTween:create(d,'tr.x',s.width+ox3,s.width))
    actions:addObject(CCActionTween:create(d,'tr.x',s.width,s.width+ox4))
    actions:addObject(CCActionTween:create(d,'tr.x',s.width+ox4,s.width))
    sprite:runAction(CCRepeatForever:create(CCSequence:create(actions)))

    actions:removeAllObjects()
    actions:addObject(CCActionTween:create(d,'tl.y',s.height,s.height+oy))
    actions:addObject(CCActionTween:create(d,'tl.y',s.height+oy,s.height))
    actions:addObject(CCActionTween:create(d,'tl.y',s.height,s.height+oy2))
    actions:addObject(CCActionTween:create(d,'tl.y',s.height+oy2,s.height))
    sprite:runAction(CCRepeatForever:create(CCSequence:create(actions)))

    actions:removeAllObjects()
    actions:addObject(CCActionTween:create(d,'tr.y',s.height,s.height+oy3))
    actions:addObject(CCActionTween:create(d,'tr.y',s.height+oy3,s.height))
    actions:addObject(CCActionTween:create(d,'tr.y',s.height,s.height+oy4))
    actions:addObject(CCActionTween:create(d,'tr.y',s.height+oy4,s.height))
    sprite:runAction(CCRepeatForever:create(CCSequence:create(actions)))
end

function Anim:createSequence(actions,repeatForever)
   local array = CCArray:create()
   for i=1,#actions do
       array:addObject(actions[i])
   end
   return repeatForever
        and CCRepeatForever:create(CCSequence:create(array))
        or CCSequence:create(array)
end

return Anim
