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

#include "body/rope.h"
#include "physics/physics.h"
#include "body/base/circle.h"
#include "body/vrope/vrope.h"

NS_PIX2D_BEGIN

Rope::Rope()
: CCNode()
, mVrope(nullptr)
, mTouchSensor(nullptr)
, mInnerSensor(nullptr)
, mAnchor(nullptr)
, mHook(nullptr)
, mLinkBody(nullptr)
{}

Rope::~Rope()
{
    if (mLinkBody) Physics::shared()->removeBody(mLinkBody);
    /// Don't need to destroy the physics nodes because because there are child nodes and will be autoreleased
    if (mVrope) {
        mVrope->removeSprites(); /// In case the rope is not removed with the scene we have to manually remove the sprites from the sprite batch node
    }
    CC_SAFE_DELETE(mVrope);
}

bool Rope::init(const RopeDef &def)
{
    /// This node's position must be set to the coordinate origin (x=0, y=0) so adding
    /// a physic node as a child will be seamless

    if (! def.batch) {
        CCLOGERROR("Can't create vrope (sprite batch nil)");
        return false;
    }

    /// b2Vec2 endPos = def.endpos + b2Vec2(0, -0.1 * Physics::shared()->unit());

    /// Create the hook body
    {
        CircleDef cd;
        /// cd.pos = def.endpos + b2Vec2(0, -0.1 * Physics::shared()->unit());
        cd.pos = def.endpos;
        cd.body_type = b2_dynamicBody;
        cd.radius = def.hookRadius;
        cd.frame = def.hookFrame;
        cd.density = def.hookDensity;
        cd.friction = def.hookFriction;
        cd.restitution = def.hookRestitution;
        mHook = Circle::create(cd);
        addChild(mHook);
    }

    {
        /// Create the inner sensor (same size than the hook)
        CircleDef cd;
        cd.pos = def.endpos;
        cd.body_type = b2_dynamicBody;
        cd.is_sensor = true;
        cd.radius = def.hookRadius;
        mInnerSensor = Circle::create(cd);
        addChild(mInnerSensor);
    }

    /// Create the outer sensor body for easy touch
    {
        CircleDef cd;
        cd.pos = def.endpos;
        cd.body_type = b2_dynamicBody;
        cd.is_sensor = true;
        cd.radius = def.sensorRadius;
        mTouchSensor = Circle::create(cd);
        addChild(mTouchSensor);
    }

    /// Connect the sensors with the hook body
    Physics::createRevoluteJoint(mHook->body(), mTouchSensor->body(), mTouchSensor->body()->GetWorldCenter());
    Physics::createRevoluteJoint(mHook->body(), mInnerSensor->body(), mInnerSensor->body()->GetWorldCenter());

    /// Create the anchor body
    {
        CircleDef cd;
        cd.density = def.anchorDensity;
        cd.pos = def.startpos;
        cd.radius = def.anchorRadius;
        cd.body_type = b2_staticBody;
        cd.category = Physics::kNoCollision;
        cd.frame = def.anchorFrame;
        mAnchor = Circle::create(cd);
        addChild(mAnchor);
    }

    /// Create the rope joint
    b2Joint *joint = Physics::shared()->createRopeJoint(mAnchor->body(), mHook->body(),def.anchorLocalAnchor,def.hookLocalAnchor);

    /// Create the vrope
    mVrope = new VRope(joint, def.batch);

    if (! mVrope) {
        CCLOGERROR("Can't create the VRope object");
        return false;
    }

    /// CCNode
    scheduleUpdate();

    return true;
}

void Rope::attach(PhysicNode *node)
{
    if (mLinkBody) {
        CC_ASSERT(false); /// A node is already attached to the rope
        return;
    }
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.position = mHook->getBodyCenter();
    mLinkBody = Physics::shared()->world()->CreateBody(&def);

    b2CircleShape shape;
    shape.m_radius = Physics::shared()->unit() * 0.25;

    b2FixtureDef fd;
    fd.density = 1.0;
    fd.filter.maskBits = 0; /// no collision
    fd.shape = &shape;
    mLinkBody->CreateFixture(&fd);

    Physics::createRevoluteJoint(mLinkBody, node->body(), mLinkBody->GetLocalCenter(), node->body()->GetLocalCenter());
    Physics::createRevoluteJoint(mLinkBody, mHook->body(), mLinkBody->GetLocalCenter(), mHook->body()->GetLocalCenter());
}

void Rope::detach()
{
    if (mLinkBody) {
        Physics::shared()->removeBody(mLinkBody);
        mLinkBody = nullptr;
    }
}

void Rope::update(float dt)
{
    /// mVrope->update(dt);
    mVrope->updateWithPreIntegratedGravity(dt);
    /// mVrope->updateWithPreIntegratedOriginGravity(dt);
    mVrope->updateSprites();
}

NS_PIX2D_END
