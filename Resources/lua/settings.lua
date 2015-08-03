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

-- Global settings singleton
-- Usage: local settings = require 'settings'()
-- The settings singleton instance is returned

local json = require 'json'
local util = require 'util'

print 'Loading package Settings...'

-- This package create a singleton "Settings" instance and provide JSON serialization.
-- Settings are loaded (loadUserSettings) when the instance is created and saved
-- (saveUserSettings) only if the something changed. So it's safe to call saveUserSettings
-- several times.
-- Note that only the `data` table will be saved. All other instance fields are not saved.
-- WARNING: Because we use the __newindex metamethod to keep track of updated
-- all the instance fields must exist (defined when the instance is created)
-- and must not be set to nil or it will stackoverflow badly.

-- The package table
local Settings = {}; -- Settings.__index = Settings

-- Singleton instance
local instance = nil

local function default()
    return {
        -- user settings
        locale = 'TBD', -- To be defined. Supported locale are 'en', 'fr' and 'es'.
        soundsEnabled = true,
        musicEnabled = true,
        showMainMenuHandAnim = true, -- Show the hand animation above the player in the main menu tile screen
        showGrid = true, -- Show/hide the game grid when a tool is seleted
        showCase = true, -- Show a popup with games
    }
end

setmetatable(Settings,
{
    __call = function(t,k)
        if not instance then
            instance = setmetatable({
                filename = 'yjmp.settings',
                defaultLevelStatus = -2, -- levels are locked by default. See Settings:init to unlock all levels
                dirty = false,
                platform = CCApplication:sharedApplication():getTargetPlatform(),
                url = {
                    twitter = 'http://twitter.com/voodoocactus',
                    facebook = 'http://www.facebook.com/voodocactustudio',
                    twitter_laurent = 'http://twitter.com/laurentzubiaur',
                    privacy = 'http://voodoocactus.com/privacy/',
                    contact = 'http://voodoocactus.com/contact/',
                    playstore = 'http://goo.gl/aYr96X',
                    appstore = 'http://goo.gl/Kl0JbU',
                },
                data = {},
                -- debug settings
                pix2d_debug = false, -- debug or release pix2d code build
                cocos2d_debug = false, -- are we running cocos2d debug or release build?
                debug_player_is_movable = false,
                debug_reset_gamedb_at_game_start = false,
                debug_start_lua_console = false,
                debug_console_ip = '0.0.0.0',
                debug_console_port = 8080,
            },Settings)
            -- Set the Settings table metamethod to failback on the data field
            -- to get the settings data
            Settings.__index = function(t,k)
                return Settings[k] and Settings[k] or t.data[k]
            end
            -- Track updates and set the `dirty` flags
            Settings.__newindex = function(t,k,v)
                -- print('update settings:',k,v)
                t.dirty = true
                t.data[k] = v
            end
            -- Load the user settings (or save the default if not yet saved)
            instance:loadUserSettings()
        end
        return instance
    end
})

function Settings:dump()
    print '----- User Settings -----'
    for k,v in pairs(self.data) do
        print(k,v)
    end
    print '----- End User Settings -----'
end

function Settings:reset()
    self.data = default()
    self.dirty = true
    self:init()
end

-- Save user settings only if something has changed
function Settings:saveUserSettings()
    if self.dirty then
        print('Saving user settings...',json.encode(self.data))
        util.writeDataFileSafe(self.filename,json.encode(self.data))
        self.dirty = false
    end
    print 'Settings: No changes to save.'
end

-- Load the user settings (or save the default if not yet saved)
function Settings:loadUserSettings()
    local data = util.readDataFileSafe(CCFileUtils:sharedFileUtils():getWritablePath()..self.filename)
    if not data or data == '' then
        self:reset()
        self:saveUserSettings()
    else
        self.data = json.decode(data)
    end
    self:init()
end

