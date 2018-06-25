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

#include "nodes/custommenuitem.h"
#include "bindings/luahelper.h"

#include <SimpleAudioEngine.h>
using namespace CocosDenshion;

NS_PIX2D_BEGIN

CustomMenuItem::CustomMenuItem()
: mHandler(0)
, mActivated(false)
{}

CustomMenuItem::~CustomMenuItem()
{
    LuaHelper::getInstance()->releaseFunction(mHandler);
}

CustomMenuItem *CustomMenuItem::create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite)
{
    CustomMenuItem *pRet = new CustomMenuItem();
    if (pRet && pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, nullptr, nullptr)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

void CustomMenuItem::registerScriptHandler(int lo)
{
    mHandler = lo;
}

void CustomMenuItem::onExit()
{
    stopAllActions();
    CCMenuItemSprite::onExit();
}

void CustomMenuItem::activate()
{
    /// Activation is postponed so the scale back action is not stopped when Cocosbuilder action are run on some buttons.
    /// CCMenuItemImage::activate();
    if (!mActivated) {
        scheduleOnce(schedule_selector(CustomMenuItem::postponedActivate), .2f);
        mActivated = true;
    }
}

void CustomMenuItem::postponedActivate(float dt)
{
    /// Notify activation if the item's menu is enabled and visible
    /// Hack to avoid activation when user keeps the item selected/down meanwhile the menu
    /// is desactivated
    CCMenu *menu = static_cast<CCMenu*>(getParent());
    if (menu->isEnabled() && menu->isVisible()) {
        CCMenuItemSprite::activate();
        /*
        if (mHandler) {
            LuaHelper::getInstance()->pushString("activate");
            LuaHelper::getInstance()->pushUserType(this,"CCMenuItem");
            LuaHelper::getInstance()->executeFunction(mHandler, 2);
        }
        */
        /// Plays the sound effect after activate. Useful for sound effect switch button.
        if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid) {
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/fx/click4.mp3");
        } else {
            SimpleAudioEngine::sharedEngine()->playEffect("sounds/fx/click4.caf");
        }
    }
    mActivated = false;
}

void CustomMenuItem::selected()
{
    CCMenuItemSprite::selected();
    if (mHandler) {
        LuaHelper::getInstance()->pushString("selected");
        LuaHelper::getInstance()->pushUserType(this,"CCMenuItem");
        LuaHelper::getInstance()->executeFunction(mHandler, 2);
    }
}

void CustomMenuItem::unselected()
{
    CCMenuItemSprite::unselected();
    if (mHandler) {
        LuaHelper::getInstance()->pushString("unselected");
        LuaHelper::getInstance()->pushUserType(this,"CCMenuItem");
        LuaHelper::getInstance()->executeFunction(mHandler, 2);
    }
}

////////////////////// CustomMenuItemToggle /////////////////////////
float CustomMenuItemToggle::smScaleActionDuration = .4f;
float CustomMenuItemToggle::smActivationDelay = .1f;
float CustomMenuItemToggle::smScaleEffectFactor = .8f;

CustomMenuItemToggle *CustomMenuItemToggle::create(CCMenuItem* item)
{
    CustomMenuItemToggle *pRet = new CustomMenuItemToggle();
    pRet->initWithItem(item);
    pRet->autorelease();
    return pRet;
}

void CustomMenuItemToggle::onEnter()
{
    CCMenuItemToggle::onEnter();
    mOldScaleX = getScaleX();
    mOldScaleY = getScaleY();
}

void CustomMenuItemToggle::onExit()
{
    stopAllActions();
    CCMenuItemToggle::onExit();
}

void CustomMenuItemToggle::activate()
{
    CCMenu *menu = static_cast<CCMenu*>(getParent());
    if (menu->isEnabled() && menu->isVisible())
        scheduleOnce(schedule_selector(CustomMenuItemToggle::postponedActivate), smActivationDelay);
}

void CustomMenuItemToggle::postponedActivate(float dt)
{
    CCMenuItemToggle::activate();
}

void CustomMenuItemToggle::selected()
{
    CCMenuItemToggle::selected();
    runAction(CCEaseElasticOut::create(CCScaleTo::create(smScaleActionDuration, mOldScaleX * smScaleEffectFactor, mOldScaleY* smScaleEffectFactor)));
}

void CustomMenuItemToggle::unselected()
{
    CCMenuItemToggle::unselected();
    runAction(CCEaseElasticOut::create(CCScaleTo::create(smScaleActionDuration, mOldScaleX, mOldScaleY)));
}

NS_PIX2D_END
