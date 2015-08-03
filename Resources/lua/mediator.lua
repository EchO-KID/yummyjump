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

-- Mediator pattern inspired by https://github.com/Olivine-Labs/mediator_lua

local class = require 'class'

print 'Load package Mediator...'

local Mediator = {
    channels = {},
    -- Centralized namespaces used with this mediator
    ns = {
        test                    = 0,
        all_coins_collected     = 1,
        all_levels_completed    = 2,
        gameplayPaused          = 3, -- Gameplay is now paused
        gameplayResumed         = 4,
        lose                    = 5,
        pauseGameplay           = 6, -- Request to pause the gameplay
        resetLevelScene         = 7, -- A table with level's options can be passed to the level (see manager.lua)
        resumeGameplay          = 8,
        runLevelScene           = 9,
        runMainMenuScene        = 10, -- The start page can be passed to the event (3: main title, 4: season menu,...)
        runNextLevel            = 11,
        season_unlocked         = 12,
        tool_focus_began        = 13, -- Player set the tool focus on the map (touch began)
        tool_focus_cancel       = 14, -- Focus is on the edge of the screen (but the tool is still selected)
        tool_focus_changed      = 15, -- Player change the tool focus
        tool_focus_ended        = 16, -- Player commit the tool's focus (release touch)
        tool_focus_moved        = 17, -- Player moves the touch but the focus has not changed yet.
        tool_selected           = 18, -- A new tool is selected in the HUD tools menu.
        tool_touched            = 19, -- Player touch a movable tool on the map. The event name (began, ended or canceled) and the target node is passed.
        tool_unselected         = 20,
        updateScore             = 21,
        win                     = 22,
        showLoseScene           = 23,
        contactTopBoundary      = 24,
        removeBalloon           = 25,
        insertCardboard         = 26,
        gameplayStarted         = 27,
        -- Published when the player has been "teleported" to another teleport.
        -- Both next position in meter and pixels is passed to the event.
        -- Other tools should react to this event (e.g. balloon should releases the player...)
        teleported              = 28,
        tool_contact            = 29, -- Contact between player and a tool
        pauseScene              = 30, -- Pause the game scene (not the same than pausing the gameplay). Show the pause menu.
        -- Doesn't actually select a tool in the tool box but activate the menu item. Used by tutorial.lua
        activateToolItem        = 31,
        localeChanged           = 32, -- i18n locale has changed. All visual components should update their labels.
        outfitChanged           = 33, -- Player outfit changed. The outfit number id is passed to the event.
        runStoryboardScene      = 34,
    }
}
Mediator.__index = Mediator

local function Subscriber(fn,options)
    options = options or {}
    if options.priority == nil then options.priority = 0 end
    if options.autorelease == nil then options.autorelease = true end
    assert(type(fn) == 'function',"Subscriber's callback is not a function")
    return {
        options = options,
        fn = fn,
        channel = nil,
    }
end

local function Channel(namespace)
    return {
        stopped = false,
        namespace = namespace,
        callbacks = {},
        addSubscriber = function(self,fn,options)
            local callback = Subscriber(fn, options)
            --[[
            print('Add new subscriber.','namespace:',self.namespace,
                   'priority:',callback.options.priority,
                   'autorelease',callback.options.autorelease)
            --]]
            table.insert(self.callbacks, callback)
            self.dirty = self.dirty or callback.options.priority ~= 0
            callback.channel = self
            return callback
        end,
        publish = function(self, result, ...)
            -- print('publish event',self.namespace)
            if self.stopped then return result end
            if self.dirty then
                -- print 'Sorting subscribers by priority...'
                table.sort(self.callbacks,function(a,b) return a.options.priority < b.options.priority end)
                self.dirty = false
            end
            for _,c in ipairs(self.callbacks) do
                local value, continue = c.fn(self.namespace,...)
                if value ~= nil then table.insert(result,value) end
                if continue ~= nil and not continue then return result end
            end
            return result
        end,
        purge = function(self)
            for i=#self.callbacks,1,-1 do
                if self.callbacks[i].options.autorelease then table.remove(self.callbacks,i) end
            end
        end,
        removeSubscriber = function(self,subscriber)
            for i,c in ipairs(self.callbacks) do
                if c.fn == subscriber.fn then table.remove(self.callbacks,i); return end
            end
        end
    }
end

