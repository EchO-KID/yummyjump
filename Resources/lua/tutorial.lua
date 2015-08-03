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

print 'Loading package Tutorial...'
local util = require 'util'
local anim = require 'anim'
local mediator = require 'mediator'
local factory = require 'factory'
local settings = require 'settings'()

local scheduler = CCDirector:sharedDirector():getScheduler()
local audio = SimpleAudioEngine:sharedEngine()

-- The package table
local Tutorial = {}; Tutorial.__index = Tutorial

setmetatable(Tutorial,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            -- package variables
            debug = false,
            layer = nil,
            physicsTouchEnabled = false,
            resetLevelButtonFlag = true, -- Mutex for the reset button
        }, Tutorial)
    end
})

function Tutorial:onLoadEntity(p)
    -- Not implemented
end

function Tutorial:onLevelLoaded()
    -- Not implemented
end

-- Create a new tutorial layer with touch holes and a callback function
-- Touches ouside the holes are ignored. If `callback` returns true then touches are
-- swallowed. On the contrary touches are passed to sub layers if returns false.
-- If `swallowAllTouches` is defined to true then all touches are swallowed
-- and callback is no more called.
function Tutorial:newLayer(holes,callback)
    -- Start with a fresh layer
    self:removeLayer()
    self.layer = CCLayer:create()
    physics:getScene():addChild(self.layer,self.level.zorder.layer.tutorial)
    for _,r in ipairs(holes) do
        -- From map unit to pixel
        r.origin = pix2d.Physics:unitToPixel(r.origin.x,r.origin.y)
        local size = pix2d.Physics:unitToPixel(r.size.width,r.size.height)
        r.size = CCSizeMake(size.x,size.y)
        -- Draw the holes if debug is enabled
        if self.debug then
            local v = vector_CCPoint_:new_local()
            v:push_back(ccp(r.origin.x, r.origin.y))
            v:push_back(ccp(r.origin.x + r.size.width, r.origin.y))
            v:push_back(ccp(r.origin.x + r.size.width, r.origin.y + r.size.height))
            v:push_back(ccp(r.origin.x, r.origin.y + r.size.height))
            self.level.draw:drawPolygon(v,ccc4f(1,0,0,1),1,ccc4f(0,0,0,0))
        end
    end
    self.layer:registerScriptTouchHandler(function(e,x,y)
        -- Must check that the layer still exists and has not be removed meanwhile
        if self.layer == nil then return end
        if self.layer.swallowAllTouches then return true end
        if e == 'began' then
            for i,r in ipairs(holes) do
                if r:containsPoint(ccp(x,y)) then
                    self.layer:setTouchEnabled(false)
                    local r,t = pix2d.Physics:pixelToUnit(x,y)
                    local cx = math.floor(r)
                    local cy = math.floor(t)
                    return callback(i,cx,cy,r,t,x,y) -- Callback can swallow (returns false) or not the touches (returns true)
                end
            end
            return true -- Swallow touches
        end
    end,
    false, -- no multi-touch
    kCCMenuHandlerPriority - 1, -- touch priority higher than CCMenu
    true) -- Swallows touches
    self.layer:setTouchEnabled(true)
end

function Tutorial:removeLayer()
    if self.layer then
        if self.debug then self.level.draw:clear() end
        self.layer:removeFromParentAndCleanup(true)
        self.layer = nil
    end
end

local function scheduleOnce(callback,delay)
    local id = nil
    id = scheduler:scheduleScriptFunc(function()
        local rc, msg = pcall(callback)
        if not rc then CCMessageBox(msg,'ERROR') end
        scheduler:unscheduleScriptEntry(id)
    end,delay,false)
end

