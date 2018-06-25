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


#include "physics/path.h"

#include "physics/physics.h"
#include "body/base/physicnode.h"

/// Cocos2dx lua support
#include <CCLuaEngine.h>
#include <tolua_fix.h>

NS_PIX2D_BEGIN

#define TOLERANCE .01f

Path::Path()
: CCActionInterval()
, mNode(nullptr)
, mIndex(0)
, mIterDir(1)
, mLoopCount(0)
, mMaxLoop(1)
, mSpeed(1.f)
, mLoopType(Path::kBackAndForth)
, mLuaHandler(-1)
, mPrevTime(.0f)
, mPrevPos(.0f)
{}

Path::~Path()
{}

bool Path::init(b2Vec2 start, b2Vec2 end, float duration)
{
    CCActionInterval::initWithDuration(duration);

    /// Start and end position
    mStartPos = start;
    mEndPos = end;
    /// Add the start/end points to the list
    mPoints.push_back(mStartPos);
    mPoints.push_back(mEndPos);
    /// Get the vector direction
    mAxis = getDirection(mStartPos, mEndPos);
    /// Get the distance between start and end
    mDistance = b2Distance(mEndPos,mStartPos);

    mPrevVelocity = b2Vec2_zero;

    return true;
}

void Path::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    mNode = dynamic_cast<PhysicNode *>(m_pTarget);
    assert(mNode); /// CCNode must be a 'PhysicNode'
    assert(mNode->body()); /// a physic body must be attached
}

void Path::update(float dt)
{
    hasReachedDestination(dt);
    return;

    if (hasReachedDestination(dt)) {
        /// Transform (set the position) to the actual destination to avoid side effect
        /// mNode->body()->SetTransform(mEndPos, mNode->body()->GetAngle());

        /// Update the current index in the path
        mIndex += mIterDir;
        /// When going forward (mIterDir > 0) then current index (mIndex) is the last index (mPoints.size() - 1) then loop or stop otherwise go to the next position
        /// When going backward (mIterDir <= 0) if the current index (mIndex) is the first index (0) then loop or stop otherwise go to the previous position
        if ((mIterDir > 0 && mPoints.size() -1 > mIndex) || (0 > mIterDir && mIndex > 0)) {
            /// We didn't reach the end or the begin of the path. So we get the next destination
            mStartPos = mEndPos;
            mEndPos = mPoints.at(mIndex + mIterDir); /// next (or previous) destination
            mAxis = getDirection(mStartPos, mEndPos);
            mDistance = b2Distance(mStartPos, mEndPos);
        } else if (mMaxLoop > -1 && mMaxLoop < ++mLoopCount) {
            /// Reached max loop.
            /// @todo call callback function
            /// unscheduleUpdate();
            /// isDone();
            return;
        } else {
            /// We've done a complete loop
            /// Call Lua script callback function
            if (mLuaHandler > -1) {
                int ret = CCLuaEngine::defaultEngine()->getLuaStack()->executeFunctionByHandler(mLuaHandler, 0);
                CCLOG("Script return code: %d",ret);
            }
            if (mLoopType == Path::kBackAndForth) {
                /// Change the points iteration direction
                mIterDir = -1 * mIterDir;
                /// Reverse the joint direction (negate the vector)
                mAxis = -mAxis;
                /// Switch start - end positions
                b2Vec2 tmp = mEndPos;
                mEndPos = mStartPos;
                mStartPos = tmp;
            } else {
                /// mLoopType == Path::kCyclic
                mIndex = 0;
                mStartPos = mPoints.at(mIndex);
                mEndPos = mPoints.at(mIndex + 1);
                mAxis = getDirection(mStartPos, mEndPos);
                mDistance = b2Distance(mStartPos, mEndPos);
            }
        }
        /// Notify base class that we reached the end of a path segment
        reachedPathSegmentEnd();
    }
}

/////////////////////////// PrismaticJointPath /////////////////////////////

PrismaticJointPath::PrismaticJointPath()
: Path()
, mJoint(nullptr)
{}

PrismaticJointPath::~PrismaticJointPath()
{
    if (mJoint) Physics::shared()->removeJoint(mJoint);
}

