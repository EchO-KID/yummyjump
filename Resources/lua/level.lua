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
local anim = require 'anim'
local util = require 'util'
local json = require 'json'
local class = require 'class'
local factory = require 'factory'
local mediator = require 'mediator'
local settings = require 'settings'()
local particle = require 'particle'()
local ScrollSprite = require 'scrollsprite'
local Bezier = require 'bezier'
-- local tween = require 'lib/tween/tween'

--[[ MobDebug configuration
local mobdebug = require('MobDebug/mobdebug')
mobdebug.start("192.168.1.10",8172)
mobdebug.off() -- turns debugging off
--]]

-- Note: We must use size in point when multi-resolution
-- support is enabled (and not getWinSizeInPixels)
local director = CCDirector:sharedDirector()
local winSize = director:getWinSize()
local scheduler = director:getScheduler()
-- local fileUtils = CCFileUtils:sharedFileUtils()
local visiblerect = pix2d.VisibleRect
local actionManager = director:getActionManager()
local audio = SimpleAudioEngine:sharedEngine()
local adClock = nil -- advertising timer

-- The package table
local Level = {}; Level.__index = Level

setmetatable(Level,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            gameHasStarted = false,
            param = { -- The level parameters
                blink = false,
            },
            defaultTouchForce = 200.0,
            defaultTouchFrequency = 5.0,
            backgroundLayer = nil,
            data = nil, -- The level's data
            -- Physics Node tags. Beware that values will be increased by maxTag (C++)
            tag = {
                player = 1,
                target = 2,
                rope = 3,
                ground = 4,
                bad = 6,
                coin = 8,
                edge = 9,
                hud = 10,
                grid = 11,
                spear = 12,
                balloon = 13,
                fan = 14,
            },
            tagLayer = { background = 1, physics = 2 },
            zorder = {
                backgroundTexture = -99,
                backSprites2 = -11,
                backSprites = -10, -- back decoration sprites
                ground = -1,
                grass = 1,
                drawNode = 2,
                iceGround = 3,
                chain = 4, -- Chain using frame sprites. For chain using batch node see batch zorder.
                platform = 5, -- slider, floating platform, teleports..
                coin = 6, -- coin and target zorder
                ennemy = 7, -- bad, spear
                batch = 8, -- batch nodes will all have this zorder (can be refactored and zorder included in the json)
                rope = 9,
                fan = 10,
                balloon = 11,
                streak = 97,
                dots = 98, -- trajectory dots sprites
                player = 99, -- The player should always be in foreground except for `frontSprites` zorder
                batchParticle = 101,
                frontSprites = 199,
                -- Background layer zorder
                background = {
                    behindBackgroundImage = -12,
                    backgroundImage = -11,
                    backSprites = -10,
                    frontSprites = 10, -- e.g. dancing sprites
                },
                layer = {
                    background = -100,
                    grid = -1,
                    physics = 0,
                    foreground = 2,
                    hud = 100,
                    tutorial = 101,
                    popup = 102,
                },
                -- player "outfit layers"
                player_idle = 0, -- "normal" sprite
                player_anim = 1, -- animation sprite (win,lose...) between the idle and outfit sprites
                player_outfit = 2, -- foreground sprite (outfit). Beware that there might be no 'outfit' sprite.
            },
            score = 0, -- The current level score
            batch = {}, -- list of CCSpriteBatchNode loaded from the level data
            particleBatch = {}, -- list of CCParticleBatchNode loaded from the level data
            touch = nil, -- Physics touchListener
            contact = nil, -- Physics contactListener
            grid = nil, -- Tools grid instance
            hud = nil, -- HUD instance
            draw = nil, -- Drawnode
            cardboardCount = 0,
            teleports = {}, -- list of teleport tools added in the map
            scheduledScripts = {},
        }, Level)
        end
    })

function Level:getLayerByName(name)
    return self.tagLayer[name] and physics:getScene():getChildByTag(self.tagLayer[name]) or nil
end

-- Schedule a function and remove it automatically on scene exit
function Level:schedule(func,delay)
    local script = director:getScheduler():scheduleScriptFunc(func,delay,false)
    table.insert(self.scheduledScripts,script)
    return script
end

function Level:createContextNode(x,y)
    local node = pix2d.OpacityNode:create()
    node:setPosition(x,y)
    local moveFadeOut = CCSequence:createWithTwoActions(
        CCMoveBy:create(0.5,ccp(0,visiblerect:sizeAt(0,0.05).height)),
        CCFadeOut:create(0.5))
    node:runAction(CCSequence:createWithTwoActions(moveFadeOut,
        CCCallFunc:create(function() node:removeFromParentAndCleanup(true) end)))
    return node
end

function Level:createLabelContext(x,y,str)
    local label = CCLabelBMFont:create(str,'Chewy.fnt')
    local node = self:createContextNode(x,y)
    node:addChild(label)
    return node
end

-- Parameters
-- translation: {1,2}
-- aabb: in map unit
-- texture
-- color
function Level:createScrollingTexture(p)
    local ox, oy = p.translation[1], p.translation[2]
    local x, y = 0, 0
    local tx, ty = 0, 0 -- temp x,y
    local tex = class.extend {
        instance = pix2d.TextureSprite:createWithAABB(p.texture,
                        pix2d.Physics:unitToPixel(p.aabb[1],p.aabb[2]),
                        pix2d.Physics:unitToPixel(p.aabb[3],p.aabb[4])),
        update = function(self)
                self:translateTexCoord(x,y)
                tx = x + ox; ty = y + oy
                x = (tx > 1 or tx < -1) and 0 or tx
                y = (ty > 1 or ty < -1) and 0 or ty
        end
    }
    if p.color then tex:setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    return tex
end

function Level:loadScrollingTexture(p)
    local layer = self:getLayerByName(p.layer) or physics:layer()
    local zorder = p.zorder and self.zorder[p.zorder] or 0
    local tag = p.tag and self.tag[p.tag] or 0
    layer:addChild(self:createScrollingTexture(p),zorder,tag)
end

function Level:loadBackgroundLayer(p)
    pix2d.Physics:setDefaultBackgroundColor(
        p.defaultColor[1]/255,p.defaultColor[2]/255,
        p.defaultColor[3]/255,p.defaultColor[4]/255)
    local sprite = CCSprite:create(p.sprite)
    sprite:setAnchorPoint(ccp(0,0))
    local season,seasonid = self.manager:getCurrentSeason()
    if seasonid == 1 then
        sprite:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCScaleTo:create(1,1,1.04), CCScaleTo:create(1,1,1))))
    end
    if p.spriteColor then sprite:setColor(ccc3(p.spriteColor[1],p.spriteColor[2],p.spriteColor[3])) end
    self.backgroundLayer:addChild(sprite,self.zorder.background.backgroundImage)
end

function Level:createSprite(p)
    assert(p.frame or p.sprite,"Can't create sprite: frame name or sprite filename not defined.")
    local sprite = nil
    if p.frame then
        sprite = pix2d.CustomSprite:createWithSpriteFrameName(p.frame)
        -- sprite = CCSprite:createWithSpriteFrameName(p.frame) else
    else
        sprite = CCSprite:create(p.sprite)
    end
    assert(sprite,"Can't create sprite")
    if p.opacity then sprite:setOpacity(p.opacity) end
    if p.anchor then sprite:setAnchorPoint(ccp(p.anchor[1],p.anchor[2])) end
    if p.position then sprite:setPosition(pix2d.Physics:unitToPixel(p.position[1],p.position[2])) end
    if p.rotation then sprite:setRotation(p.rotation) end
    if p.scale then sprite:setScaleX(p.scale[1]); sprite:setScaleY(p.scale[2]) end
    if p.skew then sprite:setSkewX(p.skew[1]); sprite:setSkewY(p.skew[2]) end
    if p.zorder then sprite:setZOrder(self.zorder[p.zorder] or p.zorder) end
    if p.tag then sprite:setTag(self.tag[p.tag]) end
    if p.color then sprite:setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    if p.flip then sprite:setFlipX(p.flip[1]); sprite:setFlipY(p.flip[2]) end
    return sprite
end

function Level:loadSprite(p)
    local layer = self:getLayerByName(p.layer) or physics:layer()
    local zorder = p.zorder and self.zorder[p.zorder] or 0
    local tag = p.tag and self.tag[p.tag] or 0
    local sprite = self:createSprite(p)
    layer:addChild(sprite,zorder,tag)
    return sprite
end

function Level:loadMoon(p)
    local moon = self:loadSprite(p)
    anim:repeatForever(moon,CCRotateTo:create(2,-15),CCRotateTo:create(2,15))
end

-- Add a touch grabber sprite to the target
-- Parameters: target, frame, callback
function Level:createTouchGrabberSprite(p)
    assert(p.target)
    assert(p.frame)
    local sprite = self:createSprite(p)
    sprite:setVisible(false)
    p.target:addChild(sprite)
    p.target:movable(true)
    local action = nil
    self.touch:registerTouchScriptHandler(function(e,t)
        if p.callback then p.callback(e,t) end
        if e == 'begin' then
            mediator:publish(mediator.ns.tool_touched,e,p.target)
            sprite:setVisible(true)
            if action then sprite:stopAction(action) end
            action = CCFadeIn:create(0.2)
            sprite:runAction(action)
            return true
        elseif e == 'ended' or e == 'canceled' then
            mediator:publish(mediator.ns.tool_touched,e,p.target)
            if action then sprite:stopAction(action) end
            action = CCSequence:createWithTwoActions(
            CCFadeOut:create(0.2),CCCallFunc:create(function()
                sprite:setVisible(false)
            end))
            sprite:runAction(action)
        end
    end,p.target)
    return sprite
end

-- Create a rope element using the following parameters
-- type: Only JSON. Must be "rope"
-- uid: The unique identifier for this physic node
-- startpos: rope start position in map unit
-- endpos: rope end position in map unit
-- anchor: frame name for the rope's anchor sprite
-- hook: frame name for the rope's hook sprite
-- batch: the batch node sprite that will be used for the rope texture (only created once)
-- LUA:
-- p = {
--     uid = 10,
--     startpos = {x,y},
--     endpos = {x,y},
--     anchor = 'cloud.png',
--     hook = 'star.png',
--     batch = 'rainbow.png'
-- }
-- JSON:
-- {
--     "type": "rope",
--     "uid": 10,
--     "startpos": [x,y],
--     "endpos": [x,y],
--     "anchor": "cloud.png",
--     "hook": "star.png",
--     "batch": "rainbow.png"
-- }
function Level:createRope(p)
    p.batch = self.batch[p.batch]
    p.tag = self.tag.rope
    p.hookRadius = 0.25
    p.sensorRadius = 0.5
    p.anchorRadius = 0.4
    p.anchorDensity = p.anchorDensity or 0.01
    p.hookDensity = p.hookDensity or 8.0 -- Should not be too low or the rope might become instable

    -- The player collides with the inner sensor and NOT the hook which is a dynamic body.
    -- Don't know why but the release of the player from the rope was buggy
    -- when the revolute joint was created against the hook.
    -- Note that the hook is required to set some weight to the end of the rope.
    local level = self
    local rope = class.extend {
        instance = factory:rope(p),
        onEnter = function(self)
            local player = nil
            -- Enable touch on the rope' outer sensor
            level:createTouchGrabberSprite { target = self:getSensor(), frame = 'grabber_circle.png' , scale = {2,2}}
            -- Touch on the anchor
            level.touch:registerTouchScriptHandler(function(e,t)
                mediator:publish(mediator.ns.tool_touched,e)
                if e == 'begin' then
                    self:getAnchor():getSprite():runAction(CCEaseElasticOut:create(CCScaleBy:create(0.3,1.1,1.1)))
                    if player then
                        local v = player:getLinearVelocity()
                        if math.abs(v.x) > 2 or math.abs(v.y) > 2 then
                            audio:playEffect(settings.audio.swish1)
                        else
                            audio:playEffect(settings.audio.click)
                        end
                        player = nil; self:detach()
                        self:getHook():setCollisionMask(physics.category.noCollision)
                    end
                    -- we want to intercept ended and canceled event so we return true
                    return true
                elseif e == 'ended' or e == 'canceled' then
                    self:getAnchor():getSprite():runAction(CCEaseElasticOut:create(CCScaleTo:create(0.3,1,1)))
                end
            end,self:getAnchor())
            -- Contact between rope's inner sensor and player
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                if not player then
                    mediator:publish(mediator.ns.tool_contact)
                    -- Figures out contact node is the player
                    player = c.nodeA == self:getInnerSensor() and c.nodeB or c.nodeA
                    -- physics:createRevoluteJoint(player,self:getInnerSensor())
                    self:attach(player)
                    -- self:getSensor():movable(false)
                    self:getInnerSensor():setCollisionMask(physics.category.noCollision)
                    -- hook collide only with ground (if collide with bad then player might not collide with bad character)
                    self:getHook():setCollisionMask(physics.category.ground)
                end
            end,self:getInnerSensor(),level.tag.player)
            -- *End* contact between *OUTER* sensor and player
            level.contact:registerEndCollisionNotificationScriptWithTag(function(c)
                    -- Must check that the end-contact is notified for a not "touching" contact.
                    -- That is the player is actually not overlaping the sensor because an end-contact is
                    -- sent when the revolute joint is created to connect both player and sensor.
                    -- Indeed the revolute joint is created with the "collideConnected" option disabled
                    -- which cease the current contact between the player and the sensor (and send the "end-contact" event).
                    -- http://www.box2d.org/forum/viewtopic.php?f=3&t=9781
                    -- We have to check that the player is actually detached (player is nil). If not
                    -- the revolute joint linking the player and the rope might is forced to strech and
                    -- until the player end contact with the outter sensor and raised this handled.
                    if not player and not c.isTouching then
                        self:getInnerSensor():setCollisionMask(physics.category.player)
                        -- self:getSensor():movable(true)
                    end
                end,
                self:getSensor(),level.tag.player)
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self:getInnerSensor())
            level.contact:cancelEndCollisionNotificationScritpWithTag(self:getSensor(),level.tag.player)
            level.touch:cancelTouchDelegate(self:getSensor())
            level.touch:cancelTouchDelegate(self:getAnchor())
        end
    }
    rope:getHook():setFixedRotation(true)
    -- The sensor collide only with the player but do not collide with other sensor
    rope:getSensor():setCollisionFilter(physics.category.sensor,physics.category.player,physics.group.sensor)
    rope:getInnerSensor():setCollisionFilter(physics.category.sensor,physics.category.player,physics.group.sensor)
    -- No collision for the rope's hook
    rope:getHook():setCollisionFilter(physics.category.hook,physics.category.noCollision,physics.group.hook)
    physics:addNode(rope,self.zorder.rope)
    return rope
