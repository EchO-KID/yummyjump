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
 
#ifndef PIX2D_DEBUGLAYER_H
#define PIX2D_DEBUGLAYER_H

#include "forwards.h"
#include "console/forwards.h"
#include "physics/physics.h"
#include "io/touchgrabber.h"

#include <cocos-ext.h>
USING_NS_CC_EXT;

NS_PIX2D_BEGIN

class DebugSettings {
public:
    static DebugSettings *getInstance();

    /// Public settings
    bool showPhysicsDraw;
    bool showStats;
    bool zoomOutScene;
    std::string levelData; /// depecreated

private:
    DebugSettings();
    virtual ~DebugSettings();
protected:
    static DebugSettings *sm_debug_settings_instance;
};

class DebugLayer : public CCLayer, public CCTableViewDataSource, public CCTableViewDelegate, public CCEditBoxDelegate {
protected:
    enum Tags {
        kTagB2DebugDrawLayer = 1
    };

public:
    explicit DebugLayer(b2World *world);
    virtual ~DebugLayer();

    static DebugLayer *create(b2World *world);

    virtual bool init();

    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual CCSize cellSizeForTable(CCTableView *table);
    virtual CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);

    virtual void update(float dt);
    virtual void draw();
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);

    /// Menu handlers
    void toggleSettings(CCObject *obj);
    void toggleBox2dDebugData(CCObject *obj, CCControlEvent event);
    void toggleShowStats(CCObject *obj, CCControlEvent event);
    void toggleZoomOutScene(CCObject *obj, CCControlEvent event);
    /// void resetPhysics(CCObject *obj, CCControlEvent event);
    void findPath(CCObject *obj, CCControlEvent event);
    void togglePausePhysics(CCObject *obj);
    void showVideoView(CCObject *obj);
    void startVideoRecording(CCObject *obj);
    void recordTouches(CCObject *obj);
    void playTouches(CCObject *obj);

    void editBoxReturn(CCEditBox* editBox);

    void log(const char* string, ...);
    void log(const std::string &s);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    void captureFrame();
#endif

private:
    CCLabelTTF *addLabel(const char *str, CCTableViewCell *cell);
    CCControlSwitch *addSwitch(const char *str, SEL_CCControlHandler action, CCTableViewCell *cell, bool status = true);
    CCControlButton *addButton(const char *str, SEL_CCControlHandler action, CCTableViewCell *cell);
    CCEditBox *addInputBox(const char *label,const char *text,CCEditBoxDelegate *delegate,CCTableViewCell *cell,int id);

private:
    CCSize mCellSize;
    unsigned int mNumberOfCells;
    CCLayerColor *mBackLayer;
    CCTableView *mTable;
    b2World* mWorld;
    std::vector<std::string> mStatStrings;
    std::vector<std::string>::reverse_iterator rit;
    std::string mStatBuf;
    CCLabelBMFont *mStatsLabel;
    pix2d_console::LuaConsole *console;
    bool mTouched;
    float mTouchRadius;
    CCPoint mTouchCenter;
    /// CCMotionStreak *mStreak;
    CCSprite *mTouchSprite;
    TouchGrabber *mTouchGrabber;
};

class CustomTableViewCell : public CCTableViewCell
{
public:
    virtual void draw();
};

NS_PIX2D_END
#endif // PIX2D_DEBUGLAYER_H
