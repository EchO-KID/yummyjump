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
local mediator = require 'mediator'
local settings = require 'settings'()

local visible = pix2d.VisibleRect
local audio = SimpleAudioEngine:sharedEngine()

print 'Loading package Storyboard...'

-- The package table
local Storyboard = {}; Storyboard.__index = Storyboard

setmetatable(Storyboard,
{
    __call = function(t,k) -- Table, Key
        return setmetatable({
            -- package variables
            var = nil,
        }, Storyboard)
    end
})

function Storyboard:loadNewStoryboardScene(id)
    -- Purge sprites sheets
    CCTextureCache:sharedTextureCache():removeAllTextures()
    CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFrames()
    if id > 4 then
        mediator:publish(mediator.ns.runMainMenuScene)
    else
        -- Load new sprites sheet
        if id < 3 then
            -- No sprite sheet for storyboard 03 and 04
            CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile(('storyboard%02d.plist'):format(id))
        end
        local scene = CCScene:create()
        self:loadStoryboard(scene,id)
        CCDirector:sharedDirector():replaceScene(CCTransitionFade:create(1,scene))
    end
end

function Storyboard:loadStoryboard(scene,id)
    local button = CCMenuItemSprite:create(CCSprite:create('button_next.png'),CCSprite:create('button_next.png'))
    button:registerScriptTapHandler(function()
        CCTextureCache:sharedTextureCache():removeAllTextures()
        CCSpriteFrameCache:sharedSpriteFrameCache():removeSpriteFrames()
        mediator:publish(mediator.ns.runMainMenuScene)
    end)
    button:setPosition(visible:pointAt(0.93,0.90))
    local menu = CCMenu:create()
    menu:setPosition(visible:leftBottom())
    menu:addChild(button)
    local layer = CCLayer:create()
    layer:addChild(menu,1)
    layer:addChild(pix2d.CocosBuilderLua:create(('data/ccb/storyboard%02d.ccbi'):format(id),
        function(target,name,node)
        end,
        function(name)
            if name == 'last' then self:loadNewStoryboardScene(id + 1) end
        end))
    scene:addChild(layer)
end

-- Public package functions
function Storyboard:init(scene)
    if settings.musicEnabled then
        audio:playBackgroundMusic(settings.audio.background,true)
    end
    pix2d.Physics:setDefaultBackgroundColor(0,0,0,1)
    CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile('storyboard01.plist')
    self:loadStoryboard(scene,1)
    return self
end

-- Return this package
return Storyboard
-- EOF