function Mediator:dump()
    for _,c in pairs(self.channels) do
        print('namespace',c.namespace,'subscribers',#c.callbacks)
    end
end

-- Register a callback function to a channel. Returns the subscriber instance.
-- namespace: the target channel's name
-- fn: the callback function
-- options: optional table with the following options.
-- options.autorelease (boolean): auto remove this subscriber when purge() is called
-- options.priority (number): subscriber's call priority. Zero is the highest priority.
-- The callback function is called each time an event is published into the namespace.
-- Callback function signature: value, continue = function(string,...)
-- When the callback function is called, the namespace is the first argument.
-- Then all arguments passed to publish function are passed to the callback.
-- For instance, when publishing the following event:
-- mediator:publish('myNamespace',x,y,'hello world')
-- All subscribers of 'myNamespace' will be called with 'myNamespace' as the first
-- parameter and then local x,y, and the string 'hello world' will be passed.
-- One can subscribe to 'myNamespace' as follow.
-- mediator:subscribe('myNamespace', function(namespace,x,y,msg) print(x,y,msg) end)
-- The callback function can return 2 values (or none). The first one is added
-- to the result returned to the publisher.
-- Subscribers can return true or nil as second value to continue event propagation
-- or false to stop the event. Subscribers with fewer priorties will not be
-- notified.
function Mediator:subscribe(namespace,fn,options)
    assert(type(namespace) == 'number','Invalid namespace type: '..type(namespace))
    -- Get the channel or create a new one if does not exist yet
    self.channels[namespace] = self.channels[namespace] or Channel(namespace)
    return self.channels[namespace]:addSubscriber(fn,options)
end

-- Publish an event into the namespace `namespace`. All subscribers to that event are
-- called respecting their priority (see options). The variadic arguments are
-- passed to the subscribers.
-- Returns the table with the result of all subscribers calls.
function Mediator:publish(namespace,...)
    assert(type(namespace) == 'number','Invalid namespace type: '..type(namespace))
    if self.channels[namespace] then
        return self.channels[namespace]:publish({}, ...)
    else
        print('WARNING: no subscribers registred in namespace',namespace)
    end
end

-- Remove autorelease subscribers
function Mediator:purge()
    for _,channel in pairs(self.channels) do
        channel:purge()
    end
end

-- Remove all subscribers
function Mediator:clear()
    self.channels = {}
end

function Mediator:removeSubscriber(subscriber)
    subscriber.channel:removeSubscriber(subscriber)
end

function Mediator:setEnabled(namespace,value)
    if self.channels[namespace] then self.channels[namespace].stopped = not value end
end

function Mediator:runUnitTests()
    -- test pruge and clear autorelease subscribers
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 1') end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 2') end, { autorelease = false })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 3') end)
    self:purge()
    self:publish(self.ns.test)
    self:clear()
    -- test pruge autorelease subscribers
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 4') end, { autorelease = false })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 5') end, { autorelease = true } )
    self:purge()
    self:publish(self.ns.test)
    self:clear()
    -- test pruge autorelease subscribers
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 6') end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 7') end, { autorelease = false })
    self:purge()
    self:publish(self.ns.test)
    self:clear()
    -- test priority
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 8') end, { priority = 5 })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 9') end, { priority = 3 })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 10') end, { priority = 7 })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 11') end, { priority = 1 })
    self:publish(self.ns.test)
    self:purge()
    self:publish(self.ns.test)
    -- test priority and autorelease
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 12') end, { priority = 3 , autorelease = false })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 13') end, { priority = 1 , autorelease = false })
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 14') end, { priority = 2 , autorelease = true })
    self:purge()
    self:publish(self.ns.test)
    self:clear()
    -- test remove subscriber
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 15') end)
    local s = self:subscribe(self.ns.test, function(name) print(name,'subscriber 16') end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 17') end)
    self:removeSubscriber(s)
    self:publish(self.ns.test)
    self:purge()
    -- test priority
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 18') end, { priority = 5})
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 19') end, { priority = 1})
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 20') end, { priority = 3})
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 21') end, { priority = -2})
    self:publish(self.ns.test)
    self:purge()
    -- Test continue/stop propagation
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 22') end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 23') return nil,false end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 24') end)
    self:publish(self.ns.test)
    self:purge()
    -- Test publish result
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 25') return 'hello' end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 26') return 'world',true end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 27') return false end)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 28') return nil,true end)
    local result = self:publish(self.ns.test)
    for i=1,#result do print(result[i]) end
    self:purge()
    -- test stop channel
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 29') end)
    self:setEnabled(self.ns.test,false)
    self:subscribe(self.ns.test, function(name) print(name,'subscriber 30') end)
    self:publish(self.ns.test)
    self:purge()

    self:dump()
end

return Mediator
-- EOF