-- Schedule a new tutorial step with a callback function,delay and holes
-- `holes` is a list of CCRect in pixel unit.
-- Only touches within the holes are not swallowed and passed by to the gameplay.
-- When the player tap whithin a hole then callback is called and the hole number
-- (index) and the touch coords are passed.
-- The gameplay is paused when the step begin and is resumed once its done (user taped
-- inside one of the holes).
function Tutorial:newStep(id)
    local step = assert(self.steps[id])
    -- Create a dummy layer with no holes to disable touches until next step
    self:newLayer({},nil)
    -- Add holes for the pause and reset buttons
    if step._updated == nil then
        table.insert(step.holes,CCRectMake(0,5.8,1,1))
        table.insert(step.holes,CCRectMake(9,5.8,1,1))
        step._updated = true
    end
    local runStep = function()
        -- Pause the gameplay
        self.paused = true
        mediator:publish(mediator.ns.pauseGameplay)
        --  Create the new layer
        self:newLayer(step.holes,function(id,...)
            -- Do nothing if level is completed
            if self.win then return end
            -- Tap the pause button?
            if id == #step.holes -1 then
                    audio:playEffect(settings.audio.click)
                    mediator:publish(mediator.ns.pauseScene)
            -- Tap the reset button?
            elseif id == #step.holes then
                if resetLevelButtonFlag then
                    resetLevelButtonFlag = false;
                    audio:playEffect(settings.audio.click)
                    mediator:publish(mediator.ns.resetLevelScene)
                end
            else
                self.physicsTouchEnabled = false
                -- we resumed the gameplay before calling callback
                self.paused = false
                mediator:publish(mediator.ns.resumeGameplay)
                -- Call the touch callback with this hole id and all the other parameters
                return step.callback(id,...)
            end
        end)
        -- Initialize the layer
        if step.init then step.init(self.layer) end
    end
    -- Schedule the step or run it now
    if step.delay > 0 then
        -- Implement using CCDelayTime instead of CCScheduler
        self.actionNode:stopAllActions()
        self.actionNode:runAction(CCSequence:createWithTwoActions(
            CCDelayTime:create(step.delay),CCCallFunc:create(function()
                runStep()
            end)))
        -- scheduleOnce(runStep,step.delay)
    else
        runStep()
    end
end

local function floatingAction(target)
    target:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        -- CCMoveBy:create(2,ccp(-5,5)),CCMoveBy:create(2,ccp(5,-5)))))
        -- CCScaleTo:create(2,1.3),CCScaleTo:create(2,1))))
        CCRotateBy:create(1,-15),CCRotateBy:create(1,15))))
end

local function arrow(frame,x,y,angle,flipX,flipY,animated)
    local pb = CCProgressTimer:create(CCSprite:createWithSpriteFrameName(frame))
    pb:setType(kCCProgressTimerTypeBar)
    pb:setMidpoint(ccp(0,1))
    pb:setBarChangeRate(ccp(1,0))
    pb:setPosition(x,y)
    if flipX then pb:setFlipX(true) end
    if flipY then pb:setFlipY(true) end
    if angle then pb:setRotation(angle) end
    floatingAction(pb)
    if animated then
        pb:runAction(CCProgressTo:create(1,100))
    else
        pb:setPercentage(100)
    end
    return pb
end

local function arrow1(...)
    return arrow('tutorial_arrow1.png',...)
end

local function arrow2(...)
    return arrow('tutorial_arrow2.png',...)
end

--[[
local function circle(x,y)
    local sprite = CCSprite:createWithSpriteFrameName('circle_anim1.png')
    sprite:runAction(CCRepeatForever:create(CCRotateBy:create(4,360)))
    sprite:setBlendFunc(util.additiveBlend())
    sprite:setScale(2)
    sprite:setOpacity(128)
    sprite:setPosition(x,y)
    return sprite
end
--]]

local function rectAnim(x,y)
    local pos = pix2d.Physics:unitToPixelCenter(x,y)
    local sprite = anim:runAnimation {
        repeatForever = true,
        frames = {'rect_anim1.png','rect_anim2.png','rect_anim3.png','rect_anim4.png','rect_anim5.png',},
        delay = 0.05,
    }
    sprite:setScale(0.5)
    sprite:setPosition(pos.x,pos.y)
    return sprite