PrismaticJointPath *PrismaticJointPath::create(b2Vec2 start, b2Vec2 end, float duration)
{
    PrismaticJointPath *ptr = new PrismaticJointPath();
    if (ptr && ptr->init(start, end, duration)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool PrismaticJointPath::init(b2Vec2 start, b2Vec2 end, float duration)
{
    if (! Path::init(start, end, duration)) return false;

    return true;
}

void PrismaticJointPath::startWithTarget(CCNode *pTarget)
{
    Path::startWithTarget(pTarget);
    /// Get the joint's upper translation
    mTranslation = b2Distance(mStartPos, mEndPos);
    /// Create the first joint
    mJoint = createPrismaticJoint();
}

b2PrismaticJoint *PrismaticJointPath::createPrismaticJoint()
{
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(mNode->body(), Physics::shared()->dummy(), mNode->body()->GetWorldCenter(), mAxis);
    jointDef.lowerTranslation = 0.f;
    jointDef.upperTranslation = mTranslation;
    jointDef.enableLimit = true;
    jointDef.maxMotorForce = mNode->body()->GetMass() * 100.f;  /// Not sure about this. Figure out the motor force according to the body mass
    jointDef.motorSpeed = mSpeed;
    jointDef.enableMotor = true;

    b2PrismaticJoint *joint = static_cast<b2PrismaticJoint *>(Physics::shared()->world()->CreateJoint(&jointDef));
#if COCOS2D_DEBUG > 0
    CCLOG("Create new prismatic joint...");
    /// joint->Dump();
#endif
    return joint;
}

b2Vec2 PrismaticJointPath::getDirection(const b2Vec2 &v1, const b2Vec2 &v2)
{
    /// Get the direction by transposing the end position (destination point) to the origin
    b2Vec2 dir = v1 - v2;
    /// Normalize the direction axis
    dir.Normalize();
    return dir;
}

bool PrismaticJointPath::hasReachedDestination(float dt)
{
    float cur = mJoint->GetJointTranslation();
    float diff = cur - mTranslation;

    float speed = (mDistance * dt) / MAX(m_elapsed, FLT_EPSILON);
    mJoint->SetMotorSpeed(speed);

    /// Check if we reached the end position (joint upper translation)
    return (mTranslation < cur || TOLERANCE > fabs(diff));
}

void PrismaticJointPath::reachedPathSegmentEnd()
{
    /// Remove the old joint and create a new one
    Physics::shared()->removeJoint(mJoint);
    mTranslation = b2Distance(mStartPos, mEndPos);
    mJoint = createPrismaticJoint();
}

/////////////////////////// VelocityPath /////////////////////////////

VelocityPath::VelocityPath()
: Path()
{}

VelocityPath::~VelocityPath()
{}

VelocityPath *VelocityPath::create(b2Vec2 start, b2Vec2 end, float duration)
{
    VelocityPath *ptr = new VelocityPath();
    if (ptr && ptr->init(start, end, duration)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool VelocityPath::init(b2Vec2 start, b2Vec2 end, float duration)
{
    if (! Path::init(start, end, duration)) return false;

    return true;
}

b2Vec2 VelocityPath::getDirection(const b2Vec2 &v1, const b2Vec2 &v2)
{
    /// This is NOT the same than PrismaticJointPath::getDirection which is v1 - v2
    b2Vec2 dir = v2 - v1;
    /// Normalize the direction axis
    dir.Normalize();
    CCLOG("direction: %f:%f",dir.x,dir.y);
    return dir;
}

bool VelocityPath::hasReachedDestination(float dt)
{
    b2Vec2 next = mStartPos + ((mDistance * dt) * mAxis);
    float distance = b2Distance(mNode->body()->GetPosition(), next);

    CCLOG("%f %f",mDistance * dt, distance);

    /// Compute the instance velocity (that is the angle of the tangent: dy/dx)
    float a = atan2(distance - mPrevPos, m_elapsed - mPrevTime);
    CCLOG("distance: %f speed: %f",mDistance,a);
    CCLOG("start: %f %f end: %f:%f pos: %f:%f",mStartPos.x,mStartPos.y,mEndPos.x,mEndPos.y,mNode->body()->GetPosition().x,mNode->body()->GetPosition().y);
    mNode->body()->SetLinearVelocity(a * mAxis);

    mPrevPos = distance;
    mPrevTime = m_elapsed;

    return false;

    /// mNode->body()->SetLinearVelocity(dt * mAxis);

///    CCLOG("elapsed: %f delta: %f distance: %f distance elasped: %f speed: % velocity: %f %f",getElapsed(),dt,mDistance, mDistance * dt, speed, velocity.x,velocity.y);

    /// Get the vectors length/norm
    /*
    float len_1 = b2DistanceSquared(mEndPos, mStartPos);
    float len_2 = b2DistanceSquared(mNode->body()->GetPosition(), mStartPos);

    return len_2 >= len_1;
*/
/*
    float d1 = b2Dot(mNode->body()->GetPosition(), mAxis);
    float d2 = b2Dot(mEndPos, mAxis);

    float elapsed = MAX(m_elapsed, FLT_EPSILON);  /// Avoid division by zero
    /// Figure out the current velocity (V = L/T)
    b2Vec2 v = ((mDistance * dt) / (elapsed * elapsed)) * mAxis;

    CCLOG("elapsed: %f velocity:%f %f",elapsed,v.x,v.y);

    /// Transform the body to the new position. Not recommended.
    /// mNode->body()->SetTransform(mStartPos + (mDistance * dt) * mAxis, mNode->body()->GetAngle());

    /// Update the body's velocity
    mNode->body()->SetLinearVelocity(v);

    /// Evaluate the position.
    return d2 < d1 || TOLERANCE > fabs(d1 - d2);
*/
}

void VelocityPath::stop(void)
{
    mNode->body()->SetLinearVelocity(b2Vec2_zero);
    CCActionInterval::stop();
}

void VelocityPath::reachedPathSegmentEnd()
{
    /*
    b2Vec2 v = mSpeed * mAxis;
    CCLOG("Apply new linear velocity %f:%f",v.x,v.y);
    /// Apply new linear velocity
    mNode->body()->SetLinearVelocity(v);
    */
}

NS_PIX2D_END
