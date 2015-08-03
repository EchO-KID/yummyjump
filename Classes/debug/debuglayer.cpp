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

#include "debug/debuglayer.h"

#include "physics/graph.h"
#include "common/settings.h"
#include "console/luaconsole.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "common/assets.h"
#include "common/visiblerect.h"

#if KAMCORD == 1 && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
# include <Kamcord/Kamcord-C-Interface.h>
#endif

#define DEBUG_PTM_RATIO 32.f

NS_PIX2D_BEGIN

////////////////////////////// Debug Settings ////////////////////////////////////
DebugSettings* DebugSettings::sm_debug_settings_instance = nullptr;

DebugSettings::DebugSettings()
: showPhysicsDraw(false)
, showStats(false)
, zoomOutScene(false)
{}

DebugSettings::~DebugSettings()
{}

DebugSettings* DebugSettings::getInstance()
{
    if (! sm_debug_settings_instance)
        sm_debug_settings_instance = new DebugSettings();
    return sm_debug_settings_instance;
}


////////////////////////////// Debug Layer ////////////////////////////////////

DebugLayer::DebugLayer(b2World *world)
: mWorld(world)
, mBackLayer(nullptr)
, mTable(nullptr)
, mNumberOfCells(10)
, mStatsLabel(nullptr)
, mStatStrings(5)
, console(nullptr)
, mTouched(false)
, mTouchRadius(10.f)
/// , mStreak(nullptr)
{
    mStatBuf.reserve(1024);
    mCellSize = CCSizeMake(VisibleRect::size().width * .3f, Assets::fontSize(Assets::kFontSizeSmall) *  2);
}

DebugLayer::~DebugLayer()
{}

