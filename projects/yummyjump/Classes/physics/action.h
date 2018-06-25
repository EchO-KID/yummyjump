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
 
#ifndef PIX2D_ACTION_H
#define PIX2D_ACTION_H

#include "forwards.h"

NS_PIX2D_BEGIN

class Action : public CCActionInterval
{
public:
    Action();
    ~Action();

    static Action *create(float duration);
    virtual bool init(float duration);

    /// overide CCActionInterval
    virtual void startWithTarget(CCNode *pTarget);
    virtual void stop(void);
    virtual void setSpeed(float value) { mSpeed = value; }
protected:
    PhysicNode *mNode;
    b2Vec2 mStartPos;
    float mSpeed;
    static ccColor4F smPathColor;
};

class MoveTo : public Action
{
public:
    /** @brief create a moveto action. We must define the start-end position and
     * speed when we create the action because when using the acion inside a
     * CCSequence we can't no more change the duration in startWithTarget
     * (because CCSequence change his actions himself)
     */
    static MoveTo *create(const b2Vec2 &start, const b2Vec2 &dest, float speed);
    virtual bool init(const b2Vec2 &start,const b2Vec2 &dest, float speed);
    virtual void update(float dt);
    void drawPath(CCObject *obj);
protected:
    b2Vec2 mDest;
    b2Vec2 mSense;
    float mDistance;
};

class CircleTo : public Action
{
public:
    virtual ~CircleTo();
    /** Create a circle action using the physics node position and the center parameter  */
    static CircleTo *create(const b2Vec2 &center, float duration);
    virtual bool init(const b2Vec2 &center, float duration);
    virtual void update(float dt);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval *reverse();
    void drawPath(CCObject *obj);
protected:
    b2Vec2 mCenter;
    float mRadius;
    float mStartAngle;
};

/// Not stable. Do not use.
class SplineTo : public CCCardinalSplineTo
{
public:

    static SplineTo* create(float duration, CCPointArray* points, float tension);
    /// Overrides
    virtual void startWithTarget(CCNode *pTarget);
    virtual void updatePosition(CCPoint &newPos);
protected:
    PhysicNode *mNode;
};

NS_PIX2D_END

#endif // PIX2D_MOVEACTION_H
