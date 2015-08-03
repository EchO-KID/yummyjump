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

#ifndef PIX2D_TOUCHGRABBER_H
#define PIX2D_TOUCHGRABBER_H

#include "forwards.h"
/// Jsoncpp is now included with CocoStudio
#include "CocoStudio/Json/lib_json/forwards.h"
//#include <json/json-forwards.h>

NS_PIX2D_BEGIN

class TouchGrabber : public CCLayer {
public:

    enum TouchEvent {
        kTouchBegan,
        kTouchMoved,
        kTouchEnded,
        kTouchCancelled,
        kTouchMax
    };

    struct TouchRecord {
        float time;
        TouchEvent event;
        float x;
        float y;
    };

public:
    TouchGrabber();
    ~TouchGrabber();

    CREATE_FUNC(TouchGrabber);

    virtual bool init();
    virtual void update(float delta);

    /// CCTouchDelegate
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    bool load(const std::string &filename);
    bool save(const std::string &filename);

    void play();
    void stop();
    void record(bool value);

    bool isRecording() { return bRecording; }
    bool isPlaying() { return bPlaying; }

protected:
    long getDeltaTime(struct timeval *start, struct timeval *end);
    void recordTouch(CCTouch *pTouch, TouchEvent event);

protected:
    bool bRecording;
    bool bPlaying;
    float mPlayDeltaTime;
    struct timeval mStartRecordTime;
    std::vector<TouchRecord> mTouchesRecVector;
    int mTouchVecIndice;
    CCTouch *mTouch;
};

NS_PIX2D_END
#endif // PIX2D_TOUCHGRABBER_H
