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
local mediator = require 'mediator'
local class = require 'class'
local settings = require 'settings'()

-- Declare shortcuts
local visible = pix2d.VisibleRect
local audio = SimpleAudioEngine:sharedEngine()

-- The package table
local Hud = {}; Hud.__index = Hud

setmetatable(Hud,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            gameplayHasStarted = false,
            gamecompleted = false,
            allCoinsCollected = false,
            tools = {}, -- List of available tools. Fill dynamically while loading the level.
            layer = nil, -- main HUD layer
            ingameMenuNode = nil, -- ingame HUD node (pause/reset buttons,score label,toolbar)
            menu = nil, -- main HUD menu
            toolsMenu = nil,
            tags = {
                toolbar_background = 1
            }
        }, Hud)
    end
})

local function unselectAllMenuItems(menu)
    util.forEachChild(menu,function(item) item:setSelectedIndex(0) end,'CCMenuItemToggle')
end

local function unselectAllOthersMenuItems(menu,selected)
    util.forEachChild(menu,function(item) if item ~= selected then item:setSelectedIndex(0) end end,'CCMenuItemToggle')
end

function Hud:selectTool(name)
    mediator:publish(mediator.ns.tool_selected,name)
    self.layer:setTouchEnabled(true)
    self.currentTool = self.tools[name]
    unselectAllOthersMenuItems(self.toolsMenu,self.currentTool.item)
end

function Hud:unselectTool(name)
    mediator:publish(mediator.ns.tool_unselected,name)
    self.layer:setTouchEnabled(false)
    unselectAllMenuItems(self.toolsMenu)
    self.currentTool = nil
end

-- Touch handler for the tool items (triggered when the item is selected)
-- If the tool is selected the touch on the layer is enabled.
-- The tool_began event is published when the player touch the screen.
function Hud:itemTouchHandler(name)
    local tool = self.tools[name]
    -- Cancel the tool if tap on the same item twice
    if tool.item:getSelectedIndex() == 0 then
        audio:playEffect(settings.audio.switch2)
        self:unselectTool(name)
        return
    end
    -- Play effect when select a tool box item
    audio:playEffect(settings.audio.switch)

    if not self.gameplayHasStarted then
        mediator:publish(mediator.ns.gameplayStarted,'toolbox') -- Start gameplay by tapping on the toolbox
    end

    if tool.count > 0 then
        self:selectTool(name)
        -- handle touches on the hud layer
        local px = nil -- previous tool index positions
        local py = nil
        local cancelFocus = false -- if has cancel focus
        -- cancellation bounds
        local lx,ly = visible:pointAt(0.05,0.05)
        local ux,uy = visible:pointAt(0.95,0.95)
        --uy = pix2d.Physics:unitToPixel(0,5.9).y -- Cancel focus if above the 6th map raw
        local touchMoved = false
        local rect
        do
            local x,y = physics:positionInPixel()
            local size = physics:sizePixel()
            rect = CCRectMake(x,y,size.width,size.height - (2 * physics:getUnitInPixel()))
        end
        local function isTouchCanceled(x,y)
            return not rect:containsPoint(ccp(x,y))
        end
        self.layer:registerScriptTouchHandler(function(e,x,y)
            -- Since calling setTouchEnabled(false) is not enough (e.g. move,ended and cancel will still be notified)
            -- we have to check explicitly first if touch is still enabled
            if not self.layer:isTouchEnabled() then return end
            -- convert position into indexes
            local r,t = pix2d.Physics:pixelToUnit(x,y)
            cx = math.floor(r)
            cy = math.floor(t)
            if e == 'moved' then
                touchMoved = true
                mediator:publish(mediator.ns.tool_focus_moved,name,cx,cy,r,t,x,y)
                -- Publish a event if grid position changed or check every moves if focus cancel is on
                if cancelFocus or cx ~= px or cy ~= py then
                    mediator:publish(mediator.ns.tool_focus_changed,name,cx,cy,r,t,x,y)
                    px = cx; py = cy
                end
                if isTouchCanceled(x,y) then
                    mediator:publish(mediator.ns.tool_focus_cancel,name,cx,cy,r,t,x,y)
                    cancelFocus = true
                end
            elseif e == 'ended' then
                if not touchMoved or not isTouchCanceled(x,y) then
                    -- Don't know why QueryMap won't work with width > 0.2 and height > 0.2
                    if isTouchCanceled(x,y) or pix2d.QueryMap:query(cx+0.5,cy+0.5,0.05,0.05) then
                        -- audio:playEffect(settings.audio.fail)
                        mediator:publish(mediator.ns.tool_focus_cancel,name,cx,cy,r,t,x,y)
                    else
                        audio:playEffect(settings.audio.card)
                        mediator:publish(mediator.ns.tool_focus_ended,name,cx,cy,r,t,x,y)
                    end
                end
                self:unselectTool(name)
            elseif e == 'canceled' then
                self:unselectTool(name) -- TODO testing required
            else
                -- Touch began
                if tool.count > 0 then
                    touchMoved = false
                    px = cx; py = cy
                    -- Must publish a tool began first (see sniffer node)
                    mediator:publish(mediator.ns.tool_focus_began,name,cx,cy,r,t,x,y)
                    -- Then check if it's a valid touch
                    if isTouchCanceled(x,y) then
                        mediator:publish(mediator.ns.tool_focus_cancel,name,cx,cy,r,t,x,y)
                    end
                    return true
                end
                return false
            end
        end,
        false, -- Changing parameters here will not have impact. They must be set in the init function below
        0,
        true)
    end
