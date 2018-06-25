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
-- local dep = require 'dep'

print 'Loading package Particle...'

local util = require 'util'

-- The package table
local Particle = {}; Particle.__index = Particle

setmetatable(Particle,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
        }, Particle)
    end
})


-- Load a particle system
-- Parameters
-- filename:
-- batch:
-- autoremove
-- position
function Particle:create(p)
    local particle = CCParticleSystemQuad:new_local()
    particle:autorelease()
    local data = require(p.filename)
    -- Total particles
    if not particle:initWithTotalParticles(data.maxParticules) then
        print "WARNING: Can't create particle"
        return nil
    end
    -- Duration
    particle:setDuration(data.duration)
    -- Mode
    particle:setEmitterMode(data.emitterType)
    -- Life
    particle:setLife(data.lifespan)
    particle:setLifeVar(data.lifespanVariance)
    -- Size
    particle:setStartSize(data.startSize)
    particle:setStartSizeVar(data.startSizeVariance)
    particle:setEndSize(data.finishSize)
    particle:setEndSizeVar(data.finishSizeVariance)
    -- angle
    particle:setAngle(data.angle)
    particle:setAngleVar(data.angleVariance)
    -- emitter position
    particle:setPosition(ccp(data.sourcePosition[1],data.sourcePosition[2]))
    particle:setPosVar(ccp(data.sourcePositionVariance[1],data.sourcePositionVariance[2]))
    -- emitter blending mode
    particle:setBlendAdditive(data.blendAdditive)
    if not data.blendAdditive then particle:setBlendFunc(util.blend(data.blendFuncSource,data.blendFuncDestination)) end
    -- emission Rate
    particle:setEmissionRate(data.maxParticules / data.lifespan) -- total particle / life
    -- color of particles
    particle:setStartColor(util.ccc4f(data.startColor))
    particle:setStartColorVar(util.ccc4f(data.startColorVariance))
    particle:setEndColor(util.ccc4f(data.finishColor))
    particle:setEndColorVar(util.ccc4f(data.finishColorVariance))
    -- Gravity Mode
    if data.emitterType == kCCParticleModeGravity then
        -- Gravity
        particle:setGravity(ccp(data.gravity[1],data.gravity[2]))
        -- radial acceleration
        particle:setRadialAccel(data.radialAcceleration)
        particle:setRadialAccelVar(data.radialAccelVariance)
        -- speed of particles
        particle:setSpeed(data.speed)
        particle:setSpeedVar(data.speedVariance)
        -- Tangential acceleration
        particle:setTangentialAccel(data.tangentialAcceleration)
        particle:setTangentialAccelVar(data.tangentialAccelVariance)
        -- particle:setRotationIsDir(data.rotationIsDir) -- Not binded by default
    elseif data.emitterType == kCCParticleModeRadius then
        -- Start Radius
        particle:setStartRadius(data.maxRadius)
        particle:setStartRadiusVar(data.maxRadiusVariance)
        -- Finish Radius
        particle:setEndRadius(data.minRadius)
        particle:setEndRadiusVar(0.0)
        -- Rotate per second
        particle:setRotatePerSecond(data.rotatePerSecond)
        particle:setRotatePerSecondVar(data.rotatePerSecondVariance)
    else
        assert(false,'Invalid emitterType in config file')
    end
    -- emiter texture
    particle:setTexture(p.batch:getTexture())
    particle:setAutoRemoveOnFinish(p.autoremove)
    -- Add to the batch node
    p.batch:addChild(particle)
    if p.position then particle:setPosition(p.position[1],p.position[2]) end
    return particle
end

-- Public package functions
function Particle:init()
    return self
end

-- Return this package
return Particle
-- EOF
