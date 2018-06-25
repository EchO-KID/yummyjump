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

local factory = {}; factory.__index = factory

-- Create a custom sprite that implement CCActionTweenDelegate
-- p.frame: the sprite frame name
-- p.position: an array with the x,y position
function factory:createCustomSprite(p)
    local sprite = pix2d.CustomSprite:createWithSpriteFrameName(p.frame)
    sprite:setPosition(pix2d.Physics:unitToPixel(p.position[1],p.position[2]))
    return sprite
end

-- Mandatory: position
local function initPhysicNode(def,p)
    assert(p.position)
    def.uid = p.uid or 0
    def.tag = p.tag or 0
    def.zorder = p.zorder or 0
    def.is_sensor = p.sensor or false
    def.body_type = p.body_type or physics.StaticBody
    def.pos.x = p.position[1]
    def.pos.y = p.position[2]
    def.angle = p.angle or 0
    def.frame = p.frame
    def.sprite = p.sprite
    def.category = p.category or 0x0001
    def.mask = p.mask or 0xFFFF
    def.group = p.group or 0
    def.restitution = p.restitution or 0.2
    def.density = p.density or 0.1
    def.friction = p.friction or 0.1
    return def
end

-- Create a Box physic node
-- Mandatory parameters: uid,position,size
function factory:box(p)
    -- assert(p.uid and p.position and p.size,"Missing required parameter(s) to factory:box")
    local def = pix2d.BoxDef:new()
    def.size.x = p.size[1]
    def.size.y = p.size[2]
    if p.center then def.center.x = p.center[1]; def.center.y = p.center[2] end
    return pix2d.Box:create(initPhysicNode(def,p))
end

-- Create a Chain physic node
function factory:chain(p)
    p.position = {0,0}
    local def = pix2d.ChainDef:new()
    for i=1,#p.points,2 do
        def.vertices:push_back(b2Vec2(p.points[i],p.points[i+1]))
    end
    return pix2d.Chain:create(initPhysicNode(def,p))
end

-- Create a Circle physic node
function factory:circle(p)
    local def = pix2d.CircleDef:new()
    def.radius = p.radius or 0.25
    return pix2d.Circle:create(initPhysicNode(def,p))
end

-- Create a Texture physic node
function factory:texture_node(p)
    -- position is useless but must be provided
    p.position = {0,0}
    local def = pix2d.TextureDef:new()
    initPhysicNode(def,p)
    def.texture = p.texture
    def.simplify = p.simplify or false
    for i=1,#p.points,2 do
        def.vertices:push_back(b2Vec2(p.points[i],p.points[i+1]))
    end
    return pix2d.Texture:create(def)
end

-- Create a rope node
function factory:rope(p)
    local def = pix2d.RopeDef:new()
    def.uid = p.uid or 0
    def.tag = p.tag or 0
    def.startpos.x = p.startpos[1]
    def.startpos.y = p.startpos[2]
    def.endpos.x = p.endpos[1]
    def.endpos.y = p.endpos[2]
    def.hookFrame = p.hook
    def.anchorFrame = p.anchor
    def.batch = p.batch
    def.anchorRadius = p.anchorRadius
    def.anchorDensity = p.anchorDensity or 0.1
    def.sensorRadius = p.sensorRadius
    def.hookRadius = p.hookRadius
    def.hookRestitution = p.hookRestitution or 0.2
    def.hookDensity = p.hookDensity or 0.1
    def.hookFriction = p.hookFriction or 0.1
    def.hookLocalAnchor = p.hookLocalAnchor or b2Vec2(0,0)
    def.anchorLocalAnchor = p.anchorLocalAnchor or b2Vec2(0,0)
    return pix2d.Rope:create(def)
end

-- Create a MoveTo action
function factory:move_to(p)
    return pix2d.MoveTo:create(pix2d.Physics:unitToMeter(p.startPos[1],p.startPos[2]),
                               pix2d.Physics:unitToMeter(p.endPos[1],p.endPos[2]),p.speed)
    -- return pix2d.MoveTo:create(b2Vec2(p.startPos[1],p.startPos[2]),b2Vec2(p.endPos[1],p.endPos[2]),p.speed)
end

