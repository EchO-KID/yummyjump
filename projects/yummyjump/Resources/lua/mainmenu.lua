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
local util = require 'util'
local scroll = require 'scroll'
local factory = require 'factory'
local mediator = require 'mediator'
local class = require 'class'
local anim = require 'anim'
local settings = require 'settings'()
local particle = require 'particle'()

print 'Loading package "MainMenu"...'

local scheduler = CCDirector:sharedDirector():getScheduler()
local visible = pix2d.VisibleRect
local audio = SimpleAudioEngine:sharedEngine()

-- The package table
local MainMenu = {}; MainMenu.__index = MainMenu

setmetatable(MainMenu,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            modalDialogShown = false, -- Dialog semaphore flag (quit dialog, settings...)
            nSeasons = 0, -- number of seasons
            levelsMenuLayer = nil,
            levelsMenus = {}, -- list of level selector menu in season order
            vcontainer = nil, -- vertical container
            container = nil, -- Horizontal container
            navItems = {},
            navTips = nil,
            comingSoon = true, -- Show the coming soon vertical menu?
            particleBatch = {}, -- list of particle systems
            st = {}, -- list of scrolling texture
            -- list of sprites to fade in/out on vertical scrolling. Must be
            -- initialized with as much tables as the seasons. That is, if
            -- there is 4 seasons and the coming soon menu then fadeNodes must contain 5 empty tables.
            fadeNodes = {},
            tag = {
                player = 1,
                ground = 2
            },
            zorder = {
                titleB = 5,
                titleA = 6,
                coin = 7,
                particleBatch = 8,
                player = 99,
                tutorial = 100,
                dialog = 101
            },
        }, MainMenu)
    end
})

function MainMenu:createLevelButton(seasonid,levelid,score)
    local item = util.createCustomMenuItem('button_rect.png','button_rect.png','button_rect_d.png')
    local size = item:getContentSize()
    if score > -2 then
        local label = CCLabelBMFont:create(tostring(levelid),'Chewy.fnt')
        label:setPosition(size.width/2,size.height/2)
        item:addChild(label)
        item:registerScriptTapHandler(
        function()
            item:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(0.2),
                CCCallFunc:create(function() audio:playEffect(settings.audio.chime2) end)))
            -- To find out a node's point in world space we must ask its parent
            -- to convert its child's coord to world space
            local worldPos = util.worldSpacePosition(item)
            local iris = pix2d.IrisWipe:create(worldPos.x,worldPos.y,false,ccc4f(0,0,0,0.8),visible:size().width*0.8,0.0,0.8)
            physics:getScene():addChild(iris)
            iris:registerCallbackHandler(function()
                mediator:publish(mediator.ns.runLevelScene,seasonid,levelid)
            end)
            local particle = pix2d.ParticleQuad:createStarsExplosion(self.particleBatch['star_particle.png'])
            -- convert to particle batch local coordinate
            local localPos = self.particleBatch['star_particle.png']:convertToNodeSpace(worldPos)
            particle:setPosition(localPos.x,localPos.y)
            -- disable menu to avoid touch on other items
            item:getParent():setEnabled(false)
        end)
        local i = score > -1 and score or 0
        local scoreNode = CCSprite:createWithSpriteFrameName('level_score_'..i..'.png')
        scoreNode:setAnchorPoint(ccp(0.5,0.0))
        scoreNode:setPosition(size.width/2,5)
        item:addChild(scoreNode)
    else
        item:setEnabled(false)
        local lock = CCSprite:createWithSpriteFrameName('lock_sd.png')
        lock:setPosition(size.width/2,size.height/2)
        item:addChild(lock)
    end
    return item
end

-- Create the levels selector menu for season `season`
function MainMenu:loadLevelsSelectorMenu(db,seasonid)
    local menu = CCMenu:create()
    local rows = CCArray:create()
    local count = 0
    for levelid, level in ipairs(db.seasons[seasonid].levels) do
        menu:addChild(self:createLevelButton(seasonid,levelid,level.score))
        count = count + 1
        if count == 5 then
            rows:addObject(CCInteger:create(5))
            count = 0
        end
    end
    if count > 0 then
        rows:addObject(CCInteger:create(count))
    end
    menu:alignItemsInColumnsWithArray(rows)
    return menu
end

function MainMenu:dummyLevelSectorMenu()
    local menu = CCMenu:create()
    local rows = CCArray:create()
    local count = 0
    for i = 1,20 do
        local item = util.createCustomMenuItem('button_rect.png','button_rect.png','button_rect_d.png')
        local lock = CCSprite:createWithSpriteFrameName('lock_sd.png')
        local size = item:getContentSize()
        lock:setPosition(size.width/2,size.height/2)
        item:addChild(lock)
        item:setEnabled(false)
        menu:addChild(item)
        count = count + 1
        if count == 5 then
            rows:addObject(CCInteger:create(5))
            count = 0
        end
    end
    if count > 0 then
        rows:addObject(CCInteger:create(count))
    end
    menu:alignItemsInColumnsWithArray(rows)
    return menu
end

function MainMenu:updateHorizontalNavItems(idx,seasonid)
    -- Enable/disable navigation arrows
    self.navItems[1]:setVisible(idx > 1)
    self.navItems[2]:setVisible(idx == 3)
    self.navItems[3]:setVisible(idx < 5 and idx ~= 3)
    self.navItems[4]:setVisible(idx == 4 and seasonid < self.nSeasons)
    self.navItems[5]:setVisible(idx == 4 and seasonid > 1)

    -- Update the page tips
    for i = 1, 5 do
        if i ~= idx then
            self.navTips[i]:unselected()
        else
            self.navTips[i]:selected()
        end
    end
end

function MainMenu:createCoin(p)
    local mainmenu = self
    local position = { pix2d.Physics:meterToUnit(p.x,p.y) }
    local season, seasonid = self.manager:getCurrentSeason()
    local frame = nil
    if seasonid == 1 then
        frame = 'cupcake.png'
    elseif seasonid == 2 then
        frame = 'pepper.png'
    elseif seasonid == 3 then
        frame = 'avocado.png'
    else
        frame = 'ice_cream_bar.png'
    end
    local coin = factory:circle {
        radius = 0.2,
        density = 0.5,
        body_type = physics.DynamicBody,
        position = position,
        frame = frame,
        restitution = 0.7,
        group = -1, -- Do not collide with player (which is the same negative group)
    }
    -- HACK we create a dummy sensor attached to the coin to delegate collision to
    -- the sensor and the player do not actually collide with the coin.
    local sensor = class.extend {
        instance = factory:circle {
            body_type = physics.DynamicBody,
            position = position,
            sensor = true,
            radius = 0.25,
        },
        onEnter = function(self)
            mainmenu.contact:registerCollisionNotificationScriptWithTag(function()
                local localPos = mainmenu.particleBatch['star_particle_2.png']:convertToNodeSpace(util.worldSpacePosition(self))
                particle:create {
                    filename = 'particles/stars2',
                    batch = mainmenu.particleBatch['star_particle_2.png'],
                    autoremove = true,
                    position = { localPos.x, localPos.y },
                }
                mainmenu.coinExists = false
                coin:removeFromParentAndCleanup(true)
                self:removeFromParentAndCleanup(true)
            end,self,mainmenu.tag.player)
        end,
        onExit = function(self)
            mainmenu.contact:cancelCollisionNotification(self)
        end,
    }
    physics:createWeldJoint(sensor,coin,b2Vec2(0,0),b2Vec2(0,0))
    local mass = coin:getMass()
    coin:applyLinearImpulse(mass * p.s * 5, mass * p.v * 5)
    physics:addNode(sensor)
    physics:addNode(coin,self.zorder.coin)
