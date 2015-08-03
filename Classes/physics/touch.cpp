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

#include "touch.h"
#include "physics/physics.h"
#include "body/base/physicnode.h"
#include "common/settings.h"
#include "bindings/luahelper.h"
#include "CCLuaEngine.h"

NS_PIX2D_BEGIN

///////////////////////////// QueryCallBack class /////////////////////////////

typedef bool (TouchListener::*SEL_QueryCallBack)(b2Fixture &fixture, TouchInfo &info);
#define query_callback_selector(_SELECTOR) (SEL_QueryCallBack)(&_SELECTOR)

class QueryCallback : public b2QueryCallback
{
public:
	explicit QueryCallback(TouchInfo &info, TouchListener *listener, SEL_QueryCallBack selector)
    : m_info(info)
    , m_fixture(nullptr)
    , m_listener(listener)
    , m_selector(selector)
	{}

	bool ReportFixture(b2Fixture* fixture)
	{
        /// Only test dynamic AND static bodies (e.g. rope anchor).
		if (fixture->GetBody()->GetType() != b2_kinematicBody) {
			if (fixture->TestPoint(m_info.pos) && (m_listener->*m_selector)(*fixture, m_info)) {
                /// If the touch is in the fixture and the body is a valid touch
                /// delegate and he has accepted the touch then we stop the query by returning false
                m_fixture = fixture;
                return false;
			}
		}
		// Continue the query.
		return true;
	}

	TouchInfo m_info;
	b2Fixture* m_fixture;
    TouchListener *m_listener;
    SEL_QueryCallBack m_selector;
};

///////////////////////////// TouchListener class /////////////////////////////

TouchListener::TouchListener()
: mMouseJoint(nullptr)
, mMouseJointMaxForce(100.f) /// Default to 100 which seems enough to move bodies but not distord joint constraints
, mMouseJointDamping(.7f)
, mMouseJointFrequency(5.f)
, mIsTouched(false)
{}

TouchListener::~TouchListener()
{
    CCLOG("Destroy touch listener");
}

void TouchListener::registerTouchDelegate(TouchDelegate *delegate, PhysicNode *node)
{
    TouchDelegateInfo info;
    info.type = kTouchDelegate;
    info.delegate = delegate;
    mPhysicNodes[node] = info;
}

void TouchListener::registerTouchScriptHandler(int lo, PhysicNode *node)
{
    TouchDelegateInfo info;
    info.type = kLuaHandlerDelegate;
    info.handler = lo;
    mPhysicNodes[node] = info;
}

void TouchListener::cancelTouchDelegate(PhysicNode *node)
{
    if (mPhysicNodes.count(node)) mPhysicNodes.erase(node);
    else CCLOGWARN("Trying to cancel unregistred touch delegate");
}

bool TouchListener::queryWorldForTouch(CCTouch *pTouch, CCEvent *pEvent, TouchInfo &info)
{
    /// we must use the touch location in OpenGL coordinates (Cartesian Coordinate System)
    /// and not the screen location (which is y-axis is upside-down in iOS)
    /// See http://www.cocos2d-x.org/wiki/Coordinate_System
    b2Vec2 pos = Physics::pixelToMeter(pTouch->getLocation()) + Physics::shared()->position();

    // Make a small box to query the physic world
	b2AABB aabb;
	b2Vec2 d;
	d.Set(.01f, .01f); /// touch precision
	aabb.lowerBound = pos - d;
	aabb.upperBound = pos + d;

    /// Init the touch info
    info.event = pEvent;
    info.touch = pTouch;
    info.pos = pos;

    // Query the world for overlapping shapes.
	QueryCallback callback(info, this, query_callback_selector(TouchListener::evaluateFixture));
    Physics::shared()->world()->QueryAABB(&callback, aabb);

	if (callback.m_fixture) {
        /// If the query successed we copy back the touch info result
        info = callback.m_info;
        return true;
    }

    return nullptr;
}

bool TouchListener::evaluateFixture(b2Fixture &fixture, TouchInfo &info)
{
    b2Body* body = fixture.GetBody();
    if (body->GetUserData()) {
        /// Body's user data MUST be a struct BodyData!
        BodyData *data = static_cast<BodyData *>(body->GetUserData());
        /// Check if the physic node has registred touch notifications
        if (mPhysicNodes.count(data->physicCocosNode)) {
            /// info.delegate = mPhysicNodes[data->physicCocosNode]; /// Get the touch delegate for that physic node
            /// info.delegate DEPRECATED
            info.body = body;
            info.fixture = &fixture;
            info.localpos = body->GetLocalPoint(info.pos);
            info.node = data->physicCocosNode;
            /// Notify the touch delegate that a touch has begun.
            /// It can accept the touch (returns true) or deny the touch (returns false)
            /// If the touch is NOT accepted then the query continues (e.g. overlaping bodies)
            TouchDelegateInfo delegateInfo = mPhysicNodes[data->physicCocosNode];
            if (delegateInfo.type == kTouchDelegate) {
                return delegateInfo.delegate->touchBegan(info);
            } else { /// kLuaHandlerDelegate
                LuaHelper::getInstance()->pushString("begin");
                LuaHelper::getInstance()->pushUserType(&info, "pix2d::TouchInfo");
                return LuaHelper::getInstance()->executeFunction(delegateInfo.handler, 2);
            }
        }
    }
    return false;
}

