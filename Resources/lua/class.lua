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

local util = require 'util'

print 'Loading package "class"...'

local Class = {}
Class.__index = Class

function Class.extend(p)
    local instance = assert(p.instance,"ERROR: Can't extend class. Instance field is nil.")
    t = util.shallowcopy(p)
    setmetatable(t,Class) -- make 't' an instance of 'Class'
    tolua.setpeer(instance,t) -- make 't' the peer table of the instance 'c'

    -- register handlers
    if p.update then
        instance:scheduleUpdateWithPriorityLua(function(dt)
            instance:update(dt)
        end, 1)
    end
    -- Warning: cleanup renamed onCleanup because CCNode::cleanup is already binded by tolua and
    -- using the same function name is causing a stack overflow because cleanup is called indefinitely
    if p.onExit or p.onEnter or p.onCleanup or p.onEnterTransitionFinish or p.onExitTransitionStart then
        instance:registerScriptHandler(function(event)
            -- print('event',event)
            if event == 'enter' and instance.onEnter then
                instance:onEnter()
            elseif event == 'exit' and instance.onExit then
                instance:onExit()
            elseif event == 'exitTransitionStart' and instance.onExitTransitionStart then
                instance:onExitTransitionStart()
            elseif event == 'enterTransitionFinish' and instance.onEnterTransitionFinish then
                instance:onEnterTransitionFinish()
            elseif event == 'cleanup' and instance.onCleanup then
                instance:onCleanup()
            end
        end)
    end
    -- return the instance
    return instance
end

-- return the package
return Class
