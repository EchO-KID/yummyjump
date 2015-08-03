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

#include "bindings/luahelper.h"
#include "CCLuaEngine.h"
#include "tolua_fix.h"

NS_PIX2D_BEGIN

LuaHelper *LuaHelper::smInstance = nullptr;

LuaHelper::LuaHelper()
: L(nullptr)
{}

LuaHelper::~LuaHelper()
{}

LuaHelper *LuaHelper::getInstance()
{
    if (smInstance == nullptr) {
        smInstance = new LuaHelper();
        smInstance->L = CCLuaEngine::defaultEngine()->getLuaStack()->getLuaState();
    }
    return smInstance;
}

/*
int LuaHelper::retainFunction(int lo)
{
    return toluafix_ref_function(L, lo, 0);
    /// if (!lua_isfunction(L, lo)) return 0;
    /// lua_pushvalue(L, lo);
    /// return luaL_ref(L, LUA_REGISTRYINDEX);
}
*/

void LuaHelper::releaseFunction(int refid)
{
    if (refid > 0) {
        toluafix_remove_function_by_refid(L, refid);
    }
    /// luaL_unref(L, LUA_REGISTRYINDEX, refid);
}

int LuaHelper::executeFunction(int refid, int numArgs)
{
    return CCLuaEngine::defaultEngine()->getLuaStack()->executeFunctionByHandler(refid, numArgs);
}

void LuaHelper::pushUserType(void *object, const char *type)
{
    tolua_pushusertype(L, object, type);
}

void LuaHelper::pushFloat(const float value)
{
    CCLuaEngine::defaultEngine()->getLuaStack()->pushFloat(value);
}

void LuaHelper::pushString(const char *str)
{
    CCLuaEngine::defaultEngine()->getLuaStack()->pushString(str);
}

void LuaHelper::raiseLuaError(const char *msg)
{
    luaL_error(L,msg);
}

NS_PIX2D_END
