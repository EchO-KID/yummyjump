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

-- Load packages
local json = require 'json'
local util = require 'util'
local class = require 'class'
local scroll = require 'scroll'
-- WARNING: physics is now a global variable
-- Here (Manager package) we actually use the 'physics'
-- package to create the physics singleton
local Physics = require 'physics'
local mediator = require 'mediator'
local MainMenu = require 'mainmenu'
local Level = require 'level'
local Hud = require 'hud'
local Grid = require 'grid'
local settings = require 'settings'()

local visible = pix2d.VisibleRect

print 'Loading package manager'

local director = CCDirector:sharedDirector()
local visible = pix2d.VisibleRect

local Manager = {
    initialized = false,
    dbFilename = 'yjmp.db',
    -- Level data files format: 'data/season_n/level_n.json'
    dataFolder = 'data',
    db = nil,
    dirty = false, -- DB needs to be saved on file on next scene
    level = nil, -- current level instance
    level_data = nil,
    hud = nil, -- hud instnace
    grid = nil, -- grid instance
    status = {
        lock = -2,
        unlock = -1,
        completed = 0
    }
}; Manager.__index = Manager

function Manager:loadGameDB()
    local data = util.readDataFileSafe(CCFileUtils:sharedFileUtils():getWritablePath()..self.dbFilename)
    if not data or data == '' then
        print 'INFO: No game database. Create the database...'
        return self:wipeGameDatabase()
    end
    return json.decode(data)
end

function Manager:saveGameDB(db)
    local data = json.encode(db)
    -- print(data)
    if not util.writeDataFileSafe(self.dbFilename,data) then
        print "ERROR: can't write game database to file"
        return nil
    end
    print 'INFO: Game database saved.'
    self.dirty = false
    return db
end

function Manager:wipeGameDatabase()
    return self:saveGameDB(require 'dummydb'())
end

function Manager:getCurrentLevelId()
    return self.db.defaults.cLevelid, self.db.defaults.cSeasonid
end

-- Returns the level and season metadata and ids or nil if no level found for levelid/seasonid
function Manager:getLevel(levelid,seasonid)
    -- Return the level and season if exist or nil,nil
    return self.db.seasons[seasonid]
        and self.db.seasons[seasonid].levels[levelid], self.db.seasons[seasonid], levelid, seasonid
        or nil, nil, levelid, seasonid
end

-- Returns the current level and season metadata plus the current level and season ids
function Manager:getCurrentLevel()
    return self:getLevel(self.db.defaults.cLevelid,self.db.defaults.cSeasonid)
end

-- Returns the next level metadata or nil if there's no more levels for the current season
function Manager:getNextLevel()
    return self:getLevel(self.db.defaults.cLevelid + 1,self.db.defaults.cSeasonid)
end

function Manager:getLevelCount(seasonid)
    return self.db.seasons[seasonid] and #self.db.seasons[seasonid].levels or nil
end

function Manager:getCurrentLevelCount()
    return self:getLevelCount(self.db.defaults.cSeasonid)
end

-- Return the next 'unlocked' level and season or nil
function Manager:getNextUnlockedLevel()
    -- Get the next level for the current season
    local level,season,levelid,seasonid = self:getNextLevel()
    -- if not level and levelid >= self:getCurrentLevelCount() then
    if not level then
        -- No more level for the current season. Check out next season if this is the last level
        local season, seasonid = self:getNextSeason()
        if season and season.levels[1].score > -2 then
            return season.levels[1], season, 1, seasonid
        end
    elseif level.score > -2 then
        return level, season, levelid, seasonid
    end
end

-- Returns the season and seasonid if exists or nil
function Manager:getSeason(seasonid)
    return self.db.seasons[seasonid] and self.db.seasons[seasonid], seasonid or nil
end

function Manager:getCurrentSeason()
    return self.db.seasons[self.db.defaults.cSeasonid], self.db.defaults.cSeasonid
end

-- Return next season and next season id if exists or nil
function Manager:getNextSeason()
    return self:getSeason(self.db.defaults.cSeasonid + 1)
end

