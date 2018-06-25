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

#include "contact.h"
#include "userdata.h"
#include "body/base/physicnode.h"

#include "bindings/luahelper.h"

/// Cocos2dx lua support
#include "CCLuaEngine.h"
#include "tolua_fix.h"

NS_PIX2D_BEGIN

ContactListener::ContactListener()
: mLocked(false)
// , mContactDelegateScript(0)
{}

ContactListener::~ContactListener()
{
    /*
    if (mContactDelegateScript) {
        LuaHelper::getInstance()->releaseFunction(mContactDelegateScript);
    }
    */
}

void ContactListener::BeginContact(b2Contact* contact)
{
    /*
    if (mContactDelegateScript) {
        notifyContactDelegateScript(mContactDelegateScript,contact,"begin",nullptr);
    }
    */
    checkCollisionWithBodyB(contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody(), contact);
    checkCollisionWithBodyB(contact->GetFixtureB()->GetBody(), contact->GetFixtureA()->GetBody(), contact);
}

void ContactListener::EndContact(b2Contact* contact)
{
    /*
    if (mContactDelegateScript) {
        notifyContactDelegateScript(mContactDelegateScript,contact,"end",nullptr);
    }
    */
    checkEndCollisionWithBodyB(contact->GetFixtureA()->GetBody(), contact->GetFixtureB()->GetBody(), contact);
    checkEndCollisionWithBodyB(contact->GetFixtureB()->GetBody(), contact->GetFixtureA()->GetBody(), contact);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    /*
    if (mContactDelegateScript) {
        notifyContactDelegateScript(mContactDelegateScript,contact,"preSolve",(void*)oldManifold);
    }
    */
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    /*
    if (mContactDelegateScript) {
        notifyContactDelegateScript(mContactDelegateScript,contact,"postSolve",(void*)impulse);
    }
    */
}

void ContactListener::notifyCollisions()
{
    /// Start notifications
    mLocked = true;

    /// Don't assign mCollision.size
    /// size_t size = mCollisions.size();
    for (int i=0; i < mCollisions.size(); ++i) {
        PostponedNotificationInfo info = mCollisions.at(i);
#if COCOS2D_DEBUG > 0
        /// dump(info);
#endif
        if (info.second.type >= kLua_PostponedNotification) {
            /// Call Lua handler
            LuaHelper::getInstance()->pushUserType(&info.first, "pix2d::ContactInfo");
            LuaHelper::getInstance()->executeFunction(info.second.lua_callback, 1);
        } else {
            /// Call the C++ delegate's callback method
            (info.second.owner->*info.second.selector)(info.first);
        }
    }
    mCollisions.clear();

    /// Notify end-collisions.
    for (int i=0; i < mEndCollisions.size(); ++i) {
        PostponedNotificationInfo info = mEndCollisions.at(i);
        if (info.second.type >= kLua_PostponedEndCollisionNotification) {
            /// Call Lua handler for
            LuaHelper::getInstance()->pushUserType(&info.first, "pix2d::ContactInfo");
            LuaHelper::getInstance()->executeFunction(info.second.lua_callback, 1);
        } else {
            /// Call the C++ delegate's callback method
            (info.second.owner->*info.second.selector)(info.first);
        }
    }
    mEndCollisions.clear();

    /// Done with notifications
    mLocked = false;
}

/*
void ContactListener::notifyContactDelegateScript(int lua_object, b2Contact *contact, const char *event, void *data)
{
    int arg = 2;
    LuaHelper::getInstance()->pushString(event);
    LuaHelper::getInstance()->pushUserType(contact,"b2Contact");
    if (strcmp(event, "preSolve") == 0) {
        arg = 3;
        LuaHelper::getInstance()->pushUserType(static_cast<b2Manifold*>(data),"b2Manifold");
    } else if (strcmp(event,"postSolve") == 0) {
        arg = 3;
        LuaHelper::getInstance()->pushUserType(static_cast<b2ContactImpulse*>(data),"b2ContactImpulse");
    }
    LuaHelper::getInstance()->executeFunction(lua_object, arg);
}
*/

