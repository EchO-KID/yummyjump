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

#ifndef PIX2D_TOUCH_H
#define PIX2D_TOUCH_H

#include "forwards.h"

NS_PIX2D_BEGIN

///////////////////////////// struct Touch /////////////////////////////

struct TouchInfo
{
    b2Body *body;               /// The box2d body under the touch
    b2Fixture *fixture;         /// The box2d fixture under the touch
    b2Vec2 pos;                 /// Touch position in world coordinates
    b2Vec2 localpos;            /// Touch position in body local coorinates
    PhysicNode *node;           /// Convenient pointer to the physic node (otherwise available as ((BodyData*)body->GetUserData)->physicCocosNode)
    /// TouchDelegate *delegate;    /// The touch delegate associted with this event
    CCTouch *touch;             /// Cocos2d touch
    CCEvent *event;             /// Cocos2d event
    bool hasMoved;              /// Flag set to true if the touch has moved.

    /// Constructor
    TouchInfo()
    : body(nullptr)
    , fixture(nullptr)
    , pos(.0f, .0f)
    , localpos(.0f, .0f)
    , node(nullptr)
    /// , delegate(nullptr)
    , touch(nullptr)
    , event(nullptr)
    , hasMoved(false)
    {}
};

///////////////////////////// class TouchDelegate /////////////////////////////
/// To enable touch notifications on a physic node the touch delegate must:
/// 1. Inherit TouchDelegate
/// 2. Implement the pure virtual methodes touchBegan/Moved/Ended/Cancelled
/// 3. Set the body user data (b2Body::SetUserData())
/// 4. If the body actually accepts the touch he can return true in touchBegan or false to avoid the touch
/// 5. Set the movable flag to true if he wants to be moved using the mouse joint (only dynamic bodies can be moved)
/// Note: only touch on static and dynamic touch is supported

/** @brief Touch delegate interface */
class TouchDelegate {
public:
    virtual bool touchBegan(const TouchInfo &touch) = 0;
    virtual void touchMoved(const TouchInfo &touch) = 0;
    virtual void touchEnded(const TouchInfo &touch) = 0;
    virtual void touchCancelled(const TouchInfo &touch) = 0;
};


/// typedef int lua_Object; We now use LUA_FUNCTION (tolua fix)

///////////////////////////// class TouchListener /////////////////////////////
/// Callbacks
typedef int (CCObject::*SEL_touch_delegate)(const TouchInfo &);
#define touch_delegate_selector(_SELECTOR) (SEL_Touch)(&_SELECTOR)

class TouchListener {
private:
    enum TouchDelegateType {
        kTouchDelegate = 0,
        kLuaHandlerDelegate
    };

    struct TouchDelegateInfo {
        TouchDelegateType type;
        union {
            TouchDelegate *delegate;    /// touch delegate
            int handler;         /// Lua script handler
        };
    };

public:
    explicit TouchListener();
    virtual ~TouchListener();

    /**
     * @brief Register a touch delegate for a physic node.
     * @warning Any previous touch delegate or lua handler will be replaced.
     */
    void registerTouchDelegate(TouchDelegate *delegate, PhysicNode *node);
    /**
     * @brief Register a Lua function as touch delegate for a physic node. The touch event name
     * (begin,moved,ended,canceled) and the touch info will be passed to the lua function.
     * @warning Any previous touch delegate or lua handler will be replaced.
     */
    void registerTouchScriptHandler(int lo, PhysicNode *target);
    /** @brief Cancel touch notifications for a physic node */
    void cancelTouchDelegate(PhysicNode *node);

    /** Spread touch notification to the touch delegate */
    virtual bool notifyTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void notifyTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void notifyTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void notifyTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    /** @brief Destroy the current mouse joint */
    void destroyMouseJoint();

    /// a max forc of 100.0 is recommended. It's enough to move bodies and still not distorting joint constraints
    void setMouseJointMaxForce(float value) { mMouseJointMaxForce = value; }
    float getMouseJointMaxForce(float value) { return mMouseJointMaxForce; }
    void setMouseJointFrequency(float value) { mMouseJointFrequency = value; }
    void setMouseJointDamping(float value) { mMouseJointDamping = value; }
    /** Returns the mouse joint reaction force or b2Vec2(0,0) if no mouse joint exists */
    b2Vec2 getReactionForce(float inv_dt) const;

private:
    /**
     * @brief query the physics world for a touch. If there are overlapping bodied it will test every bodies until the touch is accepted.
     * @return returns the touch delegate for the body under the touch or nil if no valid body was found. The TouchInfo is also updated.
     */
    bool queryWorldForTouch(CCTouch *pTouch, CCEvent *pEvent, TouchInfo &info);

    bool evaluateFixture(b2Fixture &fixture, TouchInfo &info);

    /** @brief Create a box2d moue joint using a TouchInfo */
    b2MouseJoint *createMouseJoint(TouchInfo &info);

private:
    float mMouseJointMaxForce;
    float mMouseJointDamping;
    float mMouseJointFrequency;
    /// List of physic nodes and the associated touch delegate
    std::map<const PhysicNode *, TouchDelegateInfo> mPhysicNodes;
    /// Multi-touch is not allowed by default.
    /// TODO implement a set/get to enable/disable multitouch.
    /// Android: AFAIK there's no way to disable multi-touch on Android so we implemented manually.
    /// iOS: set "setMultipleTouchEnabled" to FALSE in AppController.mm
    bool mIsTouched;                    /// Flag to check if a body has been touched
    TouchDelegateInfo mDelegateInfo;    /// Current delegate target info
    TouchInfo mInfo;                    /// Current touch info
    b2MouseJoint *mMouseJoint;          /// The mouse joint
};

NS_PIX2D_END
#endif // PIX2D_TOUCH_H
