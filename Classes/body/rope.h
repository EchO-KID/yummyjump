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
#ifndef PIX2D_ROPE_H
#define PIX2D_ROPE_H

#include "forwards.h"
#include "body/base/physicnode.h"
#include "physics/contact.h"
#include "physics/touch.h"

NS_PIX2D_BEGIN

struct RopeDef
{
    CCSpriteBatchNode *batch;       /// Pointer to the vrope's sprite batch node
    int uid;
    int tag;
    b2Vec2 startpos;
    b2Vec2 endpos;
    std::string anchorFrame;
    std::string hookFrame;
    float sensorRadius;
    float anchorRadius;
    float anchorDensity;
    float hookRadius;
    float hookRestitution;
    float hookDensity;
    float hookFriction;
    b2Vec2 anchorLocalAnchor;
    b2Vec2 hookLocalAnchor;
};

/**
 * The Rope gameplay element. Creates 3 bodies plus the rope joint:
 * anchor: top static body used to attach the rope to the world
 * hook: bottom dynamic body
 * sensor: a larger sensor body used to grab the hook easily
 *
 *  # bodyA: anchor
 *  |
 *  |
 *  @ bodyB: hook, touch and inner sensors
 *
 */

class Rope : public CCNode
{
public:
    Rope();
    virtual ~Rope();
    CREATE_FUNC_P1(Rope, create, const RopeDef &);
    virtual bool init(const RopeDef &def);
    virtual void update(float dt);

    Circle *getAnchor() { return mAnchor; }
    Circle *getHook() { return mHook; }
    Circle *getSensor() { return mTouchSensor; }
    Circle *getInnerSensor() { return mInnerSensor; }

    /// Since joint between bodies and sensor is not stable we create a dummy
    /// circle body to link the node and the rope's hook. To release the node
    /// the link body is simply destroyed. Only one node can be attach at the
    /// same time
    void attach(PhysicNode *node);
    void detach();

private:
    VRope* mVrope;
    Circle *mAnchor;
    Circle *mHook;
    Circle *mTouchSensor;
    Circle *mInnerSensor;
    b2Body *mLinkBody;
};

NS_PIX2D_END
#endif // PIX2D_ROPE_H
