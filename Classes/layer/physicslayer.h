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

#ifndef PIX2D_PHYSICSLAYER_H
#define PIX2D_PHYSICSLAYER_H

#include "forwards.h"
#include "physics/physics.h"
#include "toolbox.h"

#include <poly2tri/poly2tri.h>
#include <micropather/micropather.h>

NS_PIX2D_BEGIN

/// @brief The physics layer
class PhysicsLayer : public CCLayer {
public:

    explicit PhysicsLayer(b2World *world);
    virtual ~PhysicsLayer();
    static PhysicsLayer *create(b2World *world);

    /// CCLayer
    virtual void update(float dt);
    virtual bool init();
    virtual void setTouchEnabled(bool value);

    /// CCTouchDelegate
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void setPhysicsSpeed(float value) { timeStep = value; }
    float getPhysicsSpeed() { return timeStep; }
    virtual void registerWithTouchDispatcher();

private:
    /// const float timeStep = 1.f / 30.f; /// Turbo
    /// const float timeStep = 1.f / 120.f; /// Slow motion
    float timeStep; /// Physic speed
    const float velocityIteration;
    const float positionIteration;

    b2World *mWorld;
    /// float mAccumulator; /// See physicslayer.cpp
    /// float mPhysicsSpeed;
};

NS_PIX2D_END
#endif // PIX2D_PHYSICSLAYER_H