-- Create a CircleTo action
-- Fix me: set speed or duration in the create method
function factory:circle_to(p)
    return pix2d.CircleTo:create(b2Vec2(p.center[1],p.center[2]),p.duration)
end

-- Create a SplineTo action. Not stable. Do not use.
function factory:spline_to(p)
    local a = CCPointArray:create(#p.points)
    for i=1,#p.points,2 do
        a:addControlPoint(pix2d.Physics:unitToPixel(p.points[i],p.points[i+1]))
    end
    return pix2d.SplineTo:create(p.duration or 1,a,p.tension or 1)
end

-- Create a 'CircleTo' circle platform
function factory:platform_circle_to(p)
    p.body_type = physics.KinematicBody
    local c = self:circle(p)
    local a = self:circle_to(p)
    assert(c and a, 'Cant create the circle platform')
    a:setSpeed(p.speed)
    c:runAction(a)
    return c, a
end

-- Create a 'MoveTo' cirle platform
function factory:platform_move_to(p)
    p.body_type = physics.KinematicBody
    local c = self:circle(p)
    local a = self:move_to(p)
    assert(c and a, 'Cant create the moveto platform')
    c:runAction(a)
    return c, a
end

-- Create a texture sprite (not a physic body)
function factory:texture_sprite(p)
    local c = vector_CCPoint_:new_local()
    for i=1,#p.points,2 do
        c:push_back(pix2d.Physics:unitToPixel(p.points[i],p.points[i+1]))
    end
    local out = vector_CCPoint_:new_local()
    pix2d.Texture:triangulate(c,out)
    return pix2d.TextureSprite:create(p.texture,out)
end

-- Create a rect texture sprite
function factory:texture_AABB(p)
    return pix2d.TextureSprite:createWithAABB(
        p.texture,
        CCPoint(p.upperBound[1],p.upperBound[2]),
        CCPoint(p.lowerBound[1],p.lowerBound[2]))
end

-- TESTS
--[[
function factory:run_tests()
    -- test texture node
    local tex = self:texture_node {
        uid = 1,
        tag = 1,
        body_type = physics.StaticBody,
        texture = 'textures/ground_texture.png',
        points = {1,0, 1,4, 2,4, 4,0},
    }
    assert(tex,'Cant create the texture node')
    physics:addNode(tex)

    -- test create a Circle
    local c = self:circle {
        uid = 2,
        tag = 1,
        sprite = 'png/g9718.png',
        radius = 1,
        position = {1, 1},
        body_type = physics.KinematicBody
    }

    -- test SplineTo action
    local a = self:spline_to {
        tension = 5.5,
        duration = 3,
        points = {{1, 1}, {2, 2}, {3, 2}},
    }

    c:runAction(a)
    physics:addNode(c)

    -- test circle platform
    local c, a = self:platform_circle_to {
        uid = 3,
        tag = 1,
        sprite = 'png/bad1.png',
        radius = 1,
        position = {1, 1},
        center = {2, 2},
        duration = 2,
        speed = 0.5
    }

    -- test RepeatForever action
    c:stopAction(a) -- must stop the action before reuse it or it will crash
    c:runAction(CCRepeatForever:create(a))
    physics:addNode(c)

    -- test moveto platform
    local c, a = self:platform_move_to {
        uid = 4,
        tag = 1,
        sprite = 'png/g9735.png',
        position = {3, 3},
        start = {3, 3},
        dest = {5, 3},
        speed = 1
    }
    physics:addNode(c)

    local t = self:texture_AABB {
        texture = 'textures/stars_texture.png',
        upperBound = { 0, 300 },
        lowerBound = { 500, 0 }
    }
    assert(t, 'Cant create the texture sprite')
    -- physics:addNode(t)

    local batch = physics:layer():addBatchNode('textures/rainbow.png',100)
    --local batch = physics:layer():getBatchNode(99)

    assert(batch,'Cant create the rope batch node')

    local rope = self:rope {
        uid = 10,
        tag = 4,
        startpos = {5,5},
        endpos  = {5,3},
        batch = batch,
        frame = ''
    }
    assert(rope,'Cant create the rope')
    physics:addNode(rope)
end -- End of run_tests()
--]]

-- run the tests
--factory:run_tests()

-- return the package
return factory