end

function MainMenu:createPhysicsTitle(x,y,frame,zorder)
    -- Get the sprite frame' size
    local size = CCSpriteFrameCache:sharedSpriteFrameCache():spriteFrameByName(frame):getRect().size
    local physicsSize = pix2d.Physics:pixelToMeter(size.width,size.height)
    local mainmenu = self
    -- Create the title physics body
    local title = class.extend {
        touchBegin = { x = 0, y = 0},
        instance = factory:box {
            body_type = physics.DynamicBody,
            position = { x, y },
            uid = 1,
            sensor = true,
            frame = frame,
            size = { pix2d.Physics:pixelToUnit(size.width,size.height) },
        },
        onEnter = function(self)
            mainmenu.touch:registerTouchScriptHandler(
                function(e,t)
                    if e == 'begin' then
                        -- self.touchBegin = t.pos will not work because it
                        -- does not copy the b2Vec2 but rather assign its reference
                        self.touchBegin.x = t.pos.x
                        self.touchBegin.y = t.pos.y
                        self.isTouched = true
                        return true
                    elseif e == 'ended' or e == 'canceled' then
                        if not t.hasMoved then return end
                        local p = t.pos
                        -- print(self.touchBegin.x,self.touchBegin.y,t.pos.x,t.pos.y)
                        self.isTouched = false
                        if not mainmenu.coinExists then
                            mainmenu:createCoin {
                                s = self.touchBegin.x - p.x,
                                v = self.touchBegin.y - p.y,
                                x = t.pos.x,
                                y = t.pos.y
                            }
                            mainmenu.coinExists = true
                        end
                    end
                end,
                self)
            self:movable(true)
        end,
        onExit = function(self)
            -- self.applyForceAction:release()
            -- WARNING Must unschedule lua scheduler manually
            if self.schedulerid then self:getScheduler():unscheduleScriptEntry(self.schedulerid) end
            -- self.scaleAction:release()
            -- self.rotateAction:release()
        end
    }
    physics:addNode(title,zorder)
    -- The static bodies position and the title's local
    -- anchor used to create the distance joints
    local anchors = {
        { x - 4, y + 4, -0.5, 0.5 },
        { x + 4, y + 4, 0.5, 0.5 },
        { x + 4, y - 4, 0.5, -0.5 },
        { x - 4, y - 4, -0.5, -0.5 }
    }
    -- Create the 4 static bodies (anchor) and distance joints
    for i,v in ipairs(anchors) do
        local anchor = factory:circle {
            uid = i,
            sensor = true,
            position = { v[1], v[2] },
            body_type = physics.StaticBody,
            radius = 0.25
        }
        physics:addNode(anchor)
        physics:createDistanceJoint(title,anchor,
            b2Vec2(physicsSize.x * v[3],physicsSize.y * v[4]),
            b2Vec2(0,0),
            2.0, -- Frequency
            0.3) -- Damping ratio
    end
    -- Intro action
    title:setScale(1.8)
    title:runAction(CCSequence:createWithTwoActions(
        CCEaseElasticOut:create(CCScaleTo:create(1.2,1)), -- intro animation
        CCSequence:createWithTwoActions(
            CCDelayTime:create(0.3),
            CCCallFunc:create(function()
                anim:repeatForever(title,CCScaleTo:create(2,1.1),CCScaleTo:create(2,1))
            end))))
    --[[
    -- Run an action to animate the game title. The action applies a incremental force to the body
    local mass = title:getMass()
    -- Apply progressive vertical force from 10 to -40
    title.applyForceAction = pix2d.ActionTweenLua:create(0.5,'',10,-40,function(v,k) title:applyForceToCenter(0,mass * v) end)
    title.applyForceAction:retain()
    title.schedulerid = title:getScheduler():scheduleScriptFunc(
        function() if not title.isTouched then title:runAction(title.applyForceAction) end end,
        6,false)
    --]]
    return title
end

local function floatingAction(target)
    anim:repeatForever(target,CCRotateBy:create(1,-15),CCRotateBy:create(1,15))
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
    return sprite
end

-- Create the player
function MainMenu:createPlayer(p)
    local c = factory:circle {
        body_type = physics.DynamicBody,
        position = p.position,
        frame = p.frame,
        radius = 0.25,
        tag = self.tag.player,
        group = -1,
    }
    local hand = nil
    if settings.showMainMenuHandAnim then
        hand = class.extend {
            instance = handAnim(c:getPositionX(),80,-150,true,1),
            update = function(self,dt)
                self:setPosition(c:getPositionX(),80)
            end
        }
        hand:setOpacity(0)
        hand:runAction(CCSequence:createWithTwoActions(
            CCDelayTime:create(6),CCFadeIn:create(1)))
        physics:layer():addChild(hand,self.zorder.tutorial)
    end
    -- Create a toggle menu with all the outfits
    local toggle = CCMenuItemToggle:create(util.createMenuItem(p.frame))
    -- toggle:setScale(1.07)
    toggle:registerScriptTapHandler(function()
        settings.showMainMenuHandAnim = false
        if hand then
            hand:removeFromParentAndCleanup(true)
            hand = nil
        end
        audio:playEffect(settings.audio.click)
        self.manager:setCurrentOutfit(toggle:getSelectedIndex())
        mediator:publish(mediator.ns.outfitChanged,toggle:getSelectedIndex(),'toggle')
    end)
    for i=1,self.outfitUnlockedCount do
        local item = util.createMenuItem(self.costumes[i]..'.png')
        -- hack: increase outfit scale so it cover the player sprite
        item:setScale(1.06)
        toggle:addSubItem(item)
    end
    toggle:setSelectedIndex(self.manager.db.defaults.cCostume)
    mediator:subscribe(mediator.ns.outfitChanged,function(e,id,source)
        if source ~= 'toggle' then toggle:setSelectedIndex(id) end
    end)
    local outfitsMenu = CCMenu:create()
    local size = c:getContentSize()
    outfitsMenu:setPosition(size.width/2,size.height/2)
    outfitsMenu:addChild(toggle)
    c:addChild(outfitsMenu)

    local dv = 0.4 -- desired velocity
    local limit = 0.1
    local impulseY = 0
    local mainmenu = self
    local player = class.extend {
        instance = c,
        onEnter = function(self)
            self.mass = self:getMass()
            local function contact_handler(c)
                local cv = self:getLinearVelocity() -- current velocity
                local pos = pix2d.Physics:pixelToMeter(self:getPosition())
                local x = c.pos.x - pos.x
                local y = c.pos.y - pos.y
                -- print('pos.y',pos.y,'contact pos y',c.pos.y,'y',y)
                local impulse = 0
                if y < -limit then
                    impulse = self.mass * (dv - cv.x)
                    impulseY = self.mass * (2.0 - cv.y)
                elseif y < limit and y > -limit then
                    -- change impulse direction
                    dv = -dv
                    impulse = self.mass * (dv - cv.x)
                    impulseY = 0
                end
                -- print('impulse',impulse,'velocity',cv.x)
                self:applyLinearImpulse(impulse, impulseY)
            end
            mainmenu.contact:registerCollisionNotificationScriptWithTag(contact_handler,self,mainmenu.tag.ground)
            mainmenu.contact:registerCollisionNotificationScriptWithTag(contact_handler,self,pix2d.PhysicNode.boundary)
        end,
        onExit = function(self)
            mainmenu.contact:cancelCollisionNotification(self)
        end
    }
    physics:addNode(player,self.zorder.player)
    return player
