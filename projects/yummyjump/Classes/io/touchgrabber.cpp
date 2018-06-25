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

#include "touchgrabber.h"
#include "common/settings.h"
#include "common/assets.h"

#include <fstream>
#include <ostream>
//#include "CocoStudio/Json/lib_json/json_lib.h"
#include "CocoStudio/Json/rapidjson/rapidjson.h"

#define JSON_ERROR "JSON ERROR: "
#define MSG(x) JSON_ERROR #x

NS_PIX2D_BEGIN

TouchGrabber::TouchGrabber()
: bRecording(false)
, bPlaying(false)
, mPlayDeltaTime(.0f)
, mTouch(nullptr)
{}

TouchGrabber::~TouchGrabber()
{
    CC_SAFE_DELETE(mTouch);
}

bool TouchGrabber::init()
{
    if (CCLayer::init() == false) return false;
    // setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    setTouchPriority(INT_MIN);
    return true;
}

bool TouchGrabber::load(const std::string &filename)
{
	//! no impl
    //! std::string doc = Assets::readTextFile(filename,false);
    //! CSJson::Reader reader;
    //! CSJson::Value root;
    //! if (reader.parse(doc, root) == false) {
    //!     CCLOGERROR("ERROR: can't parse JSON touch data file %s",filename.c_str());
    //!     return false;
    //! }
    //! mTouchesRecVector.clear();
    //! for (const CSJson::Value &value : root) {
    //!     TouchRecord rec;
    //!     rec.x = value["x"].asFloat();
    //!     rec.y = value["y"].asFloat();
    //!     rec.event = (TouchEvent)value["event"].asInt();
    //!     rec.time = value["time"].asFloat();
    //!     mTouchesRecVector.push_back(rec);
    //! }
    return true;
}

bool TouchGrabber::save(const std::string &filename)
{
	//! no impl
    //! CSJson::Value root;
    //! CSJson::StyledStreamWriter writer; /// Use default indent char (tab)
    //! for (const TouchRecord &raw : mTouchesRecVector) {
    //!     CSJson::Value value;
    //!     value["x"] = raw.x;
    //!     value["y"] = raw.y;
    //!     value["time"] = raw.time;
    //!     value["event"] = raw.event;
    //!     /// CCLOG("%s %f:%f %f",raw.event.c_str(),raw.x,raw.y,raw.time);
    //!     /// Append to the array
    //!     root.append(value);
    //! }
    //! std::ofstream out(CCFileUtils::sharedFileUtils()->getWritablePath().append(filename).c_str(), std::ofstream::out);
    //! writer.write(out, root);
    //! out.close();
    return true;
}


void TouchGrabber::play()
{
    bPlaying = true;
    scheduleUpdate();
    mPlayDeltaTime = .0f;
    mTouchVecIndice = 0;
}
void TouchGrabber::stop()
{
    bPlaying = false;
    unscheduleUpdate();
}

void TouchGrabber::update(float delta)
{
    mPlayDeltaTime += delta;

    if (bPlaying == false) return;

    if (mTouchVecIndice >= mTouchesRecVector.size()) {
        stop();
        return;
    }

    TouchRecord rec = mTouchesRecVector.at(mTouchVecIndice);
    ///CCLOG("rec time: %f play dt: %f",rec.time / 1000.f, mPlayDeltaTime);

    if (rec.time / 1000.f > mPlayDeltaTime) return;

    CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    CCSet set;
    switch (rec.event) {
        case kTouchBegan:
            mTouch = new CCTouch(); /// Touch will be destroyed when ended/cancelled
            mTouch->setTouchInfo(0, rec.x, rec.y);
            set.addObject(mTouch);
            dispatcher->touchesBegan(&set, NULL);
            break;
        case kTouchMoved:
            mTouch->setTouchInfo(0, rec.x, rec.y);
            set.addObject(mTouch);
            dispatcher->touchesMoved(&set, NULL);
            break;
        case kTouchEnded:
            mTouch->setTouchInfo(0, rec.x, rec.y);
            set.addObject(mTouch);
            dispatcher->touchesEnded(&set, NULL);
            break;
        case kTouchCancelled:
            mTouch->setTouchInfo(0, rec.x, rec.y);
            set.addObject(mTouch);
            dispatcher->touchesCancelled(&set, NULL);
            break;
        default: CCAssert(false, "Unknown touch event."); break;
    }
    mTouchVecIndice++;
}

void TouchGrabber::record(bool value)
{
    if (value == bRecording) return; /// Nothing to do

    if (value == true) {
        /// Start recording. Reset recording environment.
        gettimeofday(&mStartRecordTime, NULL);
        mTouchesRecVector.clear();
    }

    setTouchEnabled(value);
    bRecording = value;
}

void TouchGrabber::recordTouch(CCTouch *pTouch, TouchEvent event)
{
    /// We use the screen coordinate (origin is the upper-left corner) and not the OpenGL coordinate (origin is the top-left corner)
    CCPoint pos = pTouch->getLocationInView();

    TouchRecord record;
    record.x = pos.x;
    record.y = pos.y;
    record.event = event;

    /// Figures out the delta time since the recording started
    struct timeval curTime;
    gettimeofday(&curTime, NULL);
    record.time = getDeltaTime(&mStartRecordTime, &curTime);

    mTouchesRecVector.push_back(record);
}

bool TouchGrabber::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (bRecording == false) return false;

    recordTouch(pTouch, kTouchBegan);

    /// Accept moved/ended events
    return true;
}

void TouchGrabber::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    recordTouch(pTouch, kTouchMoved);
}

void TouchGrabber::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    recordTouch(pTouch, kTouchEnded);
}

void TouchGrabber::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    recordTouch(pTouch, kTouchCancelled);
}

long TouchGrabber::getDeltaTime(struct timeval *start, struct timeval *end)
{
    long msec = ( end->tv_sec - start->tv_sec ) * 1000.0;
    return abs((msec += ( end->tv_usec - start->tv_usec ) / 1000.0));
}

NS_PIX2D_END
