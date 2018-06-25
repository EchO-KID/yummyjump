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
#include "layer/physicslayer.h"
#include "geom.h"
#include "body/base/physicnode.h"
#include "common/notifications.h"
#include "common/settings.h"
#include "physics/graph.h"

NS_PIX2D_BEGIN

PhysicsLayer::PhysicsLayer(b2World *world)
: CCLayer()
, mWorld(world)
/// , mAccumulator(.0f)
/// , mPhysicsSpeed(1.f)
, timeStep(1.f / 60.f) /// Default physics speed is (1.f / 60.f)
, velocityIteration(8.f) /// Default is 8.f
, positionIteration(3.f) /// Default is 3.f
{}

PhysicsLayer::~PhysicsLayer()
{
    CCLOG("Destroy physics layer.");
}

PhysicsLayer *PhysicsLayer::create(b2World *world)
{
    PhysicsLayer *layer = new PhysicsLayer(world);
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    delete layer;
    return nullptr;
}

bool PhysicsLayer::init()
{
    if (CCLayer::init() == false) return false;
    scheduleUpdate();
    PhysicsLayer::setTouchEnabled(true);
    setTag(settings::kTagPhysicsLayer);
    return true;
}

void PhysicsLayer::setTouchEnabled(bool value)
{
    if (value && !isTouchEnabled()) {
        setTouchMode(kCCTouchesOneByOne);
        setTouchPriority(settings::kTouchPriorityPhysicsLayer);
    } else if (!value && isTouchEnabled()) {
        Physics::shared()->touchListener()->destroyMouseJoint();
    }
    CCLayer::setTouchEnabled(value);
}

/// we overide registerWithTouchDispatcher to avoid the layer to swallow touches
void PhysicsLayer::registerWithTouchDispatcher()
{
    CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    if( getTouchMode() == kCCTouchesAllAtOnce )
        pDispatcher->addStandardDelegate(this, 0);
    else
        pDispatcher->addTargetedDelegate(this, getTouchPriority(), false); /// Don't swallow touches
}

void PhysicsLayer::update(float dt)
{
    /// CCLayer::update(dt); /// Does nothing

    if (Physics::shared()->isPaused()) return;

    /// Uncomment the following code to provide fast and slow motion physics.
    /// Can also be implemented by updating the time step.
    /*
    /// use a constant steptime but call the physics' step
    /// multiple time to slow down or speed up the physics
    dt *= mPhysicsSpeed;

    // max frame time to avoid spiral of death (on slow devices)
    float frameTime = MIN(dt, 0.25f);
    mAccumulator += frameTime;
    /// CCLOG("%f",timeStep);

    /// Update the physics world

    while (mAccumulator >= timeStep) {
        mWorld->Step(timeStep, velocityIteration, positionIteration); /// Fixed step time, velocity iteration and position iteration
        mAccumulator -= timeStep;
    }
    */
    /// const float timeStep = 1.f / 60.f; /// Normal speed
    /// const float timeStep = 1.f / 30.f; /// Turbo
    /// const float timeStep = 1.f / 120.f; /// Slow motion
    mWorld->Step(timeStep, velocityIteration, positionIteration);

    mWorld->ClearForces();

    /// Update physics nodes
    b2Body* next = mWorld->GetBodyList();
    while (next) {
        b2Body* body = next;
        /// Update only cocos2d physics nodes with dynamics/kimematic bodies with user data defined
        if (body->GetType() != b2_staticBody && body->GetUserData()) {
            BodyData *data = static_cast<BodyData *>(body->GetUserData());
            /// TODO check if the body is marked for destruction
            /// Update both position and rotation
            data->physicCocosNode->setPosition(Physics::meterToPixel(body->GetPosition()));
            data->physicCocosNode->setRotation( -1 * CC_RADIANS_TO_DEGREES(body->GetAngle()));
        }
        next = body->GetNext();
    }

    /// Notify registred collisions and end-collisions handlers
    Physics::shared()->notifyCollisions();

    /// @warning We can't alter the physics world while in the b2World::step method (and therefore in the contact b2ContactListener callback)
    /// so we post-process bodies/joints/fixtures destuctions and contacts notifications after b2World::Step

    /// All collisions have been notifyed so it's safe to destroy pending bodies/fixture/joints and nodes
    /// Destroy joints
    Physics::shared()->destroyPendingJoints();
    /// Destroy fixtures
    Physics::shared()->destroyPendingFixtures();
    /// Destroy bodies
    Physics::shared()->destroyPendingBodies();
    /// Destroy cocos2d physic nodes
    Physics::shared()->destroyPendingPhysicNodes();
}

bool PhysicsLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    /// Update the touch listener
    Physics::shared()->touchListener()->notifyTouchBegan(pTouch, pEvent);
    return true;
}

void PhysicsLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    Physics::shared()->touchListener()->notifyTouchMoved(pTouch, pEvent);
}

void PhysicsLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    Physics::shared()->touchListener()->notifyTouchEnded(pTouch, pEvent);
}

void PhysicsLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    Physics::shared()->touchListener()->notifyTouchCancelled(pTouch, pEvent);
}

NS_PIX2D_END