function Settings:init()
    if self.locale == 'TBD' then
        local lang = CCApplication:sharedApplication():getCurrentLanguage()
        if lang == kLanguageSpanish then
            self.locale = 'es'
        elseif lang == kLanguageFrench then
            self.locale = 'fr'
        else
            self.locale = 'en' -- Default language is English
        end
    end

    if self.platform == kTargetAndroid then
        self.audio = {
            background = 'sounds/background.mp3',
            balloonpop = 'sounds/fx/balloonpop.mp3',
            boing = 'sounds/fx/boing.mp3',
            card = 'sounds/fx/cardSlide3.mp3', -- Tool inserted in map level
            chime1 = 'sounds/fx/magic-chime-01.mp3', -- Level win (contact with target)
            chime2 = 'sounds/fx/magic-chime-02.mp3',
            chime3 = 'sounds/fx/magic-chime-03.mp3',
            chime4 = 'sounds/fx/magic-chime-04.mp3',
            click = 'sounds/fx/click4.mp3', -- UI button click
            click2 = 'sounds/fx/click1.mp3', -- cardboard
            coin1 = 'sounds/fx/coin01.mp3', -- Contact with coin
            coin2 = 'sounds/fx/coin02.mp3',
            coin3 = 'sounds/fx/coin03.mp3',
            jump1 = 'sounds/fx/jump1.mp3', -- Played when at gameplay start
            jump2 = 'sounds/fx/jump2.mp3', -- Played when the player is attached to the rope
            lose1 = 'sounds/fx/lose1.mp3',
            lose2 = 'sounds/fx/lose2.mp3',
            plunger = 'sounds/fx/plunger.mp3', -- UI dialog is removed
            swish1 = 'sounds/fx/swish-10.mp3', -- Player released from elastic
            swish2 = 'sounds/fx/swish-7.mp3', -- Player released from elastic 2
            switch = 'sounds/fx/switch34.mp3', -- Tool box item selected
            switch2 = 'sounds/fx/switch26.mp3', -- Tool box item selected
            teleport = 'sounds/fx/teleport.mp3',
            warping = 'sounds/fx/warping.mp3',
        }
    else -- default audio format is iPhone/iPad
        self.audio = {
            background = 'sounds/background.mp3',
            balloonpop = 'sounds/fx/balloonpop.caf',
            boing = 'sounds/fx/boing.caf',
            card = 'sounds/fx/cardSlide3.caf', -- Tool inserted in map level
            chime1 = 'sounds/fx/magic-chime-01.caf', -- Level win (contact with target)
            chime2 = 'sounds/fx/magic-chime-02.caf',
            chime3 = 'sounds/fx/magic-chime-03.caf',
            chime4 = 'sounds/fx/magic-chime-04.caf',
            click = 'sounds/fx/click4.caf', -- UI button click
            click2 = 'sounds/fx/click1.caf', -- cardboard
            coin1 = 'sounds/fx/coin01.caf', -- Contact with coin
            coin2 = 'sounds/fx/coin02.caf',
            coin3 = 'sounds/fx/coin03.caf',
            jump1 = 'sounds/fx/jump1.caf', -- Played when at gameplay start
            jump2 = 'sounds/fx/jump2.caf', -- Played when the player is attached to the rope
            lose1 = 'sounds/fx/lose1.caf',
            lose2 = 'sounds/fx/lose2.caf',
            plunger = 'sounds/fx/plunger.caf', -- UI dialog is removed
            swish1 = 'sounds/fx/swish-10.caf', -- Player released from elastic
            swish2 = 'sounds/fx/swish-7.caf', -- Player released from elastic 2
            switch = 'sounds/fx/switch34.caf', -- Tool box item selected
            switch2 = 'sounds/fx/switch26.caf', -- Tool box item selected
            teleport = 'sounds/fx/teleport.caf',
            warping = 'sounds/fx/warping.caf',
        }
    end

        self.defaultLevelStatus = 0 -- levels are unlocked

    if pix2d.Physics:isPix2dDebug() then
        -- self.debug_reset_gamedb_at_game_start = true -- reset game progess when the app is restarted on DEBUG
        self.debug_start_lua_console = true
        self.pix2d_debug = true
        self.debug_player_is_movable = false
        self.defaultLevelStatus = 0 -- levels are unlocked
    end
    if pix2d.Physics:isCocos2dDebug() then
        self.cocos2d_debug = true
    end
end

-- Return this package
return Settings
-- EOF
