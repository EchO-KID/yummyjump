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

#ifndef PIX2D_CONTACT_H
#define PIX2D_CONTACT_H

#include "forwards.h"

/// Forward declarations
struct lua_State;
/// typedef int lua_Object;   /// We now use LUA_FUNCTION (tolua fix)

NS_PIX2D_BEGIN

///////////////////////////// Box2d Collision Contact /////////////////////////////

/** @brief Contact information wrapped around b2Contact and passed to ContactDelegate callbacks */
struct ContactInfo
{
    b2Body *bodyA;                  /// When a delegate register for a contact
                                    /// it will always gets its body as the bodyA
    b2Body *bodyB;
    b2Fixture *fixtureA;
    b2Fixture *fixtureB;
    b2Vec2 pos;                     /// contact location in world coordinates.
                                    /// Note that sensors do not generate contact points so
                                    /// there's no contact position if one of the fixtures is a sensor!
    b2Vec2 localA;                  /// contact location in body A coordinates
    b2Vec2 localB;                  /// contact location in body B coordinates
    PhysicNode *nodeA;
    PhysicNode *nodeB;              /// Might be null !
    ContactDelegate *delegateA;
    ContactDelegate *delegateB;
    bool isTouching;
    signed short groupIndexA;       /// The contact fixture's group index.
    signed short groupIndexB;       /// Useful to know which fixture is involves
                                    /// in the contact when a body has multiple fixtures.
                                    /// (see boudary.cpp)
    b2Contact *pContact;            /// box2d contact structure. This is not
                                    /// available when register for post-collision event.

    /// Constructor is required!
    ContactInfo()
    : bodyA(nullptr)
    , bodyB(nullptr)
    , fixtureA(nullptr)
    , fixtureB(nullptr)
    , pos(.0f, .0f)
    , localA(.0f, .0f)
    , localB(.0f, .0f)
    , nodeA(nullptr)
    , nodeB(nullptr)
    , delegateA(nullptr)
    , delegateB(nullptr)
    , pContact(nullptr)
    , isTouching(false)
    , groupIndexA(0)
    , groupIndexB(0)
    {}
};

////////////////////////////// ContactDelegate //////////////////////////////

/**
 * @brief Classes that implement this interface will be notified at the very
 * moment a collision occurs and they will be able to handle the collision.
 * @warning Those methods are called within the world step so the physics world
 * can not be modified within those callbacks (e.g. create/destroy bodies,
 * fixtures, joints...).
 */
class ContactDelegate {
public:
    virtual void beginContact(const ContactInfo &contact) {}
    virtual void endContact(const ContactInfo &contact) {}
    virtual void preSolveContact(const ContactInfo &contact) { CC_UNUSED_PARAM(contact); }
    virtual void postSolveContact(const ContactInfo &contact) { CC_UNUSED_PARAM(contact); }
};

////////////////////////////// ContactListener //////////////////////////////

/// Callbacks
typedef int (CCObject::*SEL_Contact)(const ContactInfo &);
#define contact_selector(_SELECTOR) (SEL_Contact)(&_SELECTOR)

/**
 * @brief Implement the box2d contact listener and notify registred contact delegates.
 *
 * Contact delegates can register notifications for:
 * 1. collisions with any bodies
 * 2. collisions with a group of body (tag)
 * 3. collisions with one body (unique id)
 *
 * @warning *All* delegates associated to a PhysicNode must be removed/canceled
 * once it's destroyed. This can be achieved either calling corresponding
 * cancelXXX methodes for each registerXXX calls or just call cancelAllNotification once
 *
 * Delegates can register for two types of notifications:
 * 1. Realtime contact notifications: Delegate get notified when a collisions
 *    began/end and is pre/post solved. It is allowed to modified the contact but
 *    not the world structure. Use the registerContactDelegateScript to register
 *    a contact delegates. Only one delegate can be defined at once.
 * 2. Postponed collision notifications: the delegate registers using the
 *    registerCollisionsXXX methods to get notified after a collision occured.
 *    The delegate cannot alter the contacts anymore but since it gets notified
 *    after the world step it's safe to modified the world within those callback.
 *
 * @note bodies will get notified only if they can acctually collided. The
 * contact filters must be set correctly (see. b2Filter).
 */

class ContactListener : public b2ContactListener
{
private:

    /// Type of contact notification. Order of Lua and C++ notification type matters. See notifyCollisions().
    /// Warning all notification are not implemented yet.
    enum ContactNotificationType {
        /// Postponed notifications
        kPostponedNotification,
        kPostponedNotificationWithId,
        kPostponedNotificationWithTag,
        /// Postponed end collisions notifications
        PostponedEndCollisionNotification,
        PostponedEndCollisionNotificationWithId,
        PostponedEndCollisionNotificationWithTag,
        /// Postponed notifications with LUA function callbacks
        kLua_PostponedNotification,
        kLua_PostponedNotificationWithId,
        kLua_PostponedNotificationWithTag,
        /// Postponed END collision notifications with LUA callbacks
        kLua_PostponedEndCollisionNotification,
        kLua_PostponedEndCollisionNotificationWithId,
        kLua_PostponedEndCollisionNotificationWithTag
    };

