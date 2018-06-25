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

#include "body/base/box.h"
#include "physics/physics.h"
#include "CCLuaEngine.h"

NS_PIX2D_BEGIN

Box::Box(int uid)
: PhysicNode(uid)
{}

Box::Box(const BoxDef &def)
: PhysicNode(def.uid)
{}

Box::~Box()
{}

Box *Box::create(const BoxDef &def)
{
    Box *ptr = new Box(def);

    if (ptr && ptr->init(def)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool Box::init(const BoxDef &def)
{
    if (! PhysicNode::init(def)) return false;

    /// PhysicNode position is centered to the map cell by default
    /// Box is not centered so we force the node's position to avoid a
    /// a wrong position on the very first physic step.
    setPosition(Physics::unitToPixel(def.pos.x,def.pos.y));

    /// 1. Configure the body definition
    b2BodyDef bd;
    bd.type = def.body_type;
    bd.position = Physics::unitToMeter(def.pos);
    bd.angle = def.angle;
    bd.userData = createBodyData(this); /// The user data

    /// Create the body
    mBody = Physics::shared()->world()->CreateBody(&bd);

    /// 2. Create the Box shape
    b2PolygonShape shape;
    b2Vec2 size = Physics::unitToMeter(def.size);

    if (def.center.x == .0f && def.center.y == .0f)
        shape.SetAsBox(size.x /2, size.y /2);
    else {
        shape.SetAsBox(size.x /2, size.y /2, Physics::unitToMeter(def.center), def.angle);
        /// setPosition(Physics::meterToPixel(mBody->GetWorldPoint(shape.m_centroid)));
    }

    /// 3. Configure the fixture definition
    b2FixtureDef fd;
    fd.isSensor = def.is_sensor;
    fd.shape = &shape;
    fd.density = def.density;
    fd.friction = def.friction;
    fd.restitution = def.restitution;
    fd.filter.maskBits = def.mask;
    fd.filter.categoryBits = def.category;
    fd.filter.groupIndex = def.group;

    mBody->CreateFixture(&fd);

    return true;
}

void Box::drawDebugShape(const ccColor4F &color)
{
    b2Transform xf = mBody->GetTransform();
    b2PolygonShape *poly = static_cast<b2PolygonShape *>(body()->GetFixtureList()->GetShape());

    CCPoint origin = Physics::meterToPixel(b2Mul(xf, poly->m_vertices[0]));
    CCPoint destination = Physics::meterToPixel(b2Mul(xf, poly->m_vertices[2]));

    ccDrawSolidRect(origin, destination, ccc4f(color.r, color.g, color.b, color.a));
}

NS_PIX2D_END
