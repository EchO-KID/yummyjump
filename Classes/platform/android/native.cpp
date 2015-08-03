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
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include "bindings/luahelper.h"

NS_PIX2D_BEGIN

Native *Native::sm_instance = NULL;

Native::Native()
: mHandler(0)
{}

Native::~Native()
{}

Native *Native::getInstance() {
    if (!sm_instance) {
        sm_instance = new Native();
    }
    return sm_instance;
}

void Native::openURL(const char* pszUrl)
{
    JniMethodInfo minfo;
    /// See JNI parameters code
    /// http://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html
    if (JniHelper::getStaticMethodInfo(minfo,
                "com/voodoocactus/games/gameplay",
                "openURL",
                "(Ljava/lang/String;)V")) /// Method parameters: ( arg-types ) ret-type
    {
        jstring StringArg1 = minfo.env->NewStringUTF(pszUrl);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, StringArg1);
        minfo.env->DeleteLocalRef(StringArg1);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
}

bool Native::hideAd()
{
    /// Not implemented because we use interstitial ads
}

bool Native::showAd()
{
    JniMethodInfo minfo;
    if (JniHelper::getStaticMethodInfo(minfo,
                "com/voodoocactus/games/gameplay",
                "showAd",
                "()Z")) {
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, NULL);
        minfo.env->DeleteLocalRef(minfo.classID);
    }
    return true;
}

JNIEXPORT void JNICALL Java_com_voodoocactus_games_AdController_notifyAdEvent(JNIEnv * env, jobject ojb, jstring string)
{
    Native *instance = Native::getInstance();
    if (instance->getHandler()) {
        const char *str = env->GetStringUTFChars(string, 0); /// Java String to C/C++ string
        LuaHelper::getInstance()->pushString(str);
        LuaHelper::getInstance()->executeFunction(instance->getHandler(),1);
        env->ReleaseStringUTFChars(string, str); /// Must release the java string once no more used.
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