void ContactListener::checkCollisionWithBodyB(b2Body *bodyA, b2Body *bodyB, b2Contact* contact)
{
    std::vector<ContactNotificationInfo>::iterator it;
    std::vector<ContactNotificationInfo>::iterator end;

    if (bodyA->GetUserData()) {
        ContactInfo c = createContactInfoForBodyA(bodyA, contact);
        /// Check if the bodyA has registered collisions
        if (mPhysicsNodes.count(c.nodeA)) {
            /// Iterate over all the collision registrations for bodyA
            it = mPhysicsNodes[c.nodeA].begin();
            end = mPhysicsNodes[c.nodeA].end();
            while (it != end) {
                switch (it->type) {
                    case kPostponedNotificationWithId:
                    case kLua_PostponedNotificationWithId:
                        if (c.nodeB && it->uid == c.nodeB->getUniqueId())
                            mCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    case kPostponedNotificationWithTag:
                    case kLua_PostponedNotificationWithTag:
                        if (c.nodeB && it->tag == c.nodeB->getTag())
                            mCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    case kPostponedNotification:
                    case kLua_PostponedNotification:
                        mCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    default:
                        /// CC_ASSERT(false);
                        /// Could be a "end-collision" notification. Should we used another list of nodes dedicated to end-collision events?
                        break;
                }
                ++it;
            }
        }
    }
}

void ContactListener::checkEndCollisionWithBodyB(b2Body *bodyA, b2Body *bodyB, b2Contact* contact)
{
    std::vector<ContactNotificationInfo>::iterator it;
    std::vector<ContactNotificationInfo>::iterator end;

    if (bodyA->GetUserData()) {
        ContactInfo c = createContactInfoForBodyA(bodyA, contact);
        /// Check if the bodyA has registered collisions
        if (mPhysicsNodes.count(c.nodeA)) {
            /// Iterate over all the collision registrations for bodyA
            it = mPhysicsNodes[c.nodeA].begin();
            end = mPhysicsNodes[c.nodeA].end();
            while (it != end) {
                switch (it->type) {
                    case kLua_PostponedEndCollisionNotificationWithId:
                        if (c.nodeB && it->uid == c.nodeB->getUniqueId())
                            mEndCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    case kLua_PostponedEndCollisionNotificationWithTag:
                        if (c.nodeB && it->tag == c.nodeB->getTag())
                            mEndCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    case kLua_PostponedEndCollisionNotification:
                        mEndCollisions.push_back(PostponedNotificationInfo(c, *it));
                        break;
                    default:
                        /// CC_ASSERT(false);
                        break;
                }
                ++it;
            }
        }
    }
}

ContactInfo ContactListener::createContactInfoForBodyA(b2Body *bodyA, b2Contact *contact)
{
    ContactInfo info;
    /// Which body is the 'A' body?
    if (contact->GetFixtureA()->GetBody() == bodyA ) {
        info.fixtureA = contact->GetFixtureA();
        info.fixtureB = contact->GetFixtureB();
    } else {
        info.fixtureA = contact->GetFixtureB();
        info.fixtureB = contact->GetFixtureA();
    }

    info.isTouching = contact->IsTouching();

    info.bodyA = info.fixtureA->GetBody();
    info.bodyB = info.fixtureB->GetBody();

    b2WorldManifold worldManifold;
    contact->GetWorldManifold(&worldManifold);

    /// @todo manage two contact points (contact between polygons)
    info.pos = worldManifold.points[0];

    /*
    for (int i=0; i < contact->GetManifold()->pointCount; ++i) {
       CCLOG("%i: (%f %f) (%f %f)", i, worldManifold.points[i].x, worldManifold.points[i].y, info.pos.x, info.pos.y);
    }
    */

    /** Evaluate contact between body and sensor. Todo
    b2Manifold *manifold = nullptr;
    contact->Evaluate(manifold, info.bodyA->GetTransform(), info.bodyB->GetTransform());
    manifold = nullptr;
    */

    info.groupIndexA = info.fixtureA->GetFilterData().groupIndex;
    info.groupIndexB = info.fixtureB->GetFilterData().groupIndex;

    info.localA = info.bodyA->GetLocalPoint(worldManifold.points[0]);
    info.localB = info.bodyB->GetLocalPoint(worldManifold.points[0]);

    info.nodeA = info.bodyA->GetUserData() ? static_cast<BodyData *>(info.bodyA->GetUserData())->physicCocosNode : nullptr;
    info.nodeB = info.bodyB->GetUserData() ? static_cast<BodyData *>(info.bodyB->GetUserData())->physicCocosNode : nullptr;

    return info;
}

