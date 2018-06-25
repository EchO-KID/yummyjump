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
 
#include "AppDelegate.h"

#include "script_support/CCScriptSupport.h"
#include "CCLuaEngine.h"

#include "bindings/luabridgehelper.h"

#include "bindings/luahelper.h"

#include "forwards.h"
#include "common/settings.h"
#include "common/assets.h"

/// tolua++ packages. WARNING: custom Tolua binding headers must be included after tolua++.h
#include <tolua++.h>
#include "bindings/custom_bindings.hpp"
///#include "bindings/LuaBox2D/LuaBox2D.h"

#if COCOS2D_CONSOLE_DEBUG > 0
# include "console/luaconsole.h"
# include "console/tolua/command.hpp"
extern "C" {
# include "LuaSocket/luasocket.h"
}
#endif

/// Audio support
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

AppDelegate::AppDelegate()
: mHandler(0)
{}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::sharedEngine()->end();
    pix2d::LuaHelper::getInstance()->releaseFunction(mHandler);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    /// Enable multi-resolution
    pix2d::Assets::enableMutliResolutionSupport();

    /// Load custom shaders
    pix2d::Assets::loadCustomShaders();

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    /// register lua engine
    CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();
    CCScriptEngineManager::sharedManager()->setScriptEngine(pEngine);
    lua_State *L = pEngine->getLuaStack()->getLuaState();

    /// Add the Resources/lua directory to the Lua path
    /// std::string path = CCFileUtils::sharedFileUtils()->fullPathForFilename("lua");
    /// pEngine->addSearchPath(path.substr(0, path.find_last_of("/")).c_str());
    /// pEngine->addSearchPath("lua");

    /// Since cocos2d-x 2.2.1 a custom package loader function is used to load Lua package
    /// See cocos2dx_lua_loader and addLuaLoader in CCLuaStack::init
    CCFileUtils::sharedFileUtils()->addSearchPath("lua");
    CCFileUtils::sharedFileUtils()->addSearchPath("lua/lib");

    /// Register LuaBridge
    /// pix2d::register_luabridge_bindings(L);

    /// Load custom tolua binding packages
    tolua_custom_bindings_open(L);
#if COCOS2D_CONSOLE_DEBUG > 0
    /// tolua_LuaBox2D_open(L);
    tolua_command_open(L);
    /// Load extern lua C modules
    luaopen_socket_core(L);
#endif

    /// Load the Lua main script
    /// CCLuaEngine::defaultEngine()->executeScriptFile("main.lua");
    /// executeScriptFile does not use the custom lua package loader function which is
    /// required to uncrypt the package. So we use a executeString as a workaround
    /// to call `require` and thus call the custom loading function (cocos2dx_lua_loader)
    CCLuaEngine::defaultEngine()->executeString("require 'main'");

    return true;
}

void AppDelegate::registerScriptHandler(int lo)
{
    mHandler = lo;
}


// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

    /// Music is pause/resumed in lua (see manager.lua)
    if (mHandler) {
        pix2d::LuaHelper::getInstance()->pushString("didEnterBackground");
        pix2d::LuaHelper::getInstance()->executeFunction(mHandler, 1);
    }

#if COCOS2D_CONSOLE_DEBUG > 0
    CCNode *node = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(pix2d::settings::kTagDebugConsole);
    if (pix2d_console::LuaConsole *console = dynamic_cast<pix2d_console::LuaConsole *>(node)) {
        console->close();
    }
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();

    if (mHandler) {
        pix2d::LuaHelper::getInstance()->pushString("willEnterForeground");
        pix2d::LuaHelper::getInstance()->executeFunction(mHandler, 1);
    }

#if COCOS2D_CONSOLE_DEBUG > 0
    CCNode *node = CCDirector::sharedDirector()->getRunningScene()->getChildByTag(pix2d::settings::kTagDebugConsole);
    if (pix2d_console::LuaConsole *console = dynamic_cast<pix2d_console::LuaConsole *>(node)) {
        console->listen();
    }
#endif
}