end

local function handAnim(x,y,angle,animated,delay)
    local sprite = anim:runAnimation {
        repeatForever = true,
        frames = { 'hand1.png', 'hand2.png' },
        delay = delay or 0.5,
    }
    sprite:setPosition(x,y)
    if angle then sprite:setRotation(angle) end
    -- sprite:runAction(CCBlink:create(1.5,6))
    if animated then floatingAction(sprite) end
    -- sprite:runAction(CCBlink:create(1,5))
    return sprite
end

local function setHandVisible(hand,tag)
    hand:getChildByTag(1):setVisible(tag == 1)
    hand:getChildByTag(2):setVisible(tag == 2)
end

local function handNode(x,y,angle)
    local hand = CCNodeRGBA()
    hand:setCascadeOpacityEnabled(true)
    hand:addChild(CCSprite:createWithSpriteFrameName('hand1.png'),0,1)
    hand:addChild(CCSprite:createWithSpriteFrameName('hand2.png'),0,2)
    hand:setPosition(ccp(x,y))
    hand:setRotation(angle)
    setHandVisible(hand,1)
    return hand
end

local function createSensor(x,y,radius)
    local c = factory:circle {
        position = {x,y},
        sensor = true,
        category = physics.category.sensor,
        mask = physics.category.player,
        radius = radius,
    }
    physics:addNode(c)
    return c
end