-- Returns the total score, number of completed levels and the level count for
-- a season. Returns nil if the season does not exist.
function Manager:getSeasonProgress(seasonid)
    local season = self.db.seasons[seasonid]
    local score = 0.0
    local completed = 0
    local count = #season.levels
    for i=1,count do
        if season.levels[i].score > 0 then
            score = score + season.levels[i].score
        end
        if season.levels[i].score > -1 then
            completed = completed + 1
        end
    end
    return score, completed, count
end

function Manager:getSeasonProgressPercent(seasonid)
    local score,completed,count = self:getSeasonProgress(seasonid)
    if score then
        return math.floor((score/(count*3))*100), math.floor((completed/count)*100), count
    end
end

function Manager:getCurrentSeasonProgress()
    return self:getSeasonProgress(self.db.defaults.cSeasonid)
end

function Manager:getCurrentSeasonProgressPercent()
    return self:getSeasonProgressPercent(self.db.defaults.cSeasonid)
end

function Manager:getGameProgress()
    local score = 0; local completed = 0; local count = 0
    for i=1,#self.db.seasons do
        local s,c,v = self:getSeasonProgress(i)
        score = score + s; completed = completed + c; count = count + v
    end
    return score, completed, count
end

function Manager:updateGameProgress(score)
    -- assert(score > -1)
    local events = {}
    local level = self:getCurrentLevel()
    -- Score has changed?
    if level.score < score then
        -- print('New score:',score)
        level.score = score
        -- Unlock next level?
        level = self:getNextLevel()
        if level and level.score < score then
            level.score = self.status.unlock
        end
        -- Unlock next season?
        local season, seasonid = self:getNextSeason()
        if season and season.levels[1].score < -1 then
            local score, completed = self:getCurrentSeasonProgress()
            if completed >= season.threshold then
                season.levels[1].score = -1
                table.insert(events,{ ns = mediator.ns.season_unlocked, arg = {seasonid}})
            end
        end
        local score, completed, count = self:getGameProgress()
        -- Collected all bonus?
        if score == count * 3 and not self.all_coins_collected_notified then
            table.insert(events,{ ns = mediator.ns.all_coins_collected })
            self.all_coins_collected_notified = true
        end
        -- Completed all levels?
        if completed == count and not self.all_levels_completed_notified then
            table.insert(events,{ ns = mediator.ns.all_levels_completed })
            self.all_levels_completed_notified = true
        end
        self:saveGameDB(self.db)
        -- Publish postponed events
        for i,v in ipairs(events) do
            mediator:publish(v.ns,v.arg and unpack(v.arg) or nil)
        end
    end
end

function Manager:getCurrentOutfit()
    return self.db.defaults.cCostume > 0 and self.db.assets.costumes[self.db.defaults.cCostume] or nil
end

function Manager:getCurrentOutfitId()
    return self.db.defaults.cCostume
end

function Manager:setCurrentOutfit(id)
    self.dirty = true
    self.db.defaults.cCostume = id
end

function Manager:getOutfits()
    return self.db.assets.costumes
end

function Manager:getOutfit(id)
    return self.db.assets.costumes[id]
end

-- Load and decode the level data for season and level.
-- Level data format: data/season_n/level_n.json
-- Returns the decoded JSON document
function Manager:loadLevelData(seasonid,levelid)
    local filename = ('%s/S%02d/S%02dE%02d.json'):format(self.dataFolder,seasonid,seasonid,levelid)
    local data = util.readDataFileSafe(filename)
    assert(data,"ERROR: Can't load data for level["..levelid..'] season['..seasonid..']')
    return json.decode(data)
end

