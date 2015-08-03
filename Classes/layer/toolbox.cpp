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

#include "layer/toolbox.h"
#include "physics/physics.h"
#include "common/settings.h"
#include "common/notifications.h"

NS_PIX2D_BEGIN

ToolBox::ToolBox()
: CCLayer()
, mMenu(nullptr)
, mCurrentTool(kNone)
{}

ToolBox::~ToolBox()
{}

ToolBox *ToolBox::create()
{
    ToolBox *layer = new ToolBox();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return nullptr;
}

bool ToolBox::init()
{
    if (!CCLayer::init()) return false;

    /// CCSize winSize = CCDirector::sharedDirector()->getWinSizeInPixels();

    CCSprite *blockImage = CCSprite::create("png/ground-texture.png");

    CCMenuItemSprite *item = CCMenuItemSprite::create(blockImage, blockImage, this, menu_selector(ToolBox::toolChangedEvent));
    item->setUserData((void*)1);
    item->setPosition(ccp(40, 40));

    mMenu = CCMenu::createWithItem(item);
    mMenu->setPosition(ccp(0, 0));
    addChild(mMenu);

    return true;
}

void ToolBox::toolChangedEvent(CCObject *obj)
{
    CCMenuItem *item = static_cast<CCMenuItem *>(obj);
    ToolType tool = (ToolType)((long int)item->getUserData());

    if (mCurrentTool != tool) {
        CCLOG("Tool selected changed: %d", mCurrentTool);
        mCurrentTool = tool;
        NotificationData data;
        data.tool = mCurrentTool;
        CCNotificationCenter::sharedNotificationCenter()->postNotification(notification::tool_changed, &data);
    }
}

NS_PIX2D_END
