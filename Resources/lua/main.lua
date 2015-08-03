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

-- main.lua is the FIRST Lua package loaded. It's loaded once at startup.
-- If any global options/parameters must be set before including any modules then
-- make we those settings here.

-- We *must* load the settings package BEFORE including any others modules.
local settings = require 'settings'()

-- Include modules dependencies
local class = require 'class'
local manager = require 'manager'
local mediator = require 'mediator'
local director = CCDirector:sharedDirector()

local function main()
    math.randomseed(os.time())
    manager:init()
    -- an upvalue is required since the variable manager will be
    -- released when director will run the first scene (runWithScene)
    local scene = class.extend {
        instance = CCScene:create(),
        update = function(self, dt)
            self:unscheduleUpdate() -- Update must only be called once
            -- load the main menu scene and replace the current scene
            -- mediator:publish(mediator.ns.runMainMenuScene)
            mediator:publish(mediator.ns.runStoryboardScene)
        end
    }
    -- Load the first scene
    director:runWithScene(scene)
end

-- Main entry for the Lua code. Called by C++ when the when application
-- finished launching (AppDelegate::applicationDidFinishLaunching())
main()
-- EOF
