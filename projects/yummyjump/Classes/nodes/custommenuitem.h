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

#ifndef PIX2D_CUSTOMMENUSPRITE_H
#define PIX2D_CUSTOMMENUSPRITE_H

#include "forwards.h"

#include "cocos-ext.h"
USING_NS_CC_EXT;

NS_PIX2D_BEGIN

/// We have to subclass CCMenuItemImage and not CCMenuItemSprite if we want to use it with CocosBuilder
class CustomMenuItem : public CCMenuItemImage
{
public:
    CustomMenuItem();
    virtual ~CustomMenuItem();

    static CustomMenuItem *create(CCNode* normalSprite, CCNode* selectedSprite, CCNode* disabledSprite = NULL);
    /// Create item with CCSprite and not CCSpriteFrame. Not implemented (because not used)
    /// static CustomMenuImage *create(const char* normalSprite, const char* selectedSprite, const char* disabledSprite = NULL);

    /// Required for Cocosbuilder (see ccb/CCBLuaProxy)
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CustomMenuItem, create);

    void registerScriptHandler(int lo);

    virtual void onExit();

    /// override CCMenuItem method
    virtual void selected();    /// Get focus
    virtual void unselected();  /// Lost focus
    /// override activate() to get noticed when the button is clicked
    virtual void activate();

protected:
    virtual void postponedActivate(float dt);
protected:
    int mHandler;
    bool mActivated;
};

/// Helper to add shadow to CCLabelTTF because not binded to Lua and
/// because it's difficult to implement when using Cocosbuilder too.
class CustomLabelTTF : public CCLabelTTF
{
public:
    /// Must use CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD because
    /// CCLabelTTF::init must be called
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(CustomLabelTTF, create);

    /// Overide setSting to apply custom settings (e.g. shadow)
    virtual void setString(const char *label)
    {
        CCLabelTTF::setString(label);
        enableShadow(CCSizeMake(1,-1), 64, 2);
        // enableStroke(ccc3(255,255,255), 2);
    }
};

/// Helper to add shadow to CCMenuItemFont
class CustomMenuItemFont : public CCMenuItemFont
{
public:
    static CustomMenuItemFont *create(const char *text,const char *fontname,unsigned int fontsize)
    {
        CustomMenuItemFont *pRet = new CustomMenuItemFont();
        if (pRet && pRet->initWithString(text, NULL, NULL)) {
            pRet->autorelease();
            pRet->setFontNameObj(fontname);
            pRet->setFontSizeObj(fontsize);
            static_cast<CCLabelTTF *>(pRet->getLabel())->enableShadow(CCSizeMake(1,-1), 64, 2);
        } else {
            CC_SAFE_DELETE(pRet);
        }
        return pRet;
    }
};

class CustomMenuItemToggle : public CCMenuItemToggle
{
public:
    CustomMenuItemToggle() : mOldScaleX(.0f), mOldScaleY(.0f) {}
    virtual ~CustomMenuItemToggle() {}

    /** Since it's intented to be used in Lua, only this create method is provided. */
    static CustomMenuItemToggle *create(CCMenuItem* item);

    virtual void onEnter();
    virtual void onExit();

    virtual void selected();
    virtual void unselected();
    virtual void activate();
protected:
    virtual void postponedActivate(float dt);
protected:
    float mOldScaleX, mOldScaleY;
    static float smScaleActionDuration, smActivationDelay, smScaleEffectFactor;
};

NS_PIX2D_END

#endif /* PIX2D_CUSTOMMENUSPRITE_H */