end

function Hud:updateStatus(tool)
    local enabled = true
    if tool.count < 1 then
        tool.count = 0
        enabled = false
        -- Cancel tool if no more tool available
        self:unselectTool(tool.name)
    end
    tool.item:setEnabled(enabled)
    tool.labelSprite:setVisible(enabled)
    tool.label:setString(''..tool.count)
    --[[
    local meta = tool.item:getChildByTag(1)
    if meta then
        meta:setVisible(enabled)
    end
    --]]
end

function Hud:consume(name,v)
    local tool = self.tools[name]
    if -1 < tool.count - v then
        tool.count = tool.count - v
        self:updateStatus(tool)
    end
end

function Hud:fill(name,v)
    local tool = self.tools[name]
    tool.count = tool.count + v
    self:updateStatus(tool)
end

function Hud:reset(name)
    local tool = self.tools[name]
    tool.count = tool.original_count
    self:updateStatus(tool)
end

function Hud:set(name,v)
    local tool = self.tools[name]
    tool.count = v
    self:updateStatus(tool)
end

-- Debug function to print the tools status
function Hud:dumpTools()
    print 'Dump tools table:'
    for k,v in pairs(self.tools) do
        print(k)
        for i,j in pairs(v) do
            print(i,j)
        end
    end
end