void ContactListener::dump(PostponedNotificationInfo &info)
{
    ContactInfo c = info.first;
    ContactNotificationInfo n = info.second;

    switch (n.type) {
        case kPostponedNotificationWithId:
        case kLua_PostponedNotificationWithId:
                CCLOG("Contact between bodies uid %d and uid %d", c.nodeA->getUniqueId(), c.nodeB->getUniqueId());
            break;
        case kPostponedNotificationWithTag:
        case kLua_PostponedNotificationWithTag:
                CCLOG("Contact between bodies tag %d and tag %d", c.nodeA->getTag(), c.nodeB->getTag());
            break;
        case kPostponedNotification:
        case kLua_PostponedNotification:
            if (c.nodeB) {
                CCLOG("Contact between bodies %d (tag: %d) and %d (tag: %d)", c.nodeA->getUniqueId(), c.nodeA->getTag(), c.nodeB->getUniqueId(), c.nodeB->getTag());
            } else {
                CCLOG("Contact between bodies %d (tag: %d) and unknown body", c.nodeA->getUniqueId(), c.nodeA->getTag());
            }
            break;
        default:
            CC_ASSERT(false); /// Unknown notification type
            break;
    }
    CCLOG("Contact info: world position(%f %f)", c.pos.x, c.pos.y);
}

/*
void ContactListener::registerContactDelegateScript(lua_Object lo)
{
    CC_ASSERT(mContactDelegateScript == 0);
    if (int refid = LuaHelper::getInstance()->retainFunction(lo)) {
        mContactDelegateScript = refid;
    } else {
        LuaHelper::getInstance()->raiseLuaError("Lua object is not a function");
    }
}
*/

void ContactListener::cancelAllNotification(const PhysicNode *node)
{
    CCAssert(node,"Physic node is nil");
    if (mPhysicsNodes.count(node)) mPhysicsNodes.erase(node);
    CCLOG("Cancel all notification for node uid:%d tag:%d.", node->getUniqueId(), node->getTag());
#if COCOS2D_DEBUG > 0
    /// dump();
#endif
}

void ContactListener::cancelCollisionNotification(const PhysicNode *node)
{
    CCAssert(node,"Physic node is nil");
    int count = 0;

    if (mPhysicsNodes.count(node)) {
        std::vector<ContactNotificationInfo>::iterator it = mPhysicsNodes[node].begin();
        while (it != mPhysicsNodes[node].end()) {
            if (it->type == kPostponedNotification ||
                it->type == kPostponedNotificationWithId ||
                it->type == kPostponedNotificationWithTag) {
                /// iterator is invalid after erase. http://www.cplusplus.com/reference/vector/vector/erase/
                /// Erase returns the new valid iterator
                it = mPhysicsNodes[node].erase(it);
            } else if (it->type == kLua_PostponedNotification ||
                       it->type == kLua_PostponedNotificationWithId ||
                       it->type == kLua_PostponedNotificationWithTag) {
                /// Remove lua callback function reference
                LuaHelper::getInstance()->releaseFunction(it->lua_callback);
                it = mPhysicsNodes[node].erase(it);
            } else {
                ++it;
            }
        }
        /// Remove the node from the list if no more delegate are associated
        count = mPhysicsNodes[node].size();
        if (! count) {
            mPhysicsNodes.erase(node);
            count = 0;
        }
    }

    CCLOG("Canceled collision notification for node uid: %d tag: %d remain: %d",node->getUniqueId(), node->getTag(), count);
#if COCOS2D_DEBUG > 0
    /// dump();
#endif
}