    /// Information about a contact delegate's registration
    struct ContactNotificationInfo
    {
        /// The contact delegate
        ContactDelegate *delegate;
        /// @todo use an union for owner, selector and lua_callback (and delegate!?)
        /// callback owner
        CCObject *owner;
        /// callback method
        SEL_Contact selector;
        /// Lua callback method
        int lua_callback;
        /// Notification type
        ContactNotificationType type;
        /// Depending the notificaion type the union is a tag or a uid
        union {
            int tag;
            int uid;    /// Unique identifier
        };
    };

    typedef std::pair<ContactInfo, ContactNotificationInfo> PostponedNotificationInfo;

public:
    explicit ContactListener();
    virtual ~ContactListener();

    /// override b2ContactListener
    /** @brief when two fixtures begin to touch. */
    virtual void BeginContact(b2Contact* contact);
    /** @brief when two fixtures cease to touch. */
    virtual void EndContact(b2Contact* contact);
    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

    /// Set a lua function as contact delegate
    /// void registerContactDelegateScript(lua_Object lo);
    /// void notifyContactDelegateScript(int lua_object, b2Contact *contact, const char *event, void *data);

    /**
     * Postponed contacts nofitication.
     * The collision are pooled and notified outside b2World::step
     * so it's safe to modify the physics world in those callbacks
     */
    /** @brief register all contact notifications */
    void registerCollisionNotification(CCObject *owner, SEL_Contact selector, PhysicNode *node);
    /** @brief register contact notifications for unique id 'uid' */
    void registerCollisionNotificationWithId(CCObject *owner, SEL_Contact selector, PhysicNode *node, int uid);
    /** @brief register contact notifications for tag 'tag' */
    void registerCollisionNotificationWithTag(CCObject *owner, SEL_Contact selector, PhysicNode *node, int tag);

    /** @brief cancel all collision notification for the node 'node' (notification for uid and tag are also removed) */
    void cancelCollisionNotification(const PhysicNode *node);
    /** @brief cancel collision notifications between 'node' and the node with uid 'uid' */
    void cancelCollisionNotificationWithId(const PhysicNode *node, int uid);
    /** @brief cancel contact notifications between 'node' and the nodes with tag 'tag' */
    void cancelCollisionNotificationWithTag(const PhysicNode *node, int tag);

    /** @brief cancel all notification (both contact and collision notifications) */
    void cancelAllNotification(const PhysicNode *node);

    /**
     @brief Register a Lua function as the collision callback
     @params lo the Lua function
     @params node the physic node target
     */
    int registerCollisionNotificationScript(int lo, PhysicNode *node);
    int registerCollisionNotificationScriptWithId(int lo, PhysicNode *node, int uid);
    int registerCollisionNotificationScriptWithTag(int lo, PhysicNode *node, int tag);

    /// TODO registerEndCollisionNotificationScript, registerEndCollisionNotificationScriptWithId()
    int registerEndCollisionNotificationScriptWithTag(int lo, PhysicNode *node, int tag);

    void cancelEndCollisionNotificationScritpWithTag(const PhysicNode *node, int tag);

    /** @brief Postponed collisions AND end-collisions notifications */
    void notifyCollisions();

    /** @brief Physics entities should not be destroyed while notifying collisions. */
    bool isLocked() { return mLocked; }

    void dump();

protected:
    /** @brief Check if the body A has collided with body B and add the required notification info into the pool of collisions */
    void checkCollisionWithBodyB(b2Body *bodyA, b2Body *bodyB, b2Contact* contact);
    void checkEndCollisionWithBodyB(b2Body *bodyA, b2Body *bodyB, b2Contact* contact);

    /** @brief Create a contact info with bodyA */
    ContactInfo createContactInfoForBodyA(b2Body *bodyA, b2Contact *contact);

    /** @brief print debug information about a postponed contact notification  */
    void dump(PostponedNotificationInfo &info);

private:
    bool mLocked;

    /// A space is required between consecutive brackets (last two '>')
    typedef std::map<const PhysicNode *, std::vector<ContactNotificationInfo> > PhysicNodesMap;
    typedef std::map<const PhysicNode *, std::vector<ContactNotificationInfo> >::iterator PhysicNodesMapIterator;

    /// List of the registered physics nodes and their registrations
    /// One physics node can register for multiple type of collision with different bodies
    PhysicNodesMap mPhysicsNodes;

    /// Pool of collisions for post-processing
    std::vector<PostponedNotificationInfo> mCollisions;
    /// Pool of end-collisions
    std::vector<PostponedNotificationInfo> mEndCollisions;

    /// Contact delegates.
    /// int mContactDelegateScript;
};

NS_PIX2D_END
#endif // PIX2D_CONTACT_H