--[[
Create the tool box with a variable list of items. The player select an item and if the count for this
item is not zero than he can touch the screen to trigger the tool (a callback function is then called).
The menu is disabled by default. Returns the HUD menu.
p = {
name = { count, normal, selected, disabled, callback },
name2 = ...
}
name: tool's name
count: initial tool's count
normal,selected,disabled: frame name for the normal/selected/disabled sprite item
callback: callback function to call when the player touch the layer after selecting an item.
First parameter of the callbakc is the tool table.
Second and third parameters are the touch's x and y. The tool table has the following value set.
item: reference to the menu item
original_count: origial count set when the item was created
count: current count for this item
callback: current callback function
The special 'meta' key is used to provide extra parameters like a sprite to add to the item
--]]
function Hud:createToolbox(p)
    -- Create the menu
    self.toolsMenu = CCMenu:create()
    self.ingameMenuNode:addChild(self.toolsMenu)
    local maxHeight = 0
    -- Create the meta sprite
    local meta = p.meta
    p.meta = nil -- remove the meta entry from the table `p` so we don't iterate on it
    -- Create items for each entry in table 'p'. Tools are ordered using the table `names` below.
    local names = { 'rope', 'block', 'balloon', 'fan', 'cardboard', 'teleport', 'trampoline', 'elastic' }
    local blink = p['blink']
    for _,name in ipairs(names) do
        local t = p[name]
        if t ~= nil then
            local enabled = t.count > 0
            local normal = util.createMenuItem(t.normal,t.normal,t.disabled)
            local selected = util.createMenuItem(t.selected, t.selected, t.disabled)
            local toggle = pix2d.CustomMenuItemToggle:create(normal)
            toggle:addSubItem(selected)
            maxHeight = math.max(maxHeight,normal:getContentSize().height)
            maxHeight = math.max(maxHeight,selected:getContentSize().height)
            local sprite = CCSprite:createWithSpriteFrameName(meta.sprite)
            sprite:setVisible(enabled)
            local size = toggle:getContentSize()
            sprite:setPosition(meta.position[1]*size.width,meta.position[2]*size.height)
            toggle:addChild(sprite,1)
            local label = util.labelTTF(''..t.count,'Chewy','Small')
            local spriteSize = sprite:getContentSize()
            label:setPosition(spriteSize.width/2,spriteSize.height/2)
            sprite:addChild(label)
            self.tools[name] = {
                count = t.count,
                original_count = t.count,
                item = toggle,
                label = label,
                labelSprite = sprite,
                selected = t.selected,
                normal = t.normal,
                disabled = t.disabled
            }
            toggle:setEnabled(enabled)
            self.toolsMenu:addChild(toggle)
            if blink and name == blink then
                -- toggle:runAction(CCSequence:createWithTwoActions(CCDelayTime:create(0.3),CCBlink:create(1,5)))
                -- Blink only the `normal` sprite so the user is able to tap the item while is not visible. See CustomMenuItem.cpp
                local blinkAction = CCSequence:createWithTwoActions(CCDelayTime:create(0.3),CCBlink:create(1,5))
                normal:runAction(blinkAction)
                toggle:registerScriptTapHandler(function()
                    if blinkAction then normal:stopAction(blinkAction); blinkAction = nil end
                    normal:setVisible(true); self:itemTouchHandler(name)
                end)
            else
                toggle:registerScriptTapHandler(function() self:itemTouchHandler(name) end)
            end
        end
    end
    self.toolsItemMaxHeight = maxHeight
    self.toolsMenu:setAnchorPoint(ccp(0.5,0))
    self.toolsMenu:alignItemsHorizontallyWithPadding(8)
    self:runToolboxIntro()
    -- The menu's background
    local bg = CCLayerColor:create(ccc4(32,32,32,48))
    bg:setContentSize(util.childrenBoundingBox(self.toolsMenu,{10,0}).size)
    bg:setAnchorPoint(ccp(0.5,1.0))
    bg:ignoreAnchorPointForPosition(false)
    bg:setPosition(visible:top())
    self.ingameMenuNode:addChild(bg,-1,self.tags.toolbar_background)
    return self.toolsMenu
end

function Hud:runToolboxIntro()
    self.toolsMenu:setPosition(visible:top())
    self.toolsMenu:runAction(CCMoveBy:create(0.3,ccp(0,-self.toolsItemMaxHeight/2)))
end

function Hud:createPauseAndResetButtons(p)
    local rightTop = visible:rightTop()
    local leftTop = visible:leftTop()
    -- Create the menu
    self.menu = CCMenu:create()
    self.menu:setPosition(visible:leftBottom())
    self.ingameMenuNode:addChild(self.menu)
    -- Create the reset button
    local _resetButtonFlag = false
    local b = util.createCustomMenuItem('button_reset.png')
    b:registerScriptTapHandler(function()
        if not _resetButtonFlag then
            _resetButtonFlag = true
            mediator:publish(mediator.ns.resetLevelScene)
        end
    end)
    local size = b:getContentSize()
    b:setPosition(rightTop.x - size.width/2, rightTop.y - size.height/2)
    self.resetButton = b
    self.menu:addChild(b)
    -- Create the pause button
    b = util.createCustomMenuItem('button_pause.png')
    b:registerScriptTapHandler(function()
            mediator:publish(mediator.ns.pauseScene)
    end)
    b:setPosition(leftTop.x + size.width/2, leftTop.y - size.height/2)
    self.pauseButton = b
    self.menu:addChild(b)
    -- Create the score label
    --[[
    local label = CCLabelBMFont:create('0','Chewy.fnt')
    -- Set the label position to the right of the pause button
    label:setPosition(
        b:getPositionX() + b:getContentSize().width/2,
        b:getPositionY())
    label:setAnchorPoint(ccp(0,0.5))
    local oldScore = 0
    local action = nil
    -- Catch the updateScore event and run the update action
    mediator:subscribe(mediator.ns.updateScore,
        function(event,score)
            if action then label:stopAction(action) end
            action = label:runAction(CCEaseOut:create(pix2d.ActionTweenLua:create(
                0.5,'',oldScore,oldScore + score,
                function(value,key) label:setString(''..math.floor(value)) end),0.4))
            oldScore = oldScore + score
        end)
    self.ingameMenuNode:addChild(label)
    --]]
    return self.menu
