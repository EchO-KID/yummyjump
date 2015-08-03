/**
Copyright (C) 2012-2015 Laurent Zubiaur - voodoocactus.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 **/
 
/**
 * @file:   luaconsole.cpp
 * @author: Laurent Zubiaur
 * @brief:
 */

#include "console/luaconsole.h"
#include "common/settings.h"
#include <fstream>

#define LUA_LIB
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/// tolua++
#include <tolua++.h>
#include "console/tolua/command.hpp"

#include <CCLuaEngine.h>

NS_PIX2D_CONSOLE_BEGIN

LuaConsole::LuaConsole()
: Console()
, mState(NULL)
{}

LuaConsole::LuaConsole(const char *ip, int port)
: Console(ip, port)
, mState(NULL)
{}

LuaConsole::~LuaConsole()
{
    /// if (L) lua_close(L);
}

LuaConsole *LuaConsole::create(const char *ip, int port)
{
    LuaConsole *ptr = new LuaConsole(ip, port);
    if (ptr && ptr->init()) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return 0;
}

bool LuaConsole::init()
{
    if (Console::init() == false) return false;

    /// Set the tag. Required so AppDelegate can stop/start the console.
    setTag(pix2d::settings::kTagDebugConsole);

/*
    /// Create the lua state object
    mState = luaL_newstate();

    if (! mState) {
        CCLOGERROR("FATAL: Can't allocate the new Lua state");
        return false;
    }

    /// Load Lua libraries
    luaL_openlibs(mState);
*/

    /// Use the Cocos2d's lua engine
    mState = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();

    /// Open debug library. needed?
    luaopen_debug(mState);

    /// Load tolua binding packages
    tolua_command_open(mState);

    return true;
}

void LuaConsole::handleRequest(const std::string &input, std::string &output)
{
    //std::cout << input << std::endl;
    output.append("ok");

    if (input.length() < 1) {
        output = std::string("ERROR: Lua script is empty.");
        return ;
    }

    /// Load and parse the Lua script
    if (luaL_loadstring(mState, input.c_str())) {
        output = std::string(lua_tostring(mState, -1));
        CCLOGERROR("Lua Parse error: %s", output.c_str());
        return;
    }

    /// passing debug.traceback as the error function to lua_pcall
    /// http://stackoverflow.com/questions/18173054/c-lua-error-handling
    int argCount = 0; /// number of argument
    lua_getglobal(mState, "debug");
    lua_getfield(mState, -1, "traceback");
    lua_remove(mState, -2);
    int errindex = argCount - 2;
    lua_insert(mState, errindex);

    /// Run the lua script in protected mode
    if (lua_pcall(mState, argCount, LUA_MULTRET, errindex)) {
        output = std::string(lua_tostring(mState, -1));
        CCLOGERROR("ERROR: %s", output.c_str());
        /* force a complete garbage collection in case of errors */
        lua_gc(mState, LUA_GCCOLLECT, 0);
    } else {
        /// If the chunk did not raise any error we get the output global variable.
        lua_getglobal(mState, "output");
        if (lua_isstring(mState, -1)){
            const char *str = lua_tostring(mState, -1);
            size_t len = lua_strlen(mState, -1);
            output = std::string(str, len);
        }
    }
    /// std::cout << output << std::endl;
}

void LuaConsole::stackDump(lua_State *L)
{
    int i;
    int top = lua_gettop(L);
    for (i = 1; i <= top; i++) {  /* repeat for each level */
        int t = lua_type(L, i);
        switch (t) {

            case LUA_TSTRING:  /* strings */
                printf("`%s'", lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:  /* booleans */
                printf(lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TNUMBER:  /* numbers */
                printf("%g", lua_tonumber(L, i));
                break;

            default:  /* other values */
                printf("%s", lua_typename(L, t));
                break;

        }
        printf("  ");  /* put a separator */
    }
    printf("\n");  /* end the listing */
}

NS_PIX2D_CONSOLE_END