void ContactListener::cancelCollisionNotificationWithId(const PhysicNode *node, int uid)
{
    CCAssert(node,"Physic node is nil");
    if (mPhysicsNodes.count(node)) {
        std::vector<ContactNotificationInfo>::iterator it = mPhysicsNodes[node].begin();
        while (it != mPhysicsNodes[node].end()) {
            if (it->type == kPostponedNotificationWithId && it->uid == uid) {
                it = mPhysicsNodes[node].erase(it);
            } else if (it->type == kLua_PostponedNotificationWithId && it->uid == uid) {
                it = mPhysicsNodes[node].erase(it);
                LuaHelper::getInstance()->releaseFunction(it->lua_callback);
            } else {
                ++it;
            }
        }
        /// Remove the node from the list if no more delegate are associated
        if (! mPhysicsNodes[node].size())
            mPhysicsNodes.erase(node);
    }
}

void ContactListener::cancelCollisionNotificationWithTag(const PhysicNode *node, int tag)
{
    CCAssert(node,"Physic node is nil");
    if (mPhysicsNodes.count(node)) {
        std::vector<ContactNotificationInfo>::iterator it = mPhysicsNodes[node].begin();
        while (it != mPhysicsNodes[node].end()) {
            if (it->type == kPostponedNotificationWithTag && it->tag == tag) {
                it = mPhysicsNodes[node].erase(it);
            } else if (it->type == kLua_PostponedNotificationWithTag && it->tag == tag) {
                LuaHelper::getInstance()->releaseFunction(it->lua_callback);
                it = mPhysicsNodes[node].erase(it);
            } else {
                ++it;
            }
        }
        /// Remove the node from the list if no more delegate are associated
        if (! mPhysicsNodes[node].size())
            mPhysicsNodes.erase(node);
    }
}

void ContactListener::cancelEndCollisionNotificationScritpWithTag(const PhysicNode *node, int tag)
{
    if (mPhysicsNodes.count(node)) {
        std::vector<ContactNotificationInfo>::iterator it = mPhysicsNodes[node].begin();
        while (it != mPhysicsNodes[node].end()) {
            /*
            if (it->type == kLua_PostponedEndCollisionNotificationWithTag && it->tag == tag) {
                it = mPhysicsNodes[node].erase(it);
            } else */
            if (it->type == kLua_PostponedEndCollisionNotificationWithTag && it->tag == tag) {
                LuaHelper::getInstance()->releaseFunction(it->lua_callback);
                it = mPhysicsNodes[node].erase(it);
            } else {
                ++it;
            }
        }
        /// Remove the node from the list if no more delegate are associated
        if (! mPhysicsNodes[node].size())
            mPhysicsNodes.erase(node);
    }
}

void ContactListener::registerCollisionNotification(CCObject *owner, SEL_Contact selector, PhysicNode *node)
{
    CCLOG("Register post-contact notification between node %d (tag %d) and all nodes.", node->getUniqueId(), node->getTag());
    ContactNotificationInfo info;
    info.type = kPostponedNotification;
    info.owner = owner;
    info.selector = selector;

    mPhysicsNodes[node].push_back(info);
}