end

-- Distrbute horizontally 'node' children and return the local center of the aligned children
-- DEPRECATED: use CCMenu:alignItemsHorizontallyWithPadding instead
--[[
function distributeCenterHorizontal(node,margin)
    local children = node:getChildren()
    local count = children:count()
    local prev = nil
    local length = 0
    print('count',count)
    for i = 0, count-1 do
        local cur = children:objectAtIndex(i)
        if prev then
            local offset = cur:getContentSize().width / 2 + prev:getContentSize().width / 2 + margin
            length = length + offset
            cur:setPosition(prev:getPositionX() + offset,0)
        else
            cur:setPosition(0,0)
        end
        prev = cur
    end
    return ccp(length/2,0)
end
--]]

local function createBlurLayer(parent,node)
    -- Capture and blur the screen
    local blur = pix2d.FastBlur:create(node,visible:size(),2.0)
    blur:clear(pix2d.Physics:getDefaultBackgroundColor())
    local capture = blur:capture()
    -- capture = pix2d.Grayscale:create(capture,visible:size()):capture()
    -- capture:getSprite():setColor(ccc3(204,87,59))
    parent:addChild(capture)
    -- Create the pause layer
    -- local colorLayer = CCLayer:create()
    local colorLayer = CCLayerColor:create(ccc4(0,0,0,180))
    parent:addChild(colorLayer)
    return colorLayer, capture
end

function Hud:tutorialLayer(msg,callback,node)
    local center = visible:center()
    self.ingameMenuNode:setVisible(false)
    local colorLayer,capture = createBlurLayer(self.layer,node)
    -- Create the start message label
    local label = util.label(msg,center.x,center.y)
    label:runAction(CCRepeatForever:create(
        CCSequence:createWithTwoActions(CCEaseOut:create(CCFadeOut:create(1.3),0.6),CCFadeIn:create(0.3))))
    colorLayer:addChild(label)

    local sprite, action = anim:runAnimation {
        repeatForever = true,
        delay = 0.4,
        frames = { 'hand1.png', 'hand2.png' }
    }
    sprite:setPositionX(center.x)
    sprite:setPositionY(center.y - label:getContentSize().height)
    colorLayer:addChild(sprite)

    colorLayer:registerScriptTouchHandler(function()
        self.ingameMenuNode:setVisible(true)
        self.menu:runAction(CCFadeIn:create(0.5))
        self.toolsMenu:runAction(CCFadeIn:create(0.5))
        colorLayer:removeFromParentAndCleanup(true)
        capture:removeFromParentAndCleanup(true)
        if callback then callback() end
        return true
    end,
    false, -- no multi-touch (process touches one by one)
    kCCMenuHandlerPriority-1, -- touch priority higher than CCMenu
    true) -- swallows touches if handler returns true
    -- setTouchEnabled MUST be called after registerScriptTouchHandler
    -- If called before it will create a touch default touch delegate without
    -- the options passed to `registerScriptTouchHandler`
    colorLayer:setTouchEnabled(true)
end

local function assignCustomMenuItem(node,tapHandler)
    tolua.cast(node,'pix2d::CustomMenuItem')
    node:registerScriptHandler(function(name)
        if name == 'selected' then
            node:runAction(CCEaseElasticOut:create(CCScaleTo:create(0.5,1.1)))
        else
            node:runAction(CCEaseElasticOut:create(CCScaleTo:create(0.5,1.0)))
        end
    end)
    node:registerScriptTapHandler(tapHandler)
    return node
