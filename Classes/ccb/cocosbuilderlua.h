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

#pragma once
#ifndef PIX2D_COCOSBUILDERLUA_H
#define PIX2D_COCOSBUILDERLUA_H

#include "forwards.h"
#include "cocos-ext.h"
#include "nodes/custommenuitem.h"

USING_NS_CC_EXT;

NS_PIX2D_BEGIN

/*
 * Cocosbuilder lua proxy. Requires Cocosbuilder 3.0.4.
 * To link a CocosBuilder object to Lua:
 * 1. In CocosBuilder, assign the target node to an owner (Change "Don't assign" to "Owner var") and give it a name.
 * 2. Call CocosBuilder::registerLoaders() (c++ or lua)
 * 2. In Lua, call pix2d.CocosBuilderLua:create and pass the filename and the handlers to catch variable assignment and end animation events.
 *
 * You can set both custom class and owner var. You'll just have to use tolua.cast to cast the CCNode into the custom class.
 * WARNING: This class does not provide support for Cocosbuilder custom classes.
 */

class CocosBuilderLua
: public CCObject
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
, public CCBAnimationManagerDelegate
{
public:
    CocosBuilderLua();
    virtual ~CocosBuilderLua();

    /// WARNING function are mandatory. So both function must be provided
    static CCNode *create(const char *filename, int assignMemberHandler = -1, int animationHandler = -1);

    static void registerLoaders();

    CCNode* loadFromFile(const char* pCCBFileName);
    void registerAssignVariableHandler(int obj);
    void registerAnimationDelegateHandler(int obj);

    /// Implement pure virtual methods

    /// Link callback to menu events (select...)
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char *pSelectorName);
    /// Link callback to CCControl events
    virtual extension::SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject * pTarget, const char *pSelectorName);
    /// Link CocosBuilder object to member variable
    virtual bool onAssignCCBMemberVariable(CCObject * pTarget, const char *pMemberVariableName, CCNode * pNode);
    /// Callback on node has loaded
    virtual void onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader);
    /// Callback on each time a CocosBuilder animation has completed
    virtual void completedAnimationSequenceNamed(const char *name);

protected:
    CCBAnimationManager* mAnimationManager;
    int mOnAssignMemberVariableHandler;
    int mAnimationManagerDelegateHandler;
};

/// Provide a loader for CustomMenuItem custom class
class CCBCustomMenuItemSpriteLoader : public CCMenuItemImageLoader { /// Must extend the loader for CCMenuItemImage
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBCustomMenuItemSpriteLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CustomMenuItem);
};

class CCBCustomLabelTTFLoader : public CCLabelTTFLoader {
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(CCBCustomLabelTTFLoader, loader);
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(CustomLabelTTF);
};

NS_PIX2D_END

#endif /* PIX2D_COCOSBUILDERLUA_H */