void ContactListener::registerCollisionNotificationWithId(CCObject *owner, SEL_Contact selector, PhysicNode *node, int uid)
{
    CCLOG("Register post-contact notification between node %d and node %d", node->getUniqueId(), uid);
    ContactNotificationInfo info;
    info.type = kPostponedNotificationWithId;
    info.owner = owner;
    info.selector = selector;
    info.uid = uid;

    mPhysicsNodes[node].push_back(info);
}

void ContactListener::registerCollisionNotificationWithTag(CCObject *owner, SEL_Contact selector, PhysicNode *node, int tag)
{
    CCLOG("Register post-contact notification between node tag %d and node tag %d", node->getTag(), tag);
    ContactNotificationInfo info;
    info.type = kPostponedNotificationWithTag;
    info.owner = owner;
    info.selector = selector;
    info.tag = tag;

    mPhysicsNodes[node].push_back(info);
}

int ContactListener::registerCollisionNotificationScript(int lo, PhysicNode *node)
{
    ContactNotificationInfo info;
    info.type = kLua_PostponedNotification;
    info.lua_callback = lo;

    mPhysicsNodes[node].push_back(info);
    return lo;
}

int ContactListener::registerCollisionNotificationScriptWithId(int lo, PhysicNode *node, int uid)
{
    ContactNotificationInfo info;
    info.type = kLua_PostponedNotificationWithId;
    info.uid = uid;
    info.lua_callback = lo;

    mPhysicsNodes[node].push_back(info);

    return lo;
}

int ContactListener::registerCollisionNotificationScriptWithTag(int lo, PhysicNode *node, int tag)
{
    ContactNotificationInfo info;
    info.type = kLua_PostponedNotificationWithTag;
    info.tag = tag;
    info.lua_callback = lo;

    mPhysicsNodes[node].push_back(info);

    return lo;
}

int ContactListener::registerEndCollisionNotificationScriptWithTag(int lo, PhysicNode *node, int tag)
{
    ContactNotificationInfo info;
    info.type = kLua_PostponedEndCollisionNotificationWithTag;
    info.tag = tag;
    info.lua_callback = lo;

    mPhysicsNodes[node].push_back(info);

    return lo;
}

void ContactListener::dump()
{
    int count = 0;
    PhysicNodesMapIterator it = mPhysicsNodes.begin();
    while (it != mPhysicsNodes.end()) {
        count += it->second.size();
        std::cout << "Physic node uid [" << it->first->getUniqueId() << "] tag[" << it->first->getTag() << "]" << std::endl;
        std::cout << "Delegates [" << it->second.size() << "]:" << std::endl;
        for (int i=0; i < it->second.size(); ++i) {
            ContactNotificationInfo info = it->second.at(i);
            switch (info.type) {
                case kPostponedNotification:
                    std::cout << "kPostponedNotification" << std::endl;
                    break;
                case kPostponedNotificationWithId:
                    std::cout << "kPostponedNotificationWithId [" << info.uid << "]" << std::endl;
                    break;
                case kPostponedNotificationWithTag:
                    std::cout << "kPostponedNotificationWithTag [" << info.tag << "]" << std::endl;
                    break;
                case kLua_PostponedNotification:
                    std::cout << "kLua_PostponedNotification" << std::endl;
                    break;
                case kLua_PostponedNotificationWithId:
                    std::cout << "kLua_PostponedNotificationWithId [" << info.uid << "]" << std::endl;
                    break;
                case kLua_PostponedNotificationWithTag:
                    std::cout << "kLua_PostponedNotificationWithTag [" << info.tag << "]" << std::endl;
                    break;
                case kLua_PostponedEndCollisionNotificationWithTag:
                    std::cout << "kLua_PostponedEndCollisionNotificationWithTag [" << info.tag << "]" << std::endl;
                    break;
                default:
                    std::cout << "Unknown type: " << info.type << std::endl;
            }
        }
        ++it;
    }
    std::cout << "Physic nodes [" << mPhysicsNodes.size() << "] Total delegates [" << count << "]" << std::endl;
}

NS_PIX2D_END