end -- End createRope

-- Create a balloon targeted to the player
function Level:createPlayerBalloon(p)
    p.targetTag = self.tag.player
    p.targetMass = self.player:getMass()
    p.targetCategory = physics.category.player
    local balloon = self:createGenericBalloon(p)
    mediator:subscribe(mediator.ns.teleported,function(_)
        if balloon then balloon:releaseTarget() end
    end)
    mediator:subscribe(mediator.ns.removeBalloon,function(_)
        balloon = nil
    end)
    return balloon
end

-- Create a "generic" balloon that can be attached to any PhysicNode.
-- Common parameters
-- p.batch: batch texture name used for the balloon rope
-- p.anchor: frame name used for the balloon
-- startpos: start position of the balloon rope (anchor position) in map unit
-- endpos: end position of the balloon rope (anchor position) in map unit
-- Specific parameters
-- p.targetTag: tag of the target node that can be automatically attached to the balloon. Disabled if nil.
-- p.targetCategory: the physic category used to filter collisions between the balloon and other bodies.
-- p.targetMass:
-- Warning: the balloon is removed from the scene when touching the spear ennemy.
-- Any nodes keeping a references to a balloon must subscribe to the removeBalloon event
-- and clear the reference.
function Level:createGenericBalloon(p)
    p.batch = self.batch[p.batch]
    -- p.tag = self.tag.balloon
    p.hookRadius = 0.25
    p.sensorRadius = 0.5
    p.anchorRadius = 0.25
    p.anchorDensity = 100 -- Balloon should be much heavier than the target to avoid ballancing effect
    p.hookDensity = 0.0
    -- p.anchorLocalAnchor = b2Vec2(0,-0.09)

    local level = self
    local removed = false -- See scheduler script below
    local balloon = class.extend {
        instance = factory:rope(p),
        launch = function(self)
            local anchor = self:getAnchor()
            anchor:setBodyType(physics.DynamicBody)
            -- schedule the continious force upwards to reverse the gravity.
            -- This shoulde be 10 (that is negative gravity which is -10) but
            -- don't know why it's a different value
            anchor:scheduleUpdateWithPriorityLua(function()
                if physics:isPaused() then return end -- We must check that the physics is not paused
                anchor:applyForceToCenter(0,self.totalMass * 28)
            end,1)
        end,
        releaseTarget = function(self)
            if self.target then
                self.totalMass = self.totalMass - self.target:getMass()
                self:detach()
                self.target = nil;
            end
            self:getHook():setCollisionMask(physics.category.noCollision)
            if self.releaseCallback then self.releaseCallback() end
        end,
        onEnter = function(self)
            self:getAnchor():setLinearDamping(2)
            self.scriptId = self:getScheduler():scheduleScriptFunc(function()
                -- BUG FIX: Since it might be called while the balloon has just been
                -- removed (e.g. balloon touch a spear) we have to check that the
                -- balloon still exitst before running the action
                if removed then return end
                self:getAnchor():getSprite():runAction(CCSequence:createWithTwoActions(
                CCScaleTo:create(0.3,1.2,0.9),
                CCEaseElasticOut:create(CCScaleTo:create(1.0,1,1)))) end,4,false)
            level.touch:registerTouchScriptHandler(function(e,t)
                mediator:publish(mediator.ns.tool_touched)
                if e == 'begin' then
                    audio:playEffect(settings.audio.switch2)
                    self:getAnchor():getSprite():runAction(CCEaseElasticOut:create(CCScaleBy:create(0.3,1.1,1.1)))
                    self:releaseTarget()
                    return true
                elseif e == 'ended' or e == 'canceled' then
                    self:getAnchor():getSprite():runAction(CCEaseElasticOut:create(CCScaleTo:create(0.3,1,1)))
                end
            end,self:getAnchor())
            if p.targetTag then
                level.contact:registerCollisionNotificationScriptWithTag(function(c)
                    if not self.target then
                        -- Signal contact with this tool
                        mediator:publish(mediator.ns.tool_contact)
                        -- Figures out which contact node is the target
                        -- TODO Is this really necessary. nodeB should always by the second body (self is bodyA and
                        -- target body is bodyB).
                        self.target = c.nodeA == self:getInnerSensor() and c.nodeB or c.nodeA
                        -- We can't reset the target angular velocity because it
                        -- might avoid player lose it's direction and might go
                        -- in the wrong direction when released from the balloon
                        -- target:setAngularVelocity(0)
                        self:attach(self.target)
                        self:launch()
                    end
                end,self:getInnerSensor(),p.targetTag)
            end
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                self:getAnchor():runAction(CCSequence:createWithTwoActions(
                    CCScaleBy:create(0.2,1.5),CCCallFunc:create(function()
                        mediator:publish(mediator.ns.removeBalloon,self)
                        removed = true
                        self:removeFromParentAndCleanup(true)
                        audio:playEffect(settings.audio.balloonpop)
                    end)))
            end,self:getAnchor(),level.tag.spear)
        end,
        onExit = function(self)
            if p.targetTag then
                level.contact:cancelCollisionNotification(self:getInnerSensor())
            end
            level.touch:cancelTouchDelegate(self:getAnchor())
            self:getScheduler():unscheduleScriptEntry(self.scriptId)
        end
    }
    balloon.totalMass = balloon:getAnchor():getMass() +
                     balloon:getSensor():getMass() +
                     balloon:getInnerSensor():getMass() +
                     balloon:getHook():getMass() +
                     p.targetMass
    -- print('balloon mass:',balloon.totalMass,'target mass',p.targetMass)
    balloon:getAnchor():setTag(self.tag.balloon)
    -- by default rope's anchor does not collide
    -- balloon can collide with sensor (fan) and ennemy (spear)
    balloon:getAnchor():setCollisionFilter(physics.category.misc,bit.bor(physics.category.ennemy,physics.category.sensor),0)
    balloon:getSensor():setCollisionFilter(physics.category.sensor,p.targetCategory,physics.group.sensor)
    balloon:getInnerSensor():setCollisionFilter(physics.category.sensor,p.targetCategory,physics.group.sensor)
    -- No collision for the rope's hook
    balloon:getHook():setCollisionFilter(physics.category.hook,physics.category.noCollision,physics.group.hook)
    physics:addNode(balloon,self.zorder.balloon)
    return balloon
end

function Level:createFloatingPlatform(p)
    local level = self
    local platform = class.extend {
        balloons = {},
        instance = factory:box {
            uid = 1,
            size = { 1.9, 0.9 }, -- Set a smaller size to avoid collision on the edge with ground (was {2,1})
            position = p.position,
            -- Do not set a density too high or the platform will no more be able to float but
            -- we still have to set a density high enough to be stable.
            density = 1.0,
            frame = p.frame,
            body_type = physics.StaticBody,
            zorder = self.zorder.platform,
            category = physics.category.platform,
            mask = bit.bor(physics.category.platform,physics.category.player,physics.category.ground),
        },
        onEnter = function(self)
            self:setLinearDamping(1)
            self:setAngularDamping(2)
            -- Remove the balloon from the list if destroyed (e.g. contact with spear)
            mediator:subscribe(mediator.ns.removeBalloon,function(_,balloon)
                for i=#self.balloons,1,-1 do
                    if self.balloons[i] == balloon then table.remove(self.balloons,i) end
                end
            end)
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                for _,b in pairs(self.balloons) do b:launch() end
                self:setBodyType(physics.DynamicBody)
            end,self,level.tag.player)
        end,
        onExit = function(self)
        end
    }
    -- WARNING we can't create the balloon in the platform's onEnter handler
    -- because createGenericBalloon defines onEnter too and will not be called
    -- from platform'onEnter (see CCNode::onEnter)
    local createPlatformBalloon = function(x,y)
        local p = util.shallowcopy(level.data.tools.balloon.meta)
        p.startpos = { x, y + 1 }
        p.endpos = { x, y }
        p.uid = 10
        p.targetTag = nil -- No auto-attach
        -- the platform has a mass of zero because it's created as a static
        -- body so we only add the mass of the player
        p.targetMass = self.player:getMass()
        p.targetCategory = physics.category.noCollision
        local balloon = level:createGenericBalloon(p)
        -- balloon:getAnchor():setBodyType(physics.DynamicBody)
        return balloon
    end
    table.insert(platform.balloons,createPlatformBalloon(p.position[1] - 1.25, p.position[2] - 0.125))
    table.insert(platform.balloons,createPlatformBalloon(p.position[1] + 0.25, p.position[2] - 0.125))
    local c = 0 -- balloon count
    for _,b in pairs(platform.balloons) do
        local joint = physics:createRevoluteJointWithAnchor(platform,b:getHook(),b:getHook():getBodyCenter())
        -- Callback when the ballon releases the target
        b.releaseCallback = function()
            if joint then
                physics:removeJoint(joint)
                joint = nil
                c = c + 1
                -- When there's no more balloon we set a low mass so the player
                -- is now able to move the platform
                if c > 1 then platform:setMass(0.1) end
            end
        end
    end
    physics:addNode(platform)
    return platform
end

function Level:createCardboard(p)
    local level = self
    local param = {
        uid = 1,
        size = { 0.9, 0.9 },
        frame = p.frame,
        density = p.density,
        position = p.position,
        tag = self.tag.platform,
        zorder = self.zorder.platform,
        body_type = physics.DynamicBody,
        category = physics.category.platform,
        mask = bit.bor(physics.category.platform,physics.category.ground,physics.category.player),
    }
    level.cardboardCount = level.cardboardCount + 1
    local box = class.extend {
        instance = factory:box(param),
        onEnter = function(self)
            level.touch:registerTouchScriptHandler(function(e,t)
                if e == 'begin' then
                    if level.cardboardCount < 10 then
                        local pos = pix2d.Physics:meterToUnit(self:getBodyCenter())
                        param.position[1] = pos.x
                        param.position[2] = pos.y + 0.1
                        level:createCardboard(param)
                        mediator:publish(mediator.ns.insertCardboard)
                        audio:playEffect(settings.audio.click2)
                    end
                    return true
                end
            end,self)
            mediator:subscribe(mediator.ns.insertCardboard,function(_)
                self:runAction(CCSequence:createWithTwoActions(
                CCScaleTo:create(0.3,1.2,0.9),
                CCEaseElasticOut:create(CCScaleTo:create(1.0,1,1))))
            end)
        end
    }
    physics:addNode(box)
    return box
end