-- Replace the current scene with a new scene.
-- An intermediary "loading" scene is created and initialized with `initLoader`.
-- Then the target scene is created and initialized with `initTarget`. The target
-- init function is called as follow:
-- initTarget(manager,targetscene,...)
-- Finally the loading scene is replaced with the target scene.
function Manager:loadScene(initLoader,initTarget,releaseMemory,...)
    -- Save the database if needed
    if self.dirty then self:saveGameDB(self.db) end
    local arg = { ... }
    local manager = self
    local loader = class.extend {
        instance = CCScene:create(),
        onEnterTransitionFinish = function(self)
            self.transitionDidFinish = true
        end,
        update = function(self,dt)
            if self.transitionDidFinish then
                self:unscheduleUpdate() -- in case there's an issue we don't want update to be call twice
                -- Release memory between the scene
                if releaseMemory then util.releaseMemory() end
                local target = class.extend {
                    instance = CCScene:create(),
                    onExit = function(self)
                        mediator:purge() -- Remove auto-release subscribers on exit
                    end
                }
                -- Scene initialized correctly. We can safely create the Lua console
                if settings.debug_start_lua_console then
                    target:addChild(pix2d_console.LuaConsole:create(settings.debug_console_ip,settings.debug_console_port))
                end
                -- We use pcall (xpcall in debug) to call the scene init function in order to catch exception
                -- TODO print message to user and return to mainmenu
                local rc = 0; local msg = ''
                if settings.pix2d_debug then
                    rc, msg = xpcall(initTarget,function(err) return debug.traceback(err) end,manager,target,unpack(arg))
                else
                    rc, msg = pcall(initTarget,manager,target,unpack(arg))
                end
                if not rc then
                    CCMessageBox(manager.i18n('fatal'),'Error')
                    print("Lua ERROR: Can't initialize the scene:",msg)
                end
                director:replaceScene(target)
            end
        end
    }
    director:replaceScene(initLoader(loader) or loader)
end

local function newSceneInit(scene)
    pix2d.Physics:setDefaultBackgroundColor(1,189/255,195/255,1)
    local sprite = CCSprite:create('loading_sprite.png')
    sprite:setPosition(visible:center())
    scene:addChild(sprite)
    --[[
    local label = util.labelTTF('Loading...','Chewy','Medium')
    label:setPosition(visible:center())
    scene:addChild(label)
    --]]
    return nil -- no transition
end

local function replaceSceneInit(scene)
    pix2d.Physics:setDefaultBackgroundColor(1,1,1,1)
    return CCTransitionCrossFade:create(0.2,scene)
end

function Manager:loadStoryboard(scene)
    local storyboard = require 'storyboard'():init(scene)
end

-- Load the level seasonid/levelid into scene. We create the HUD and grid here
-- to decouple the modules and avoid module loop
function Manager:loadLevel(scene,seasonid,levelid,param)
    -- TODO this seems to be a performance bottleneck and should be investigated
    -- Removing releaseMemory speed up level loading
    -- self.releaseMemory()
    -- Don't know why but some of the data level seems to be garbage collected when the level is reset
    -- So we have to loaded the data file every time
    -- if not self.level_data or seasonid ~= self.db.defaults.cSeasonid or levelid ~= self.db.defaults.cLevelid then
    self.db.defaults.cSeasonid = seasonid
    self.db.defaults.cLevelid = levelid
    self.level_data = self:loadLevelData(seasonid,levelid)
    assert(self.level_data.season == seasonid,'ERROR: invalid level data: json season does not match')
    assert(self.level_data.levelid == levelid,'ERROR: invalid level data: json levelid does not match')
    -- Load the spritesheets
    -- CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA4444)
    -- CCTexture2D:setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGBA8888) -- Default
    local spritesheets = self.level_data.assets.spritesheets
    if spritesheets then
        for _,v in ipairs(spritesheets) do
            CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile(v)
        end
    end
    -- end
    -- Create the global physics instance
    Physics:create(scene,self.level_data.world)
    -- Create and init the HUD
    self.hud = Hud():init(self)
    -- self.hud.layer:retain()
    self.hud:createPauseAndResetButtons()
    -- end
    self.level_data.tools.meta = {
        sprite = 'item_count.png',
        position = {0.5,0}
    }

    -- Create the HUD menu available at self.hud.menu
    self.hud:createToolbox(self.level_data.tools)
    -- Create and init the GRID
    if settings.showGrid then
        local unit = physics:getUnitInPixel()
        local grid = Grid() -- create a new grid instance
        grid.radius = 0.5
        grid.color = ccc4f(1.0,1.0,1.0,0.4)
        grid.origin_x = unit
        grid.origin_y = unit
        grid.spacing_x = unit
        grid.spacing_y = unit
        local size = physics:sizePixel()
        size.height = size.height - (2 * unit)
        grid.size = size
        grid.focus.x = 5 * grid.spacing_x
        grid.focus.y = 5 * grid.spacing_y
        grid:init() -- Initialize the instance
        -- We can now access the layer created in the init function above
        -- grid.layer:retain()
        grid.layer:setVisible(false) -- Not visible by default
        self.grid = grid
    else
        self.grid = nil
    end
    -- Instanciate and initialize a new level
    self.level = Level():init(self,param)
