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

#include "native.h"
#include "bindings/luahelper.h"
#import "AppController.h"

NS_PIX2D_BEGIN

Native *Native::sm_instance = NULL;

Native::Native()
: mHandler(0)
{}

Native::~Native()
{
    LuaHelper::getInstance()->releaseFunction(mHandler);
}

Native *Native::getInstance() {
    if (!sm_instance) {
        sm_instance = new Native();
    }
    return sm_instance;
}

void Native::openURL(const char* pszUrl)
{
    if (!pszUrl) return;
    NSURL *nsurl = [NSURL URLWithString:[NSString stringWithCString:pszUrl encoding:NSUTF8StringEncoding]];
    [[UIApplication sharedApplication] openURL:nsurl];
}

bool Native::hideAd()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    return [appController hideAd];
    /// [UIApplication sharedApplication].keyWindow.rootViewController;
}

bool Native::showAd()
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    return [appController showAd];
}

void Native::notifyAdEvent(const char *event)
{
    if (mHandler) {
        LuaHelper::getInstance()->pushString(event);
        LuaHelper::getInstance()->executeFunction(mHandler,1);
    }
}

void Native::registerAdMobScriptHandler(int lo)
{
    unregisterAdMobScriptHandler();
    mHandler = lo;
}

void Native::unregisterAdMobScriptHandler()
{
    LuaHelper::getInstance()->releaseFunction(mHandler);
    mHandler = 0;
}

NS_PIX2D_END
