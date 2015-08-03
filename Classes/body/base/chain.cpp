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

#include "body/base/chain.h"
#include "physics/physics.h"

NS_PIX2D_BEGIN

Chain::Chain(int uid)
: PhysicNode(uid)
{}

Chain::Chain(const ChainDef &def)
: PhysicNode(def.uid)
{}

Chain::~Chain()
{}

Chain *Chain::create(const ChainDef &def)
{
    Chain *ptr = new Chain(def);

    if (ptr && ptr->init(def)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool Chain::init(const ChainDef &def)
{
    if (! PhysicNode::init(def)) return false;

    /// PhysicNode position is centered to the map cell by default
    /// Chain is not centered so we force the node's position to avoid a
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

    /// 2. Create the Chain shape
    std::vector<b2Vec2> vertices;
    for (const b2Vec2 v : def.vertices) {
        vertices.push_back(Physics::unitToMeter(v.x, v.y));
    }
    b2ChainShape shape;
    shape.CreateChain(&vertices[0], vertices.size());

    /// Add sprites along the chain path. The sprite is duplicated and/or split
    /// to fit every chain segments.
    if (!def.frame.empty()) {
        CCSprite *tmp = getSprite(); /// We use the default sprite created by PhysicNode
        CCSize size = tmp->getContentSize();
        for (int i=0; i < def.vertices.size() - 1; ++i) {
            CCPoint p1 = Physics::unitToPixel(def.vertices[i]);
            CCPoint p2 = Physics::unitToPixel(def.vertices[i+1]);
            float distance = ccpDistance(p1, p2);
            float angle = -1 * CC_RADIANS_TO_DEGREES(ccpToAngle(p2 - p1));
            float t = .0f;
            for (t=.0f; t < 1.f; t = t + (size.width / distance)) {
                float w = distance * (1.f - t) >= size.width ? size.width : distance * (1.f - t);
                CCRect r = tmp->getTextureRect();
                r.size.width = w;
                CCSprite *sprite = CCSprite::createWithTexture(tmp->getTexture());
                sprite->setAnchorPoint(ccp(.0f,1.f));
                sprite->setPosition(ccpLerp(p1,p2,t));
                sprite->setTextureRect(r, tmp->isTextureRectRotated(), CCSizeMake(w,tmp->getContentSize().height));
                sprite->setRotation(angle);
                addChild(sprite);
            }
        }
        /// We can now remove the sprite
        tmp->removeFromParentAndCleanup(true);
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

NS_PIX2D_END