end

-- Create the pause layer.
-- msg: a string to be displayed at the center of the screen
-- node: the node to blur (should be the scene)
function Hud:pauseLayer(node)
    local center = visible:center()
    self.ingameMenuNode:setVisible(false)
    local colorLayer, capture = createBlurLayer(self.layer,node)

    -- audio:playEffect(settings.audio.pause)

    -- Create the pause layer
    local resumeGame = function()
        -- audio:playEffect(settings.audio.switch2)
        self.ingameMenuNode:setVisible(true)
        self:runToolboxIntro()
        colorLayer:removeFromParentAndCleanup(true)
        capture:removeFromParentAndCleanup(true)
        mediator:publish(mediator.ns.resumeGameplay)
        return false
    end
    -- As suggested by Sandra resume should only be done using the resume button
    --[[
    colorLayer:registerScriptTouchHandler(
    resumeGame,
    false, -- no multi-touch (process touches one by one)
    kCCMenuHandlerPriority +1, -- touch priority LOWER than CCMenu
    true) -- swallows touches if handler returns true
    -- setTouchEnabled MUST be called after registerScriptTouchHandler
    -- If called before it will create a touch default touch delegate without
    -- the options passed to `registerScriptTouchHandler`
    colorLayer:setTouchEnabled(true)
    --]]

    local menu = nil
    local node = pix2d.CocosBuilderLua:create('data/ccb/pause.ccbi',
    function(target,name,node)
        if name == 'reset' then
            assignCustomMenuItem(node,function() mediator:publish(mediator.ns.resetLevelScene) end)
        elseif name == 'resume' then
            assignCustomMenuItem(node,resumeGame)
        elseif name == 'next' then
            local nextlevel = self.manager:getNextLevel()
            if nextlevel and nextlevel.score > -2 then
                assignCustomMenuItem(node,function() mediator:publish(mediator.ns.runNextLevel) end)
            else
                node:setVisible(false)
            end
        elseif name == 'music' then
            -- Hack to create a toogle button instead of a default menu item
            local toggle = CCMenuItemToggle:create(util.createMenuItem('button_music.png'))
            toggle:addSubItem(util.createMenuItem('button_music_disabled.png'))
            local backgroundMusicLoaded = settings.musicEnabled
            toggle:registerScriptTapHandler(function()
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
            toggle:setSelectedIndex(settings.musicEnabled and 0 or 1)
            local menu = CCMenu:create()
            menu:addChild(toggle)
            menu:setPosition(0,0)
            node:addChild(menu)
        elseif name == 'sounds' then
            -- Hack to create a toogle button instead of a default menu item
            local toggle = CCMenuItemToggle:create(util.createMenuItem('button_sounds.png'))
            toggle:addSubItem(util.createMenuItem('button_sounds_disabled.png'))
            toggle:registerScriptTapHandler(function()
                settings.soundsEnabled = not settings.soundsEnabled
                audio:setEffectsVolume(settings.soundsEnabled and 1 or 0)
            end)
            toggle:setSelectedIndex(settings.soundsEnabled and 0 or 1)
            local menu = CCMenu:create()
            menu:addChild(toggle)
            menu:setPosition(0,0)
            node:addChild(menu)
        elseif name == 'mainmenu' then
            assignCustomMenuItem(node,function() mediator:publish(mediator.ns.runMainMenuScene,5) end)
        elseif name == 'stats' then
            local levelid, seasonid = self.manager:getCurrentLevelId()
            local score = self.manager:getSeasonProgress(seasonid)
            tolua.cast(node,'CCLabelBMFont')
            node:setString(string.format('%s %d-%d',self.manager.i18n('level'),levelid,seasonid))
        elseif name == 'title' then
            tolua.cast(node,'CCLabelBMFont')
            node:setString(self.manager.i18n('paused'))
        end
    end,function() end)
    colorLayer:addChild(node)
end

function Hud:runGamecompletedScene(event)
    self.layer:addChild(pix2d.CocosBuilderLua:create('data/ccb/gamecompleted.ccbi',
    function(target,name,node)
        if name == 'back' then
            assignCustomMenuItem(node,function() mediator:publish(event) end)
        elseif name == 'label1' then
            tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('wellDone'))
        elseif name == 'label2' then
            if self.allCoinsCollected then
                tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('allCoinsCollected'))
            elseif self.gamecompleted then
                tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('allLevelsCompleted'))
            end
        elseif name == 'label3' then
            if self.allCoinsCollected then
                tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('moreLevelComingSoon'))
            elseif self.gamecompleted then
                tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('allLevelsCompletedComment'))
            end
        end
    end,function() end))
    self.gamecompleted = false -- Don't think it's required since the a new hud is created on each level but just in case
    selg.allCoinsCollected = false
