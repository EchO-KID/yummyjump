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

print 'Loading package Season4...'
local util = require 'util'
local mediator = require 'mediator'
-- The package table
local Season4 = {}; Season4.__index = Season4

setmetatable(Season4,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            -- package variables
            pathEntities = {},
        }, Season4)
    end
})

-- Path finder is not used yet
--[[
function Season4:extendTexture(level,tex,vertices)
    -- Call overided function
    self._extendTexture(level,tex,vertices)
    local width,height = self.graph:getSize()
    local x,y = 0,0
    for j=0,height-1 do
        for i=0,width-1 do
            if pix2d.QueryMap:query(x+0.25,y+0.25,0.02,0.02,self.level.tag.ground) then  -- Query for ground tag only
                self.graph:update(i,j,pix2d.Graph.solidGround)
            end
            x = x + 0.5
        end
        x = 0
        y = y + 0.5
    end
    local x,y = pix2d.Physics:pixelToUnit(self.level.player:getPosition())
    x = x * 2
    y = y * 2
    for _,e in ipairs(self.pathEntities) do
        self:solvePath(x,y,e)
    end
    self.graph:dump()
end

function Season4:solvePath(x,y,target)
    local path = vector_b2Vec2_:new_local()
    local px,py = pix2d.Physics:pixelToUnit(target:getPosition())
    px = px * 2
    py = py * 2
    print('target position',px,py)
    local points = { px, py } -- Start from the current target position
    if self.graph:solve(b2Vec2(px,py),b2Vec2(x,y),path) == pix2d.Graph.solved then
        for i=0,path:size() do
            table.insert(points,path[i].x)
            table.insert(points,path[i].y)
            print(path[i].x,path[i].y)
        end
        self.level:createPathAction({
            points = points,
            action = 'moveTo',
            loop = false,
            speed = 0.3,
        },target)
    else
        -- target:removeFromParentAndCleanup(true)
    end
end
--]]

function Season4:createSeaLion(p)
    p.radius = 0.5
    p.frame = 'sea_lion.png'
    local bad = self.level:createBad(p)
    bad:getSprite():runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCRotateTo:create(1,-8),CCRotateTo:create(1,8))))
end

function Season4:createBadFollow(p)
    local bad = self.level:createBad(p)
    mediator:subscribe(mediator.ns.gameplayStarted, function()
        self.level:schedule(function()
            local bx,by = pix2d.Physics:pixelToUnit(bad:getPosition())
            local px,py = pix2d.Physics:pixelToUnit(self.level.player:getPosition())
            bad:stopAllActions()
            self.level:createPathAction({
                action = 'moveTo',
                speed = p.speed,
                loop = false,
                points = { bx,by,px,py }
            },bad)
        end,0.5)
    end)
end

function Season4:onLoadEntity(p)
    -- print('season4','parse entity',p.type)
    -- if p.type == 'badPathFinder' then
    --    table.insert(self.pathEntities,self.level:createBad(p))
    -- elseif p.type == 'badFollow' then
    if p.type == 'badFollow' then
        self:createBadFollow(p)
    elseif p.type == 'seaLion' then
        self:createSeaLion(p)
    end
end

function Season4:onLevelLoaded()
end

-- Public package functions
function Season4:init(level)
    self.level = level
    local worldSizeUnit = physics:sizeUnits()
    -- Path finder works but is not used yet
    --[[
    -- Create the path finder graph with world size * 2 so we have a precision of half a map unit
    self.graph = pix2d.Graph(worldSizeUnit.x * 2, worldSizeUnit.y * 2)
    self.graph:dump()
    self._extendTexture = level.extendTexture
    level.extendTexture = function(...)
        self:extendTexture(...)
    end
    --]]
    return self
end

-- Return this package
return Season4
-- EOF
