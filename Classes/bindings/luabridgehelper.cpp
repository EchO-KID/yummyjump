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

#include "bindings/luabridgehelper.h"

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "LuaBridge.h"
using namespace luabridge;

#include "physics/action.h"
#include "physics/physics.h"
#include "body/base/physicnode.h"
#include "body/base/circle.h"

NS_PIX2D_BEGIN

bool register_luabridge_bindings(lua_State* L)
{
    if (! L) return false;

    /// Try to disable luabridge security
    /// luabridge::setHideMetatables(false);

    /// define Cocos2d bindings first
    getGlobalNamespace(L)
    /// namespace (this is not the C++ namespace)
    .beginNamespace("pix2d")
    /// CCObject
    .beginClass<CCObject>("CCObject")
    .endClass()
    /// CCNode
    .deriveClass<CCNode,CCObject>("CCNode")
    .addFunction("runAction", &CCNode::runAction)
    .endClass()
    /// CCAction
    .deriveClass<CCAction,CCObject>("CCAction")
    .endClass()
    /// CCFiniteTimeAction
    .deriveClass<CCFiniteTimeAction, CCAction>("CCFiniteTimeAction")
    .endClass()
    /// CCActionInterval
    .deriveClass<CCActionInterval, CCFiniteTimeAction>("CCActionInterval")
    .endClass()
    /// CCCardinalSplineTo
    .deriveClass<CCCardinalSplineTo, CCActionInterval>("CCCardinalSplineTo")
    .endClass()
    /// CCSequence
    .deriveClass<CCSequence,CCActionInterval>("CCSequence")
    .addStaticFunction("createWithTwoActions", &CCSequence::createWithTwoActions)
    .endClass()
    /// CCRepeatForever
    .deriveClass<CCRepeatForever,CCActionInterval>("CCRepeatForever")
    .addStaticFunction("create", &CCRepeatForever::create)
    .endClass()
    /// End namespace
    .endNamespace();


    /// because of inherence dependencies order is important
    /*
    Physics::register_Lua(L);
    PhysicNode::register_Lua(L);
    Circle::register_Lua(L);
    SplineTo::register_Lua(L);
    CircleTo::register_Lua(L);
    MoveTo::register_Lua(L);
    */
    return true;
}
/**** How to use LuaBridge: ***/
/*
 /// Register a class with static function
 void Physics::register_Lua(lua_State *L)
 {
    getGlobalNamespace(L)
    .beginNamespace("pix2d")
    .beginClass<Physics>("Physics")
    .addStaticFunction("shared", &Physics::shared)
    .addFunction("addNode", &Physics::addNode)
    .endClass()
    .endNamespace();
 }

 /// A derived class example and a static function using template
 void SplineTo::register_Lua(lua_State *L)
 {
    getGlobalNamespace (L)
    .beginNamespace("pix2d")
    .deriveClass<SplineTo,CCCardinalSplineTo> ("SplineTo")
    .addStaticFunction<SplineTo* (*)(float,float,LuaRef)>("create", &SplineTo::create)
    .addFunction("reverse", &SplineTo::reverse)
    .endClass()
    .endNamespace();
 }


 /// A C++ function with a Lua table parameter
 MoveTo *MoveTo::create(LuaRef ref)
 {
    if (ref.isTable() == false)
        return nullptr;
    return MoveTo::create(b2Vec2(ref["start"][1],ref["start"][2]),
                          b2Vec2(ref["dest"][1],ref["dest"][2]),
                          ref["speed"]);
 }
*/

NS_PIX2D_END
