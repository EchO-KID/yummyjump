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
 
#include "boundary.h"
#include "physics/physics.h"

NS_PIX2D_BEGIN

Boundary *Boundary::create(const CCRect &rect)
{
    Boundary *ptr = new Boundary();
    if (ptr && ptr->init(rect)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool Boundary::init(const CCRect &rect)
{
    setTag(PhysicNode::kBoundaryTag);
    /// Body definition
    b2BodyDef bd;
    bd.userData = createBodyData(this); /// The user data
    bd.position.SetZero();
    bd.type = b2_staticBody;

    /// Edge shape
    b2EdgeShape edge;

    /// Fixture definition
    b2FixtureDef fd;
    fd.shape = &edge;
    // fd.filter.categoryBits = 0;
    // fd.filter.maskBits = 0;

    Physics *p = Physics::shared();
    b2Vec2 origin = p->position() + p->unitToMeter(rect.origin.x, rect.origin.y);
    b2Vec2 topLeft = origin + p->unitToMeter(.0f, rect.size.height);
    b2Vec2 topRight = origin + p->unitToMeter(rect.size.width, rect.size.height);
    b2Vec2 bottomRight = origin + p->unitToMeter(rect.size.width, .0f);

    /// Create the four boundaries in clock-wize order from origin (left -> top -> right -> bottom)
    mBody = p->world()->CreateBody(&bd);
    /// Left boundary
    edge.Set(origin, topLeft);
    fd.filter.groupIndex = Physics::kBoundaryLeft;
    mBody->CreateFixture(&fd);

    /// Top boundary
    edge.Set(topLeft, topRight);
    fd.filter.groupIndex = Physics::kBoundaryTop;
    mBody->CreateFixture(&fd);

    /// Right boundary
    edge.Set(topRight, bottomRight);
    fd.filter.groupIndex = Physics::kBoundaryRight;
    mBody->CreateFixture(&fd);

    /// Bottom boundary
    edge.Set(bottomRight, origin);
    fd.filter.groupIndex = Physics::kBoundaryBottom;
    mBody->CreateFixture(&fd);

    return true;
}
NS_PIX2D_END
