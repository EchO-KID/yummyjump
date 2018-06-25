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

#include "circle.h"
#include "physics/physics.h"
#include "CCLuaEngine.h"
#include "common/settings.h"

#if COCOS2D_CONSOLE_DEBUG > 0
# include "debug/debuglayer.h"
#endif

NS_PIX2D_BEGIN

Circle::Circle(int uid)
: PhysicNode(uid)
{}

Circle::Circle(const CircleDef &def)
: PhysicNode(def.uid)
{}

Circle::~Circle()
{}

Circle *Circle::create(const CircleDef &def)
{
    Circle *ptr = new Circle(def);
    if (ptr && ptr->init(def)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool Circle::init(const CircleDef &def)
{
    if (! PhysicNode::init(def)) return false;

    /// 1. Configure the body definition
    b2BodyDef bd;
    bd.position = Physics::unitToMeterCenter(def.pos);
    bd.angle = def.angle;
    bd.type = def.body_type;
    bd.userData = createBodyData(this); /// The user data

    /// 2. Create the circle shape
    b2CircleShape shape;
    shape.m_p.SetZero();
    shape.m_radius = Physics::shared()->unit() * (def.radius > .0f ? def.radius : .25f);

    /// 3. Configure the fixture definition
    b2FixtureDef fd;
    fd.shape = &shape;
    fd.density = def.density;
    fd.friction = def.friction;
    fd.restitution = def.restitution;
    fd.isSensor = def.is_sensor;
    fd.filter.maskBits = def.mask;
    fd.filter.categoryBits = def.category;
    fd.filter.groupIndex = def.group;

    /// 4. Create the body and the fixture
    mBody = Physics::shared()->world()->CreateBody(&bd);
    if (mBody) {
        mBody->CreateFixture(&fd);
    } else {
        CCLOGERROR("Can't create the circle's body.");
        return false;
    }

    /// Success
    return true;
}

#if COCOS2D_CONSOLE_DEBUG > 0
void Circle::draw()
{
    if (DebugSettings::getInstance()->showPhysicsDraw == false)
        return;

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);
    kmGLPushMatrix();

    if (CCSprite *s = dynamic_cast<CCSprite *>(getChildByTag(settings::kTagPhysicsNodeSprite))) {
        //CCPoint a = s->getAnchorPoint();
        CCRect bb = s->boundingBox();
        /*
        CCRect bb = CCRectMake(s->getPosition().x - s->getContentSize().width * a.x,
                               s->getPosition().y - s->getContentSize().height * a.y,
                               s->getContentSize().width * a.x,
                               s->getContentSize().height * a.y);
        */
        CCPoint vertices[4] = {
            CCPoint( bb.origin.x, bb.origin.y ),
            CCPoint( bb.origin.x, bb.origin.y + bb.size.height ),
            CCPoint( bb.origin.x + bb.size.width, bb.origin.y + bb.size.height ),
            CCPoint( bb.origin.x + bb.size.width, bb.origin.y)
        };

        ccDrawColor4B(255, 255, 0, 255);
        glLineWidth(2);

        ccDrawPoly(vertices, 4, true);

    }

    kmGLPopMatrix();
}
#endif

void Circle::drawDebugShape(const ccColor4F &color)
{
    CCPoint center = Physics::meterToPixel(mBody->GetWorldCenter());
    float radius = Physics::meterToPixel(mBody->GetFixtureList()->GetShape()->m_radius);
    ccDrawColor4F(color.r, color.g, color.b, color.a);
    ccDrawCircle(center, radius, .0f, 20, true);
}

NS_PIX2D_END
