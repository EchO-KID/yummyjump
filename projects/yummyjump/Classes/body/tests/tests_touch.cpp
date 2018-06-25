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

#include "body/tests/tests_touch.h"
#include "body/base/box.h"
#include "body/base/circle.h"
#include "physics/physics.h"
#include "common/notifications.h"
#include "common/settings.h"

NS_PIX2D_BEGIN

TestsTouch::TestsTouch()
: mBox(nullptr)
, mCircle(nullptr)
{}

TestsTouch::~TestsTouch()
{
    /// MUST cancel all touch delegates
    Physics::shared()->touchListener()->cancelTouchDelegate(mBox);
    Physics::shared()->touchListener()->cancelTouchDelegate(mCircle);
}

TestsTouch *TestsTouch::create()
{
    TestsTouch *ptr = new TestsTouch();
    if (ptr && ptr->init()) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool TestsTouch::init()
{
    _setZOrder(INT_MAX);

    {
        CircleDef def;
        def.shape.m_radius = 1.f;
        def.body.position = Physics::unitToMeterCenter(4.f, 2.f);
        def.body.type = b2_staticBody;
        mCircle = Circle::create(def);

        /// mCircle->setPosition(ccp(100, 100));
        addChild(mCircle);
    }

    {
        BoxDef def;
        def.body.position = Physics::unitToMeterCenter(4.f, 4.f);
        def.size.Set(1.f, 1.f);
        def.body.type = b2_staticBody;
        mBox = Box::create(def);
        addChild(mBox);
    }

    /// Register this physics node as a self touch delegate
    Physics::shared()->touchListener()->registerTouchDelegate(this, mCircle);
    Physics::shared()->touchListener()->registerTouchDelegate(this, mBox);

    return true;
}

void TestsTouch::draw()
{
    mBox->drawDebugShape(ccc4f(1.f, .0f, .0f, 1.f));
    mCircle->drawDebugShape(ccc4f(.0f, 1.f, .0f, 1.f));
}

bool TestsTouch::touchBegan(const TouchInfo &touch)
{
    if (touch.body == mBox->body()) {
        CCLOG("Touch began on box");
        /// Don't accept touch on the box
        return false;
    } else {
        CCLOG("Touch began on circle");
        /// Accept touch on circle
        return true;
    }
}
void TestsTouch::touchMoved(const TouchInfo &touch)
{
    if (touch.body == mBox->body()) CCLOG("Touch moved on box");
    else CCLOG("Touch moved on circle");
}

void TestsTouch::touchEnded(const TouchInfo &touch)
{
    if (touch.body == mBox->body()) CCLOG("Touch ended on box");
    else CCLOG("Touch ended on circle");
}

void TestsTouch::touchCancelled(const TouchInfo &touch)
{
    if (touch.body == mBox->body()) CCLOG("Touch cancelled on box");
    else CCLOG("Touch cancelled on circle");
}

NS_PIX2D_END
