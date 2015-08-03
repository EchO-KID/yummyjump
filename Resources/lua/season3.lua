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
local factory = require 'factory'
local class = require 'class'

print 'Loading package Season3...'

-- The package table
local Season3 = {}; Season3.__index = Season3

setmetatable(Season3,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
        }, Season3)
    end
})

function Season3:createBadBox(p)
    local level = self.level
    p.tag = level.tag.bad
    p.body_type = physics.KinematicBody
    p.category = physics.category.ennemy
    p.mask = physics.category.player -- Only collide with player
    p.sensor = true
    local bad = class.extend {
        instance = factory:box(p),
        onEnter = function(self)
            level.contact:registerCollisionNotificationScriptWithTag(
                function() mediator:publish(mediator.ns.lose) end,
                self,level.tag.player)
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    if p.path then
        level:createPathAction(p.path,bad)
        local actionManager = CCDirector:sharedDirector():getActionManager()
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(bad) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(bad) end)
    end
    physics:addNode(bad,level.zorder.ennemy,level.tag.bad)
    return bad
end

function Season3:createCrabBad(p)
    p.size = {1,0.5}
    local bad = self:createBadBox(p)
    local node = pix2d.CocosBuilderLua:create('data/ccb/animcrab.ccbi',function() end,function() end)
    bad:addChild(node)
end

function Season3:onLoadEntity(p)
    if p.type == 'crab' then
        self:createCrabBad(p)
    end
end

function Season3:onLevelLoaded()
end

-- Public package functions
function Season3:init(level)
    self.level = level
    -- Lose if touch the upper world boundary
    mediator:subscribe(mediator.ns.contactTopBoundary,function()
        mediator:publish(mediator.ns.lose)
    end)
    return self
end

-- Return this package
return Season3
-- EOF