DebugLayer* DebugLayer::create(b2World *world)
{
    DebugLayer *pRet = new DebugLayer(world);
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool DebugLayer::init()
{
    CCLayer::init();

    /// Layer init
    scheduleUpdate();
    setTouchEnabled(true);
    setTouchPriority(INT_MIN);
    setTouchMode(kCCTouchesAllAtOnce);

    CCSize winSize = VisibleRect::size();

    /// Create the stats label
    mStatsLabel = CCLabelBMFont::create("", "fonts/roboto.fnt");
    mStatsLabel->setAnchorPoint(ccp(.0f,1.f));
    mStatsLabel->setPosition(ccp(0, winSize.height));
    addChild(mStatsLabel);

    /// Init the Box2d Debug draw
    B2DebugDrawLayer *debugdraw = B2DebugDrawLayer::create(mWorld, DEBUG_PTM_RATIO);
    addChild(debugdraw, INT_MAX, kTagB2DebugDrawLayer);
    debugdraw->setVisible(DebugSettings::getInstance()->showPhysicsDraw);

    /// Enable director stats
    CCDirector::sharedDirector()->setDisplayStats(true);

    mBackLayer = CCLayerColor::create(ccc4(128,128,128, 200), winSize.width * .3f, winSize.height);
    mBackLayer->setAnchorPoint(ccp(1,0));
    mBackLayer->ignoreAnchorPointForPosition(false);
    mBackLayer->setPosition(0,0);
    addChild(mBackLayer);

    CCSize size = mBackLayer->getContentSize();

    mTable = CCTableView::create(this, CCSizeMake(mCellSize.width, mCellSize.height * (mNumberOfCells+1)));
    mTable->setTouchPriority(getTouchPriority());
    mTable->setDirection(kCCScrollViewDirectionVertical);
    mTable->setVerticalFillOrder(kCCTableViewFillTopDown);
    //mTable->setAnchorPoint(ccp(0,0));
    //mTable->ignoreAnchorPointForPosition(false);
    mTable->setPosition(ccp(0,100));
    mTable->setDelegate(this);
    mTable->reloadData();
    mBackLayer->addChild(mTable);

    /// The settings toggle button
    CCSize tipSize = VisibleRect::sizeAt(.05f, .1f); /// width = 10%, height = 5% of visible screen size
    CCLayerColor *tip = CCLayerColor::create(ccc4(128,128,128, 200), tipSize.width, tipSize.height);
    tip->ignoreAnchorPointForPosition(false);
    /// The top right corner of the back layer
    /// tip->setAnchorPoint(ccp(.0f, 1.f));
    /// tip->setPosition(mBackLayer->getPosition() + mBackLayer->getContentSize());
    /// The bottom right corner
    tip->setAnchorPoint(ccp(.0f, .0f));
    tip->setPositionX(mBackLayer->getPositionX() + mBackLayer->getContentSize().width);
    tip->setPositionY(mBackLayer->getPosition().y);
    mBackLayer->addChild(tip);

    CCMenuItem *item = CCMenuItem::create(this, menu_selector(DebugLayer::toggleSettings));
    item->setContentSize(tip->getContentSize());
    item->setAnchorPoint(CCPointZero);
    item->setPosition(CCPointZero); /// By default the menu position is set to the center of the screen
    if (CCSprite *icon = CCSprite::create("ui/settings.png")) {
        icon->setPosition(ccp(item->getContentSize().width / 2, item->getContentSize().height / 2));
        item->addChild(icon);
    }

    CCMenu *menu = CCMenu::createWithItem(item);
    menu->setAnchorPoint(CCPointZero);
    menu->setPosition(CCPointZero);
    ///menu->setPosition(ccp(17,25));
    tip->addChild(menu);

    /// Create the lua console
    console = new pix2d_console::LuaConsole();

#if KAMCORD == 1 && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    /// Kamcord configuration
    Kamcord_SetVideoFPS(30); /// Valide FPS are 30 or 60
    /// Kamcord_SetAudioRecordingProperties(unsigned int numChannels, unsigned int frequency, unsigned int bitrate)
    /// Kamcord_SetMode(unsigned long long mode)
    Kamcord_SetVideoQuality(KC_STANDARD_VIDEO_QUALITY);  /// KC_STANDARD_VIDEO_QUALITY or KC_TRAILER_VIDEO_QUALITY
#endif

    /// Add motion streak
    /*
    float fade = .5f;
    float minSeg = 1.f;
    float stroke = 16.f;
    mStreak = CCMotionStreak::create(fade, minSeg, stroke, ccWHITE, "textures/streak.png");
    mStreak->setFastMode(true);
    addChild(mStreak);
    */

    mTouchSprite = CCSprite::create("streak.png");
    mTouchSprite->setVisible(false);
    addChild(mTouchSprite);

    mTouchGrabber = TouchGrabber::create();
    addChild(mTouchGrabber);

    return true;
}

CCTableViewCell* DebugLayer::tableCellAtIndex(CCTableView *table, unsigned int idx)
{
    CCTableViewCell *cell = table->dequeueCell();

    /// To add a new cell in the table just add a new 'case' and increment the cell number (mNumberOfCells)
    if (!cell) {
        cell = new CustomTableViewCell();
        cell->autorelease();
        switch(idx) {
            case 0: addLabel("Debug settings", cell); break;
            case 1: addSwitch("Box2d debug:", cccontrol_selector(DebugLayer::toggleBox2dDebugData), cell, DebugSettings::getInstance()->showPhysicsDraw); break;
            case 2: addSwitch("Show stats:", cccontrol_selector(DebugLayer::toggleShowStats), cell, DebugSettings::getInstance()->showStats); break;
            case 3: addSwitch("Zoom out scene:", cccontrol_selector(DebugLayer::toggleZoomOutScene), cell, DebugSettings::getInstance()->zoomOutScene); break;
            case 4: addButton("Pause physics", cccontrol_selector(DebugLayer::togglePausePhysics), cell); break;
            // case 5: addButton("Reset physics", cccontrol_selector(DebugLayer::resetPhysics), cell); break;
            case 5: addButton("Find path", cccontrol_selector(DebugLayer::findPath), cell); break;
            case 6: addButton("Start record", cccontrol_selector(DebugLayer::startVideoRecording), cell); break;
            case 7: addButton("Show Video", cccontrol_selector(DebugLayer::showVideoView), cell); break;
            case 8: addButton("Record touches", cccontrol_selector(DebugLayer::recordTouches), cell); break;
            case 9: addButton("Play touches", cccontrol_selector(DebugLayer::playTouches), cell); break;
            /// case 10: addInputBox("Client", "192.158.39.1",this, cell,1); break;
            default:
                break;
        }
    }
    return cell;
}

CCSize DebugLayer::cellSizeForTable(CCTableView *table)
{
    return mCellSize;
}

unsigned int DebugLayer::numberOfCellsInTableView(CCTableView *table)
{
    return mNumberOfCells;
}

CCLabelTTF *DebugLayer::addLabel(const char *str, CCTableViewCell *cell)
{
    CCLabelTTF *label = LabelTTF(str, Assets::kRoboto, Assets::kFontSizeMedium);
    label->setAnchorPoint(ccp(0,.5f));
    label->setColor(ccc3(211, 215, 207));
    cell->addChild(label);
    return label;
}

CCControlSwitch *DebugLayer::addSwitch(const char *str, SEL_CCControlHandler action, CCTableViewCell *cell, bool status)
{
    CCLabelTTF *label = LabelTTF(str, Assets::kRoboto, Assets::kFontSizeSmall);
    label->setAnchorPoint(ccp(0,.5f));
    label->setColor(ccc3(211, 215, 207));
    cell->addChild(label);

    CCSprite *onSprite = CCSprite::create("ui/switch-on.png");
    CCSprite *offSprite = CCSprite::create("ui/switch-off.png");
    CCSprite *thumbSprite = CCSprite::create("ui/switch-thumb.png");
    CCSprite *maskSprite = CCSprite::create("ui/switch-mask.png");

    CCControlSwitch *control = CCControlSwitch::create(maskSprite, onSprite, offSprite, thumbSprite, nullptr, nullptr);
    control->setTouchPriority(getTouchPriority());
    control->setAnchorPoint(ccp(0,.5f));
    control->setPosition(ccp(label->getContentSize().width + 10, 0));
    control->setOn(status);
    control->needsLayout();
    control->addTargetWithActionForControlEvents(this, action, CCControlEventValueChanged);
    cell->addChild(control);
    return control;
}

CCEditBox *DebugLayer::addInputBox(const char *label,const char *text,CCEditBoxDelegate *delegate,CCTableViewCell *cell,int id)
{
    CCEditBox *editBox = CCEditBox::create(CCSizeMake(cell->getContentSize().width * 0.8,Assets::fontSize(Assets::kFontSizeSmall)*2), CCScale9Sprite::create("ui/green_edit.png"));
    editBox->setPlaceHolder(label);
    editBox->setText(text);
    editBox->setFont(Assets::font(Assets::kRoboto), Assets::kFontSizeSmall);
    /// editBox->setMaxLength();
    editBox->setReturnType(kKeyboardReturnTypeDone);
    editBox->setDelegate(this);
    editBox->setUserObject(CCInteger::create(id));
    cell->addChild(editBox);
    return editBox;
}

void DebugLayer::editBoxReturn(CCEditBox* editBox)
{
    CCInteger *integer = dynamic_cast<CCInteger*>(editBox->getUserObject());
    CCAssert(integer,"No user object defined for the edit box");
    switch (integer->getValue()) {
        case 1: // editBox->getText();
            break;
        default: CCLOGWARN("WARNING: Unknown edit box id: %d", integer->getValue());
            break;
    }
}

CCControlButton *DebugLayer::addButton(const char *str, SEL_CCControlHandler action, CCTableViewCell *cell)
{
    CCScale9Sprite *backgroundButton = CCScale9Sprite::create("ui/button.png");
    CCScale9Sprite *backgroundHighlightedButton = CCScale9Sprite::create("ui/buttonHighlighted.png");
    CCLabelTTF *label = LabelTTF(str, Assets::kRoboto, Assets::kFontSizeSmall);
    label->setColor(ccc3(211, 215, 207));
    CCControlButton *button = CCControlButton::create(label, backgroundButton);
    button->setTouchPriority(getTouchPriority());
    button->setAnchorPoint(ccp(0,.5f));
    button->setBackgroundSpriteForState(backgroundHighlightedButton, CCControlStateHighlighted);
    button->setTitleColorForState(ccWHITE, CCControlStateHighlighted);
    button->addTargetWithActionForControlEvents(this, action, CCControlEventTouchUpInside);
    cell->addChild(button);
    return button;
}

void DebugLayer::tableCellTouched(CCTableView* table, CCTableViewCell* cell)
{
    CC_UNUSED_PARAM(table);
    CC_UNUSED_PARAM(cell);

    /// CCLOG("cell touched at index: %i", cell->getIdx());
}

void DebugLayer::toggleSettings(CCObject *obj)
{
    CC_UNUSED_PARAM(obj);

    float x = mBackLayer->getPosition().x;
    float width = mBackLayer->getContentSize().width;
    if (x >= width)
        mBackLayer->runAction(CCEaseIn::create(CCMoveTo::create(.2f, VisibleRect::origin()),.2f));
    else if (x <= 0)
        mBackLayer->runAction(CCEaseIn::create(CCMoveTo::create(.2f, CCPoint(width,0)),.2f));
}

void DebugLayer::togglePausePhysics(CCObject *obj)
{
    CC_UNUSED_PARAM(obj);

    Physics::shared()->isPaused() ? Physics::shared()->resume() : Physics::shared()->pause();
}

void DebugLayer::toggleBox2dDebugData(CCObject *obj, CCControlEvent event)
{
    CC_UNUSED_PARAM(event);

    if (event & CCControlEventValueChanged) {
        DebugSettings::getInstance()->showPhysicsDraw = !DebugSettings::getInstance()->showPhysicsDraw;
        getChildByTag(kTagB2DebugDrawLayer)->setVisible(DebugSettings::getInstance()->showPhysicsDraw);
    }
}

void DebugLayer::toggleShowStats(CCObject *obj, CCControlEvent event)
{
    CC_UNUSED_PARAM(obj);

    if (event & CCControlEventValueChanged) {
        DebugSettings::getInstance()->showStats = !DebugSettings::getInstance()->showStats;
        mStatsLabel->setVisible(DebugSettings::getInstance()->showStats);
    }
}

void DebugLayer::toggleZoomOutScene(CCObject *obj, CCControlEvent event)
{
    CC_UNUSED_PARAM(obj);

    if (event & CCControlEventValueChanged) {
        DebugSettings::getInstance()->zoomOutScene = !DebugSettings::getInstance()->zoomOutScene;
        float scale = DebugSettings::getInstance()->zoomOutScene ? 0.5 : 1.0;
        CCDirector::sharedDirector()->getRunningScene()->setScale(scale);
    }
}

void DebugLayer::playTouches(CCObject *obj)
{
    if (mTouchGrabber->isPlaying()) {
        mTouchGrabber->stop();
    } else {
        mTouchGrabber->load(CCFileUtils::sharedFileUtils()->getWritablePath().append("touches.json"));
        mTouchGrabber->play();
    }
}

void DebugLayer::recordTouches(CCObject *obj)
{
    CCControlButton *button = static_cast<CCControlButton*>(obj);
    if (mTouchGrabber->isRecording()){
        button->setTitleForState(new CCString("Record touches"), CCControlStateNormal);
        mTouchGrabber->record(false);
        mTouchGrabber->save("touches.json");
    } else {
        button->setTitleForState(new CCString("Recording..."), CCControlStateNormal);
        mTouchGrabber->record(true);
    }
}

void DebugLayer::showVideoView(CCObject *obj)
{
#if KAMCORD == 1 && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Kamcord_StopRecording();
    Kamcord_ShowView();
#endif
}

void DebugLayer::startVideoRecording(CCObject *obj)
{
#if KAMCORD == 1 && (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    Kamcord_StopRecording();
    Kamcord_StartRecording();
#endif
}

/*
void DebugLayer::resetPhysics(CCObject *obj, CCControlEvent event)
{
    CC_UNUSED_PARAM(obj);
    CC_UNUSED_PARAM(event);
    if (CCScene *scene = LevelLoader::createWithData(DebugSettings::getInstance()->levelData.c_str()))
        CCDirector::sharedDirector()->replaceScene(scene);
}
*/

void DebugLayer::findPath(CCObject *obj, CCControlEvent event)
{
    /// Path finding test
/*
    Physics::shared()->graph()->dump();

    b2Vec2Path mapPath;
    Physics::shared()->graph()->solve(mapPath, b2Vec2(0,0), b2Vec2(3.f,3.f));

    b2Vec2Path path;
    for (int i = 0; i < mapPath.size(); ++i) {
        CCLOG("%.2fx%.2f",mapPath[i].x, mapPath[i].y);
        path.push_back(Physics::indexToMeter(mapPath[i]));
    }

    CCNode *layer = getParent()->getChildByTag(settings::kTagPhysicsLayer);
    layer->removeChildByTag(settings::kTagPath, true);
    layer->addChild(Path::create(path, nullptr), 0, settings::kTagPath);
*/
}

void DebugLayer::log(const char* string, ...)
{
    char buf[128];
	va_list arg;
	va_start(arg, string);
    vsnprintf(buf, 255, string, arg);
	va_end(arg);
    mStatStrings.push_back(std::string(buf).append("\n"));
}

void DebugLayer::log(const std::string &s)
{
    mStatStrings.push_back(std::string(s).append("\n"));
}

void DebugLayer::update(float dt)
{
    /// Reset the number of draws stat
    g_uNumberOfDraws = 0;
}

void DebugLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    std::string str("touches: ");
    char buf[64] = {0};
    mTouched = true;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it) {
        if (CCTouch *touch = dynamic_cast<CCTouch *>(*it)) {
            mTouchRadius = 10.f;
            mTouchCenter = touch->getLocation();
            snprintf(buf, 63, "%.0f:%.0f ", mTouchCenter.x, mTouchCenter.y);
        }
        str.append(buf);
    }
    /// mStreak->reset();
    mTouchSprite->setVisible(true);
    mTouchSprite->setOpacity(200);
    mTouchSprite->setPosition(mTouchCenter);
    /// mStreak->setPosition(mTouchCenter);
    log(str);
}

void DebugLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    std::string str("touches: ");
    char buf[64] = {0};
    mTouched = true;
    for(CCSetIterator it = pTouches->begin(); it != pTouches->end(); ++it) {
        if (CCTouch *touch = dynamic_cast<CCTouch *>(*it)) {
            mTouchRadius = 10.f;
            mTouchCenter = touch->getLocation();
            snprintf(buf, 63, "%.0f:%.0f ", mTouchCenter.x, mTouchCenter.y);
        }
        str.append(buf);
    }
    mTouchSprite->setVisible(false);
    /// mStreak->setPosition(mTouchCenter);
    log(str);
}

void DebugLayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    if (mTouchSprite->isVisible())
        mTouchSprite->runAction(CCFadeOut::create(1.5f));
    mTouched = false;
}

void DebugLayer::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    if (mTouchSprite->isVisible())
        mTouchSprite->runAction(CCFadeOut::create(1.5f));
    mTouched = false;
}

void DebugLayer::draw()
{
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();

    if (DebugSettings::getInstance()->showStats) {
        log("%s", CCDirector::sharedDirector()->statsString());
        log("bodies/contacts/joints: %d/%d/%d",mWorld->GetBodyCount(),mWorld->GetContactCount(),mWorld->GetJointCount());
        /// reverse logging
        for( rit = mStatStrings.rbegin(); rit != mStatStrings.rend(); ++rit)
            mStatBuf.append(*rit);
        mStatsLabel->setString(mStatBuf.c_str());
        /// clear both buffer and strings vector
        mStatStrings.clear();
        mStatBuf.clear();
    }

    kmGLPopMatrix();
}

void CustomTableViewCell::draw()
{
    CCTableViewCell::draw();
}

NS_PIX2D_END