-- Create the player
function Level:createPlayer(p)
    if self.player then
        print 'WARNING: intend creating another player instance'
        return self.player
    end
    local c = factory:circle {
        body_type = physics.DynamicBody,
        position = p.position,
        frame = p.frame,
        radius = 0.25,
        tag = self.tag.player,
        uid = p.uid,
        density = 1.0,
        restitution = 0.1,
        friction = 1.0
    }
    c:setCascadeColorEnabled(true)
    assert(c,"can't create the player circle")
    -- We MUST disable sleeping on the player because when sleeping we might miss
    -- some contact with moving platform like bads which pass through the player
    -- without triggering any collision.
    c:setSleepingAllowed(false)
    --print('player radius in pixel',pr.x*director:getContentScaleFactor(),c:getSprite():getContentSize().width)

    if self.param.blink then
        c:runAction(CCBlink:create(1,5))
    end

    local outfit = self.manager:getCurrentOutfit()
    if outfit then
        local sprite = CCSprite:createWithSpriteFrameName(outfit..'.png')
        sprite:setScale(1.06)
        c:addChild(sprite,self.zorder.player_outfit)
    end

    -- create the motion streak
    local fade = 0.4
    local minSeg = 0.1
    local stroke = 6.0
    local streak = CCMotionStreak:create(fade, minSeg, stroke, ccc3(255,255,255), 'streak.png')
    streak:setFastMode(true)
    streak:setBlendFunc(util.alphaBlend())
    --[[
    local array = CCArray:create()
    array:addObject(CCTintTo:create(0.2, 255,0,5))
    array:addObject(CCTintTo:create(0.2, 255,132,0))
    array:addObject(CCTintTo:create(0.2, 255,246,0))
    array:addObject(CCTintTo:create(0.2, 95,255,0))
    array:addObject(CCTintTo:create(0.2, 20,58,255))
    streak:runAction(CCRepeatForever:create(CCSequence:create(array)))
    --]]
    physics:layer():addChild(streak,self.zorder.streak)
    -- We reset streak motion when the player is telepoted
    -- To actually reset the streak we must call reset() and then set the streak
    -- position to the new teleported position and avoid setting the position in
    -- the player's update function because it's still the old (not teleported)
    -- position.
    local resetStreak = false
    mediator:subscribe(mediator.ns.teleported,function(e,mp,pp)
        resetStreak = true
        streak:reset()
        streak:setPosition(pp)
    end)

    local dv = 0.6 -- desired vertical velocity
    local limitY = 0.09 -- 0.25 * 0.5-- 0.1 --
    local impulseX = 0.0 -- Horizontal impulse
    local impulseY = 0.0 -- Vertical impulse
    local level = self

    self.player = class.extend {
        instance = c,
        update = function(self,dt)
            if not resetStreak then streak:setPosition(ccp(self:getPosition()))  -- Update the streak position
            else resetStreak = false end -- Avoid setting streak position because streak has been reset
        end,
        onEnter = function(self)
            local mass = self:getMass()
            local function contact_handler(contact)
                -- Get the current velocity.
                local cv = self:getLinearVelocity()
                local pos = self:getBodyCenter()
                -- local x = contact.pos.x - pos.x
                local y = contact.pos.y - pos.y
                if y < -limitY then
                    -- Bounce against the ground.
                    impulseX = mass * (dv - math.abs(cv.x))
                    -- Apply impulse in the same direction
                    if cv.x < 0.0001 then impulseX = -impulseX end
                    -- Vertical impulse
                    impulseY = mass * (2.22 - math.abs(cv.y))
                    -- impulseY = mass * 1.8
                elseif y <= limitY and y >= -limitY then
                    -- Bounce against walls (contact is on the left or right side of the player).
                    impulseX = mass * (dv - math.abs(cv.x))
                    -- Invert horizontal impulse direction
                    if cv.x > 0.0001 then impulseX = -impulseX end
                    -- Avoid vertical impulse
                    impulseY = 0.0
                end
                -- print(y,cv.x,cv.y,'Impulse',impulseX,impulseY)
                self:applyLinearImpulse(impulseX, impulseY)
            end
            level.contact:registerCollisionNotificationScriptWithTag(contact_handler,self,level.tag.ground)
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                if c.groupIndexB == physics.group.boundaryBottom then
                    mediator:publish(mediator.ns.lose)
                elseif c.groupIndexB == physics.group.boundaryTop then
                    mediator:publish(mediator.ns.contactTopBoundary)
                else
                    contact_handler(c)
                end
            end,self,pix2d.PhysicNode.boundary)
            -- Apply the first horizontal velocity
            self:applyLinearImpulse(mass * (p.initialImpulse or dv),0)
            -- enable movable player (for debug)
            if settings.debug_player_is_movable then
                level.touch:registerTouchScriptHandler(function(e,t) return true end,self)
                self:movable(true)
            end
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
            level.touch:cancelTouchDelegate(self)
        end
    }
    assert(self.player,"Can't extend player")
    self.player:setCollisionCategory(physics.category.player)
    physics:addNode(self.player,self.zorder.player)

    -- TODO Before gameplay player animation
    --[[
    local animSprite = nil
    local animAction = nil

    local scheduleNextAnim = function(func)
        player:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(4),
            CCCallFunc:create(func)))
    end

    local animSleeping = function()

    end

    mediator:subscribe(mediator.ns.gameplayStarted,function(_)
        if animSprite then animSprite:removeFromParentAndCleanup(true) end
        if animAction then player:stopAction(animAction) end
    end)
    --]]

    -- Hack to simulate touch on the player to start the gameplay
    -- (touch on the physic layer is disabled when the gameplay is paused).
    local layer = CCLayer:create()
    local ss = pix2d.Physics:unitToPixel(1,1)
    local rect = CCRectMake(self.player:getPositionX()-(ss.x/2),self.player:getPositionY()-(ss.y/2),
        self.player:getContentSize().width + ss.x, self.player:getContentSize().height + ss.y)
    -- self.draw:drawSegment(rect.origin,ccpAdd(rect.origin,ccp(rect.size.width,rect.size.height)),2,ccc4f(1,0,0,1))
    local flag = true
    layer:registerScriptTouchHandler(function(e,x,y)
        if flag and rect:containsPoint(ccp(x,y)) then
            mediator:publish(mediator.ns.gameplayStarted,'player') -- Start gameplay by tapping on the player
            flag = false
        end
        return true
    end,false,0,true)
    layer:setTouchEnabled(true)
    physics:getScene():addChild(layer)
    -- Disable/enable touch on the player when the game is paused/resume (tap on the pause button)
    local s1 = mediator:subscribe(mediator.ns.resumeGameplay,function(_)
        if layer then layer:setTouchEnabled(true) end
    end)
    local s2 = mediator:subscribe(mediator.ns.gameplayPaused,function(_)
        if layer then layer:setTouchEnabled(false) end
    end)
    -- gameplayStarted can be published by Level:createPlayer or Hud:itemTouchHandler (touch on tool box menu)
    mediator:subscribe(mediator.ns.gameplayStarted,function(_)
        if self.gameHasStarted then return end
        audio:playEffect(settings.audio.jump1)
        self.gameHasStarted = true
        mediator:publish(mediator.ns.resumeGameplay)
        layer:removeFromParentAndCleanup(true)
        layer = nil
        -- Since layer is removed we must remove the subscriber on 'resumeGameplay' and 'gameplayPaused'
        mediator:removeSubscriber(s1)
        mediator:removeSubscriber(s2)
    end)

    return self.player
end

-- Directly transpose the physic node to a new position with a fade in/out action.
-- Parameters
-- level: instance of this level
-- target: the target physic node
-- points: an array of x,y coordinates in "centered" map unit and a delay time.
--         For instance, {{1,1,3}, {3,4,2}} will transpose the node to map cell (1,1)
--         after a delay of 3 seconds. Then wait 2 seconds and transpose the node to 3,4.
-- loop: Repeat forever the apparition actions.
local function createApparitionActions(level,target,points,loop)
    -- Must enable cascade opacity or the physic node's sprite child will not be fade in/out
    target:setCascadeOpacityEnabled(true)
    local function apparitionAction(t,x,y)
        return CCSequence:createWithTwoActions(
        CCFadeOut:create(t),
        CCCallFunc:create(function()
            local pp = pix2d.Physics:unitToPixelCenter(x,y)
            particle:create {
                filename = 'particles/stars2',
                batch = level.particleBatch['star_particle_2.png'],
                autoremove = true,
                position = { pp.x, pp.y }
            }
            local mp = pix2d.Physics:unitToMeterCenter(x,y)
            target:setBodyPosition(mp.x,mp.y)
            target:runAction(CCFadeIn:create(0.5))
        end))
    end
    local delay = 0.5 -- minimum time between apparitions
    local action = nil
    for i=1,#points do
        local tmp = CCSequence:createWithTwoActions(
            CCDelayTime:create(math.max(points[i][3] - delay, 0)),
            apparitionAction(delay,points[i][1],points[i][2]))
        if action then tmp = CCSequence:createWithTwoActions(action,tmp) end
        action = tmp
    end
    target:runAction(loop and CCRepeatForever:create(action) or action)
end

-- Create coins
function Level:createCoin(p)
    local level = self
    local coin = class.extend {
        instance = factory:circle {
            body_type = physics.KinematicBody,
            position = p.position,
            sensor = true,
            sprite = p.sprite,
            frame = p.frame,
            radius = 0.25,
            tag = self.tag.coin,
            uid = 4
        },
        onEnter = function(self)
            local function contactHandler(c)
                -- Avoid further collision
                self:setCollisionMask(physics.category.noCollision)
                mediator:publish(mediator.ns.updateScore,1)
                -- Run scale and fade out action then remove the coin
                self:runAction(CCSequence:createWithTwoActions(
                    CCScaleTo:create(0.4,1.6),
                    CCCallFunc:create(function()
                        self:setVisible(false)
                        self:setCollisionMask(physics.category.noCollision)
                        -- self:removeFromParentAndCleanup(true)
                    end)))
                self:getSprite():runAction(CCFadeOut:create(0.4))
                -- Create the particle effect.
                -- BUG FIX: when garbage collect occurs it might release the particle (calling tolua_collect_CCParticleSystemQuad)
                -- which will do a c++ `delete` on the CCParticleSystem. The only way to prevent the garbage collector to collect
                -- the particle is to keep a reference to the particle userdata.
                local _ps = particle:create {
                    filename = 'particles/stars2',
                    batch = level.particleBatch['star_particle_2.png'],
                    autoremove = false,
                    position = { self:getPosition() } -- multiple return values to table
                }
                level.part_tmp = level.part_tmp or {}
                table.insert(level.part_tmp,_ps)
            end
            level.contact:registerCollisionNotificationScriptWithTag(contactHandler,self,level.tag.player)
            if p.apparition then
                mediator:subscribe(mediator.ns.gameplayStarted,function()
                    createApparitionActions(level,self,p.apparition,p.apparitionLoop)
                end)
            end
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    assert(coin,"Can't extend from coin")
    if p.color then coin:getSprite():setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    if p.path then
        self:createPathAction(p.path,coin)
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(coin) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(coin) end)
    end
    physics:addNode(coin,self.zorder.coin)
    --[[
    coin:getSprite():runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCRotateTo:create(1.0, 35),
        CCRotateTo:create(1.0,-35))))
    --]]
    anim:dance(coin:getSprite())
    return coin
end

function Level:loadCoin(p)
    self:createCoin(p)
end

-- DEPRECATED
function Level:loadCoins(p)
    for i=1,#p.positions do
        p.position = p.positions[i]
        self:createCoin(p)
    end
end

-- Create a path action: moveTo, circleTo or splineTo
-- Positions are in map unit. The cirle radius is figured out using the center parameter and the target position.
-- circleTo: { center = { 1, 2 }, duration = 4, type = 'circleTo', loop = true }
-- moveTo: { points = { 1,2, 4,5, 6,5 }, speed = 0.4, type = 'moveTo', loop = true }
-- splineTo: { pointr = { 1,2, 3,4, 5,6 }, type = 'splineTo', tension = 2, duration = 4, loop = true }
function Level:createPathAction(path,target)
    local action = nil
    if path.action == 'circleTo' then
        action = factory:circle_to(path)
    elseif path.action == 'moveTo' then
        path.startPos = { path.points[1], path.points[2] }
        path.endPos   = { path.points[3], path.points[4] }
        action = factory:move_to(path)
        for i=3, #path.points-2, 2 do
            path.startPos = { path.points[i], path.points[i+1] }
            path.endPos   = { path.points[i+2],path.points[i+3] }
            action = CCSequence:createWithTwoActions(action,factory:move_to(path))
        end
    elseif path.action == 'splineTo' then
        action = factory:spline_to(path)
    else
        assert(false,'Unknown action type')
    end
    target:runAction(action)
    if path.loop then
        target:stopAction(action) -- must stop the action before reuse it or it will crash
        target:runAction(CCRepeatForever:create(action))
    end
    return action
end

function Level:createBad(p)
    p.tag = self.tag.bad
    p.radius = p.radius or 0.25
    p.body_type = physics.KinematicBody
    p.category = physics.category.ennemy
    p.mask = physics.category.player -- Only collide with player
    p.sensor = true
    local level = self
    local bad = class.extend {
        instance = factory:circle(p),
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
        self:createPathAction(p.path,bad)
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(bad) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(bad) end)
    end
    -- TODO add option to the editor parser to activate the tintto action
    --[[
    bad:getSprite():runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCTintTo:create(1.0,255,0,0),CCTintTo:create(1.0,255,255,255))))
    --]]
    physics:addNode(bad,self.zorder.ennemy,self.tag.bad)
    return bad
end