end

function Hud:createScoreMenu(node,score)
    self.ingameMenuNode:setVisible(false)
    local colorLayer, capture = createBlurLayer(self.layer,node)
    -- Get saved score
    -- local score = self.manager:getCurrentLevel().score
    local coin1, coin2, coin3
    local particle1, particle2, particle3 = nil, nil, nil
    local fx1, fx2, fx3 = nil, nil, nil
    local ccb = pix2d.CocosBuilderLua:create('data/ccb/winscene.ccbi',
    function(target,name,node)
        if name == 'reset' then
            assignCustomMenuItem(node,function()
                if self.gamecompleted or self.allCoinsCollected then self:runGamecompletedScene(mediator.ns.resetLevelScene)
                else mediator:publish(mediator.ns.resetLevelScene) end
            end)
        elseif name == 'next' then
            assignCustomMenuItem(node,function()
                if self.gamecompleted or self.allCoinsCollected then self:runGamecompletedScene(mediator.ns.runNextLevel)
                else mediator:publish(mediator.ns.runNextLevel) end
            end)
            local enabled = self.manager:getNextUnlockedLevel() ~= nil
            node:setEnabled(enabled)
            node:setVisible(enabled)
        elseif name == 'mainmenu' then
            assignCustomMenuItem(node,function()
                if self.gamecompleted or self.allCoinsCollected then self:runGamecompletedScene(mediator.ns.runMainMenuScene)
                else mediator:publish(mediator.ns.runMainMenuScene,5) end
            end)
        elseif name == 'stats' then
            local levelid, seasonid = self.manager:getCurrentLevelId()
            tolua.cast(node,'CCLabelBMFont'):setString(('%s %d-%d'):format(self.manager.i18n('level'),levelid,seasonid))
        elseif name == 'title' then
            tolua.cast(node,'CCLabelBMFont'):setString(self.manager.i18n('winlabel'))
        elseif name == 'coin1' then
            coin1 = node
        elseif name == 'coin2' then
            coin2 = node
        elseif name == 'coin3' then
            coin3 = node
        elseif name == 'particle1' then
            particle1 = tolua.cast(node,'CCParticleSystem')
        elseif name == 'particle2' then
            particle2 = tolua.cast(node,'CCParticleSystem')
        elseif name == 'particle3' then
            particle3 = tolua.cast(node,'CCParticleSystem')
        end
    end, function(name)
        if name == 'Intro' then
            coin1:setVisible(score > 0)
            coin2:setVisible(score > 1)
            coin3:setVisible(score > 2)
            if score > 0 then
            particle1:runAction(CCSequence:createWithTwoActions(
                CCDelayTime:create(0.5),CCCallFunc:create(function()
                    if particle1 then
                        fx1 = audio:playEffect(settings.audio.chime2)
                        particle1:setVisible(true)
                        particle1:resetSystem()
                    end
                end)))
            end
            if score > 1 then
            particle2:runAction(CCSequence:createWithTwoActions(
                CCDelayTime:create(1.0),CCCallFunc:create(function()
                    if particle2 then
                        fx2 = audio:playEffect(settings.audio.chime3)
                        particle2:setVisible(true)
                        particle2:resetSystem()
                    end
                end)))
            end
            if score > 2 then
            particle3:runAction(CCSequence:createWithTwoActions(
                CCDelayTime:create(1.5),CCCallFunc:create(function()
                    if particle3 then
                        fx3 = audio:playEffect(settings.audio.chime4)
                        particle3:setVisible(true)
                        particle3:resetSystem()
                    end
                end)))
            end
        end
    end)
    colorLayer:addChild(class.extend {
        instance = ccb,
        onExit = function(self)
            particle1 = nil; particle2 = nil; particle3 = nil
            if fx1 then audio:stopEffect(fx1) end
            if fx2 then audio:stopEffect(fx2) end
            if fx3 then audio:stopEffect(fx3) end
        end
    })
    if self.newSeasonsUnlocked then
        for _,v in pairs {'mainmenu01','mainmenu02','mainmenu03'} do
            CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile(v..'.plist')
        end
        local layer,dialog = util.dialog(kCCMenuHandlerPriority -2,visible:sizeAt(0.6,0.7),'ok',function ()
            return true
        end,nil,'messagebox.png')
        dialog:addChild(util.label(self.manager.i18n('wellDone'),0,80))
        dialog:addChild(util.label(self.manager.i18n('newSeason'),0,50,0.8))
        local thumbnail = CCSprite:createWithSpriteFrameName('thumbnail_season_'..self.newSeasonsUnlocked..'.png')
        thumbnail:setScale(0.8)
        thumbnail:setPositionY(-30)
        dialog:addChild(thumbnail)
        colorLayer:addChild(layer)
        self.newSeasonsUnlocked = nil
    end
    mediator:publish(mediator.ns.gameplayPaused)