end

local function createControlButton(text,x,y,handler)
    local button = CCControlButton:create(
        util.label(text,0,0,0.7),
        CCScale9Sprite:createWithSpriteFrameName('button_rect.png'))
    button:setPosition(x,y)
    button:addHandleOfControlEvent(function()
        audio:playEffect(settings.audio.switch)
        handler()
    end,CCControlEventTouchUpInside)
    button:setMargins(10,6)
    button:setTouchPriority(kCCMenuHandlerPriority - 3)
    return button
end

function MainMenu:createSettingsMenu()
    -- Disable touch on scroll view
    self.modalDialogShown = true
    self.scrollView:setTouchEnabled(false)
    local localeHasChanged = false
    local layer,node = util.dialog(kCCMenuHandlerPriority -3,visible:sizeAt(0.6,0.6),'ok',function(e,layer,node)
        self.scrollView:setTouchEnabled(true)
        if localeHasChanged then
            mediator:publish(mediator.ns.localeChanged)
        end
        node:runAction(CCSequence:createWithTwoActions(
            CCDelayTime:create(0.1),
            CCCallFunc:create(function() audio:playEffect(settings.audio.swish1) end)))
        node:runAction(CCSequence:createWithTwoActions(
            CCEaseBackIn:create(CCMoveTo:create(0.5,ccp(visible:pointAt(0.5,1.5)))),
            CCCallFunc:create(function()
                layer:removeFromParentAndCleanup(true)
            end)))
        self.modalDialogShown = false
        return false
    end,ccc4(28,28,28,128))
    node:setPosition(visible:pointAt(0.5,1.5))
    -- Languages
    local updateButtonsLabels = nil
    local lang = createControlButton('Language',0,70,function()
        localeHasChanged = true
        if settings.locale == 'en' then
            self.manager:setLocale('fr')
        elseif settings.locale == 'fr' then
            self.manager:setLocale('es')
        else
            self.manager:setLocale('en')
        end
        updateButtonsLabels()
    end)
    local resetGame = createControlButton('Reset game',0,30,function()
        local layer,node = util.messageBox(self.manager.i18n('resetWarning'),kCCMenuHandlerPriority -4,'cancelok',function(e)
            if e == 'ok' then
                self.manager:resetGame()
            end
            return true
        end)
        physics:getScene():addChild(layer)
    end)
    local showGrid = createControlButton('Show Grid',0,-10,function()
        settings.showGrid = not settings.showGrid
        updateButtonsLabels()
    end)
    local replayStoryboard = createControlButton('Replay video',0,-50,function ()
        mediator:publish(mediator.ns.runStoryboardScene)
    end)
    -- Update the buttons lable using the current locale
    local function updateTitle(control,key)
        control:setTitleForState(CCString:create(self.manager.i18n(key)),CCControlStateNormal)
    end
    updateButtonsLabels = function ()
        updateTitle(lang,'lang')
        updateTitle(showGrid,settings.showGrid and 'showGrid' or 'hideGrid')
        updateTitle(resetGame,'resetGame')
        updateTitle(replayStoryboard, 'replayAnim')
    end
    updateButtonsLabels()
    -- Add the buttons
    node:addChild(lang)
    node:addChild(showGrid)
    node:addChild(resetGame)
    node:addChild(replayStoryboard)
    node:runAction(CCEaseBounceOut:create(CCMoveTo:create(0.5,visible:center())))
    return layer
end

--[[
function MainMenu:createTextureGround(p)
p.body_type = physics.StaticBody
p.tag = self.tag.ground
local ground = factory:texture_node(p)
assert(ground,'ERROR: Can\'t create texture ground')
physics:addNode(ground,self.zorder.ground)
end
--]]
function MainMenu:initPhysics()
    local width, height = pix2d.Physics:pixelToUnit(0,15)
    physics:addNode(pix2d.Boundary:create(CCRectMake(0,0,10,7)))
    local ground = factory:texture_node {
        uid = 1,
        tag = self.tag.ground,
        texture = 'ground_texture.png',
        points = {0, 0, 10, height}
    }
    ground:setVisible(false) -- Hack the ground because we use several ground textures
    physics:addNode(ground)
    self:createPlayer {
        position = {3,0.5},
        frame = 'idle.png',
    }
    self:createPhysicsTitle(3.4,3.5,'title_yummy.png',self.zorder.titleA)
    self:createPhysicsTitle(7.8,4.1,'title_jump.png',self.zorder.titleB)
end