function Level:createSpear(p)
    local level = self
    local spear = class.extend {
        instance = factory:box {
            uid = 1,
            angle = p.angle,
            frame = p.frame,
            sensor = true,
            body_type = physics.KinematicBody,
            size = { 1, 0.5 },
            position = p.position,
            category = physics.category.ennemy,
            mask = bit.bor(physics.category.balloon,physics.category.player), -- Only collide with player and balloon
        },
        onEnter = function(self)
            level.contact:registerCollisionNotificationScriptWithTag(
                function() mediator:publish(mediator.ns.lose) end,
                self,level.tag.player)
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    physics:addNode(spear,self.zorder.ennemy,self.tag.spear)
end


-- Create the level's target. Note that the target is not removed but just set
-- to not visible when touched by the player.
-- {
--   "type": "target",
--   "uid": 5,
--   "position": [8, 1],
--   "frame": "cake.png"
-- }
function Level:createTarget(p)
    local c = factory:circle {
        body_type = physics.KinematicBody,
        position = p.position,
        sensor = true,
        radius = 0.5,
        tag = self.tag.target,
        uid = p.uid,
        frame = p.frame
    }
    assert(c,"can't create the level target")
    local level = self
    local target = class.extend {
        instance = c,
        onEnter = function(self)
            level.contact:registerCollisionNotificationScriptWithTag(function()
                local part = particle:create {
                    filename = 'particles/stars2',
                    batch = level.particleBatch['star_particle_2.png'],
                    autoremove = true,
                    position = { self:getPosition() } -- multiple return values to table
                }
                -- See createCoin
                level.part_tmp = level.part_tmp or {}
                table.insert(level.part_tmp,part)
                self:runAction(CCSequence:createWithTwoActions(
                    CCScaleTo:create(0.15,0.0),
                    CCCallFunc:create(function()
                        self:setVisible(false)
                        self:stopAllActions() -- In case there is stil a "apparition" action running
                    end)))
                self:runAction(CCRotateTo:create(0.15,90))
                mediator:publish(mediator.ns.win,level.score)
                self:setCollisionMask(physics.category.noCollision)
            end,self,level.tag.player)
            if p.apparition then
                mediator:subscribe(mediator.ns.gameplayStarted,function()
                    createApparitionActions(level,self,p.apparition,p.apparitionLoop)
                end)
            end
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    if p.color then target:getSprite():setColor(ccc3(p.color[1],p.color[2],p.color[3])) end

    if p.path then
        self:createPathAction(p.path,target)
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(target) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(target) end)
    end
    physics:addNode(target,self.zorder.coin)
    -- Add the 'dancing' action
    anim:dance(target:getSprite())
    -- Add the glow animation
    local color = pix2d.Physics:getDefaultBackgroundColor()
    color = ccc3(color.r*255,color.g*255,color.b*255)

    for i=1,2 do
        local glow = CCSprite:createWithSpriteFrameName('target_glow.png')
        -- glow:setColor(i==1 and ccc3(255,246,19) or ccc3(255,255,255))
        glow:setOpacity(i==1 and 60 or 40)
        glow:setRotation(i==1 and 0 or 90)
        glow:runAction(CCRepeatForever:create(CCRotateBy:create(20,360)))
        glow:setScale(i==1 and 1.7 or 1.2)
        glow:setBlendFunc(util.additiveBlend())
        target:addChild(glow,-1)
    end

    --[[
    local glow = pix2d.CustomSprite:createWithSpriteFrameName(p.frame)
    -- glow:setColor(ccc3(255,255,0))
    anim:repeatForever(glow,CCScaleTo:create(1.5,1.05),CCScaleTo:create(1.5,1.2))
    glow:setScale(1.1)
    glow:setOpacity(200)
    glow:setBlendFunc(util.overlayBlend())
    anim:dance(glow)
    target:addChild(glow,-1)
    --]]
    return target
end

function Level:loadSlider(p)
    -- Start-end position in pixels
    local pp1 = pix2d.Physics:unitToPixel(p.startpos[1],p.startpos[2])
    local pp2 = pix2d.Physics:unitToPixel(p.endpos[1],p.endpos[2])
    -- Start-end position in meters
    local startpos = pix2d.Physics:unitToMeter(p.startpos[1],p.startpos[2])
    local endpos = pix2d.Physics:unitToMeter(p.endpos[1],p.endpos[2])
    -- slider direction
    local direction = math.abs(math.floor(math.deg(ccpToAngle(ccpSub(pp1,pp2)))))
    if direction >= 45 and direction <= 135 then
        p.frame = 'slider_vertical.png'
        p.grabber = 'grabber_rect_v.png'
        p.scale = { 1.25, 2.75 }
    else
        p.frame = 'slider_horizontal.png'
        p.grabber = 'grabber_rect_h.png'
        p.scale = { 2, 2 }
    end
    -- print('slider start',pp1.x,pp1.y,'end',pp2.x,pp2.y,'direction',direction)
    p.body_type = physics.DynamicBody
    p.density = 1.0 -- Beware not to set a huge density.
    -- A density above 10 or so the slider and player might overlap.
    -- Use the friction joint to avoid the player to move vertical slider (see below)
    p.size = { p.size[1] * 0.9, p.size[2] * 0.9 } -- Shrink the box to avoid collision on the edges
    local level = self
    local box = class.extend {
        instance = factory:box(p),
        onEnter = function(self)
            level:createTouchGrabberSprite { target = self, frame = p.grabber, scale = p.scale }
        end,
        onExit = function(self)
            level.touch:cancelTouchDelegate(self)
        end
    }
    physics:addNode(box,self.zorder.platform)
    if p.color then box:getSprite():setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    box:getSprite():runAction(anim:createSequence({
        CCDelayTime:create(2),
        CCScaleTo:create(0.2,1.15),
        CCEaseElasticOut:create(CCScaleTo:create(0.6,1))
    },true))
    mediator:subscribe(mediator.ns.gameplayStarted,function()
        box:getSprite():stopAllActions()
        box:getSprite():setScale(1)
    end)
    box:setGravityScale(0) -- cancel gravity
    -- create the prismatic joint
    physics:createPrismaticJoint(box,startpos,endpos)
    -- TODO fine tune the friction joint/slider density
    physics:createFrictionJoint(box,1.5) -- Avoid vertical sliders to move down under the player's weight
    -- Allow collision with other platform, the player and the ground
    box:setCollisionFilter(
        physics.category.platform,
        bit.bor(physics.category.platform,physics.category.player,physics.category.ground),
        0)
    -- Draw the slider path with dots
    local distance = ccpDistance(pp1,pp2)
    local time = 0
    -- local rate = 0.7
    for i=0,distance,physics:getUnitInPixel()/2 do
        time = i/distance
        self.draw:drawDot(ccpLerp(pp1,pp2,time),3,ccc4f(1,1,1,0.8))
    end
end

-- Extent a physic texture with new vertices
function Level:extendTexture(tex,vertices)
    local vec = vector_b2Vec2_:new_local()
    for i,p1,p2 in util.ipairs2(vertices) do
        vec:push_back(b2Vec2(p1,p2))
    end
    tex:addVertices(vec)
end

-- Convert index map to texture vertices
-- points: array of map indices. Must contains 2 or 4 coords ({x,y} or {x,y,x,y})
local function mapIndexToVertices(v)
    local t = {}
    if #v == 2 then
        local c = b2Vec2(v[1], v[2])
        table.insert(t,c.x)
        table.insert(t,c.y)
        table.insert(t,c.x + 1)
        table.insert(t,c.y + 1)
    elseif #v == 4 then
        local s = b2Vec2(v[1],v[2])
        local e = b2Vec2(v[3],v[4])
        table.insert(t,s.x)
        table.insert(t,s.y)
        table.insert(t,e.x + 1)
        table.insert(t,e.y + 1)
    else
        assert(false,'ERROR: texture ground definition must have 2 or 4 points')
    end
    return t
end

-- Returns a texture physic body.
-- The polygon can be created by giving all the vertices (in map unit) or the
-- map indices (p.indices == true)
-- p.points: a two dimentional array of pairs of numbers. Each array must
-- p.indices: create the polygon using vertices or indices
-- Floating vertices are allowed (e.g. [1.2, 3.4]).
-- vertices are not centered to the map item. The vertice is the left-bottom
-- of the mat item.
-- Warning: Nested array require a whitespace before the closing bracket
-- JSON:
-- {
--    "type": "freehandTextureGround",
--    "uid": 8,
--    "points": [[2,2, 2,3.2, 3,3, 3,2], [2.4, 5.5, 6.7] ],
--    "texture": "textures/ground_texture.png"
--}
function Level:createBodyTexture(p)
    local tex = nil
    for _,t in ipairs(p.points) do
        if p.indices then t = mapIndexToVertices(t) end
        if not tex then
            p.points = t
            tex = factory:texture_node(p)
        else
            self:extendTexture(tex,t)
        end
    end
    -- Not relevant because GL_OPEN_CLAMP_TO_BORDER is not supported in OpenGL ES 2.0
    -- tex:getTextureSprite():setRepeat(p.repeatH,p.repeatV)
    if p.color then tex:getTextureSprite():setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    if p.opacity then tex:getTextureSprite():setOpacity(p.opacity) end
    -- tex:getTextureSprite():setOpacity(128)
    return tex
end

-- Create polygon static physic ground. The body can be composed of several rectangles.
-- points: a two dimentional array. Each nested array must contains one or two points.
--         If only one point is provided then a rect texture is create at this map position.
--         If two points are provided a rect texture is created with the first point
--         the upper-left poisition and the other the bottom-right position in the map.
-- Warning: Nested JSON array requires a whitespace before the closing bracket (see example below)
-- JSON input:
-- {
--     "type": "textureGround",
--     "indices": true
--     "uid": 10,
--     "points": [[7,4], [0,4,3,4] ],
--     "texture": "textures/ground_texture.png"
-- }
function Level:loadGround(p)
    p.body_type = physics.StaticBody
    p.tag = self.tag.ground
    p.category = physics.category.ground
    local ground = class.extend {
        instance = self:createBodyTexture(p),
        onEnter = function(self)
            self.schedulerid = self:getScheduler():scheduleScriptFunc(function()
                self:runAction(CCEaseElasticOut:create(
                    pix2d.ActionTweenLua:create(2.0,'',0,0.3,function(v,k)
                        self:getTextureSprite():translateTexCoord(0,v)
                    end)))
            end,5,false)
        end,
        onExit = function(self)
            self:getScheduler():unscheduleScriptEntry(self.schedulerid)
        end
    }
    physics:addNode(ground,self.zorder.ground)
end

-- Generic texture polygon body
function Level:loadTextureBody(p)
    -- p.points = mapIndexToVertices(p.points)
    p.category = physics.category.ground
    local tb = factory:texture_node(p)
    if p.color then tb:getTextureSprite():setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    physics:addNode(tb)
    return tb
end

function Level:createShadowSensor(p)
    p.sensor = true
    p.category = physics.category.sensor
    p.mask = physics.category.player
    local sensor = factory:box(p)
    physics:addNode(sensor)

    local speed = p.speed or 0.3
    local color = nil
    self.contact:registerCollisionNotificationScriptWithTag(function(c)
        color = c.nodeB:getSprite():getColor()
        c.nodeB:runAction(CCTintTo:create(speed,color.r * p.darkness,color.g * p.darkness,color.b * p.darkness))
    end,sensor,self.tag.player)
    self.contact:registerEndCollisionNotificationScriptWithTag(function(c)
        c.nodeB:runAction(CCTintTo:create(speed,color.r,color.g,color.b))
    end,sensor,self.tag.player)
    return sensor
end

-- Generic sprite polugon body
function Level:loadPolyonBody(p)
    -- TODO
end

function Level:loadLine(p)
    local color = util.toColor4f(p.color)
    for i=1,#p.points-2,2 do
        -- print(p.points[i],p.points[i+1])
        local from = pix2d.Physics:unitToPixel(p.points[i],p.points[i+1])
        local to = pix2d.Physics:unitToPixel(p.points[i+2],p.points[i+3])
        self.draw:drawSegment(from,to,p.radius,color)
        from = to
    end
end

-- "type": "lines",
-- "points": [[0,4,3,4,3,5], [8,5,8,4,10,4], [4,0,4,1],[8,0,8,1] ],
-- "radius": 2,
-- "color": [103,35,29,255]
function Level:loadLines(p)
    local color = util.toColor4f(p.color)
    for j=1,#p.points do
        local from = pix2d.Physics:unitToPixel(p.points[j][1],p.points[j][2])
        for i=3,#p.points[j],2 do
            local to = pix2d.Physics:unitToPixel(p.points[j][i],p.points[j][i+1])
            self.draw:drawSegment(from,to,p.radius,color)
            from = to
        end
    end
end

-- Draw a solid polygon. Concave polygon are not supported (cf. CCDrawNode)
-- parameters:
-- points: list of vertices in map unit (e.g. {100,110,200,230,400,450})
-- fillColor: table of float color (e.g. {1.0,0,0,1.0})
-- borderColor:
-- borderWidth
function Level:loadPolygon(p)
    local vertices = vector_CCPoint_:new_local()
    for i=1,#p.points,2 do
        vertices:push_back(pix2d.Physics:unitToPixel(p.points[i],p.points[i+1]))
    end
    self.draw:drawPolygon(vertices,util.toColor4f(p.fillColor),p.borderWidth,util.toColor4f(p.borderColor))
end

function Level:loadTexture(p)
    local layer = self:getLayerByName(p.layer) or physics:layer()
    local zorder = p.zorder and self.zorder[p.zorder] or 0
    local tag = p.tag and self.tag[p.tag] or 0
    local texture = factory:texture_sprite(p)
    if p.opacity then texture:setOpacity(p.opacity) end
    if p.color then texture:setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
    if p.scale then texture:setScaleX(p.scale[1]); texture:setScaleY(p.scale[2]) end
    texture:setBlendFunc(util.alphaBlend())
    layer:addChild(texture,zorder)
    return texture
end

--[[
function Level:loadLight(p)
   local texture = self:loadTexture(p)
   anim:repeatForever(texture,CCScaleTo:create(2,1.1,1),CCScaleTo:create(2,1))
   --local color = texture:getColor()
   -- anim:repeatForever(texture,CCTintTo:create(2,color.r*1.1,color.g*1.1,color.b*1.1),CCTintTo:create(2,color.r,color.g,color.b))
end
-]]

-- TODO
function Level:createFreehandGround(points)
    local count = #points
    if count < 3 then return end
    p = {}
    p.uid = 1
    p.body_type = physics.StaticBody
    p.tag = self.tag.ground
    local t = {}
    for i=1,count do
        table.insert(t,points[i][1])
        table.insert(t,points[i][2])
    end
    p.points = t
    p.density = 10
    p.texture = 'ground_texture.png'
    p.simplify = true
    p.category = physics.category.ground
    local ground = factory:texture_node(p)
    assert(ground)
    physics:addNode(ground)
    -- ground:setBodyType(physics.DynamicBody)
end

-- Create a 'dancing' sprite with frame `p.frame` at position `p.position` (in unit coordinates)
-- p = {
--    frame = 'image.png',
--    position = { 5,8 }
-- }
function Level:createDancingSprite(p)
    local sprite = self:createSprite(p)
    anim:dance(sprite)
    self.backgroundLayer:addChild(sprite,self.zorder[p.zorder] or self.zorder.background.frontSprites)
end

function Level:loadInfiniteScrollingSprite(p)
    local layer = self:getLayerByName(p.layer) or physics:layer()
    local zorder = p.zorder and self.zorder[p.zorder] or 0
    local tag = p.tag and self.tag[p.tag] or 0
    p.startPos = pix2d.Physics:unitToPixel(p.startPos[1],p.startPos[2])
    p.endPos = pix2d.Physics:unitToPixel(p.endPos[1],p.endPos[2])
    local sprite = ScrollSprite():init(p)
    layer:addChild(sprite.node,tag,zorder)
end

-- Create a dynamic sensor body to move the target body.
-- If not provided, a static body is created to attach the target to the world
-- Mandatory: position,target,touchCallback
-- Optional: radius, damping, anchor
function Level:createRotationalTouchGrabber(p)
    local c = factory:circle {
        uid = 1,
        sensor = true,
        body_type = physics.DynamicBody,
        category = physics.category.noCollision,
        radius = p.radius or 0.75,
        position = p.position,
        frame = 'grabber_rotate.png',
    }
    physics:createRevoluteJointWithLimit(p.target,c,p.target:getBodyCenter(),0,0)
    -- physics:createWeldJoint(p.target,c,b2Vec2(0,0),b2Vec2(0,0))
    if not p.anchor then
        -- The static body used as the target's anchor to the world
        p.anchor = factory:circle {
            uid = 1,
            sensor = true,
            body_type = physics.StaticBody,
            position = p.position,
            radius = 0.25,
            category = physics.category.noCollision,
        }
        physics:addNode(p.anchor)
    end
    physics:createRevoluteJoint(c,p.anchor)
    c:getSprite():setVisible(false)
    local action = nil
    self.touch:registerTouchScriptHandler(function(e,t)
        if p.touchCallback then p.touchCallback(e,t) end
        if e == 'begin' then
            mediator:publish(mediator.ns.tool_touched,e,p.target)
            c:getSprite():setVisible(true)
            if action then c:getSprite():stopAction(action) end
            action = CCFadeIn:create(0.2)
            c:getSprite():runAction(action)
            return true
        elseif e == 'ended' or e == 'canceled' then
            mediator:publish(mediator.ns.tool_touched,e,p.target)
            if action then c:getSprite():stopAction(action) end
            action = CCSequence:createWithTwoActions(
            CCFadeOut:create(0.2),CCCallFunc:create(function()
                c:getSprite():setVisible(false)
            end))
            c:getSprite():runAction(action)
        end
    end,c)
    c:movable(true)
    c:setGravityScale(0)
    c:setAngularDamping(p.damping or 10)
    physics:addNode(c)
    -- if p.angle then c:setBodyRotation(p.angle) end
end

function Level:createFanPaper(parent,position,anchor,angle)
    local sprite = CCSprite:createWithSpriteFrameName('fan_paper.png')
    local size = sprite:getContentSize()
    size = pix2d.Physics:pixelToMeter(size.width,size.height)
    local paper = class.extend {
        instance = factory:box {
            uid = 1,
            body_type = physics.DynamicBody,
            frame = 'fan_paper.png',
            sensor = true,
            position = { position.x, position.y },
            angle = angle,
            size = { size.x,size.y },
            density = 0.001,
            category = physics.category.noCollision,
        },
        flag = false,
        time = 0,
        setPaperEnabled = function(self,value)
            if value then
                self.joint:SetLimits(0,0)
                self:setAngularVelocity(0)
                self:scheduleUpdateWithPriorityLua(function(dt)
                    self.time = self.time + dt
                    if self.time > 0.3 then
                        self.time = 0
                        self.flag = not self.flag
                        self:getSprite():setFlipY(self.flag)
                    end
                end,1)
            else
                self.joint:SetLimits(math.rad(-170),math.rad(170))
                self:unscheduleUpdate()
            end
        end,
    }
    -- paper:setGravityScale(0.1)
    -- paper:setAngularDamping(1000)
    paper.joint = physics:createRevoluteJointWithLimit(paper,parent,anchor,0,0)
    return paper
end

function Level:createFanSensors(p,position)
    local pivot = pix2d.Physics:unitToMeter(p.center[1],p.center[2])
    local sensor = factory:box {
        uid = 1,
        sensor = true,
        body_type = physics.DynamicBody,
        position = { position.x , position.y },
        size = { 2.5, 0.5 },
        angle = p.angle,
        density = 0.00001,
        category = physics.category.sensor,
    }
    sensor:setGravityScale(0)
    sensor.enabled = p.enabled
    -- Begin contact with sensor. Add the node references to the nodes list and
    -- schedule the update method to apply a continious force
    self.contact:registerCollisionNotificationScriptWithTag(function(c)
        if not sensor.nodes then
            sensor.nodes = {}
            sensor.count = 0
            sensor:scheduleUpdateWithPriorityLua(function(dt)
                if physics:isPaused() or not sensor.enabled then return end
                local c = sensor:getBodyCenter() -- current fan position
                local d = ccpNormalize(ccp(c.x - pivot.x, c.y - pivot.y)) -- current fan direction
                for _,node in pairs(sensor.nodes) do
                    -- Node's mass can't be stored in an upvalue because the balloon
                    -- might still be a static body which has no mass (mass = 0)
                    local mass = node:getMass()
                    -- print('force',mass*d.x*self.dv.x,mass*d.y*self.dv.y)
                    -- Apply a force of the fan direction
                    node:applyForceToCenter(mass * d.x * 2.5, mass * d.y * 2.5)
                end
                -- Apply a force to the papers
            end,1)
        end
        sensor.nodes[c.nodeB] = tolua.cast(c.nodeB,'pix2d::PhysicNode')
        sensor.count = sensor.count + 1
    end,sensor,self.tag.balloon)

    local removeBalloonFromList = function(balloon)
        if sensor.nodes and sensor.nodes[balloon] then
            sensor.nodes[balloon] = nil
            sensor.count = sensor.count - 1
            if not sensor.count then
                sensor.nodes = nil
                sensor:unscheduleUpdate()
            end
        end
    end
    -- End collision. Remove the node reference and unschedule the update method
    self.contact:registerEndCollisionNotificationScriptWithTag(function(c)
        removeBalloonFromList(c.nodeB)
    end,sensor,self.tag.balloon)
    -- Remove the balloon if it's remove from the world (destroyed)
    mediator:subscribe(mediator.ns.removeBalloon,function(_,balloon)
        removeBalloonFromList(balloon:getAnchor())
    end)

    return sensor
end

-- Parameters
-- position = {1,1}, position of the fan in unit
-- center = {1.5,1.5}, center for the sensors in unit
-- angle
-- enabled
function Level:loadFan(p)
    if p.enabled == nil then p.enabled = true end
    -- Create the fan sprite
    local level = self
    local fan = class.extend {
        instance = factory:circle {
            uid = 1,
            tag = self.tag.fan,
            angle = p.angle,
            body_type = physics.DynamicBody,
            sensor = true,
            frame = 'fan.png',
            position = p.position,
            radius = 0.5,
            category = physics.category.noCollision,
        },
        onEnter = function(self)
            self:setAngularDamping(10)
            self:setGravityScale(0)
            self:getSprite():runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
                CCMoveBy:create(0.05,ccp(-0.35,0.35)),
                CCMoveBy:create(0.05,ccp(0.35,-0.35)))))
            self:setFanEnabled(self.sensor.enabled)
        end,
        setFanEnabled = function(self,value)
            self.paperA:setPaperEnabled(value)
            self.paperB:setPaperEnabled(value)
            local color = value and ccc3(255,255,255) or ccc3(150,150,150)
            self:setColor(color)
            self.paperA:getSprite():setColor(color)
            self.paperB:getSprite():setColor(color)
            if value then
                pix2d.NodeUtil:resumeSchedulerAndActions(self)
            else
                pix2d.NodeUtil:pauseSchedulerAndActions(self)
            end
        end,
    }
    fan:setCascadeColorEnabled(true)
    -- Create the fan's sensor
    fan.sensor = self:createFanSensors(p,pix2d.Physics:meterToUnit(fan:getWorldPoint(pix2d.Physics:unitToMeter(1.25,0))))
    -- Create the fan's papers
    local positionA = pix2d.Physics:meterToUnit(fan:getWorldPoint(b2Vec2(0.2,0.2)))
    local anchorA = fan:getWorldPoint(b2Vec2(0.1,0.2))
    local positionB = pix2d.Physics:meterToUnit(fan:getWorldPoint(b2Vec2(0.2,-0.2)))
    local anchorB = fan:getWorldPoint(b2Vec2(0.1,-0.2))
    fan.paperA = self:createFanPaper(fan,positionA,anchorA,p.angle)
    fan.paperB = self:createFanPaper(fan,positionB,anchorB,p.angle)

    -- Create the blade animation
    fan.blade = CCSprite:createWithSpriteFrameName('fan_blade.png')
    fan.blade:runAction(CCRepeatForever:create(CCBlink:create(1,10)))
    fan.blade:setPosition(9,0)
    fan:addChild(fan.blade,-1)

    level:createRotationalTouchGrabber {
        position = p.position,
        target = fan,
        radius = 1,
        touchCallback = function(e,t)
            if e == 'ended' or e == 'canceled' then
                if not t.hasMoved then
                    fan.sensor.enabled = not fan.sensor.enabled
                    fan:setFanEnabled(fan.sensor.enabled)
                    audio:playEffect(fan.sensor.enabled and settings.audio.click or settings.audio.switch2)
                end
            end
        end,
    }
    physics:createRevoluteJointWithLimit(fan.sensor,fan,fan:getBodyCenter(),0,0)
    physics:addNode(fan.paperA,self.zorder.fan)
    physics:addNode(fan.paperB,self.zorder.fan)
    physics:addNode(fan.sensor)
    physics:addNode(fan,self.zorder.fan)