end

function Hud:loseScene(x,y)
    self.pauseButton:setVisible(false)
    -- Create the iris wipe action and show the menu when it's done
    local iris = pix2d.IrisWipe:create(x,y,false,ccc4f(0,0,0,0.8),visible:size().width*0.8,0.2,0.4)
    iris:registerCallbackHandler(function()
        self.ingameMenuNode:setVisible(true);
        self.resetButton:setVisible(true)
    end)

    -- Close the iris transition and restart the level
    local mutex = true
    local function closeIrisAndResetLevel()
        if mutex then
            iris:getStencil():runAction(CCSequence:createWithTwoActions(
            CCScaleTo:create(0.1,0),
            CCCallFunc:create(function() mediator:publish(mediator.ns.resetLevelScene,{blink=true}) end)))
            -- Move the stencil to follow the scale action
            iris:getStencil():runAction(CCMoveTo:create(0.1,ccp(x,y)))
            mutex = false
        end
    end

    local s = pix2d.Physics:unitToPixel(1,1)
    local rect = CCRectMake(x-(s.x/2),y-(s.y/2),s.x,s.y)
    local dummyLayer = CCLayer:create()
    dummyLayer:registerScriptTouchHandler(function(e,x,y)
        if rect:containsPoint(ccp(x,y)) then
            closeIrisAndResetLevel()
        end
        return false
    end,false,0,false)
    dummyLayer:setTouchEnabled(true)
    self.layer:addChild(dummyLayer)

    self.resetButton:registerScriptTapHandler(closeIrisAndResetLevel)
    self.layer:addChild(iris,self.menu:getZOrder()-1)
end

-- DEPRECATED
function Hud:loseScene2(x,y)
    self.ingameMenuNode:setVisible(false)
    self.layer:addChild(pix2d.CocosBuilderLua:create('data/ccb/losescene.ccbi',
    function(target,name,node)
        if name == 'reset' then
            assignCustomMenuItem(node,function() mediator:publish(mediator.ns.resetLevelScene) end)
        end
    end,function() end))
end

