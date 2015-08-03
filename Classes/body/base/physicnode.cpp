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

#include "physicnode.h"
#include "physics/physics.h"
#include "bindings/luahelper.h"

NS_PIX2D_BEGIN

CustomSprite::CustomSprite()
: mTweenActionHandler(0)
{}
CustomSprite::~CustomSprite()
{
    CCLOG("Release custom sprite function.");
    LuaHelper::getInstance()->releaseFunction(mTweenActionHandler);
}

CustomSprite* CustomSprite::create(const char *pszFilename)
{
    CustomSprite* pRet = new CustomSprite();
    if (pRet && pRet->initWithFile(pszFilename)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

CustomSprite* CustomSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CustomSprite* pRet = new CustomSprite();
    if (pRet && pRet->initWithSpriteFrameName(pszSpriteFrameName)) {
        pRet->autorelease();
    } else {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

/*
CustomSprite* CustomSprite::createWithTexture(CCTexture2D *pTexture)
{
    CustomSprite* pobSprite = new CustomSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}
*/

void CustomSprite::convertToNodeSpaceNormalize(float *x, float *y)
{
    *x = getContentSize().width * (*x);
    *y = getContentSize().height * (*y);
}

void CustomSprite::updateTweenAction(float value, const char* key)
{
    if (mTweenActionHandler > -1) {
        LuaHelper::getInstance()->pushFloat(value);
        LuaHelper::getInstance()->pushString(key);
        LuaHelper::getInstance()->executeFunction(mTweenActionHandler, 2);
    }
}

void CustomSprite::unregisterTweenActionHandler()
{
    LuaHelper::getInstance()->releaseFunction(mTweenActionHandler);
}

void CustomSprite::registerTweenActionHandler(int lo)
{
    unregisterTweenActionHandler();
    mTweenActionHandler = lo;
}

PhysicNode::PhysicNode()
: CCNodeRGBA()
, mUniqueId(Physics::shared()->getNextUniqueId())
, mIsMovable(false)
, mBody(nullptr)
, mMarkedForDestruction(false)
{}

PhysicNode::PhysicNode(const int uid)
: CCNodeRGBA()
, mUniqueId(uid)
, mIsMovable(false)
, mBody(nullptr)
, mMarkedForDestruction(false)
{}

PhysicNode::~PhysicNode()
{
    CCLOG("Destroy physic node uid:%d tag:%d", mUniqueId, getTag());
    /// Destroy the physic body and the attached user data
    if (mBody) {
        Physics::shared()->removeBody(mBody);
        mBody = nullptr;
    }
}

bool PhysicNode::init(const PhysicNodeDef &def)
{
    /// Set initial CCNode's position and rotation
    setPosition(Physics::unitToPixelCenter(def.pos.x, def.pos.y));
    setRotation(-1 * CC_RADIANS_TO_DEGREES(def.angle));
    /// Set the CCNode's tag
    setTag(def.tag);
    setZOrder(def.zorder);

    /// Load a sprite from an image or texture name
    if (def.sprite.length()) {
        if (CustomSprite *sprite = CustomSprite::create(def.sprite.c_str())) {
            sprite->setTag(settings::kTagPhysicsNodeSprite);
            addChild(sprite);
        } else {
            CCLOGERROR("Can't create sprite with image ['%s']", def.sprite.c_str());
            return false;
        }
    } else if (def.frame.length()) {
        if (CustomSprite *sprite  = CustomSprite::createWithSpriteFrameName(def.frame.c_str())) {
            sprite->setTag(settings::kTagPhysicsNodeSprite);
            addChild(sprite);
        } else {
            CCLOGERROR("Can't create sprite with frame name ['%s']",def.frame.c_str());
            return false;
        }
    }

    /// Success
    return true;
}

void PhysicNode::dump()
{
    std::cout << "PhysicNode...." << std::endl;
    std::cout << "Unique id: " << getUniqueId() << std::endl;
    std::cout << "tag: " << CCNode::getTag() << std::endl;
}

BodyData *PhysicNode::createBodyData()
{
    return createBodyData(this);
}

BodyData *PhysicNode::createBodyData(PhysicNode *node)
{
    BodyData *data = new BodyData;
    data->physicCocosNode = node;
    return data;
}

void PhysicNode::applyLinearImpulse(float x, float y)
{
    mBody->ApplyLinearImpulse(b2Vec2(x,y), mBody->GetWorldCenter());
}

void PhysicNode::applyForceToCenter(float x, float y)
{
    mBody->ApplyForceToCenter(b2Vec2(x,y));
}

void PhysicNode::setCollisionFilter(unsigned short category, unsigned short mask, signed short group)
{
    b2Fixture *fixture = mBody->GetFixtureList();
    b2Filter filter;
    while (fixture) {
        filter.categoryBits = category;
        filter.maskBits = mask;
        filter.groupIndex = group;
        fixture->SetFilterData(filter);
        fixture = fixture->GetNext();
    }
}

void PhysicNode::getCollisionFilter(unsigned short *category, unsigned short *mask, signed short *group)
{
    b2Filter filter = mBody->GetFixtureList()->GetFilterData();
    *category = filter.categoryBits;
    *mask = filter.maskBits;
    *group = filter.groupIndex;
}

void PhysicNode::setCollisionCategory(unsigned short category)
{
    b2Fixture *fixture = mBody->GetFixtureList();
    b2Filter filter;
    while (fixture) {
        filter = fixture->GetFilterData();
        filter.categoryBits = category;
        fixture->SetFilterData(filter);
        fixture = fixture->GetNext();
    }
}

void PhysicNode::setCollisionMask(unsigned short mask)
{
    b2Fixture *fixture = mBody->GetFixtureList();
    b2Filter filter;
    while (fixture) {
        filter = fixture->GetFilterData();
        filter.maskBits = mask;
        fixture->SetFilterData(filter);
        fixture = fixture->GetNext();
    }
}

void PhysicNode::setCollisionGroup(signed short group)
{
    b2Fixture *fixture = mBody->GetFixtureList();
    b2Filter filter;
    while (fixture) {
        filter = fixture->GetFilterData();
        filter.groupIndex = group;
        fixture->SetFilterData(filter);
        fixture = fixture->GetNext();
    }
}

void PhysicNode::setMass(float value)
{
    mBody->GetFixtureList()->SetDensity(value);
    mBody->ResetMassData();
    /*
    /// Tried to change the body's mass using the snippet below but body
    /// becomes unstable and does not collide anymore. Requires more
    /// more investigation and testing
    b2MassData data;
    data.mass = value;
    data.center = mBody->GetLocalCenter();
    mBody->SetMassData(&data);
    */
}

NS_PIX2D_END