end

-- Create a teleport tool
-- Parameters:
-- position
-- angle
-- group: teleport group
-- index: this teleport group index
-- effectFrame: DEPRECATED
-- movable:
-- path:
function Level:createTeleport(p)
    assert(p.group)
    local level = self
    local positionCenter = { p.position[1] + 0.5, p.position[2] + 0.5} -- center
    -- init this group entry
    level.teleports[p.group] = level.teleports[p.group] or {}
    local box = class.extend {
        instance = factory:box {
            uid = 1,
            angle = p.angle,
            body_type = p.movable and physics.DynamicBody or physics.KinematicBody,
            sensor = true,
            position = positionCenter,
            frame = p.frame,
            size = {1,0.25},
            mask = physics.category.player,
            category = physics.category.platform,
        },
        -- To avoid infinite looping between teleport, the next teleport is
        -- disabled and then enabled again when contact with player ends
        enabled = true,
        index = p.index or #level.teleports[p.group] + 1, -- add at the last index of its group
        group = p.group, -- This teleport group. Teleports loop between of the same group
    }
    level.contact:registerCollisionNotificationScriptWithTag(function(c)
        local count = #level.teleports[box.group]
        if not box.enabled or count == 1 then return end  -- nothing to do if there's only one teleport
        local nextTeleport = level.teleports[box.group][box.index < count and box.index + 1 or 1]
        nextTeleport.enabled = false
        -- Transform player position from current teleport coordinates to the next one
        local pos = nextTeleport:getWorldPoint(box:getLocalPoint(c.nodeB:getBodyCenter()))
        c.nodeB:setBodyPosition(pos.x,pos.y)
        -- Transform the velocity to the next teleport
        local v = nextTeleport:getWorldVector(box:getLocalVector(level.player:getLinearVelocity()))
        v = ccp(v.x,v.y)
        -- The normal
        local n = nextTeleport:getWorldVector(b2Vec2(0,1))
        n = ccpNormalize(ccp(n.x,n.y))
        -- vector reflection formula
        -- v2 = v1 - 2 * N * (N dot v1)
        v = ccpSub(v,ccpMult(ccpMult(n,2),ccpDot(n,v)))
        -- clamp velocity
        local mv = 4.0 -- absolute max velocity
        v.x = clampf(v.x,-mv,mv)
        v.y = clampf(v.y,-mv,mv)
        self.player:setLinearVelocity(b2Vec2(v.x,v.y))
        -- Anti gravity
        c.nodeB:applyForceToCenter(0,-1 * c.nodeB:getMass() * physics:getGravity().y)
        mediator:publish(mediator.ns.teleported,pos,pix2d.Physics:meterToPixel(pos))
        audio:playEffect(settings.audio.teleport)
    end,box,level.tag.player)
    level.contact:registerEndCollisionNotificationScriptWithTag(function(c)
        box.enabled = true
    end,box,level.tag.player)

    -- The groups colors
    local colors = {
        { 102, 255, 0   }, -- light green
        { 255, 2  , 205 }, -- purple
        { 37 , 212, 255 }, -- light blue
    }
    local color = ccc3(colors[p.group][1],colors[p.group][2],colors[p.group][3])
    box:getSprite():setColor(color)
    if p.angle then box:setBodyRotation(p.angle) end
    box:setGravityScale(0)
    -- Teleport is movable by the user or there's a path action
    if p.movable then
        level:createRotationalTouchGrabber {
            position = p.position,
            target = box,
            -- anchor = anchor,
        }
    else
        -- Create a action path if not movable
        if p.path then
            self:createPathAction(p.path,box)
            mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(box) end)
            mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(box) end)
        end
    end
    -- Add the teleport into its group
    level.teleports[box.group] = level.teleports[box.group] or {}
    level.teleports[box.group][box.index] = box

    local glow = CCSprite:createWithSpriteFrameName('teleport_glow.png')
    glow:setColor(color)
    glow:setAnchorPoint(ccp(0.5,0))
    glow:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCScaleTo:create(1,1,0.8),CCScaleTo:create(1,1,1.2))))
    box:addChild(glow,-2)

    local blur = CCSprite:createWithSpriteFrameName('teleport_glow_blur.png')
    blur:setAnchorPoint(ccp(0.5,0))
    blur:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCScaleTo:create(1,1,0.6),CCScaleTo:create(1,1.1))))
    box:addChild(blur,-3)

    -- Add teleport rings effect
    for i=1,3 do
        local sprite = CCSprite:createWithSpriteFrameName('teleport_ring.png')
        sprite:setColor(color)
        sprite:setOpacity(128)
        sprite:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCMoveTo:create(2,ccp(0,5 + (10 * i))),CCCallFunc:create(function()
            sprite:setPosition(0,0)
        end))))
        sprite:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
        CCFadeOut:create(2),CCCallFunc:create(function()
            sprite:setOpacity(255)
        end))))
        box:addChild(sprite,-1)
    end
    --[[
    for i=1, 5 do
        assert(p.effectFrame)
        local sprite = CCSprite:createWithSpriteFrameName(p.effectFrame)
        sprite:setPosition(ccp(0,sprite:getContentSize().height * 0.6 * i))
        sprite:runAction(CCSequence:createWithTwoActions(
        CCDelayTime:create(0.1 * i),CCCallFunc:create(function()
            sprite:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
            CCFadeIn:create(0.5),CCFadeOut:create(0.5))))
        end)))
        box:addChild(sprite,-1)
    end
    --]]
    -- Add the teleport to the scene
    physics:addNode(box,self.zorder.platform)
    return box
end

-- Create a circle static body with no collision. Anchor and target node are joint
-- using the target current position and the anchor's center.
-- Parameters:
-- target: node that will be attached to this anchor
-- limit: if not nil it will set the rotation limit
-- position: this anchor position in map unit
function Level:createAnchor(p)
    local anchor = factory:circle {
        uid = 1,
        sensor = true, -- Avoid density
        -- body_type = physics.StaticBody, -- default is static body
        position = p.position,
        radius = 0.25,
        category = physics.category.noCollision,
    }
    local joint = nil
    if p.limit then
        joint = physics:createRevoluteJointWithLimit(anchor,p.target,anchor:getBodyCenter(),p.limit[1],p.limit[2])
    else
        joint = physics:createRevoluteJointWithAnchor(anchor,p.target,anchor:getBodyCenter())
    end
    physics:addNode(anchor)
    return anchor, joint
end