-- Public package functions
function Tutorial:init(level)
    self.level = level
    -- Figure out the current tutorial id (e.g. S01E03 for the season 1 - episode 3)
    local levelid,seasonid = self.level.manager:getCurrentLevelId()
    self.tutorialId = ('S%02dE%02d'):format(seasonid,levelid)
    -- Create the action node
    self.actionNode = CCNode:create()
    physics:layer():addChild(self.actionNode)
    -- Disable/enable touch on the turorial layer when the gameplay is paused/resumed
    -- so the user is still able to tap on the pause layer
    self.paused = false
    mediator:subscribe(mediator.ns.gameplayPaused,function()
        if self.layer then
            self.layer:setVisible(false)
            self.layer:setTouchEnabled(false)
            self.actionNode:getActionManager():pauseTarget(self.actionNode)
            pix2d.NodeUtil:pauseSchedulerAndActions(self.layer)
        end
    end)
    mediator:subscribe(mediator.ns.gameplayResumed,function()
        if self.layer then
            self.layer:setVisible(true)
            self.layer:setTouchEnabled(true)
            self.actionNode:getActionManager():resumeTarget(self.actionNode)
            pix2d.NodeUtil:resumeSchedulerAndActions(self.layer)
        end
        if self.paused then
            mediator:publish(mediator.ns.pauseGameplay)
        end
        if self.physicsTouchEnabled then
            physics:layer():setTouchEnabled(true)
        end
    end)
    -- When the level is completed we MUST disable pause/reset buttons. See newStep function.
    self.win = false
    mediator:subscribe(mediator.ns.win,function()
        self.win = true
    end)
    -- Tutorial step example
    --[[
    self.example =
    {
    -- The init function is called once the step layer is created. The layer is passed to the function
    init = function(layer)
    end,
    -- The callback function is called when the user touch one of the layer's holes. The holes id and
    -- the touch coords are passed. Useful if a tool has to be created.
    callback = function(id,cx,cy,r,t,x,y)
    end,
    -- The "touche holes" for this step. Only touch inside the holes are notified.
    -- x,y coord and size are in map unit
    holes = { CCRectMake(x,y,width,height), CCRectMake(x,y,width,height) },
    -- Delay to wait before running this step.
    delay = 1,
    }
    --]]
    ------------------- Tutorial S01E01 -------------------
    self.S01E01 = {
        -- 1. Tap on the player to start gameplay
        {
            init = function(layer)
                layer:addChild(arrow1(370,120,15,false,false,true))
                local hand = handAnim(48,190,-30,true)
                hand:setVisible(false)
                hand:runAction(anim:createSequence {
                    CCDelayTime:create(1),
                    CCBlink:create(1,4),
                    CCCallFunc:create(function() hand:setVisible(true) end)
                })
                layer:addChild(hand)
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial')
                self:newStep(2);
                return true
            end,
            holes = {
                CCRectMake(0,4,1,1), -- the player
            },
            delay = 0,
        }, {
            -- 2. Tap on the block item
            init = function(layer)
                layer:addChild(handAnim(260,270,30,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.activateToolItem,'block')
                self:newStep(3);
                return true
            end,
            holes = {
                CCRectMake(5,5.7,1,1), -- the block item
            },
            delay = 1
        }, {
            -- 3. Tap on the map
            init = function(layer)
                layer:addChild(rectAnim(6,0))
                layer:addChild(handAnim(270,50,140,true))
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                mediator:publish(mediator.ns.tool_focus_ended,'block',cx,cy,r,t,x,y)
                return true
            end,
            holes = {
                CCRectMake(6,0,1,1) -- Where to put the block
            },
            delay = 1
        }
    }
    ------------------- Tutorial S01E05 -------------------
    self.S01E05 = {
        {
            -- 1. Select the rope tool
            init = function(layer)
                layer:addChild(handAnim(220,260,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                mediator:publish(mediator.ns.activateToolItem,'rope')
                self:newStep(2)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(4,5.7,1,1)
            },
            delay = 0
        }, {
            -- 2. Insert the rope
            init = function(layer)
                layer:addChild(rectAnim(5,2))
                layer:addChild(handAnim(224,150,140,true))
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                self.layer.swallowAllTouches = true
                -- self.layer:setTouchEnabled(false)
                -- Request a new rope
                mediator:publish(mediator.ns.tool_focus_ended,'rope',cx,cy,r,t,x,y)
                -- Wait for the player to collide with the rope
                mediator:subscribe(mediator.ns.tool_contact,function()
                    self:newStep(3)
                end)
                return true
            end,
            holes = {
                CCRectMake(5,2,1,1) -- Where to put the block
            },
            delay = 1.5
        }, {
            -- 3. Drag the player
            init = function(layer)
                local hand = handNode(224,130,120)
                layer:addChild(hand)
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCMoveTo:create(1,ccp(170,160)),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255);  hand:setPosition(ccp(224,130))
                    end),
                },true))
                -- Touch on physics layer is desabled when gameplay is paused
                -- but here we want the player to be able to grab the rope even if
                -- the gameplay is paused
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
                -- Check that the user has touch and release the tool
                local released = false
                mediator:subscribe(mediator.ns.tool_touched,function(_,e)
                    if e == 'begin' then released = false
                    elseif e == 'ended' then released = true end
                end)
                -- Create a sensor to know when the user must release the rope
                local c = createSensor(6,3,0.1)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    if released then
                        self:newStep(4)
                        release = false -- in case the player collide with the sensor again
                    end
                end,c,self.level.tag.player)
            end,
            callback = function(id)
                return false
            end,
            holes = {
                -- CCRectMake(4.25,2.25,2.5,2.5),
                CCRectMake(4.25,2.25,2.5,0.8),
                CCRectMake(4.25,3.9,2.5,0.8),
                CCRectMake(4.25,3.05,0.8,1.65),
                CCRectMake(5.95,3.05,0.8,1.65),
            },
            delay = 0.5
        }, {
            -- 4. Release the player from the rope
            init = function(layer)
                layer:addChild(handAnim(284,195,-120,true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
            end,
            callback = function(id) return false end,
            holes = {
                CCRectMake(5.25,3.25,0.5,0.5),
            },
            delay = 0
        }
    }
    ------------------- Tutorial S01E05 -------------------
    self.S01E10 = {
        {
            -- Start the gameplay
            init = function(layer)
                layer:addChild(handAnim(48,190,-30,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial')
                self:newStep(2);
                return true
            end,
            holes = {
                CCRectMake(0,4,1,1), -- the player
            },
            delay = 0,
        }, {
            -- 2. Focus on the slider
            init = function(layer)
                local hand = handNode(224,140,0)
                layer:addChild(hand)
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCMoveTo:create(1,ccp(150,140)),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(ccp(224,140))
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
            end,
            callback = function(id) self:removeLayer(); return false end,
            holes = { CCRectMake(4,3,2,1) },
            delay = 0.3,
        }
    }
    ------------------- Tutorial S02E01 -------------------
    self.S02E01 = {
        {
            -- 1. Select the balloon tool
            init = function(layer)
                layer:addChild(handAnim(280,260,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                mediator:publish(mediator.ns.activateToolItem,'balloon')
                self:newStep(2)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(5,5.7,1,1)
            },
            delay = 0
        }, {
            -- 2. Insert the balloon
            init = function(layer)
                layer:addChild(rectAnim(4,1))
                layer:addChild(handAnim(254,70,-50,true))
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                self.layer.swallowAllTouches = true
                mediator:publish(mediator.ns.tool_focus_ended,'balloon',cx,cy,r,t,x,y)
                local sensor = createSensor(4,4,0.25)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    self:newStep(3)
                end,sensor,self.level.tag.balloon)
                return true
            end,
            holes = {
                CCRectMake(4,1,1,1) -- Where to put the block
            },
            delay = 1
        }, {
            -- 3. Insert the rope
            init = function(layer)
                layer:addChild(handAnim(254,200,-50,true))
            end,
            callback = function()
                -- Simulate a "teleportation" so the balloon releases the player
                local pos = self.level.player:getBodyCenter() -- Must provide the position in meter and pixel
                mediator:publish(mediator.ns.teleported,pos,pix2d.Physics:meterToPixel(pos))
                self:removeLayer() -- Stop the tutorial
                return true
            end,
            holes = {
                CCRectMake(4,3.5,1,1) -- Where to put the block
            },
            delay = 0
        }
    }
    ------------------- Tutorial S02E03 -------------------
    local sensor = nil
    self.S02E08 = {
        {
            -- 1. Select the fan tool
            init = function(layer)
                sensor = createSensor(2,1,0.25)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    physics:createRevoluteJoint(self.level.player,sensor)
                end,sensor,self.level.tag.player)
                layer:addChild(handAnim(320,260,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                mediator:publish(mediator.ns.activateToolItem,'fan')
                self:newStep(2)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(6,5.7,1,1)
            },
            delay = 0
        }, {
            -- 2. Insert the fan
            init = function(layer)
                layer:addChild(rectAnim(6,4))
                layer:addChild(handAnim(340,210,-50,true))
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                self.layer.swallowAllTouches = true
                mediator:publish(mediator.ns.tool_focus_ended,'fan',cx,cy,r,t,x,y)
                self:newStep(3)
                return true
            end,
            holes = {
                CCRectMake(6,4,1,1) -- Where to put the block
            },
            delay = 0.5
        }, {
            -- 2. Rotate the fan
            init = function(layer)
                local startPos = ccp(350,180)
                local endPos = ccp(290,180)
                local hand = handNode(startPos.x,startPos.y,0)
                layer:addChild(hand)
                local bc = ccBezierConfig()
                bc.controlPoint_1 = ccp(startPos.x,140)
                bc.controlPoint_2 = ccp(endPos.x,140)
                bc.endPosition = endPos
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCBezierTo:create(1,bc),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(startPos)
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
                mediator:subscribe(mediator.ns.tool_touched,function(_,e,target)
                    if e == 'ended' then
                        local angle = math.deg(util.normalizeAngle(target:getAngle()))
                        if 170 < angle and angle < 190 then
                            if sensor then
                                sensor:removeFromParentAndCleanup(true)
                                sensor = nil
                                self.level.player:applyLinearImpulse(self.level.player:getMass() * 0.6,0)
                                --[[
                                self.physicsTouchEnabled = true
                                physics:layer():setTouchEnabled(false)
                                self.layer.swallowAllTouches = true
                                self.layer:setVisible(false)
                                --]]
                                self:removeLayer()
                            end
                        end
                    end
                end)
            end,
            callback = function(id) return false end,
            holes = { CCRectMake(5.5,3.5,2,2) },
            delay = 0.5,
        }
    }
    --[[----------------- Tutorial S02E05 -------------------
    self.S02E05 = {
        {
            -- 1. Select the rope tool
            init = function(layer)
                layer:addChild(handAnim(100,90,-90,true))
                sensor = createSensor(2,1,0.25)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    sensor:removeFromParentAndCleanup(true)
                    local pos = pix2d.Physics:meterToUnit(self.level.player:getBodyCenter())
                    sensor = createSensor(pos.x-0.5,pos.y-0.5,0.25)
                    self.level.player:setAngularVelocity(0)
                    physics:createRevoluteJoint(self.level.player,sensor)
                    self:newStep(2)
                end,sensor,self.level.tag.player)
            end,
            callback = function(id)
                self.layer:setVisible(false)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(1,1,1,1)
            },
            delay = 0.5
        }, {
            -- 2. Enable fan
            init = function(layer)
                layer:addChild(handAnim(360,80,0,true))
                physics:layer():setTouchEnabled(true)
                local subscriber = nil
                subscriber = mediator:subscribe(mediator.ns.tool_touched,function(_,e,target)
                    if sensor and e == 'ended' and not target.sensor.enabled then
                        mediator:removeSubscriber(subscriber)
                        physics:contactListener():cancelCollisionNotification(sensor)
                        self.level.player:applyLinearImpulse(self.level.player:getMass() * 0.6,0)
                        sensor:removeFromParentAndCleanup(true)
                        sensor = nil
                        self:newStep(3)
                    end
                end)
            end,
            callback = function(id)
                return false
            end,
            holes = {
                CCRectMake(7,2,1,1)
            },
            delay = 0.5
        }, {
            -- 3. Select the balloon tool
            init = function(layer)
                layer:addChild(handAnim(280,260,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.activateToolItem,'balloon')
                self:newStep(4)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(5,5.7,1,1)
            },
            delay = 0.5
        }, {
            -- 4. Insert the balloon
            init = function(layer)
                layer:addChild(rectAnim(5,1))
                layer:addChild(handAnim(294,70,-50,true))
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                self.layer.swallowAllTouches = true
                mediator:publish(mediator.ns.tool_focus_ended,'balloon',cx,cy,r,t,x,y)
                sensor = createSensor(5,3,0.25)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    sensor:removeFromParentAndCleanup(true)
                    sensor = nil
                    local pos = pix2d.Physics:meterToUnit(self.level.player:getBodyCenter())
                    sensor = createSensor(pos.x-0.5,pos.y-0.5,0.25)
                    physics:createRevoluteJoint(self.level.player,sensor)
                    self:newStep(5)
                end,sensor,self.level.tag.player)
                return true
            end,
            holes = {
                CCRectMake(5,1,1,1) -- Where to put the block
            },
            delay = 1
        }, {
            -- 5. Enable fan
            init = function(layer)
                layer:addChild(handAnim(180,240,0,true))
                physics:layer():setTouchEnabled(true)
                mediator:subscribe(mediator.ns.tool_touched,function(_,e,target)
                    if sensor and e == 'ended' and target.sensor.enabled then
                        physics:contactListener():cancelCollisionNotification(sensor)
                        sensor:removeFromParentAndCleanup(true)
                        sensor = nil
                        self:removeLayer()
                    end
                end)
            end,
            callback = function(id)
                return false
            end,
            holes = {
                CCRectMake(3,5,1,1)
            },
            delay = 0.5
        }
    }
    --]]
    ------------------- Tutorial S02E17 -------------------
    self.S02E17 = {
        {
            -- 1. Select the balloon tool
            init = function(layer)
                --layer:addChild(handAnim(280,260,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                physics:layer():addChild(handAnim(280,70,-50,true),self.level.zorder.frontSprites)
                self:removeLayer() -- Stop the tutorial
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(9,4,1,1)
            },
            delay = 0
        }
    }
    ------------------- Tutorial S03E01 -------------------
    self.S03E01 = {
        {
            -- 1. Start the gameplay
            init = function(layer)
                layer:addChild(handAnim(260,90,0,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                self:newStep(2)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(4.5,2,1,1)
            },
            delay = 0
        }, {
            -- 2. Focus on the slider
            init = function(layer)
                local hand = handNode(254,60,0)
                layer:addChild(hand)
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCMoveTo:create(1,ccp(254,20)),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(ccp(254,60))
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
            end,
            callback = function(id) self:removeLayer(); return false end,
            holes = { CCRectMake(4.5,0.8,1,1) },
            delay = 1.5,
        }
    }
    ------------------- Tutorial S03E07 -------------------
    self.S03E07 = {
        -- 1. Tap on the player to start gameplay
        {
            init = function(layer)
                layer:addChild(arrow2(130,215,0,false,false,true))
                local arrow2 = arrow2(350,215,0,false,false,false)
                arrow2:setPercentage(0)
                arrow2:runAction(CCSequence:createWithTwoActions(
                CCDelayTime:create(1.2),CCProgressTo:create(1,100)))
                layer:addChild(arrow2)
                local hand = handAnim(48,190,-30,true)
                layer:addChild(hand)
                hand:setOpacity(0)
                layer.swallowAllTouches = true
                hand:runAction(CCSequence:createWithTwoActions(
                    CCDelayTime:create(2.5),CCCallFunc:create(function()
                        layer.swallowAllTouches = false
                        hand:runAction(CCFadeIn:create(0.5))
                    end)))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                self:newStep(2);
                return true
            end,
            holes = {
                CCRectMake(0,4,1,1), -- the player
            },
            delay = 1.8,
        }, {
            -- 2. Select the teleport tool
            init = function(layer)
                layer:addChild(handAnim(360,260,-30,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.activateToolItem,'teleport')
                self:newStep(3)
                return true -- Swallows touch
            end,
            holes = {
                CCRectMake(6.5,5.7,1,1)
            },
            delay = 3.5
        }, {
            -- 3. Insert the fan
            init = function(layer)
                layer:addChild(rectAnim(3,1))
                layer:addChild(handAnim(190,70,-50,true))
                sensor = createSensor(8,4,0.25)
                physics:contactListener():registerCollisionNotificationScriptWithTag(function()
                    sensor:removeFromParentAndCleanup(true)
                    local pos = pix2d.Physics:meterToUnit(self.level.player:getBodyCenter())
                    sensor = createSensor(pos.x-0.5,pos.y-0.5,0.25)
                    physics:createRevoluteJoint(self.level.player,sensor)
                    self.level.player:setAngularVelocity(0)
                    self:newStep(4)
                end,sensor,self.level.tag.player)
            end,
            callback = function(id,cx,cy,r,t,x,y)
                self.layer:setVisible(false)
                self.layer.swallowAllTouches = true
                mediator:publish(mediator.ns.tool_focus_ended,'teleport',cx,cy,r,t,x,y)
                return true
            end,
            holes = {
                CCRectMake(3,1,1,1) -- Where to put the block
            },
            delay = 0.5
        }, {
            -- 4. Rotate the teleport
            init = function(layer)
                local startPos = ccp(140,50)
                local endPos = ccp(170,20)
                local hand = handNode(startPos.x,startPos.y,0)
                layer:addChild(hand)
                local bc = ccBezierConfig()
                bc.controlPoint_1 = ccp(120,40)
                bc.controlPoint_2 = ccp(160,0)
                bc.endPosition = endPos
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCBezierTo:create(1,bc),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(startPos)
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
                mediator:subscribe(mediator.ns.tool_touched,function(_,e,target)
                    if e == 'ended' then
                        local angle = math.deg(util.normalizeAngle(target:getAngle()))
                        if 80 < angle and angle < 100 then
                            if sensor then
                                sensor:removeFromParentAndCleanup(true)
                                sensor = nil
                                self.level.player:applyLinearImpulse(self.level.player:getMass() * 0.6,0)
                                self.physicsTouchEnabled = true
                                physics:layer():setTouchEnabled(false)
                                self.layer.swallowAllTouches = true
                                self.layer:setVisible(false)
                            end
                        end
                    end
                end)
            end,
            callback = function(id) return false end,
            holes = { CCRectMake(2.5,0.5,2,2) },
            delay = 0.5,
        }
    }
    ------------------- Tutorial S03E18 -------------------
    self.S03E17 = {
        -- 1. Tap on the player to start gameplay
        {
            init = function(layer)
                layer:addChild(handAnim(48,90,-30,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                self:newStep(2);
                return true
            end,
            holes = {
                CCRectMake(0,2,1,1), -- the player
            },
            delay = 1.5,
        }, {
            -- 2. Rotate the trampoline
            init = function(layer)
                local startPos = ccp(240,120)
                local endPos = ccp(235,110)
                local hand = handNode(startPos.x,startPos.y,0)
                layer:addChild(hand)
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCMoveTo:create(1,endPos),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(startPos)
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
                mediator:subscribe(mediator.ns.tool_touched,function(_,e,target)
                    if e == 'ended' then
                        self:removeLayer()
                        -- Check for the right angle. Removed because too strict.
                        --[[
                        local angle = math.deg(util.normalizeAngle(target:getAngle()))
                        if 305 < angle and angle < 325 then
                            self:removeLayer()
                        end
                        --]]
                    end
                end)
            end,
            callback = function(id) return false end,
            holes = { CCRectMake(3.5,2,2,2) },
            delay = 0.5,
        }
    }
    ------------------- Tutorial S04E06 -------------------
    self.S04E06 = {
        -- 1. Tap on the player to start gameplay
        {
            init = function(layer)
                layer:addChild(handAnim(100,140,-30,true))
            end,
            callback = function(id)
                mediator:publish(mediator.ns.gameplayStarted,'tutorial') -- Start the gameplay through the tutorial
                self:newStep(2);
                return true
            end,
            holes = {
                CCRectMake(1,3,1,1), -- the player
            },
            delay = 0,
        }, {
            -- 2. Rotate the trampoline
            init = function(layer)
                local startPos = ccp(80,90)
                local endPos = ccp(50,70)
                local hand = handNode(startPos.x,startPos.y,0)
                layer:addChild(hand)
                hand:runAction(anim:createSequence({
                    CCDelayTime:create(0.7),
                    CCCallFunc:create(function() setHandVisible(hand,2) end),
                    CCDelayTime:create(0.3),
                    CCMoveTo:create(1,endPos),
                    CCDelayTime:create(0.3),
                    CCCallFunc:create(function() setHandVisible(hand,1) end),
                    CCDelayTime:create(0.5),
                    CCFadeOut:create(0.8),
                    CCCallFunc:create(function()
                        hand:setOpacity(255); hand:setPosition(startPos)
                    end),
                },true))
                self.physicsTouchEnabled = true
                physics:layer():setTouchEnabled(true)
            end,
            callback = function(id) self:removeLayer(); return false end,
            holes = { CCRectMake(1,2,1,1) },
            delay = 1.5,
        }
    }
    ---------------------------------------------------------
    -- Load the steps for the current season/level
    self.steps = assert(self[self.tutorialId])
    -- Starts with the very first steps of the tutorial
    self:newStep(1)
    return self
end

-- Return this package
return Tutorial
-- EOF
