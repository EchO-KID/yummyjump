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

#include "body/tests/test_rope.h"
#include "physics/physics.h"
#include "body/rope.h"

NS_PIX2D_BEGIN

TestRope::TestRope()
: CCNode()
, mWorld(nullptr)
, mRope(nullptr)
{}

TestRope::~TestRope()
{
}

bool TestRope::init(CCLayer *layer)
{
    CCSpriteBatchNode *batch = CCSpriteBatchNode::create("textures/rainbow.png");
    batch->setTag(99);
    layer->addChild(batch);

    /// Create the box2d world
    mWorld = new b2World(b2Vec2(.0f,-10.f));

    b2BodyDef bd;
    bd.position.Set(5, 10);
    bd.type = b2_staticBody;

    /// 2. Create the circle shape
    b2CircleShape shape;
    shape.m_p.SetZero();
    shape.m_radius = 1.f;

    /// 3. Configure the fixture definition
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = 1.f;
    fd.friction = .2f;
    fd.restitution = .1f;

    /// 4. Create the body and the fixture
    b2Body *bodyA = mWorld->CreateBody(&bd);
    bodyA->CreateFixture(&fd);

    bd.type = b2_dynamicBody;
    bd.position.Set(5,3);
    b2Body *bodyB = mWorld->CreateBody(&bd);
    bodyB->CreateFixture(&fd);

    new VRope(bodyA, bodyB,batch);

    layer->addChild(CCSprite::create("textures/rainbow.png"));

    return true;
}

void TestRope::update(float dt)
{
}

void TestRope::draw()
{
    mWorld->DrawDebugData();
}

NS_PIX2D_END