-- To set the desired chain projection distance you have to tune the projection
-- and mouseMaxForce/mouseFrequency parameters
-- Mandatory parameters:
-- startpos, endpos: starting an ending chain position in map unit
-- projection: table with desired vertical and horizontal distance projection in map unit
-- Optional parameters:
-- movable: should the player be able to move the chain?
-- count: Total number of chain's nodes
-- color:
-- batch/frame: build the chain using either a batch node sprite or a sprite frame
-- overlap: nodes horizontal overlap percent
-- density: nodes density
-- height: chain's nodes height in map unit
-- sensorHeight: chain's touch sensor height in map unit
-- mouseMaxForce: should not be too high or the player might be able to pass through the chain nodes
-- mouseFrequency:
-- anchors: create the anchors body if true (default)
-- initialize: intialize the chain's node position and angle (true by default)
-- mask: collision mask for all the nodes
-- close: should the chain should be closed (first and last node are joint). false by default.
-- fadeIn: flag to enable/disable rope fade in
function Level:createChain(p)
    local level = self
    -- Update all chain batched sprites
    local chain = class.extend {
        instance = CCNode:create(),
        sprites = {}, -- list of sprite batch
        nodes = {}, -- list of PhysicNodes
        updateBatchNodes = function(self,dt)
            -- Update the batched sprites
            for i=1,#self.nodes do
                self.sprites[i]:setPosition(self.nodes[i]:getPosition())
                self.sprites[i]:setRotation(self.nodes[i]:getRotation())
            end
        end,
        onEnter = function(self)
            -- fade in effect on enter
            if p.batch then
                -- Schedule to update the node position/rotation
                self:scheduleUpdateWithPriorityLua(function() self:updateBatchNodes() end,1)
                if self.fadeIn then
                    for i=1,#self.sprites do
                        self.sprites[i]:runAction(CCSequence:createWithTwoActions(
                        CCDelayTime:create(0.05 * i),CCFadeIn:create(0.5)))
                    end
                end
            elseif self.fadeIn then
                for i=1,#self.nodes do
                    self.nodes[i]:getSprite():runAction(CCSequence:createWithTwoActions(
                    CCDelayTime:create(0.05 * i),CCFadeIn:create(0.5)))
                end
            end
        end,
        onExit = function(self)
            -- Remove the sprites from the batch node
            for _,sprite in pairs(self.sprites) do
                sprite:removeFromParentAndCleanup(true)
            end
        end
    }
    chain.fadeIn = p.fadeIn == nil and true or p.fadeIn
    -- Start trajectory projection
    self:createTrajectoryDots()
    local function computeLaunchVelocity()
        -- Get the mouse joint reaction force
        local force = self.touch:getReactionForce(-50) -- multiplied inverted reaction force
        -- avoid downward force (y <=0 ) and requires a minimum force on the
        -- chain (0.2) or the player would be able to throw the hero horizontally with too much force
        if force.y <= 0.2 then return nil end
        -- Get the desired trajectory distance
        local distance = pix2d.Physics:unitToMeter(
        force.x * p.projection[1], force.y * p.projection[2])
        -- Project vertical velocity for height
        local vy = physics:calculateVerticalVelocityForHeight(distance.y)
        -- Project vertical velocity for width
        local vx = distance.x / physics:getTimestepsToTop(b2Vec2(0,vy)) * 60;
        return b2Vec2(vx,vy)
    end
    local function setTrajectoryDotsPosition(velocity)
        local startpos = self.player:getBodyCenter()
        for i=1,10 do
            local pos = pix2d.Physics:meterToPixel(physics:getTrajectoryPoint(startpos,velocity,i*5))
            level.dots[i]:setPosition(pos.x,pos.y)
        end
    end
    local function isTouchingChain()
        for _,node in ipairs(chain.nodes) do
            if node.isTouching then return true end
        end
        return false
    end
    local function projectTrajectory(showDots)
        if isTouchingChain() then -- if the player is actually touching one of the chain's nodes
            local v = computeLaunchVelocity()
            if v then -- if there is a velocity (can be avoid if downward)
                setTrajectoryDotsPosition(v)
                level.dotsNode:setVisible(showDots)
                return v
            end
        end
        level.dotsNode:setVisible(false)
        return nil
    end
    -- End trajectory projection
    -- Touch handler on every node
    local function touchHandler(e,t)
        if e == 'begin' then
            -- Set specific mouse joint parmeters for the chain
            self.touch:setMouseJointMaxForce(p.mouseMaxForce or self.defaultTouchForce)
            self.touch:setMouseJointFrequency(p.mouseFrequency or self.defaultTouchFrequency)
            projectTrajectory(true)
            return true
        elseif e == 'moved' then
            projectTrajectory(true)
        elseif e == 'ended' or e == 'canceled' then
            level.dotsNode:setVisible(false)
            -- Reset the mouse joint parameters to defaults
            self.touch:setMouseJointMaxForce(self.defaultTouchForce)
            self.touch:setMouseJointFrequency(self.defaultTouchFrequency)
            -- Check that the player is actually touching one of the chain's nodes
            local v = projectTrajectory(false)
            if v then
                if math.abs(v.x) > 3 or math.abs(v.y) > 3 then
                    audio:playEffect(settings.audio['swish'..math.floor(math.random(2))])
                end
                self.player:setLinearVelocity(v)
            end
        end
    end
    -- Chain tuning parameters
    local count = p.count or 5 -- Total number of chain's nodes
    local no = p.overlap or 0.1 -- node overlaping percent
    local density = p.density or 1.0 -- nodes individual density. Small density might leads to the player passing through the chain
    local sensorHeight = p.sensorHeight or 0.5
    local height = p.height or 0.1 -- rope nodes height
    p.movable = p.movable == nil and true or p.movable
    -- end parameters
    local noc = no / 2 -- Overlaping center. That's where the node will be joint using a revolute joint
    local p1 = ccp(p.startpos[1],p.startpos[2])
    local p2 = ccp(p.endpos[1],p.endpos[2])
    local length = ccpDistance(p1,p2) -- Chain's length in map unit
    local size = { (length / count) * (1 + no), height } -- Node's size in map unit. Each node is made `no` percent bigger.
    local width = size[1]
    local centerX = width / 2
    local offsetX = width * (1 - no) -- Next node position
    local anchorOffsetX = width * (0.5 - noc) -- Next node anchor position
    local prev = nil -- previous node (and the last one when the loop's done)
    local first = nil -- first node of the chain
    local sensors = {} -- list of sensors. Empty if the chain is not movable
    -- Create the chain's nodes until `count`
    for i=0,count-1 do
        -- Box position is the center of the box but we want the chain to start
        -- at the givent start position (p1.x) so we start at p1.x then we shift
        -- the node of its half width (centerX). Then we move to the next node
        -- position (offsetX * i)
        local x = p1.x + centerX + (offsetX *i)
        local node = class.extend {
            instance = factory:box {
                uid = 1,
                size = size,
                density = density,
                position = { x, p1.y }, -- We create a linear chain. The actual position is set later.
                body_type = physics.DynamicBody,
                -- Collide only with player and platform by default
                mask = p.mask or bit.bor(physics.category.player,physics.category.platform),
                category = physics.category.platform,
                group = physics.group.chain, -- Chain nodes don't collide with other chain nodes
                friction = 1.0,
                restitution = 1.0,
                frame = p.frame,
            },
            onExit = function(self)
                level.contact:cancelCollisionNotification(self)
                level.contact:cancelEndCollisionNotificationScritpWithTag(self,level.tag.player)
            end
        }
        -- Track weither the player is touching or not this node
        node.isTouching = false
        self.contact:registerCollisionNotificationScriptWithTag(function()
            node.isTouching = true
        end,node,self.tag.player)
        self.contact:registerEndCollisionNotificationScriptWithTag(function()
            node.isTouching = false
        end,node,self.tag.player)
        if p.movable then
            -- Create the node's sensor
            local sensor = class.extend {
                instance = factory:box {
                    uid = 1,
                    size = { width, sensorHeight },
                    position = {x, p1.y},
                    density = 0.1, -- Do not set a density too small or sensors might not be able to move the chain
                    body_type = physics.DynamicBody,
                    category = physics.category.noCollision,
                    sensor = true,
                },
                onExit = function(self)
                    level.touch:cancelTouchDelegate(self)
                end
            }
            level:createTouchGrabberSprite {
                target = sensor, frame = 'grabber_circle.png', scale = {2,2}, callback = touchHandler
            }
            -- Joint sensor and chain's node
            physics:createRevoluteJointWithLimit(node,sensor,node:getBodyCenter(),0,0)
            physics:addNode(sensor)
            table.insert(sensors,sensor)
        end
        if prev then
            -- Joint previous and current chain nodes
            physics:createRevoluteJointWithAnchor(node,prev,pix2d.Physics:unitToMeter(x - anchorOffsetX,p1.y))
        else
            first = node
        end
        prev = node
        -- Create the chain sprite
        if p.batch then
            -- local s = pix2d.Physics:unitToPixel(width * (1 - noc),size[2])
            local s = pix2d.Physics:unitToPixel(width * (1 - (no * 0.4)),size[2])
            local sprite = util.createBatchSprite(self.batch[p.batch],s.x,s.y,true)
            table.insert(chain.sprites,sprite)
            -- if p.color then sprite:setColor(ccc3(p.color[1],p.color[2],p.color[3])) end
            -- Batch sprites are not visible if fade in is enabled
            if chain.fadeIn then sprite:setOpacity(0) end
        else
            node:getSprite():setOpacity(0)
        end
        chain:addChild(node)
        table.insert(chain.nodes,node)
    end
    if p.close then
        local x = p1.x - offsetX + centerX
        local pos = pix2d.Physics:unitToMeter(x, p1.y)
        prev:setBodyPosition(pos.x,pos.y)
        physics:createRevoluteJointWithAnchor(first,prev,pix2d.Physics:unitToMeter(x + anchorOffsetX,p1.y))
    end
    -- Set the nodes original position and angle
    if p.initialize == nil and true or p.initialize then
        local p1 = pix2d.Physics:unitToMeter(p1.x,p1.y)
        local p2 = pix2d.Physics:unitToMeter(p2.x,p2.y)
        p1 = ccp(p1.x,p1.y)
        p2 = ccp(p2.x,p2.y)
        local dt = 1 / count
        local t = dt / 2 -- start a half time (center of the node)
        local pp = ccpLerp(p1,p2,0) -- previous position
        for i,node in ipairs(chain.nodes) do
            local pos = ccpLerp(p1,p2,t)
            node:setBodyPosition(pos.x,pos.y)
            node:setBodyRotation(math.atan2(pos.y - pp.y,pos.x - pp.x))
            -- We must set the node position and rotation manually here because batch
            -- sprites are updated using node's position/rotation, not the physic body
            -- rotation but the CCNode position/angle which are not set when we use batch
            -- (it's node manually when we define a sprite/frame)
            node:setPosition(pix2d.Physics:meterToPixel(pos.x,pos.y))
            node:setRotation(-1 * math.deg(node:getAngle()))
            if p.movable then
                sensors[i]:setBodyPosition(pos.x,pos.y)
                sensors[i]:setBodyRotation(node:getAngle())
            end
            t = t + dt
            pp = pos
        end
    end
    -- Create the anchors body if requested (true by default)
    p.anchors = p.anchors == nil and true or p.anchors
    if p.anchors then
        for i=1,2 do
            self:createAnchor {
                target = (i == 1) and first or prev,
                position = (i == 1) and { p.startpos[1]-0.5+(width * noc), p.startpos[2]-0.5 }
                or { p.endpos[1]-0.5-(width * noc), p.endpos[2]-0.5 },
            }
        end
    end
    physics:addNode(chain,self.zorder.chain)
    return chain
end

function Level:createCircleBody(p)
    local circle = factory:circle(p)
    physics:addNode(circle)
    return circle
end

function Level:createBoxBody(p)
    p.category = physics.category.platform
    local box = factory:box(p)
    local size = pix2d.Physics:unitToPixel(p.size[1]/2,p.size[2]/2)
    physics:addNode(box,p.zorder or 0,p.tag or 0)
    return box
end

function Level:createBeachBall(p)
    local level = self
    local ball = class.extend {
        instance = self:createCircleBody(p),
        onEnter = function(self)
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                self:runAction(CCSequence:createWithTwoActions(
                    CCEaseBackOut:create(CCScaleTo:create(0.1,1.1)),CCEaseBackOut:create(CCScaleTo:create(0.1,1))))
                audio:playEffect(settings.audio.boing)
            end,self,level.tag.player)
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    if p.path then
        self:createPathAction(p.path,ball)
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(ball) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(ball) end)
    end
end

-- Parameters
-- restitution: trampoline vertical restitution in map unit (e.g. restitution = 2 will push the player up to 2 map unit)
-- movable
-- angle
-- position
function Level:createTrampoline(p)
    local level = self
    p.body_type = p.movable and physics.DynamicBody or physics.KinematicBody
    position = assert(p.position)
    p.restitution = p.restitution or 2
    p.uid = p.uid or 0
    p.size =  { 1, 0.25 }
    p.sensor = true
    p.position = { p.position[1] + 0.5, p.position[2] + 0.5 }
    local box = class.extend {
        instance = factory:box(p),
        onEnter = function(self)
            local restitution = pix2d.Physics:unitToMeter(p.restitution,0).x
            level.contact:registerCollisionNotificationScriptWithTag(function(c)
                local mass = c.nodeB:getMass()
                local dv = physics:calculateVerticalVelocityForHeight(restitution)
                c.nodeB:setLinearVelocity(self:getWorldVector(b2Vec2(0,dv)))
                self:getSprite():runAction(CCSequence:createWithTwoActions(
                    CCEaseBackOut:create(CCScaleTo:create(0.1,0.8,1.1)),CCEaseBackOut:create(CCScaleTo:create(0.1,1))))
                audio:playEffect(settings.audio.boing)
            end,self,level.tag.player)
        end,
        onExit = function(self)
            level.contact:cancelCollisionNotification(self)
        end
    }
    -- Add the umbrella leg
    if p.addSprite then
        box:getSprite():addChild(self:createSprite(p.addSprite))
    end
    if p.movable then
        level:createRotationalTouchGrabber {
            position = position,
            target = box,
            radius = 1,
            -- anchor = anchor,
        }
    elseif p.path then
        self:createPathAction(p.path,box)
        mediator:subscribe(mediator.ns.pauseGameplay,function(e) actionManager:pauseTarget(box) end)
        mediator:subscribe(mediator.ns.resumeGameplay,function(e) actionManager:resumeTarget(box) end)
    end
    physics:addNode(box,self.zorder.platform)
end

-- Parameters
-- startpos:
-- endpos:
-- count: number of ropes attached to the chain
-- speed: motor speed in degree per second (90 by default)
function Level:createPlatterLift(p)
    local radius = 0.25
    local startpos = ccp(p.startpos[1],p.startpos[2])
    local endpos = ccp(p.endpos[1],p.endpos[2])
    -- Approximate a circle with cubic Bézier curves
    -- http://spencermortensen.com/articles/bezier-circle/
    -- P_0 = (0,1), P_1 = (c,1), P_2 = (1,c), P_3 = (1,0)
    -- P_1 = (1,0), P_1 = (1,-c), P_2 = (c,-1), P_3 = (0,-1)
    -- P_2 = (0,-1), P_1 = (-c,-1), P_3 = (-1,-c), P_4 = (-1,0)
    -- P_3 = (-1,0), P_1 = (-1,c), P_2 = (-c,1), P_3 = (0,1)
    local c = 0.55191502449
    local arc = {
        ccp(0,1),  ccp(c,1),   ccp(1,c),   ccp(1,0),   -- P0
        ccp(1,0),  ccp(1,-c),  ccp(c,-1),  ccp(0,-1),  -- p1
        ccp(0,-1), ccp(-c,-1), ccp(-1,-c), ccp(-1,0),  -- p2
        ccp(-1,0), ccp(-1,c),  ccp(-c,1),  ccp(0,1),   -- P3
    }
    -- get angle of end position and origin (must transpose end position to origin first)
    local angle = ccpToAngle(ccpSub(endpos,startpos))
    -- rotate,transpose and scale the four circle quadrants
    -- first two quadrants are translated to endpos. The other two to startpos
    for i=1,16 do
        arc[i] = ccpRotateByAngle(arc[i],ccp(0,0),angle)
        arc[i] = ccpMult(arc[i],radius * 1.1)
        arc[i] = ccpAdd(i > 8 and startpos or endpos,arc[i])
    end
    local _path = {}
    for i=1,16,4 do table.insert(_path,Bezier():initWithPoints(arc[i],arc[i+1],arc[i+2],arc[i+3])) end
    -- Draw the chain using CCDrawNode
    --[[
    local precision = 0.05
    local dt = 1 / ((math.pi * radius * 0.5) / precision) -- circle quadrant length
    local points = {}
    for i=1,#_path do
        for t=0,1,dt do
            local x,y = _path[i]:pointAt(t)
            table.insert(points,x)
            table.insert(points,y)
        end
    end
    self:loadPolygon { points = points, fillColor = {0,0,0,0}, borderWidth = 1, borderColor = {255,0,0,255} }
    --]]
    ---[[
    -- Add two lines to connect both arcs. We use linear bezier curves to simulate lines.
    table.insert(_path,3,Bezier():lineToBezier(arc[8].x,arc[8].y,arc[9].x,arc[9].y))
    table.insert(_path,6,Bezier():lineToBezier(arc[16].x,arc[16].y,arc[1].x,arc[1].y))
    -- Create the actual chain
    local lengthQuad = math.pi * radius * 0.5 -- Circle quadrant length
    local length = (lengthQuad * 4) + (ccpDistance(arc[8],arc[9]) * 2)
    -- We MUST set the node's width to half quadrant (that is two nodes per quadrants). See below
    local nodeWidth = lengthQuad * 0.5
    local count = math.ceil(length / nodeWidth)
    local chain = self:createChain {
        batch = p.chainBatch,
        sprite = p.chainSprite,
        color = p.color,
        count = count,
        density = 0.1, -- Should not be too big or the chain might break
        height = 0.1,
        fadeIn = p.fadeIn,
        mouseMaxForce = 0,
        overlap = 0.2,
        projection = {0,0},
        movable = false,
        anchors = false, -- do not create any anchors
        startpos = p.startpos,
        endpos = { p.startpos[1] + length, p.startpos[2] },
        initialize = true,
        mask = physics.category.platform,
        close = true,
    }
    -- Set the chain initial position and rotation
    -- We must set ALL nodes positions or the chain will not wrap the wheels completely
    -- There's exactly 2 nodes per quadrant (as we defined the node width as half quadrant length)
    -- So there's count - 8 nodes left to set on the two lines. We ensure that no nodes are left
    -- by checking if `count` is odd.
    local lineCount1, remain = math.modf((count - 8) / 2)
    local lineCount2 = remain > 0 and lineCount1 + 1 or lineCount1
    local dt = { 2, 2, lineCount1, 2, 2, lineCount2 }
    local j = 1
    for i=1,#_path do
        for t=1, dt[i] do
            local tt = t / dt[i]
            local x,y = _path[i]:pointAt(tt)
            local dx,dy = _path[i]:derivativeAt(tt)
            local angle = ccpToAngle(ccp(dx,dy))
            --[[
            -- Draw debug dots
            local pos = pix2d.Physics:unitToPixel(x,y)
            self.draw:drawDot(pos,1,ccc4f(0,1,0,1))
            --]]
            local pos = pix2d.Physics:unitToMeter(x,y)
            local node = assert(chain.nodes[j])
            -- if not node then print("WARNING not enough nodes"); break end
            node:setBodyPosition(pos.x,pos.y)
            node:setBodyRotation(angle)
            node:setPosition(pix2d.Physics:meterToPixel(pos.x,pos.y))
            node:setRotation(-1 * math.deg(angle))
            j = j + 1
        end
    end
    assert(count == j - 1)
    -- print(count,j-1)
    -- Create the two wheels
    ---[[
    for i=1,2 do
        local position = i==1 and p.startpos or p.endpos
        position = { position[1] - 0.5, position[2] - 0.5 }
        local wheel = class.extend {
            instance = factory:circle {
                uid = 1,
                radius = radius * 0.9,
                position = position,
                body_type = physics.DynamicBody,
                frame = p.wheelFrame,
                mask = physics.category.platform,
                category = physics.category.platform,
            },
        }
        physics:addNode(wheel)
        local anchor,joint = self:createAnchor { target = wheel, position = position }
        joint:EnableMotor(true)
        joint:SetMotorSpeed(math.rad(p.speed or 90))
        joint:SetMaxMotorTorque(2000)
    end
    --]]
    for i=1,#p.ropes do
        local j = math.floor((count-1) * p.ropes[i]) + 1
        local pos = pix2d.Physics:meterToUnit(chain.nodes[j]:getBodyCenter())
        pos.x = pos.x - 0.5
        pos.y = pos.y - 0.5
        local anchor = class.extend {
            instance = factory:circle {
                uid = 1,
                radius = 0.25,
                category = physics.category.noCollision,
                --sensor = true,
                position = { pos.x, pos.y },
                body_type = physics.KinematicBody,
                density = 10,
            },
            ---[[
            update = function(self,dt)
                local pos = chain.nodes[j]:getBodyCenter()
                self:setBodyPosition(pos.x,pos.y)
            end
            --]]
        }

        physics:addNode(anchor)
        local rope = self:createRope {
            uid = 1,
            startpos = { pos.x, pos.y },
            endpos = { pos.x, pos.y -1 },
            anchor = 'cloud.png',
            hook = 'lollipop.png',
            batch = 'balloon_rope.png',
            anchorDensity = 0.1,
            hookDensity = 1.0, -- Do not set to low
        }
        rope:getAnchor():setBodyType(physics.DynamicBody)
        -- In order to stablize the rope we have to enforce the distance between
        -- the kinematic anchor and ALL rope's components (hook,sensor and inner sensor)
        physics:createRevoluteJoint(rope:getAnchor(),anchor)
        physics:createRopeJoint(anchor,rope:getSensor())
        physics:createRopeJoint(anchor,rope:getInnerSensor())
        physics:createRopeJoint(anchor,rope:getHook())
    end
end

function Level:createIceGround(p)
    p.category = physics.category.platform
    p.zorder = self.zorder.iceGround
    local chain = factory:chain(p)
    physics:addNode(chain)
end

function Level:createTrajectoryDots()
    if not self.dots then
        self.dots = {}
        self.dotsNode = CCNode:create()
        physics:layer():addChild(self.dotsNode,self.zorder.dots)
        for i=1,10 do
            local sprite = CCSprite:createWithSpriteFrameName('dot.png')
            table.insert(self.dots,sprite)
            self.dotsNode:addChild(sprite)
        end
        self.dotsNode:setVisible(false)
    end
end

function Level:createRedrawNode()
    if not self.redrawNode then
        local draw = pix2d.DrawNode:create()
        draw:scheduleUpdateWithPriorityLua(function(dt)
            draw:clear()
            draw:drawDot(ccp(-100,-100),1,ccc4f(0,0,0,0)) -- Must not be empty or it will be buggy on android
        end,-1) -- Schedule update with lower priority (will be called before the other update)
        physics:layer():addChild(draw,self.zorder.drawNode)
        -- Dummy draw to avoid a bug on android if CCDrawNode is empty
        draw:drawDot(ccp(-100,-100),1,ccc4f(0,0,0,0))
        self.redrawNode = draw
    end
end

function Level:createElasticRope(p)
    local multiplier = 40 -- Rope reaction force multiplier
    local enabled = true
    p.sprite = nil
    p.frame = nil -- make sure we don't use any sprite on the physic nodes
    p.sensor = true
    p.radius = 0.25
    p.zorder = self.zorder.player + 1
    p.category = physics.category.sensor
    p.mask = physics.category.player
    self:createRedrawNode()
    -- Create the core sensor
    local core = factory:circle(p)
    self:createTrajectoryDots()
    local function setTrajectoryDotsPosition(velocity)
        local startpos = self.player:getBodyCenter()
        for i=1,10 do
            local pos = pix2d.Physics:meterToPixel(physics:getTrajectoryPoint(startpos,velocity,i*5))
            self.dots[i]:setPosition(pos.x,pos.y)
        end
    end
    local pivot = ccp(core:getPosition())
    -- Create the sprite
    local carabiner = CCSprite:createWithSpriteFrameName('carabiner.png')
    carabiner:setAnchorPoint(ccp(0.5,0.5))
    carabiner:setPosition(pivot)
    physics:layer():addChild(carabiner)
    -- Release joint function
    local joint = nil -- Distance joint between the player and the core sensor
    local function releasePlayerFromRope()
        if joint then
            self.dotsNode:setVisible(false)
            physics:removeJoint(joint)
            joint = nil
            self.player:movable(false)
            --self.redrawNode:clear()
            core:unscheduleUpdate()
            -- self.player:setCollisionMask(mask)
            self.touch:cancelTouchDelegate(self.player)
        end
    end
    -- We must release the player from the elastic when teleported (see level S04E11)
    mediator:subscribe(mediator.ns.teleported,function(e,mp,pp)
        releasePlayerFromRope()
        self.touch:destroyMouseJoint() -- BUG fix: Release the mouse joint or the player still be movable once teleported
    end)

    -- local category, mask, group = self.player:getCollisionFilter()
    self.contact:registerCollisionNotificationScriptWithTag(function(c)
        if not enabled then return end
        enabled = false
        local player = c.nodeB
        -- player:setCollisionMask(physics.category.sensor)
        local y = 2 - (carabiner:getContentSize().height / 2)
        core:scheduleUpdateWithPriorityLua(function()
            -- self.redrawNode:clear()
            local pos = ccp(player:getPosition())
            carabiner:setRotation(-90 - math.deg(ccpToAngle(ccpSub(pos,pivot))))
            self.redrawNode:drawSegment(pos,carabiner:convertToWorldSpaceAR(ccp(0,y)),1,ccc4f(0,0,0,0.5))
        end,1)
        joint = physics:createDistanceJointWithLength(core,player,0.05,3.8,0.1)
        player:setAngularVelocity(0)
        player:setLinearVelocity(b2Vec2(0,0))
        self:createTouchGrabberSprite {
            target = player, frame = 'grabber_circle.png', scale = {2,2},
            callback = function(e,t)
                -- touch handler might have been removed but this method can still
                -- be called until it's actually removed so we have to check joint still exists
                if not joint then return end
                if e == 'moved' then
                    setTrajectoryDotsPosition(joint:GetReactionForce(multiplier))
                    self.dotsNode:setVisible(true)
                elseif e == 'ended' or e == 'canceled' then
                    local v = joint:GetReactionForce(multiplier)
                    if math.abs(v.x) > 3 or math.abs(v.y) > 3 then
                        audio:playEffect(settings.audio['swish'..math.floor(math.random(2))])
                    end
                    player:setLinearVelocity(v)
                    releasePlayerFromRope()
                end
            end
        }
    end,core,self.tag.player)
    -- Outter sensor
    p.radius = 1
    local shell = factory:circle(p)
    self.contact:registerEndCollisionNotificationScriptWithTag(function(c)
        enabled = true
    end,shell,self.tag.player)
    -- Add the sensors
    physics:addNode(core)
    physics:addNode(shell)
    -- mediator:subscribe(mediator.ns.teleported,releasePlayerFromRope)
end

function Level:loadBoundary(p)
    -- boundady tag is set in host code
    physics:addNode(pix2d.Boundary:create(CCRectMake(p.position[1],p.position[2],p.size[1],p.size[2])))
end

function Level:registerEvents()
    -- Add lost level animation
    mediator:subscribe(mediator.ns.lose,function(e,pl)
        physics:pause()
        physics:layer():setTouchEnabled(false)
        audio:playEffect(settings.audio['lose'..math.floor(math.random(2))])
        local player = self.player
        anim:runAnimation {
            sprite = player:getSprite(),
            repeatForever = true,
            delay = 0.2,
            frames = { 'anim_lose_1.png', 'anim_lose_2.png' }
        }
        -- player:getSprite():setScale(0.5)
        if player:getPositionY() < 0 or player:getPositionY() > visiblerect:top().y then
            local script = nil
            script = scheduler:scheduleScriptFunc(function()
                scheduler:unscheduleScriptEntry(script)
                mediator:publish(mediator.ns.resetLevelScene,{ blink = true })
            end, 0.5, false)
        else
            -- physics:layer():runAction(CCFollow:create(player))
            -- physics:layer():runAction(CCEaseOut:create(CCScaleTo:create(1.5,2.0),5))
            -- self.backgroundLayer:runAction(CCEaseOut:create(CCScaleTo:create(1.5,1.5),5))
            mediator:publish(mediator.ns.showLoseScene,player:getPosition())
        end
    end)

    -- Pause gameplay
    mediator:subscribe(mediator.ns.pauseGameplay,function(_)
        physics:pause()
        physics:layer():setTouchEnabled(false)
    end)
    -- Resume gameplay
    mediator:subscribe(mediator.ns.resumeGameplay,function(_)
        if self.gameHasStarted then
            physics:resume()
            physics:layer():setTouchEnabled(true)
            -- pix2d.NodeUtil:resumeSchedulerAndActions(self.backgroundLayer)
            -- pix2d.NodeUtil:resumeSchedulerAndActions(physics:layer())
        end
        self.backgroundLayer:setVisible(true)
        physics:layer():setVisible(true)
        mediator:publish(mediator.ns.gameplayResumed)
    end, { priority = 99 })

    mediator:subscribe(mediator.ns.gameplayPaused, function()
        -- Save rendering the background and physics layer
        -- pix2d.NodeUtil:pauseSchedulerAndActions(self.backgroundLayer)
        -- pix2d.NodeUtil:pauseSchedulerAndActions(physics:layer())
        self.backgroundLayer:setVisible(false)
        physics:layer():setVisible(false)
    end, { priority = 99 })

    mediator:subscribe(mediator.ns.win,function()
        physics:pause()
        local script = nil -- local script = scheduler:scheduleScriptFunc(...) will not work
        script = scheduler:scheduleScriptFunc(function()
            mediator:publish(mediator.ns.pauseGameplay)
            self.hud:createScoreMenu(physics:getScene(),self.score)
            scheduler:unscheduleScriptEntry(script)
        end,0.8,false)
        self.player:addChild(CCSprite:createWithSpriteFrameName('win.png'),self.zorder.player_anim)
        -- hack to set the child to the same color if the player has not the
        -- default color (for instance in a shadow. See createShadowSensor)
        self.player:setColor(self.player:getColor())
        -- player:runAction(CCRepeatForever:create(CCEaseElasticOut:create(CCRotateTo:create(0.5,0.0))))
        audio:playEffect(settings.audio.chime1)
     end)

    mediator:subscribe(mediator.ns.updateScore,function(_,score)
        self.score = self.score + score
        audio:playEffect(settings.audio['coin'..self.score])
    end)

    mediator:subscribe(mediator.ns.tool_focus_ended,
    function(event,tool,cx,cy,r,t,x,y)
        if tool == 'block' then
            local ground = physics:layer():getChildByTag(self.tag.ground)
            assert(ground,"ERROR: Can't add block because no ground found!")
            local vertices = mapIndexToVertices { cx, cy }
            self:extendTexture(ground,vertices)
        elseif tool == 'rope' then
            local p = util.shallowcopy(self.data.tools.rope.meta)
            p.uid = 9
            p.startpos = { cx, cy + 1 }
            p.endpos =   { cx, cy }
            self:createRope(p)
        elseif tool == 'balloon' then
            local p = util.shallowcopy(self.data.tools.balloon.meta)
            p.startpos = {cx, cy + 1 }
            p.endpos = { cx, cy }
            p.uid = 10
            self:createPlayerBalloon(p)
        elseif tool == 'fan' then
            local p = util.shallowcopy(self.data.tools.fan.meta)
            p.position = { cx, cy }
            p.center = { p.position[1] + 0.5, p.position[2] + 0.5 } -- add an half unit to get the unit's center
            self:loadFan(p)
        elseif tool == 'cardboard' then
            local p = util.shallowcopy(self.data.tools.cardboard.meta)
            p.position = { cx + 0.5, cy +0.5 } -- center
            self:createCardboard(p)
        elseif tool == 'teleport' then
            local p = util.shallowcopy(self.data.tools.teleport.meta)
            p.position = { cx, cy }
            self:createTeleport(p)
        elseif tool == 'trampoline' then
            local p = util.shallowcopy(self.data.tools.trampoline.meta)
            p.position = { cx, cy }
            self:createTrampoline(p)
        elseif tool == 'elastic' then
            local p = util.shallowcopy(self.data.tools.elastic.meta)
            p.position = { cx, cy }
            self:createElasticRope(p)
        ---[[ DEPRECATED
        elseif tool == 'freehand' then
            self:createFreehandGround(self.touches)
        --]]
        else
            assert(false,'Unknown tool name',tool)
        end
        self.hud:consume(tool,1)
    end)
end

function Level:init(manager,param)
    self.manager = manager
    self.data = self.manager.level_data
    self.hud = self.manager.hud

    -- Call the garbage collector so it should not be called while playing the level
    util.collectGarbage()

    -- Copy level's parameters passed from the manager.
    if param then
        self.param.blink = param.blink or self.param.blink
    end

    -- Release background music if not enabled
    if not settings.musicEnabled then
        audio:stopBackgroundMusic(true)
    end

    -- mobdebug.on()
    assert(physics,'global physics variable not set')
    self.touch = physics:touchListener()
    self.touch:setMouseJointMaxForce(self.defaultTouchForce) -- Set mouse joint max force (if not set, default is 100.0)

    self.contact = physics:contactListener()
    assert(self.contact,'no physics contact listener')
    -- The draw node
    self.draw = pix2d.DrawNode:create()
    physics:layer():addChild(self.draw,self.zorder.drawNode)
    -- Dummy draw to avoid a bug on android if CCDrawNode is empty
    self.draw:drawDot(ccp(-100,-100),1,ccc4f(0,0,0,0))
    -- increment Lua tags with the C++ max tag value
    local maxtag = pix2d.PhysicNode.maxtag
    for k, v in pairs(self.tag) do
        self.tag[k] = maxtag + v
    end

    -- Load custom scripts. Script filename must not contain extention (.lua)
    if self.data.scripts then
        self.customScripts = {}
        for _,script in ipairs(self.data.scripts) do
            table.insert(self.customScripts, require (script)():init(self))
        end
    end

    -- Load batch node to the cache
    if self.data.assets.batch then
        for _,filename in ipairs(self.data.assets.batch) do
            local batch = CCSpriteBatchNode:create(filename) -- TODO initial batch capacity
            self.batch[filename] = batch
            physics:layer():addChild(batch,self.zorder.batch)
        end
    end
    -- Load the batch particles to the cache
    if self.data.assets.particleBatch then
        for _,filename in ipairs(self.data.assets.particleBatch) do
            self.particleBatch[filename] = CCParticleBatchNode:create(filename,200)
            physics:layer():addChild(self.particleBatch[filename],self.zorder.batchParticle)
        end
    end
    physics:layer():setTag(self.tagLayer.physics)
    -- Must create the background layer BEFORE loading the level graph
    self.backgroundLayer = CCLayer:create()
    physics:getScene():addChild(self.backgroundLayer,self.zorder.layer.background,self.tagLayer.background)
    -- Map the level entities type to a create functions
    local func_map = {
        background = self.loadBackgroundLayer,
        sprite = self.loadSprite,
        texture = self.loadTexture,
        scrollingTexture = self.loadScrollingTexture,
        ground = self.loadGround,
        player = self.createPlayer,
        coins = self.loadCoins, -- bundle loading coins
        coin = self.loadCoin, -- load coin one by one
        rope = self.createRope,
        balloon = self.createPlayerBalloon,
        target = self.createTarget,
        dancingSprite = self.createDancingSprite,
        slider = self.loadSlider,
        polygon = self.loadPolygon,
        line = self.loadLine,
        lines = self.loadLines,
        infiniteSprite = self.loadInfiniteScrollingSprite,
        bad = self.createBad,
        spear = self.createSpear,
        boundary = self.loadBoundary,
        fan = self.loadFan,
        floatingPlatform = self.createFloatingPlatform,
        cardboard = self.createCardboard,
        chain = self.createChain,
        teleport = self.createTeleport,
        circle = self.createCircleBody,
        box = self.createBoxBody,
        textureBody = self.loadTextureBody,
        beachBall = self.createBeachBall,
        trampoline = self.createTrampoline,
        platterLift = self.createPlatterLift,
        iceGround = self.createIceGround,
        elasticRope = self.createElasticRope,
        shadow = self.createShadowSensor,
        moon = self.loadMoon,
        -- light = self.loadLight,
    }
    -- Call the create function for each level entities
    for _,p in ipairs(self.data.graph) do
        local func = func_map[p.type]
        if func then
            -- self:func(p) is not valid because it will attempt to
            -- call the function named `func` which does not exists in self (aka Hud)
            func(self,p)
        elseif self.customScripts then
            for i=1,#self.customScripts do
                if self.customScripts[i].onLoadEntity then self.customScripts[i]:onLoadEntity(p) end
            end
        else
            print('WARNING: Unknown entity create procedure:',p.type)
        end
    end
    self:registerEvents()
    -- Add the grid and the hud
    if self.manager.grid then
        physics:getScene():addChild(self.manager.grid.layer,self.zorder.layer.grid,self.tag.grid)
    end
    physics:getScene():addChild(self.manager.hud.layer,self.zorder.layer.hud,self.tag.hud)

    -- Call onLevelLoaded on custom scripts
    if self.customScripts then
        for i=1,#self.customScripts do
            if self.customScripts[i].onLevelLoaded then self.customScripts[i]:onLevelLoaded() end
        end
    end

    -- Pause the gameplay on entering the scene.
    -- Kinematic actions (e.g. bad moving on a path using MoveTo action) are
    -- paused using CCActionManager::pauseTarget but actions are all started
    -- on entering the scene. Therefore we have to pause the gameplay after
    -- the onEnter event.
    -- Note that if we do want to perform the very first physic step we have to
    -- call physics:pause() here.
    -- physics:pause()
    -- We call pauseGameplay bedore AND after the onEnter event so the Hud is
    -- disabled too when entering the scene
    mediator:publish(mediator.ns.pauseGameplay)
    physics:layer():addChild(class.extend {
        instance = CCNode:create(),
        level = self,
        update = function(self,dt)
            if not self.level.gameHasStarted then mediator:publish(mediator.ns.pauseGameplay) end
            self:unscheduleUpdate()
            -- self:removeFromParentAndCleanup(true)
        end,
        onExit = function(self)
            -- print 'Unschedule scripts..'
            for _,script in ipairs(self.level.scheduledScripts) do
                director:getScheduler():unscheduleScriptEntry(script)
            end
        end
    })

    --[[
    -- Capture all levels
    physics:layer():addChild(class.extend {
        level = self,
        instance = CCNode:create(),
        update = function(self)
            self:unscheduleUpdate()
            local levelid,seasonid = self.level.manager:getCurrentLevelId()
            util.captureScreen(('S%02dE%02d.png'):format(seasonid,levelid))
            mediator:publish(mediator.ns.runNextLevel)
        end
    })
    --]]

    if settings.platform == kTargetAndroid then
        physics:layer():setKeypadEnabled(true)
        physics:layer():registerScriptKeypadHandler(function(key)
            if key == "backClicked" then mediator:publish(mediator.ns.runMainMenuScene,5) end
        end)
    end

    -- Check network reachability. Only implemented on iOS for now
    --[[
    local checkNetworkReachabilityLayer = function()
        local layer = CCLayer:create()
        layer:registerScriptTouchHandler(function(e,x,y)
            return true
        end,false,kCCMenuHandlerPriority-3,true)
        layer:setTouchEnabled(true)
        local item = util.createMenuItem('button_ok.png')
        item:registerScriptTapHandler(function()
            if pix2d.Native:getInstance():checkNetworkReachable() then
                showAdScreen()
                layer:removeFromParentAndCleanup(true)
            end
        end)
        local menu = CCMenu:create()
        menu:setTouchPriority(kCCMenuHandlerPriority -4)
        menu:addChild(item)
        layer:addChild(menu)
        physics:getScene():addChild(layer)
    end
    --]]

    -- Pause/resume director and background music on Ad show/hide
    pix2d.Native:getInstance():registerAdMobScriptHandler(function(event)
        if event == 'adsWillShow' then
            if audio:isBackgroundMusicPlaying() then
                audio:pauseBackgroundMusic()
            end
            director:pause();
        elseif event == 'adsWillHide' then
            if settings.musicEnabled then
                audio:resumeBackgroundMusic()
            end
            director:resume();
            adClock = os.time()
        end
    end)
    if not adClock then adClock = os.time() end
    local curTime = os.time()
    -- print('DEBUG ad: clock',adClock,curTime,curTime - adClock)
    if curTime - adClock > 600 then -- Ad timer is set to 10 minutes
        -- print 'DEBUG ad: show ad'
        if pix2d.Native:getInstance():showAd() then
            -- print 'DEBUG ad: reset ad timer'
            adClock = nil
        end
        if settings.platform == kTargetMacOS and settings.showCase then
            local label = util.label(self.manager.i18n('getMobileApp'),0,100)
            local layer, node = util.dialog(kCCMenuHandlerPriority -3, visiblerect:sizeAt(0.8,0.8),'ok',function(e,layer,node)
                settings.showCase = false
                settings:saveUserSettings()
                return true
            end,ccc4(28,28,28,128))
            local googleplay = util.createCustomMenuItemWithSprite('desktop/googleplay.png',nil,nil,function()
                pix2d.Native:getInstance():openURL(settings.url.playstore)
            end)
            local appstore = util.createCustomMenuItemWithSprite('desktop/appstore.png',nil,nil,function()
                pix2d.Native:getInstance():openURL(settings.url.appstore)
            end)
            appstore:setPosition(ccp(-50,-100))
            googleplay:setPosition(ccp(50,-100))
            local menu = CCMenu:create()
            menu:addChild(appstore)
            menu:addChild(googleplay)
            menu:setPosition(ccp(0,0))
            menu:setTouchPriority(kCCMenuHandlerPriority -3)
            node:addChild(CCSprite:create('desktop/showcase.png'))
            node:addChild(label)
            node:addChild(menu)
            physics:getScene():addChild(layer,self.zorder.layer.popup,0)
        end
    end

    print '----------- Level initialized! -----------'
    -- mobdebug.off()
    return self
end

-- Return this package
return Level
--
-- EOF
