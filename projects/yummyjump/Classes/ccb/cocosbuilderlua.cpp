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

#include "ccb/cocosbuilderlua.h"
#include "bindings/luahelper.h"

NS_PIX2D_BEGIN

CocosBuilderLua::CocosBuilderLua()
: mAnimationManager(NULL)
, mOnAssignMemberVariableHandler(0)
, mAnimationManagerDelegateHandler(0)
{}

CocosBuilderLua::~CocosBuilderLua()
{
    LuaHelper::getInstance()->releaseFunction(mOnAssignMemberVariableHandler);
    LuaHelper::getInstance()->releaseFunction(mAnimationManagerDelegateHandler);
}

CCNode *CocosBuilderLua::create(const char *filename, int assignMemberHandler, int animationHandler)
{
    CocosBuilderLua *proxy = new CocosBuilderLua();
    if (proxy) {
        proxy->autorelease();
        proxy->registerAssignVariableHandler(assignMemberHandler);
        proxy->registerAnimationDelegateHandler(animationHandler);
        return proxy->loadFromFile(filename);
    }
    return NULL;
}

void CocosBuilderLua::registerLoaders()
{
    CCNodeLoaderLibrary *loaders = CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary();
    loaders->registerCCNodeLoader("CustomMenuItem", CCBCustomMenuItemSpriteLoader::loader());
    loaders->registerCCNodeLoader("CustomLabelTTF", CCBCustomLabelTTFLoader::loader());
}

CCNode *CocosBuilderLua::loadFromFile(const char* pCCBFileName)
{
    /// Create a autorealease reader
    CCBReader* reader = new CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
    /// Load the node graph and retrieve the ccb action manager
    CCNode* node = reader->readNodeGraphFromFile(pCCBFileName, this);
    /// Register the animation delegate
    if (mAnimationManagerDelegateHandler > 0) {
        reader->getAnimationManager()->setDelegate(this);
        mAnimationManager = reader->getAnimationManager();
    }
    CC_SAFE_RELEASE_NULL(reader);
    /// CCLOG("Retain count: %d",retainCount());
    return node;
}

void CocosBuilderLua::registerAnimationDelegateHandler(int obj)
{
    mAnimationManagerDelegateHandler = obj;
}

void CocosBuilderLua::registerAssignVariableHandler(int obj)
{
    mOnAssignMemberVariableHandler = obj;
}

SEL_MenuHandler CocosBuilderLua::onResolveCCBCCMenuItemSelector(CCObject * pTarget, const char *pSelectorName)
{
    CC_UNUSED_PARAM(pTarget);
    CC_UNUSED_PARAM(pSelectorName);
    return NULL;
}

SEL_CCControlHandler CocosBuilderLua::onResolveCCBCCControlSelector(CCObject * pTarget, const char *pSelectorName)
{
    CC_UNUSED_PARAM(pTarget);
    CC_UNUSED_PARAM(pSelectorName);
    return NULL;
}

bool CocosBuilderLua::onAssignCCBMemberVariable(CCObject * pTarget, const char *pMemberVariableName, CCNode * pNode)
{
    if (mOnAssignMemberVariableHandler > 0) {
        LuaHelper::getInstance()->pushUserType(pTarget,"CCObject");
        LuaHelper::getInstance()->pushString(pMemberVariableName);
        LuaHelper::getInstance()->pushUserType(pNode,"CCNode");
        LuaHelper::getInstance()->executeFunction(mOnAssignMemberVariableHandler, 3);
    }
    return true;
}

void CocosBuilderLua::onNodeLoaded(CCNode * pNode, CCNodeLoader * pNodeLoader)
{
    CC_UNUSED_PARAM(pNode);
    CC_UNUSED_PARAM(pNodeLoader);
}

void CocosBuilderLua::completedAnimationSequenceNamed(const char *name)
{
    LuaHelper::getInstance()->pushString(name);
    LuaHelper::getInstance()->executeFunction(mAnimationManagerDelegateHandler, 1);
}

NS_PIX2D_END
