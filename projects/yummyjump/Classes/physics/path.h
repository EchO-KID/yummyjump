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

#ifndef PIX2D_PATH_H
#define PIX2D_PATH_H

#include "forwards.h"
#include "physics/physics.h"

NS_PIX2D_BEGIN

/// DEPRECATED
class Path : public CCActionInterval
{
public:
    enum LoopType {
        kCyclic = 0,
        kBackAndForth
    };

    explicit Path();
    virtual ~Path();
    /// overide CCActionInterval
    virtual void startWithTarget(CCNode *pTarget);
    virtual void update(float dt);

    void addPoint(const b2Vec2 &dest) { mPoints.push_back(Physics::shared()->unitToMeterCenter(dest)); }

    /** @brief register a lua function callback that will be called on every loop */
    void lua_registerCallBack(int handler) { mLuaHandler = handler; }

    void setLoopType(LoopType type) { mLoopType = type; }
    /**
     @brief Set the maximum loop. If zero then walk through the whole path only once.
     If 1 then loop once (that is walk the path twice) etc... If negative then loop indefinitely. */
    void setMaxLoop(int value) { mMaxLoop = value; }
    /** @brief Set the motor' speed */
    void setSpeed(float value) { mSpeed = value; }

    PhysicNode *node() { return mNode; }

protected:
    virtual bool init(b2Vec2 start, b2Vec2 end, float duration);
    /// Pure virtual methods
    virtual b2Vec2 getDirection(const b2Vec2 &v1, const b2Vec2 &v2) = 0;
    virtual bool hasReachedDestination(float dt) = 0;
    virtual void reachedPathSegmentEnd() = 0;
protected:
    PhysicNode *mNode;
    LoopType mLoopType;
    size_t mLoopCount;
    int mMaxLoop;
    b2Vec2 mStartPos;
    b2Vec2 mEndPos;
    float mDistance;                    /// Distance between start and end position
    float mSpeed;
    b2Vec2 mAxis;
    int mIterDir;                       /// Iteration direction (backward or forward)
    size_t mIndex;                      /// Current points vector index
    std::vector<b2Vec2> mPoints;        /// Path's points
    int mLuaHandler;
    b2Vec2 mPrevVelocity;
    float mPrevTime;
    float mPrevPos;
};

/////////////////////////// PrismaticJointPath /////////////////////////////

class PrismaticJointPath : public Path
{
public:
    PrismaticJointPath();
    ~PrismaticJointPath();
    static PrismaticJointPath *create(b2Vec2 start, b2Vec2 end, float duration);
    virtual void startWithTarget(CCNode *pTarget);
protected:
    b2PrismaticJoint *createPrismaticJoint();
    bool init(b2Vec2 start, b2Vec2 end, float duration);
    virtual b2Vec2 getDirection(const b2Vec2 &v1, const b2Vec2 &v2);
    virtual bool hasReachedDestination(float dt);
    virtual void reachedPathSegmentEnd();
protected:
    b2PrismaticJoint *mJoint;
    float mTranslation;
};

/////////////////////////// VelocityPath /////////////////////////////

class VelocityPath : public Path
{
public:
    VelocityPath();
    ~VelocityPath();
    static VelocityPath *create(b2Vec2 start, b2Vec2 end, float duration);
    virtual void stop(void);
protected:
    bool init(b2Vec2 start, b2Vec2 end, float duration);
    virtual b2Vec2 getDirection(const b2Vec2 &v1, const b2Vec2 &v2);
    virtual bool hasReachedDestination(float dt);
    virtual void reachedPathSegmentEnd();
};

NS_PIX2D_END
#endif // PIX2D_PATH_H
