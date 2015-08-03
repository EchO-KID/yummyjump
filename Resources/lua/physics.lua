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

-- The Physics singleton is now a global variable.
-- Do not use this package directly unless to create the physics singleton (create function)

local instance = nil -- internal singleton instance

local Physics = {
    StaticBody = b2_staticBody,
    KinematicBody = b2_kinematicBody,
    DynamicBody = b2_dynamicBody,
    -- Collision category filter.
    -- This should be used to filter collision in order to avoid unwanted collisions.
    -- Then to filter the collision notifications use the
    -- registerCollisionNotificationScriptWithTag and provide the tag
    -- of a specific node type.
    -- For instance, balloons can collide with any ennemy (bad and spear) but
    -- get notified only for collision with spear.
    category = {
        noCollision = 0,
        hook = bit.lshift(1,0), -- use LuaJIT bitwise. See README.txt
        player = bit.lshift(1,1),
        ennemy = bit.lshift(1,2), -- Generic category for ennemies (bad, spear...)
        ground = bit.lshift(1,3),
        sensor = bit.lshift(1,4),
        platform = bit.lshift(1,5), -- Generic category for platform (slider,wood box..)
        balloon = bit.lshift(1,6),
        misc = 0xFFFF
    },
    -- Collision group filter
    group = {
        hook = -1, -- rope's hook should not collide with other hook
        sensor = -2, -- sensor doesn't collide with other sensor
        boundaryLeft    = pix2d.Physics.kBoundaryLeft, -- 1
        boundaryRight   = pix2d.Physics.kBoundaryRight, -- 2
        boundaryTop     = pix2d.Physics.kBoundaryTop, -- 3
        boundaryBottom  = pix2d.Physics.kBoundaryBottom, -- 4
        chain = -5,
    },
}
Physics.__index = Physics

--[[
print 'Physics categories'
for k,v in pairs(Physics.category) do
    print(k,v)
end
print('bit or',bit.bor(Physics.category.ground,Physics.category.player))
--]]

-- Pause the physics. The `pause` event must be published explicitly
function Physics:pause()
    -- we can't call physics:pause() because of recursion
    -- but we must use the super class to call the method
    if not physics:isPaused() then
        pix2d.Physics.pause(self)
    end
end

-- Resume the physics and publish the `resume` event
function Physics:resume()
    if physics:isPaused() then
        pix2d.Physics.resume(self)
    end
end

-- Create the physics instance using the scene `scene`and the box2d world meta data `p`
-- p = {
--    unit = 0.5,
--    position = { 0, 0 },
--    size = { 10, 7 },
--    gravity = { 0, -10 }
-- }
function Physics:create(scene,p)
    -- Populate the physics definition structure
    local def = pix2d.PhysicsDef:new()
    def.scene = scene
    def.unit = p.unit
    def.pos.x = p.position[1]
    def.pos.y = p.position[2]
    def.size.x =  p.size[1]
    def.size.y = p.size[2]
    def.gravity.x = p.gravity[1]
    def.gravity.y = p.gravity[2]

    -- Update the global variable `physics`
    instance = pix2d.Physics:create(def)
    physics = instance

    -- Extent the physics instance
    local t  = tolua.getpeer(physics) or {}
    setmetatable(t, Physics)
    tolua.setpeer(physics, t)
end

return Physics
-- EOF