end

function Manager:runStoryboardScene()
    self:loadScene(newSceneInit,self.loadStoryboard,true)
end

function Manager:runLevelScene(seasonid,levelid,releaseMemory)
    self:loadScene(newSceneInit,self.loadLevel,releaseMemory,seasonid,levelid)
end

-- Relead the current level without releasing memory
function Manager:reloadLevelScene(param)
    local levelid,seasonid = self:getCurrentLevelId()
    -- BUG FIX: pause the physics while we restart the level. If not the
    -- gameplay might send other events (e.g. win/lose) while the level is resetting and might crash.
    mediator:publish(mediator.ns.pauseGameplay)
    self:loadScene(replaceSceneInit,self.loadLevel,false,seasonid,levelid,param)
end

function Manager:runNextLevel()
    local level,season,levelid,seasonid = self:getNextUnlockedLevel()
    if level then
        self:runLevelScene(seasonid,levelid)
    else
        self:runMainMenuScene()
    end
end

function Manager:resetGame()
    self.db = self:wipeGameDatabase()
    self:runMainMenuScene()
end

-- load the main menu in the scene `scene`
function Manager:runMainMenuScene(pageid)
    self:loadScene(newSceneInit,
    function(self,scene)
        -- Since the user is waiting we take the opportunity to force a garbage collection
        -- We release memory BEFORE creating the menu because unused sprite frame are
        -- released and might be missing when creating sprite on the fly in the main menu
        -- (e.g. change player's costume)
        -- util.releaseMemory()
        -- TODO now provides hardcoded box2d physics parameters
        -- should be loaded from files (mainmenu will use physics like any other level)
        p = {
            unit = 0.5,
            position = { 0, 0 },
            size = { 10, 7 },
            gravity = { 0, -10 }
        }
        -- Create the physics instance
        Physics:create(scene,p)
        -- By default the main menu is started at the title page
        MainMenu():init(self,scene,pageid or 3)
    end, true) -- Release memory
end

function Manager:setLocale(locale)
    settings.locale = locale
    self.i18n.setLocale(settings.locale)
    self.i18n.loadFile('labels.lua')
end

function Manager:init()
    if not self.initialized then
        -- Register for application enter background and foreground
        tolua.cast(CCApplication:sharedApplication(),'AppDelegate'):registerScriptHandler(function(e)
            if e == 'didEnterBackground' then
                if settings.musicEnabled then
                    SimpleAudioEngine:sharedEngine():pauseBackgroundMusic()
                end
            else
                -- willEnterForeground
                if settings.musicEnabled then
                    SimpleAudioEngine:sharedEngine():resumeBackgroundMusic()
                end
            end
        end)

        pix2d.CocosBuilderLua:registerLoaders()
        -- Load (or create if doe not exist) the game database
        self.db = self:loadGameDB()
        -- subscribes to events
        mediator:subscribe(mediator.ns.runStoryboardScene,
            function(event) self:runStoryboardScene(score) end,
            { autorelease = false })
        mediator:subscribe(mediator.ns.runNextLevel,
            function(event,score) self:runNextLevel(score) end,
            { autorelease = false })
        mediator:subscribe(mediator.ns.runLevelScene,
            function(event,seasonid,levelid,releaseMemory) self:runLevelScene(seasonid,levelid,releaseMemory) end,
            { autorelease = false })
        mediator:subscribe(mediator.ns.runMainMenuScene,
            function(event,pageid) self:runMainMenuScene(pageid) end,
            { autorelease = false })
        mediator:subscribe(mediator.ns.resetLevelScene,
            function(event,param) self:reloadLevelScene(param) end,
            { autorelease = false})
        mediator:subscribe(mediator.ns.win,
            function(event,score) self:updateGameProgress(score) end,
            { autorelease = false})
        self.initialized = true
        -- load i18n library
        self.i18n = require 'lib/i18n/init'
        -- Load the labels for the current locale
        self:setLocale(settings.locale)
        -- settings:dump()
    end
    return self
end

return Manager
-- EOF