-- create the main menu in the scene `scene`.
-- Start the menu at page `pageid`
function MainMenu:init(manager,scene,pageid)
    self.manager = manager
    local db = manager.db
    print 'Initialize main menu...'

    for _,v in pairs {'actions01','actions02','mainmenu01','mainmenu02','mainmenu03'} do
        CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile(v..'.plist')
    end

    local top = visible:top()
    local center = visible:center()

    self.touch = physics:touchListener()
    self.contact = physics:contactListener()

    -- increment Lua tags with the C++ max tag value
    local maxtag = pix2d.PhysicNode.maxtag
    for k, v in pairs(self.tag) do
        self.tag[k] = maxtag + v
    end
    -- Copy the costumes
    self.costumes = util.shallowcopy(db.assets.costumes)
    self.nCostumes = #self.costumes
    self.cCostume = db.defaults.cCostume

    pix2d.Physics:setDefaultBackgroundColor(1,1,1,1)


    ------------------------------ SEASONS ------------------------------------
    -- Create the seasons layers
    local seasonLayers = {}
    for i,v in ipairs(db.seasons) do
        local layer = pix2d.OpacityNode:create()
        -- Create the item image
        local normal = CCScale9Sprite:createWithSpriteFrameName('messagebox2.png')
        normal:setContentSize(visible:sizeAt(0.4,0.6))
        local item = CCMenuItemSprite:create(normal,normal)
        item:registerScriptTapHandler(function()
            if not self.vcontainer.isScrolling then
                self.container:moveToNextPage(true)
            end
        end)
        -- Create the menu
        local menu = CCMenu:create()
        menu:addChild(item)
        menu:setPosition(center)
        layer:addChild(menu)
        -- Create the season image at the center of the menu item
        local sprite = pix2d.CustomSprite:createWithSpriteFrameName('thumbnail_season_'..i..'.png')
        anim:dance(sprite)
        sprite:setPosition(center)
        layer:addChild(sprite)
        if db.seasons[i].levels[1].score < -1 then
            local lockSprite = CCSprite:createWithSpriteFrameName('lock_hd.png')
            lockSprite:setPosition(center)
            layer:addChild(lockSprite)
        end
        local score,completed = manager:getSeasonProgressPercent(i)
        -- levels progress bar
        local x,y = visible:pointAt(0.5,0.25)
        local pg, bg = util.progressBarVertical('pg_'..i..'.png','pg_bg_'..i..'.png',x,y,completed,layer)
        bg:setOpacity(127)
        pg:addChild(util.label(completed..'%',pg:getContentSize().width/2,(pg:getContentSize().height/2),0.55))
        if score >= 100 then
            local x,y = visible:pointAt(0.65,0.75)
            local badge = CCSprite:createWithSpriteFrameName('badge.png')
            badge:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
                CCRotateTo:create(2,-15),CCRotateTo:create(2,15))))
            badge:setPosition(x,y)
            layer:addChild(badge)
        end
        table.insert(seasonLayers,layer)
        table.insert(self.fadeNodes,{})
    end
    -- Add the comming soon
    if self.comingSoon then
        table.insert(self.fadeNodes,{})
        local createComingSoon = function()
            local normal = CCScale9Sprite:createWithSpriteFrameName('messagebox2.png')
            normal:setContentSize(visible:sizeAt(0.6,0.6))
            normal:setPosition(center)
            local label1 = util.label(manager.i18n('comingSoon1'),visible:pointAt(0.5,0.6))
            anim:repeatForever(label1,CCSkewTo:create(1,20,1),CCSkewTo:create(1,-20,1))
            local label2 = util.label(manager.i18n('comingSoon2'),visible:pointAt(0.5,0.4))
            anim:repeatForever(label2,CCSkewTo:create(1,20,1),CCSkewTo:create(1,-20,1))
            mediator:subscribe(mediator.ns.localeChanged,function()
                label1:setString(manager.i18n('comingSoon1'))
                label2:setString(manager.i18n('comingSoon2'))
            end)
            local layer = CCLayer:create()
            layer:addChild(normal)
            layer:addChild(label1)
            layer:addChild(label2)
            return layer
        end
        table.insert(seasonLayers,createComingSoon())
    end
    -------------------------- VERTICAL CONTAINER ------------------------------
    -- Create the vertical container and "activate" the levels selector menu
    -- accordingly to the selected season
    self.vcontainer = scroll:createContainer(
    'vertical',
    seasonLayers,
    visible:size(),
    db.defaults.cSeasonid - 1, -- starting page is the current season
    -- Cascade opacity not working when the season thumbnail is animated (dancing animation)
    -- so it's disabled
    nil,
    --[[
    function(x,y,s) -- The page is scrolling
        for _,v in ipairs(seasonLayers) do
            -- local opacity = 255 - math.abs(math.abs(self.vcontainer:getPositionY()) - v:getPositionY())
            -- opacity = math.abs(math.min(opacity,255))
        end
    end,
    --]]
    function(idx) -- The page changed
        -- Show the level menu for the current selected season
        idx = idx + 1
        local cSeasonid = db.defaults.cSeasonid
        if idx == cSeasonid then return end -- nothing to do
        if self.levelsMenuLayer ~= nil then
            self.navItems[4]:setVisible(idx < self.nSeasons)
            self.navItems[5]:setVisible(idx > 1)
            -- self.levelsMenuLayer is nil and navItems is empty the first time this
            -- function is called (Scroll:pageChangedCallback)
            for i=1,self.nSeasons do
                self.levelsMenuLayer:getChildByTag(i):setVisible(i == idx)
            end
        end
        if #self.st > 0 then
            -- Background texture fade in/out
            -- Only the most upwards texture is fade in/out to get a smooth
            -- transition.
            local s1 = self.st[math.max(idx,cSeasonid)]
            local s2 = self.st[math.min(idx,cSeasonid)]
            for _,t in ipairs(self.st) do
                t:setVisible(false)
                t:stopAllActions()
            end
            -- Moving downwards
            if idx < cSeasonid then
                s1:setVisible(true)
                s2:setVisible(true)
                s2:setOpacity(255)
                s1:runAction(CCSequence:createWithTwoActions(
                    CCFadeOut:create(0.5),CCCallFunc:create(function()
                        s1:setVisible(false)
                    end)))
            else
                s2:setVisible(true)
                s2:setOpacity(255)
                s1:setVisible(true)
                -- s1:setOpacity(0)
                s1:runAction(CCSequence:createWithTwoActions(
                    CCFadeIn:create(0.5),CCCallFunc:create(function()
                        s2:setVisible(false)
                    end)))
            end

            -- Fading ground texture is buggy so we just toggle their visibility
            if self.fadeNodes[idx] then
                for _,n in ipairs(self.fadeNodes[idx]) do
                    n:setVisible(true)
                end
            end
            if self.fadeNodes[cSeasonid] then
                for _,n in ipairs(self.fadeNodes[cSeasonid]) do
                    n:setVisible(false)
                end
            end
        end
        db.defaults.cSeasonid = idx
    end
    )

    ----------------------------- CREDITS --------------------------------------
    local lineX, lineY = visible:size().width / 2, 0
    local linePadding = 2
    local fontName = pix2d.Assets:font(pix2d.Assets.Chewy)

    -- The credits content node. Will be created below and when receive the `localeChanged` event
    local creditsContentNode = nil
    local creditsMenu = nil
    local container = CCNode:create()

    local creditsConstructors = {
        label = function(p)
            local label = pix2d.CustomLabelTTF:create()
            label:setFontName(pix2d.Assets:font(pix2d.Assets.Chewy))
            label:setString(p.text)
            label:setFontSize(24)
            label:setPosition(ccp(lineX,lineY))
            creditsContentNode:addChild(label)
            label:setAnchorPoint(ccp(0.5,1))
            return 24
        end,
        titleLabel = function(p)
            local label = CCLabelTTF:create(p.text,fontName,18)
            label:setColor(ccc3(254,253,192))
            label:setPosition(ccp(lineX,lineY))
            creditsContentNode:addChild(label)
            label:setAnchorPoint(ccp(0.5,1))
            return 18
        end,
        -- Create a external url link
        -- Parameters: text, url
        linkLabel = function(p)
            local label = pix2d.CustomMenuItemFont:create(p.text,fontName,24)
            label:registerScriptTapHandler(function ()
                pix2d.Native:getInstance():openURL(p.url)
            end)
            label:setPosition(ccp(lineX,lineY))
            label:setAnchorPoint(ccp(0.5,1))
            creditsMenu:addChild(label)
            return 24
        end,
        image = function(p)
            local sprite = CCSprite:createWithSpriteFrameName(p.frame)
            if p.scale then sprite:setScale(p.scale) end
            sprite:setAnchorPoint(ccp(0.5,1))
            sprite:setPosition(ccp(lineX,lineY))
            creditsContentNode:addChild(sprite)
            return sprite:getContentSize().height * sprite:getScale()
        end,
        linkImage = function(p)
            local sprite = CCSprite:createWithSpriteFrameName(p.frame)
            local item = CCMenuItemSprite:create(sprite,sprite)
            item:registerScriptTapHandler(function()
                pix2d.Native:getInstance():openURL(p.url)
            end)
            item:setAnchorPoint(ccp(0.5,1))
            if p.scale then item:setScale(p.scale) end
            item:setPosition(ccp(lineX,lineY))
            creditsMenu:addChild(item)
            return sprite:getContentSize().height * item:getScale()
        end
    }

    local createCreditsLabels = function ()
        local appVersion = require 'version'.version
        if settings.pix2d_debug or settings.cocos2d_debug then
            appVersion = appVersion .. ' DEBUG'
        end

        local creditsData = {
            {
                ctor = 'titleLabel',
                text = manager.i18n('credits_1'),
            },{
                ctor = 'image',
                frame = 'voodoocactus.png',
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_2'),
            },{
                ctor = 'label',
                text = 'Laurent Zubiaur'
            },{
                ctor = 'linkImage',
                frame = 'twitter_bird_blue.png',
                url = settings.url.twitter_laurent,
                scale = 0.6
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_3'),
            },{
                ctor = 'label',
                text = 'Alejandra Espeja',
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_10'),
            },{
                ctor = 'label',
                text = 'Alphonse Zubiaur',
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_8'),
            },{
                ctor = 'label',
                text = 'Lehbib Lasyad',
            },{
                ctor = 'label',
                text = 'Emeric Deltour',
            },{
                ctor = 'label',
                text = 'Emilie Zubiaur',
            },{
                ctor = 'label',
                text = 'Sandra Quintanilla',
            },{
                ctor = 'label',
                text = 'Yves Amieva',
            },{
                ctor = 'label',
                text = 'David DeFelice',
            },{
                ctor = 'label',
                text = 'Mike DeFelice',
            },{
                ctor = 'label',
                text = 'Sylvain Wolkenar',
            },{
                ctor = 'label',
                text = 'megasoft78',
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_4'),
            },{
                ctor = 'label',
                text = 'cocos2dx',
            },{
                ctor = 'label',
                text = 'box2d',
            },{
                ctor = 'label',
                text = 'CocosBuilder',
            },{
                ctor = 'label',
                text = 'Tiled Map Editor',
            },{
                ctor = 'label',
                text = 'Inkscape',
            },{
                ctor = 'label',
                text = 'GIMP',
            },{
                ctor = 'label',
                text = 'Glue Sprites Sheet',
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_9'),
            },{
                ctor = 'label',
                text = 'soundjay.com',
            },{
                ctor = 'label',
                text = 'kenney.nl',
            },{
                ctor = 'label',
                text = 'Brandon Morris',
            },{
                ctor = 'label',
                text = 'LloydEvans09',
            },{
                ctor = 'label',
                text = "Taira Komori's Japanese Free Sound Effects",
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_6'),
            },{
                ctor = 'linkLabel',
                text = 'www.voodoocactus/privacy',
                url = settings.url.privacy,
            },{
                ctor = 'titleLabel',
                text = manager.i18n('credits_7'),
            },{
                ctor = 'linkLabel',
                text = 'www.voodoocactus/contact',
                url = settings.url.contact,
            },{
                ctor = 'titleLabel',
                text = 'Version',
            },{
                ctor = 'label',
                text = appVersion,
            }
        }
        creditsContentNode = CCNode:create()
        creditsMenu = CCMenu:create()
        creditsMenu:setPosition(ccp(0,0))
        creditsContentNode:addChild(creditsMenu)
        -- Call constructors
        for _,t in ipairs(creditsData) do
            lineY = lineY - linePadding - creditsConstructors[t.ctor](t)
        end
        creditsContentNode:setPosition(ccp(0,-lineY))
        container:setContentSize(CCSizeMake(visible:size().width,math.abs(lineY)))
        container:addChild(creditsContentNode)
    end
    mediator:subscribe(mediator.ns.localeChanged,function()
        creditsContentNode:removeFromParentAndCleanup(true)
        createCreditsLabels()
    end)
    -- Call once to create the credits
    createCreditsLabels()

    local creditsScrollView = CCScrollView:create()
    local scrollViewSize = visible:sizeAt(1,0.8)
    creditsScrollView:setViewSize(scrollViewSize)
    creditsScrollView:setPosition(visible:pointAt(0,0.1))
    creditsScrollView:setContainer(container)
    local creditsScrollViewOriginalOffset = ccp(0, lineY + scrollViewSize.height)
    creditsScrollView:setContentOffset(creditsScrollViewOriginalOffset)
    creditsScrollView:updateInset()
    creditsScrollView:setDirection(kCCScrollViewDirectionVertical)
    creditsScrollView:setBounceable(true)
    -- creditsScrollView:setBounceable(false)
    creditsScrollView:setClippingToBounds(true)

    local creditsColorLayer = CCLayerColor:create(ccc4(42,42,42,48))
    creditsColorLayer:setContentSize(visible:sizeAt(0.8,0.8))
    creditsColorLayer:setPosition(visible:pointAt(0.1,0.1))
    --[[
    -- Pause/resume the credits layer on touch
    creditsColorLayer:registerScriptTouchHandler(function(e)
        if e == 'began' then
            -- creditsScrollView:pause(creditsColorLayer)
        elseif e == 'ended' or e == 'canceled' then
            -- creditsScrollView:resume(creditsColorLayer)
        end
        return true
    end,
    false, -- no multi-touch (process touches one by one)
    kCCMenuHandlerPriority - 1,
    false) -- Do not swallows touches
    creditsColorLayer:setTouchEnabled(true)
    --]]
    local creditsContainer = CCNode:create()
    creditsContainer:addChild(creditsColorLayer)
    creditsContainer:addChild(creditsScrollView)

    ----------------------------- Outfits -------------------------------------
    local createOutfits = function()
        local layer = CCLayer:create()
        local dialog = CCScale9Sprite:createWithSpriteFrameName(frame or 'messagebox2.png')
        dialog:setContentSize(visible:sizeAt(0.8,0.7))
        dialog:setPosition(center)
        layer:addChild(dialog)

        local blur = CCSprite:create('white_circle_blur.png')
        blur:setPosition(visible:pointAt(0.7,0.5))
        blur:setScale(4)
        layer:addChild(blur)
        local playerSprite = pix2d.CustomSprite:createWithSpriteFrameName('idle_hd.png')
        playerSprite:setPosition(visible:pointAt(0.7,0.5))
        layer:addChild(playerSprite)
        local outfitSprite = nil
        local function updateOutfitSprite(frame)
            if outfitSprite then outfitSprite:removeFromParentAndCleanup(true) end
            outfitSprite = pix2d.CustomSprite:createWithSpriteFrameName(frame)
            outfitSprite:setScale(1.03) -- hack to be sure that the outfit covers the player' sprite
            playerSprite:addChild(outfitSprite)
            local size = playerSprite:getContentSize()
            outfitSprite:setPosition(size.width/2,size.height/2)
        end
        -- The player sprite
        mediator:subscribe(mediator.ns.outfitChanged,function(e,id,source)
            if source ~= 'menu' then
                if id > 0 then
                    updateOutfitSprite('outfit_'..manager:getOutfit(id)..'_hd.png')
                else
                    outfitSprite:removeFromParentAndCleanup(true)
                    outfitSprite = nil
                end
            end
        end)
        local score,completed,levelCount = manager:getGameProgress()
        local menu = CCMenu:create()
        menu:setPosition(visible:leftBottom())
        local container = CCNode:create()
        container:addChild(menu)
        local lineY, lineX = 0, visible:pointAtX(0.2)
        -- Add the cancel outfit button
        local item = util.createCustomMenuItem('outfit_cancel_hd.png')
        item:registerScriptTapHandler(function()
            if manager:getCurrentOutfitId() ~= 0 then
                outfitSprite:removeFromParentAndCleanup(true)
                outfitSprite = nil
                manager:setCurrentOutfit(0)
                mediator:publish(mediator.ns.outfitChanged,0,'menu')
            end
        end)
        lineY = item:getContentSize().height / 2
        item:setPosition(lineX,lineY)
        lineY = item:getContentSize().height
        menu:addChild(item)
        local outfits = manager:getOutfits()
        local unlocked = 2 -- default unlock outfit count
        -- threshold to unlock a new outfit (total number of stars divided by number of outfit)
        local inc = (levelCount * 3) / (#outfits - unlocked)
        local count = 0
        for i,v in ipairs(outfits) do
            local threshold = (i - unlocked) * inc
            if i > unlocked and threshold > score then  -- First two outfits are unlocked
                local item = CCSprite:createWithSpriteFrameName('outfit_disabled_hd.png')
                item:setOpacity(127)
                container:addChild(item)
                lineY = lineY + 10
                local size = item:getContentSize()
                local posY = lineY + (size.height / 2)
                item:setPosition(lineX,posY)
                -- The label
                local label = util.label(threshold,lineX,lineY,0.5)
                label:setAnchorPoint(ccp(0.5,1))
                container:addChild(label)
                -- the star
                local star = CCSprite:createWithSpriteFrameName('star.png')
                star:setScale(0.2)
                star:setAnchorPoint(ccp(0.5,0))
                star:setPosition(lineX,lineY)
                lineY = lineY + size.height + 10
                container:addChild(star)
            else
                count = count + 1
                -- Outfit format: outfit_<name>_hd.png
                local frame = 'outfit_' .. v .. '_hd.png'
                local item = util.createCustomMenuItem(frame)
                if manager:getCurrentOutfitId() == i then
                    updateOutfitSprite(frame)
                end
                item:registerScriptTapHandler(function()
                    if manager:getCurrentOutfitId() ~= i then
                        updateOutfitSprite(frame)
                        manager:setCurrentOutfit(i)
                        mediator:publish(mediator.ns.outfitChanged,i,'menu')
                    end
                end)
                local size = item:getContentSize()
                item:setPosition(lineX,lineY + (size.height / 2))
                menu:addChild(item)
                lineY = lineY + size.height
            end
        end
        self.outfitUnlockedCount = count
        local viewSize = visible:sizeAt(0.4,0.6)
        container:setContentSize(CCSizeMake(viewSize.width,lineY))
        local scroll = CCScrollView:create()
        scroll:setTouchPriority(kCCMenuHandlerPriority -1)
        scroll:setViewSize(viewSize)
        scroll:setPosition(visible:pointAt(0.1,0.2))
        scroll:setContainer(container)
        -- local creditsScrollViewOriginalOffset = ccp(0, lineY + scrollViewSize.height)
        -- scroll:setContentOffset(creditsScrollViewOriginalOffset)
        scroll:updateInset()
        scroll:setDirection(kCCScrollViewDirectionVertical)
        scroll:setBounceable(true)
        scroll:setClippingToBounds(true)
        layer:addChild(scroll)
        -- Avoid changing outfit while scrolling
        local flag = true
        layer:registerScriptTouchHandler(function(e)
            if e == 'began' then
                menu:setEnabled(true)
            elseif e == 'moved' then
                if flag then
                    menu:setEnabled(false)
                    flag = false
                end
            else
                flag = true
            end
            return true
        end,
        false, -- no multi-touch (process touches one by one)
        kCCMenuHandlerPriority - 2,
        false) -- Do not swallows touches
        layer:setTouchEnabled(true)


        -- Show the current score (stars)
        local x,y = visible:pointAt(0.7,0.3)
        local label = util.label(score,x,y,0.8)
        label:setAnchorPoint(ccp(1.2,0.6))
        layer:addChild(label)
        -- the star
        local star = CCSprite:createWithSpriteFrameName('star.png')
        star:setScale(0.4)
        star:setAnchorPoint(ccp(-0.2,0.5))
        star:setPosition(ccp(x,y))
        layer:addChild(star)

        return layer, scroll, menu
    end
    local outfitsLayer, outfitScroll, outfitMenu = createOutfits()

    ----------------------------- TITLE LAYER ----------------------------------
    local titleLayer = CCLayer:create()
    -- Workaroud to add the physics layer to the scrolling
    -- TODO sprite in the parallax foreground are behind the physics layer
    physics:layer():removeFromParentAndCleanup(false)
    titleLayer:addChild(physics:layer())

    -- Music credit
    --[[
    local musicByLabel1 = util.label('Music By',visible:pointAt(0.03,0.13))
    local musicByLabel2 = util.label('Al.Zubiaur',visible:pointAt(0.03,0.10))
    musicByLabel1:setOpacity(200)
    musicByLabel2:setOpacity(200)
    musicByLabel1:setScale(0.3)
    musicByLabel2:setScale(0.5)
    musicByLabel1:setSkewX(-20)
    musicByLabel2:setSkewX(-20)
    musicByLabel1:setAnchorPoint(ccp(0,0.5))
    musicByLabel2:setAnchorPoint(ccp(0,0.5))
    anim:repeatForever(musicByLabel1,CCSkewTo:create(1,20,1),CCSkewTo:create(1,-20,1))
    anim:repeatForever(musicByLabel2,CCSkewTo:create(1,20,1),CCSkewTo:create(1,-20,1))
    physics:layer():addChild(musicByLabel1)
    physics:layer():addChild(musicByLabel2)
    --]]

    -- twitter
    local twitterButton = util.createCustomMenuItem('button_twitter.png')
    twitterButton:setPosition(visible:pointAt(0.95,0.9))
    twitterButton:registerScriptTapHandler(function() pix2d.Native:getInstance():openURL(settings.url.twitter) end)
    -- facebook
    local facebookButton = util.createCustomMenuItem('button_facebook.png')
    facebookButton:setPosition(visible:pointAt(0.85,0.9))
    facebookButton:registerScriptTapHandler(function() pix2d.Native:getInstance():openURL(settings.url.facebook) end)
    -- Music
    local backgroundMusicLoaded = false
    if audio:isBackgroundMusicPlaying() then
        backgroundMusicLoaded = true
    elseif settings.musicEnabled then
        audio:preloadBackgroundMusic(settings.audio.background)
        backgroundMusicLoaded = true
    end
    local musicToggle = CCMenuItemToggle:create(util.createMenuItem('button_music.png'))
    musicToggle:addSubItem(util.createMenuItem('button_music_disabled.png'))
    musicToggle:registerScriptTapHandler(function()
        settings.musicEnabled = not settings.musicEnabled
        if settings.musicEnabled then
            if backgroundMusicLoaded then
                audio:resumeBackgroundMusic()
            else
                backgroundMusicLoaded = true
                audio:playBackgroundMusic(settings.audio.background,true)
            end
        else
            audio:pauseBackgroundMusic()
        end
    end)
    musicToggle:setSelectedIndex(settings.musicEnabled and 0 or 1)
    musicToggle:setPosition(visible:pointAt(0.05,0.9))
    -- Sounds
    audio:setEffectsVolume(settings.soundsEnabled and 1 or 0)
    local soundsToggle = CCMenuItemToggle:create(util.createMenuItem('button_sounds.png'))
    soundsToggle:addSubItem(util.createMenuItem('button_sounds_disabled.png'))
    soundsToggle:registerScriptTapHandler(function()
        settings.soundsEnabled = not settings.soundsEnabled
        audio:setEffectsVolume(settings.soundsEnabled and 1 or 0)
    end)
    soundsToggle:setSelectedIndex(settings.soundsEnabled and 0 or 1)
    soundsToggle:setPosition(visible:pointAt(0.15,0.9))
    -- settings
    local settingsButton = util.createCustomMenuItem('button_settings.png')
    settingsButton:setPosition(visible:pointAt(0.25,0.9))
    settingsButton:registerScriptTapHandler(function()
        physics:getScene():addChild(self:createSettingsMenu())
    end)
    -- menu
    local titleMenu = CCMenu:create()
    titleMenu:setPosition(ccp(0,0))
    titleLayer:addChild(titleMenu)
    titleMenu:addChild(twitterButton)
    titleMenu:addChild(facebookButton)
    titleMenu:addChild(soundsToggle)
    titleMenu:addChild(musicToggle)
    titleMenu:addChild(settingsButton)

    ----------------------------- LEVELS MENUS ---------------------------------
    -- Create a levels selector menus for each seasons.
    -- Each menu is created in its own layer which is visible
    -- when its season is selected
    local seasonsTitles = {}
    self.levelsMenuLayer = CCLayer:create()
    local labelPos = ccp(top.x,top.y - visible:sizeAt(1,0.1).height)
    for i,v in ipairs(db.seasons) do
        local layer = CCLayer:create()
        layer:setVisible(db.defaults.cSeasonid == i)
        self.levelsMenuLayer:addChild(layer,0,i)
        self.nSeasons = self.nSeasons + 1
        layer:addChild(pix2d.CocosBuilderLua:create('data/ccb/levels.ccbi',
        function(target,name,node)
            if name == 'title' or name == 'titleShadow' then
                local label = tolua.cast(node,'CCLabelBMFont')
                label:setString(manager.i18n('season_name_'..i))
                table.insert(seasonsTitles,{ id = i, label = label })
            elseif name == 'scoreUnlocked' then
                local score,completed,count = manager:getSeasonProgress(i)
                tolua.cast(node,'CCLabelBMFont'):setString(completed..'/'..count)
            elseif name == 'scoreStars' then
                local score,completed,count = manager:getSeasonProgress(i)
                tolua.cast(node,'CCLabelBMFont'):setString(score..'/'..count*3)
            end
        end,function() end))
        local levelMenu = self:loadLevelsSelectorMenu(db,i)
        table.insert(self.levelsMenus,levelMenu)
        layer:addChild(levelMenu)
    end
    -- Add the coming soon level menu
    if self.comingSoon then
        self.nSeasons = self.nSeasons + 1
        local comingSoonLayer = CCLayer:create()
        comingSoonLayer:setVisible(false)
        local colorLayer = CCLayerColor:create(ccc4(42,42,42,48))
        colorLayer:setContentSize(visible:sizeAt(0.8,0.6))
        colorLayer:setPosition(visible:pointAt(0.1,0.2))
        local blur = CCSprite:create('white_circle_blur.png')
        blur:setPosition(center)
        blur:setColor(ccc3(182,79,207))
        blur:setOpacity(230)
        blur:setScale(4)
        local questionMark = pix2d.CustomSprite:createWithSpriteFrameName('question_mark_hd.png')
        anim:dance(questionMark)
        questionMark:setPosition(center)
        local comingSoonMenu = self:dummyLevelSectorMenu()
        comingSoonLayer:addChild(comingSoonMenu)
        comingSoonLayer:addChild(colorLayer)
        comingSoonLayer:addChild(blur)
        comingSoonLayer:addChild(questionMark)
        self.levelsMenuLayer:addChild(comingSoonLayer,0,self.nSeasons)
        table.insert(self.levelsMenus,comingSoonMenu)
    end
    -- Update the seasons titles when locale changed
    mediator:subscribe(mediator.ns.localeChanged,function ()
        for i,v in ipairs(seasonsTitles) do
            v.label:setString(manager.i18n('season_name_' .. v.id))
        end
    end)
    -- Create the page tip menu
    local menuPageTip = CCMenu:create()
    self.navTips = {}
    for i = 1, 5 do
        local item = util.createCustomMenuItem('scroll_nav_normal.png','scroll_nav_selected.png')
        menuPageTip:addChild(item,i)
        table.insert(self.navTips,item)
    end
    menuPageTip:alignItemsHorizontallyWithPadding(visible:sizeAt(0.02,1).width)
    menuPageTip:setPositionY(visible:bottom().y + visible:sizeAt(1,0.05).height)
    menuPageTip:setEnabled(false) -- TODO change page when tap the nav items
    menuPageTip:setVisible(true)

    -- Create the page navigation menu
    local navItemsDef = {
        {
            frame = 'arrow_left.png',
            position = visible:left(),
            tapHandler = function() self.container:moveToPreviousPage(true) end,
            blink = true,
            anchor = ccp(0,0.5)
        }, {
            frame = 'button_play.png',
            position = ccp(visible:pointAt(1,0.2)),
            tapHandler = function() self.container:moveToNextPage(true) end,
            blink = false,
            anchor = ccp(1,0.5)
        }, {
            frame = 'arrow_right.png',
            position = visible:right(),
            tapHandler = function() self.container:moveToNextPage(true) end,
            blink = true,
            anchor = ccp(1,0.5)
        }, {
            frame = 'arrow_up.png',
            position = visible:top(),
            tapHandler = function() self.vcontainer:moveToNextPage(true) end,
            blink = true,
            anchor = ccp(0.5,1)
        }, {
            frame = 'arrow_down.png',
            position = visible:bottom(),
            tapHandler = function() self.vcontainer:moveToPreviousPage(true) end,
            blink = true,
            anchor = ccp(0.5,0)
        }
    }
    self.menuNav = CCMenu:create()
    self.menuNav:setPosition(visible:leftBottom())
    for _,v in ipairs(navItemsDef) do
        local item = util.createCustomMenuItem(v.frame)
        if v.blink then item:runAction(anim:blinkFade()) end
        item:setPosition(v.position)
        item:setAnchorPoint(v.anchor)
        item:registerScriptTapHandler(v.tapHandler)
        self.menuNav:addChild(item)
        table.insert(self.navItems,item)
    end
    -- Add a animation to the "play" button arrow
    local x,y = self.navItems[2]:getPosition()
    local a1 = CCMoveBy:create(0.3,ccp(visible:sizeAt(-0.1,0).width,0))
    a1 = CCEaseIn:create(a1,0.3)
    local a2 = CCMoveTo:create(0.3,ccp(x,y))
    a2 = CCEaseOut:create(a2,0.3)
    self.navItems[2]:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(a1,a2)))

    self.hasScrolled = false
    -- Create the horizontal container
    self.container = scroll:createContainer(
    'horizontal',
    {
        creditsContainer,
        outfitsLayer,
        titleLayer,
        self.vcontainer,
        self.levelsMenuLayer
    },
    visible:size(),
    pageid - 1,
    -- disable touches so menu buttons (e.g. start,facebook...) can't be activated while srolling
    function(x,y,started)
        if not started then
            outfitScroll:setTouchEnabled(false)
            titleMenu:setEnabled(false)
            outfitMenu:setEnabled(false)
            creditsScrollView:setTouchEnabled(false)
            physics:layer():setTouchEnabled(false)
        end
    end,
    -- on page changed event. Index start at zero
    function(idx)
        physics:layer():setTouchEnabled(idx == 2)
        for _,menu in ipairs(self.levelsMenus) do
            menu:setEnabled(idx ==4)
        end
        if idx == 0 then -- Scrolled to CREDITS page
            creditsScrollView:setTouchEnabled(true)
            --[[
            -- Scroll credits
            local scriptId = nil
            scriptId = scheduler:scheduleScriptFunc(function()
                creditsScrollView:setContentOffsetInDuration(ccp(0,0),20)
                scheduler:unscheduleScriptEntry(scriptId)
            end,1.5,false)
            --]]
        elseif idx == 1 then -- Scrolled to OUTFITS menu page
            outfitMenu:setEnabled(true)
            outfitScroll:setTouchEnabled(true)
            -- creditsScrollView:setContentOffset(creditsScrollViewOriginalOffset,false)
        elseif idx == 2 then -- Scrolled to MAIN TITLE page
            titleMenu:setEnabled(true)
            physics:layer():setTouchEnabled(true)
        end
        self:updateHorizontalNavItems(idx + 1,db.defaults.cSeasonid)
    end)
    -- Update the nav items
    self:updateHorizontalNavItems(pageid,db.defaults.cSeasonid)


    --------------------------- PARALLAX ---------------------------------------
    local parallax = CCParallaxNode:create()

    local createScrollingTexture = function (p)
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
        return tex
    end

    for i=1,self.nSeasons do
        local tex = createScrollingTexture {
            aabb = { -1, 0, 14, 7 },
            translation = { 0.002, -0.002 },
            texture = 'menu_bg_texture_'..i..'.png',
        }
        tex:setVisible(db.defaults.cSeasonid == i)
        tex:setOpacity(db.defaults.cSeasonid == i and 255 or 0)
        tex:setBlendFunc(util.alphaBlend())
        parallax:addChild(tex,0,ccp(0.1,0),ccp(0,0))
        table.insert(self.st,tex)
    end

    -- Background image
    --[[
    for i=0,3 do
        local bg = CCSprite:create(parallaxMeta.background[idx])
        parallax:addChild(bg,-1,ccp(0.2,0),ccp(bg:getContentSize().width * i,0))
        table.insert(nodes,bg)
    end
    --]]

    local mountSprites = { 'mount_3.png', 'cactus.png', 'palm_tree.png', 'iceberg.png' }
    local positions = { ccp(100,0), ccp(600,0), ccp(1380,0) }
    for i=1,3 do
        for j=1,4 do
            local sprite = CCSprite:createWithSpriteFrameName(mountSprites[j])
            sprite:setAnchorPoint(ccp(0.5,0))
            -- anim:repeatForever(sprite,CCScaleTo:create(1,1,1.1),CCScaleTo:create(1,1))
            parallax:addChild(sprite,0,ccp(0.5,0),positions[i])
            sprite:setVisible(db.defaults.cSeasonid == j)
            table.insert(self.fadeNodes[j],sprite)
        end
    end

    -- The ground texture
    local groundSprites = {'ground_texture.png','ground_texture.png','ground_texture_season3.png','ground_texture_season4.png'}
    if self.comingSoon then table.insert(groundSprites,'coming_soon_ground_texture.png') end
    for i=1,#groundSprites do
        local groundTexture = factory:texture_AABB{
            texture = groundSprites[i],
            -- total width size is the screen size + number of screen * parallax x-ratio
            upperBound = { 0, visible:bottom().y + 15},
            lowerBound = { visible:size().width, visible:bottom().y }
        }
        if i == 2 then groundTexture:setColor(ccc3(255,168,110)) end
        groundTexture:setVisible(db.defaults.cSeasonid == i)
        table.insert(self.fadeNodes[i],groundTexture)
        physics:layer():addChild(groundTexture)
        -- parallax:addChild(groundTexture,0,ccp(1.0,0),ccp(0,0))
    end

    for i=0,8 do
        local bg = CCSprite:create('cloud_parallax1.png')
        bg:setPositionY(top.y)
        bg:setOpacity(128)
        bg:setAnchorPoint(ccp(0.5,1))
        anim:repeatForever(bg,CCScaleTo:create(1,1),CCScaleTo:create(1,1,1.1))
        parallax:addChild(bg,2,ccp(1.8,0),ccp(bg:getContentSize().width * i,top.y))
    end

    for i=0,10 do
        local bg = CCSprite:create('cloud_parallax2.png')
        bg:setOpacity(128)
        bg:setAnchorPoint(ccp(0.5,1))
        anim:repeatForever(bg,CCScaleTo:create(1,1,1.1),CCScaleTo:create(1,1))
        parallax:addChild(bg,1,ccp(2.2,0),ccp(bg:getContentSize().width * i,visible:top().y))
    end

    self.container:addChild(parallax,-1)

    local view = scroll:create(visible:size(),self.container)
    -- view:addChild(self.texBackground)
    view:addChild(self.container)
    view:addChild(self.menuNav)
    view:addChild(menuPageTip)
    scene:addChild(view,-1)
    self.scrollView = view

    -- Create the particle batch node
    -- The particle batch is added to the container layer so
    -- the particle emitter position must be converted to the batch node space
    local particlesTextures = { 'star_particle.png', 'star_particle_2.png' }
    for _,f in ipairs(particlesTextures) do
        self.particleBatch[f] = CCParticleBatchNode:create(f,100)
        self.container:addChild(self.particleBatch[f],self.zorder.particleBatch)
    end

    -- Dummy node to save settings on exit
    local node = class.extend {
        instance = CCNode:create(),
        onEnter = function(self)
            if settings.musicEnabled and not audio:isBackgroundMusicPlaying() then
                audio:setBackgroundMusicVolume(1)
                audio:playBackgroundMusic(settings.audio.background,true)
            end
        end,
        onExit = function(self)
            settings:saveUserSettings()
        end
    }
    scene:addChild(node)

    -- Register for the back key on android
    if settings.platform == kTargetAndroid then
        view:setKeypadEnabled(true)
        -- Key can be either "backClicked" or "menuClicked"
        view:registerScriptKeypadHandler(function(key)
            if key ~= "backClicked" or self.modalDialogShown then return end
            self.modalDialogShown = true
            local layer,dialog = util.dialog(kCCMenuHandlerPriority -2,visible:sizeAt(0.6,0.3),'cancelok',function(e)
                if e == 'ok' then CCDirector:sharedDirector():endToLua() end
                self.modalDialogShown = false
                return true
            end,nil,'messagebox.png')
            dialog:addChild(util.label(self.manager.i18n('quitPrompt'),0,0))
            view:addChild(layer,self.zorder.dialog)
        end)
    end

    if settings.platform == kTargetMacOS then
        local exitButton = util.createCustomMenuItem('button_menu.png',nil,nil,function()
            pix2d.Native:getInstance():exitApp()
        end)
        local googleplay = util.createCustomMenuItemWithSprite('desktop/googleplay.png',nil,nil,function()
            pix2d.Native:getInstance():openURL(settings.url.playstore)
        end)
        local appstore = util.createCustomMenuItemWithSprite('desktop/appstore.png',nil,nil,function()
            pix2d.Native:getInstance():openURL(settings.url.appstore)
        end)
        exitButton:setPosition(visible:pointAt(0.35,0.9))
        googleplay:setPosition(visible:pointAt(0.5,0.9))
        appstore:setPosition(visible:pointAt(0.65,0.9))
        titleMenu:addChild(googleplay)
        titleMenu:addChild(appstore)
        titleMenu:addChild(exitButton)
    end

    self:initPhysics()

    -- pix2d.Native:getInstance():hideAd()
end

return MainMenu
--EOF
