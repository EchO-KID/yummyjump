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

#include "physics/action.h"
#include "physics/physics.h"
#include "body/base/physicnode.h"
#include "CCLuaEngine.h"
#include "common/notifications.h"

#define PATH_LINE_WIDTH 2

NS_PIX2D_BEGIN

ccColor4F Action::smPathColor = ccc4f(1.f, 1.f, 1.f, .5);

Action::Action()
: CCActionInterval()
, mNode(nullptr)
, mSpeed(0.f) /// No speed set yet
{}

Action::~Action()
{}

Action *Action::create(float duration)
{
    Action *ptr = new Action();
    if (ptr && ptr->init(duration)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return NULL;
}

bool Action::init(float duration)
{
    return CCActionInterval::initWithDuration(duration);
}

void Action::startWithTarget(CCNode *pTarget)
{
    mNode = dynamic_cast<PhysicNode *>(pTarget);

    assert(mNode); /// CCNode must be a 'PhysicNode'
    assert(mNode->body()); /// a physic body must be attached
    assert(mNode->body()->GetType() == b2_kinematicBody); /// must be a kinematic body

    if (mNode && mNode->body()) {
        CCActionInterval::startWithTarget(pTarget);
        mStartPos = mNode->body()->GetPosition();
    }
}

void Action::stop(void)
{
    CCActionInterval::stop();
    mNode = nullptr;
}

/////////////////////// MoveTo ///////////////////////

MoveTo *MoveTo::create(const b2Vec2 &start, const b2Vec2 &dest, float speed)
{
    MoveTo *ptr = new MoveTo();
    if (ptr && ptr->init(start, dest, speed)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return NULL;
}

bool MoveTo::init(const b2Vec2 &start,const b2Vec2 &dest, float speed)
{
    mDest = Physics::unitToMeterCenter(dest);
    mStartPos = Physics::unitToMeterCenter(start);
    mDistance = b2Distance(mStartPos, mDest);
    mSense = mDest - mStartPos;
    mSense.Normalize();

    /// Add a observer if doesn't exist yet
    /*
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(MoveTo::drawPath), notification::refresh_drawnode, nullptr);
    drawPath(nullptr);
    */

    return Action::init(mDistance / speed);
}

void MoveTo::drawPath(CCObject *obj)
{
    /// TODO
    /*
    CCPoint p1 = Physics::meterToPixel(mStartPos.x, mStartPos.y);
    CCPoint p2 = Physics::meterToPixel(mDest.x, mDest.y);
    Physics::shared()->layer()->getDrawNode()->drawSegment(p1, p2, PATH_LINE_WIDTH, smPathColor);
    */
}

void MoveTo::update(float dt)
{
    /// Use transform to move the kinematic body. This is not the best approach but at least it's very simple to implement.
    mNode->body()->SetTransform(mStartPos + ((mDistance * dt) * mSense), mNode->body()->GetAngle());

    /// Another way to move the kinematic body would be to set the linear velocity but this
    /// requires the elapsed time which is no more available when using CCActionEase.
    /// This can be hacked by overiding the step method in CCActionEase.
    /// To work properly we must get the instantaneous velocity.
    /*
    b2Vec2 next = mStartPos + ((mDistance * dt) * mAxis);
    float distance = b2Distance(mNode->body()->GetPosition(), next);

    /// Compute the instance velocity (that is the slope of the tangent at dy/dx)
    float a = atan2(distance - mPrevPos, m_elapsed - mPrevTime);
    CCLOG("distance: %f speed: %f",mDistance,a);
    CCLOG("start: %f %f end: %f:%f pos: %f:%f",mStartPos.x,mStartPos.y,mEndPos.x,mEndPos.y,mNode->body()->GetPosition().x,mNode->body()->GetPosition().y);
    mNode->body()->SetLinearVelocity(a * mAxis);

    mPrevPos = distance;
    mPrevTime = m_elapsed;
    */
}

/////////////////////// CircleTo ///////////////////////

CircleTo::~CircleTo()
{
    /// Physics::shared()->layer()->refreshDrawNode();
}

CircleTo *CircleTo::create(const b2Vec2 &center, float duration)
{
    CircleTo *ptr = new CircleTo();
    if (ptr && ptr->init(center, duration)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return NULL;
}

bool CircleTo::init(const b2Vec2 &center, float duration)
{
    mCenter = Physics::unitToMeter(center);
    return Action::init(duration);
}

void CircleTo::startWithTarget(CCNode *pTarget)
{
    Action::startWithTarget(pTarget);
    assert(mNode);
    if (! mNode) return;

    b2Vec2 pos = mNode->body()->GetPosition();
    mRadius = b2Distance(pos, mCenter);
    mStartAngle = atan2(pos.y - mCenter.y, pos.x - mCenter.x);

    if (mSpeed > 0)
        setDuration(2 * M_PI * mRadius / mSpeed);

    /// Add a observer if doesn't exist yet
    // CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(CircleTo::drawPath), notification::refresh_drawnode, nullptr);
    /// We must call a refresh here because startWithTarget can be called multple times
    // Physics::shared()->layer()->refreshDrawNode();
}

void CircleTo::drawPath(CCObject *obj)
{
    /// TODO
    /*
    CCDrawNode *draw = Physics::shared()->layer()->getDrawNode();
    std::vector<CCPoint> vertex;
    float precision = .2f;
    double cir = 2 * M_PI; /// circle circumference
    for (float a = .0f; a < cir; a += precision) {
        float x = mCenter.x + mRadius * cos(a);
        float y = mCenter.y + mRadius * sin(a);
        vertex.push_back(Physics::meterToPixel(x,y));
    }
    draw->drawPolygon(&vertex[0], vertex.size(), ccc4f(0,0,0,0), PATH_LINE_WIDTH, smPathColor);
    */
}

void CircleTo::update(float dt)
{
    /// float a = (360 * dt) * M_PI / 180;  /// Degree to radian
    /// a += mStartAngle;
    float a = CC_DEGREES_TO_RADIANS(360 * dt) + mStartAngle;
    float x = mCenter.x + mRadius * cos(a);
    float y = mCenter.y + mRadius * sin(a);
    /// CCLOG("dt:%f a:%f pos:%f:%f", dt, a, x, y);
    mNode->body()->SetTransform(b2Vec2(x,y), mNode->body()->GetAngle());
}

CCActionInterval *CircleTo::reverse()
{
    assert(false); /// Not implemented yet
	return NULL;
}

//////////////////////// SplineTo //////////////////////////

SplineTo* SplineTo::create(float duration, CCPointArray* points, float tension)
{
    SplineTo *ptr = new SplineTo();
    if (ptr && ptr->CCCardinalSplineTo::initWithDuration(duration, points, tension)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return NULL;
}

void SplineTo::startWithTarget(CCNode *pTarget)
{
    mNode = dynamic_cast<PhysicNode *>(pTarget);

    assert(mNode && mNode->body()->GetType() == b2_kinematicBody); /// Must be a instance of PhysicNode and a kinematic body

    if (mNode)
        CCCardinalSplineTo::startWithTarget(pTarget);
}

void SplineTo::updatePosition(CCPoint &newPos)
{
    mNode->body()->SetTransform(Physics::pixelToMeter(newPos), mNode->body()->GetAngle());
    m_previousPosition = newPos;
}

NS_PIX2D_END