-- Initialize and return the HUD
function Hud:init(manager)
    self.manager = manager
    self.layer = CCLayer:create()
    -- We have to register the touch handler BEFORE adding the layer to the scene.
    -- Because the touch delegate is created once when the layer enter the scene (onEnter())
    -- calling registerScriptTouchHandler after will not create a new touch delegate so
    -- the default touch delegate is always used (standard delegate: kCCTouchesAllAtOnce)
    self.layer:registerScriptTouchHandler(
        function(e,x,y) return false end,
        false,
        -- kCCMenuHandlerPriority + 1, -- Fewer touch priority than CCMenu
        0, -- Priority higher than the PhysicsLayer touch priority (lower number is a higher priority)
        true) -- Swallow touches
    -- Call setTouchEnabled AFTER `registerScriptTouchHandler`
    self.layer:setTouchEnabled(false)
    -- scene:addChild(self.layer)

    self.ingameMenuNode = CCNode:create()
    self.layer:addChild(self.ingameMenuNode)

    mediator:subscribe(mediator.ns.tool_touched, function()
        if self.currentTool then self:unselectTool(self.currentTool) end
    end)

    local _gameplayPausedFlag = false
    mediator:subscribe(mediator.ns.resumeGameplay,function()
        self.toolsMenu:setEnabled(true)
        _gameplayPausedFlag = false
    end)
    mediator:subscribe(mediator.ns.pauseGameplay,function()
        if gameplayStarted then  self.toolsMenu:setEnabled(false) end
    end)

    mediator:subscribe(mediator.ns.showLoseScene,function(e,x,y)
        self.toolsMenu:setVisible(false)
        self.menu:setEnabled(true)
        self:loseScene(x,y)
    end)

    mediator:subscribe(mediator.ns.lose,function(e,x,y)
        self.toolsMenu:setEnabled(false)
        self.menu:setEnabled(false)
        self.ingameMenuNode:setVisible(false)
        self.layer:setTouchEnabled(false)
    end)

    mediator:subscribe(mediator.ns.win,function(e,x,y)
        self.toolsMenu:setEnabled(false)
        self.menu:setEnabled(false)
        self.layer:setTouchEnabled(false)
    end)

    mediator:subscribe(mediator.ns.season_unlocked,function(_,seasonid)
        self.newSeasonsUnlocked = seasonid
    end)

    mediator:subscribe(mediator.ns.all_levels_completed,function()
        self.gamecompleted = true
    end)

    mediator:subscribe(mediator.ns.all_coins_collected,function()
        self.allCoinsCollected = true
    end)

    mediator:subscribe(mediator.ns.gameplayStarted,function()
        self.gameplayHasStarted = true
    end)

    mediator:subscribe(mediator.ns.pauseScene,function()
        -- Check that we don't pause the scene twice
        if not _gameplayPausedFlag then
            _gameplayPausedFlag = true
            mediator:publish(mediator.ns.pauseGameplay)
            self:pauseLayer(physics:getScene())
            mediator:publish(mediator.ns.gameplayPaused)
        end
        return false
    end)

    mediator:subscribe(mediator.ns.activateToolItem,function(_,name)
        unselectAllMenuItems(self.toolsMenu)
        self.tools[name].item:setSelectedIndex(1)
    end)

    -- Sniffer node to check on-the-fly if a tool can be inserted in the current map cell
    self.layer:addChild(class.extend {
        instance = CCNode:create(),
        canceled = false,
        onEnter = function(self)
            mediator:subscribe(mediator.ns.tool_focus_changed,function(_,...)
                self.arg = {...}
                self.canceled = false
            end)
            mediator:subscribe(mediator.ns.tool_focus_moved,function(_,...)
                self.arg = {...}
                self.canceled = false
            end)
            mediator:subscribe(mediator.ns.tool_focus_began,function(_,...)
                self.arg = {...}
                self.canceled = false
                self:scheduleUpdateWithPriorityLua(function(dt)
                    -- self.arg[1] = name, self.arg[2] = cx, ...
                    if pix2d.QueryMap:query(self.arg[2] + 0.5, self.arg[3] + 0.5, 0.05, 0.05) then
                        if not self.canceled then
                            self.canceled = true
                            mediator:publish(mediator.ns.tool_focus_cancel,unpack(self.arg))
                        end
                    elseif self.canceled then
                        self.canceled = false
                        mediator:publish(mediator.ns.tool_focus_changed,unpack(self.arg))
                    end
                end,1)
            end)
            mediator:subscribe(mediator.ns.tool_unselected,function()
                self:unscheduleUpdate()
            end)
        end,
    })

    return self
end

return Hud
-- EOF
