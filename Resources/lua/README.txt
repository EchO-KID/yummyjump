Notes
-------------------
Don't use dot (.) in lua filename or require will not find the files (dot are 
converted into slash)

Touch management
-------------------
Enable touch on layer:

layer:registerScriptTouchHandler(
    function(name)
        if name == 'begin' then ...
    end,
    false, -- no multi-touch (process touches one by one)
    kCCMenuHandlerPriority +1, -- touch priority LOWER than CCMenu
    true) -- swallows touches if handler returns true
    
setTouchEnabled MUST be called after registerScriptTouchHandler  
If called before it will create a touch default touch delegate without
the options passed to `registerScriptTouchHandler`
layer:setTouchEnabled(true)

bitwise operations
-------------------
Since standard bitwise support is only available starting Lua 5.2 (bit32 module)
we use LuaJIT bitwise implementation (bit module).

Stable lua files
--------------------
class.lua           provide C++ inheritance and events (onExit,update...)
common.lua          misc. helper functions
loader.lua          load a level from a json document
anim.lua            animation related helper functions
factory.lua         interface with host code and low level create function
notification.lua    Lua wrapper around CCNotification
physics.lua         box2d physics helpers
json.lua            third-party json implementation in lua
manager.lua         Package to load and create scenes (e.g. main menu or level scenes)
main.lua            Main Lua script entry. Called by C++ once when the application has started
scroll.lua          Provides vertical and horizontal scrolling layer used by the main menu.
util.lua            Misc. helpers
hud.lua             Head-Up Display user interface in game 

Others
------------------------
reload_level.lua:   only for dev/debug

json
------------------------
Available json api
https://github.com/harningt/luajson
https://github.com/mpx/lua-cjson
dkjson
JSON4Lua http://json.luaforge.net/ https://github.com/craigmj/json4lua

LPEG support
------------
TODO try lpeg with lua
http://www.inf.puc-rio.br/~roberto/lpeg