b2MouseJoint *TouchListener::createMouseJoint(TouchInfo &info)
{
    /// Only dynamic bodies can be "moved".
    if (info.body->GetType() == b2_dynamicBody && info.node->isMovable()) {
        /// Body is movable. Create a mouse joint.
        b2MouseJointDef md;
        md.dampingRatio = mMouseJointDamping;
        md.frequencyHz = mMouseJointFrequency;
        md.bodyA = Physics::shared()->dummy();
        md.bodyB = info.body;
        md.target = info.pos;
        md.collideConnected = false;
        md.maxForce = mMouseJointMaxForce * info.body->GetMass();
        b2MouseJoint *mouseJoint = static_cast<b2MouseJoint *>(Physics::shared()->world()->CreateJoint(&md));
        info.body->SetAwake(true);
        return mouseJoint;
    }

    return nullptr;
}

bool TouchListener::notifyTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    /// No multi-touch allowed
    if (mMouseJoint || mIsTouched) return false;

    /// Reset the touch info structure
    mInfo = TouchInfo();

    /// Query the world for a touch
    mIsTouched = queryWorldForTouch(pTouch, pEvent, mInfo);

    mInfo.hasMoved = false;

    if (mIsTouched) {
        /// Check if the body is movable and create the mouse joint
        mMouseJoint = createMouseJoint(mInfo);
        /// Get the info for the current delegate
        mDelegateInfo = mPhysicNodes[mInfo.node];
    }

    /// always check mouse moved.
    return true;
}

void TouchListener::notifyTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    b2Vec2 pos = Physics::pixelToMeter(pTouch->getLocation()) + Physics::shared()->position();

	if (mMouseJoint) mMouseJoint->SetTarget(pos);

    if (mIsTouched) {
        mInfo.pos = pos;
        mInfo.localpos = mInfo.body->GetLocalPoint(pos);
        mInfo.event = pEvent;
        mInfo.touch = pTouch;
        mInfo.hasMoved = true;
        if (mDelegateInfo.type == kTouchDelegate) {
            mDelegateInfo.delegate->touchMoved(mInfo);
        } else {
            LuaHelper::getInstance()->pushString("moved");
            LuaHelper::getInstance()->pushUserType(&mInfo, "pix2d::TouchInfo");
            LuaHelper::getInstance()->executeFunction(mDelegateInfo.handler, 2);
        }
    } else {
        /// Grab a body by moving the touch. We notify a touch began eventhough
        /// it's actually a touch moved.
        notifyTouchBegan(pTouch, pEvent);
    }
}

void TouchListener::notifyTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (mIsTouched) {
        mInfo.pos = Physics::pixelToMeter(pTouch->getLocation()) + Physics::shared()->position();
        mInfo.localpos = mInfo.body->GetLocalPoint(mInfo.pos);
        mInfo.event = pEvent;
        mInfo.touch = pTouch;
        if (mDelegateInfo.type == kTouchDelegate) {
            mDelegateInfo.delegate->touchEnded(mInfo);
        } else {
            LuaHelper::getInstance()->pushString("ended");
            LuaHelper::getInstance()->pushUserType(&mInfo, "pix2d::TouchInfo");
            LuaHelper::getInstance()->executeFunction(mDelegateInfo.handler, 2);
        }
        mIsTouched = false;
    }

    /// Release the mouse joint
    destroyMouseJoint();
}

void TouchListener::notifyTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (mIsTouched) {
        mInfo.pos = Physics::pixelToMeter(pTouch->getLocation()) + Physics::shared()->position();
        mInfo.localpos = mInfo.body->GetLocalPoint(mInfo.pos);
        mInfo.event = pEvent;
        mInfo.touch = pTouch;
        if (mDelegateInfo.type == kTouchDelegate) {
            mDelegateInfo.delegate->touchCancelled(mInfo);
        } else {
            LuaHelper::getInstance()->pushString("cancelled");
            LuaHelper::getInstance()->pushUserType(&mInfo, "pix2d::TouchInfo");
            LuaHelper::getInstance()->executeFunction(mDelegateInfo.handler, 2);
        }
        mIsTouched = false;
    }

    /// Release the mouse joint
    destroyMouseJoint();
}

void TouchListener::destroyMouseJoint()
{
    if (mMouseJoint) {
        Physics::shared()->removeJoint(mMouseJoint);
        mMouseJoint = nullptr;
    }
}

b2Vec2 TouchListener::getReactionForce(float32 inv_dt) const
{
    if (mMouseJoint)
        return mMouseJoint->GetReactionForce(inv_dt);
    b2Vec2 v;
    v.SetZero();
    return v;
}

NS_PIX2D_END
