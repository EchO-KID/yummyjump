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

#include "texture.h"
#include "physics/physics.h"
#include "poly2tri/poly2tri.h"
#include "clipper/clipper.hpp"
#include "sprites/texturesprite.h"

NS_PIX2D_BEGIN

Texture::Texture(int uid)
: PhysicNode(uid)
, mTextureSprite(nullptr)
{}

Texture::~Texture()
{
    CCLOG("Destroy physics texture node.");
}

Texture *Texture::create(TextureDef &def)
{
    Texture *ptr = new Texture(def.uid);
    if (ptr && ptr->init(def)) {
        ptr->autorelease();
        return ptr;
    }
    delete ptr;
    return nullptr;
}

bool Texture::init(TextureDef &def)
{
    /// a minimum of 2 vertices is required to create AABB texture
    if (def.vertices.size() < 2) {
        CCLOGERROR("There must be at least 2 vertices.");
        return false;
    }

    if (! PhysicNode::init(def))
        return false;

    /// Configure and create the body
    b2BodyDef bd;
    /// BUG: Dynamic bodies are not created with the correct position (static and kinematic bodies
    /// position are correct though).
    /// To avoid this bug we must create a STATIC body and after triangulation we are able to set the target
    /// body type (dynamic or kinemtic).
    bd.type = b2_staticBody;
    // bd.type = def.body_type;
    // bd.position = b2Vec2_zero;
    bd.userData = createBodyData(this); /// The user data
    mBody = Physics::shared()->world()->CreateBody(&bd);

    mFilter.groupIndex = def.group;
    mFilter.maskBits = def.mask;
    mFilter.categoryBits = def.category;
    mFixtureDef.density = def.density;
    mFixtureDef.friction = def.friction;
    mFixtureDef.restitution = def.restitution;
    mFixtureDef.isSensor = def.is_sensor;

    if (def.simplify) {
        this->simplifyPolygon(def.vertices);
    }

    bool rc = false;
    if (def.vertices.size() == 2)
        rc = createAABBTexture(def);
    else
        rc = createTriangulatedTexture(def);

    if (rc) {
        /// Set the body's position to the center of the polygon
        mBody->SetTransform(mBody->GetWorldCenter(), mBody->GetAngle());
        /// Must set the CCNode position in case its a static body (which position is not updated automatically. See. PhysicsLayer)
        setPosition(Physics::meterToPixel(mBody->GetPosition()));
        /// We can now set the body type
        if (def.body_type != b2_staticBody) {
            mBody->SetType(def.body_type);
        }
    } else {
        Physics::shared()->removeBody(mBody);
    }

    return rc;
}

bool Texture::createTriangulatedTexture(TextureDef &def)
{
    /// Triangulate and create the body's fixtures
    CCPointVector points;
    triangulate(def.vertices, points);

    /// Create the texture sprite
    mTextureSprite = TextureSprite::create(def.texture, points);
    if (mTextureSprite) {
        addChild(mTextureSprite);
        return true;
    }
    return false;
}

bool Texture::createAABBTexture(TextureDef &def)
{
    CCPoint upperbound, lowerbound;
    aabb(def.vertices, upperbound, lowerbound);

    /// Create the texture
    mTextureSprite = TextureSprite::createWithAABB(def.texture, upperbound, lowerbound);
    if (mTextureSprite) {
        addChild(mTextureSprite);
        return true;
    }
    return false;
}

void Texture::addVertices(std::vector<b2Vec2> vertices)
{
    if (vertices.size() == 2) {
        CCPoint upperbound, lowerbound;
        aabb(vertices, upperbound, lowerbound);
        mTextureSprite->addAABBPolygon(upperbound, lowerbound);
    } else {
        CCPointVector points;
        triangulate(vertices, points);
        mTextureSprite->addPolygon(points);
    }
}

void Texture::aabb(const std::vector<b2Vec2> &vertices, CCPoint &upperbound, CCPoint &lowerbound)
{
    b2Vec2 p1 = Physics::unitToMeter(vertices.at(0));   /// Upperbound (top-left)
    b2Vec2 p2 = Physics::unitToMeter(vertices.at(1));   /// Lowerbound (bottom-right)

    b2Vec2 vec[4];
    vec[0].Set(p1.x, p1.y);
    vec[1].Set(p2.x, p1.y);
    vec[2].Set(p2.x, p2.y);
    vec[3].Set(p1.x, p2.y);

    /// 2. Create the Box shape
    b2PolygonShape shape;
    shape.Set(vec, 4);

    /// 3. Configure and create the fixture
    b2FixtureDef fd(mFixtureDef);
    fd.shape = &shape;
    b2Fixture *fixture = mBody->CreateFixture(&fd);
    fixture->SetFilterData(mFilter);

    upperbound = Physics::meterToPixel(p1);
    lowerbound = Physics::meterToPixel(p2);
}

void Texture::triangulate(const std::vector<b2Vec2> &vertices, CCPointVector &points)
{
    /// convertion from b2Vec2 to p2t::Point
    vector<p2t::Point*> polyline;
    for (int i = 0; i < vertices.size(); ++i) {
        b2Vec2 v = Physics::unitToMeter(vertices[i]);
        polyline.push_back(new p2t::Point(v.x, v.y));
    }

    ///  Create CDT and add primary polyline
    /* NOTE: polyline must be a simple polygon. The polyline's points
       constitute constrained edges. No repeat points!!! */
    p2t::CDT cdt(polyline);

    cdt.Triangulate();

    vector<p2t::Triangle*> triangles;
    triangles = cdt.GetTriangles();

    /// Create the body's fixtures
    b2Vec2 vec[3];
    b2PolygonShape shape;
    b2FixtureDef fd(mFixtureDef);

    for (p2t::Triangle *tri : triangles) {
        /// Create the triangle shape
        for (int i = 0; i < 3; ++i) {
            const p2t::Point &p = *tri->GetPoint(i);
            vec[i].Set(p.x, p.y);
            points.push_back(Physics::meterToPixel(vec[i]));
        }
        shape.Set(vec, 3);
        /// Create the fixture
        fd.shape = &shape;
        b2Fixture *fixture = mBody->CreateFixture(&fd);
        fixture->SetFilterData(mFilter);
    }

    freeContainer(polyline);
}

template <class T> void Texture::freeContainer(T &cntr)
{
    for (typename T::iterator it = cntr.begin(); it != cntr.end(); ++it)
        delete * it;
    cntr.clear();
}

void Texture::dump()
{
    PhysicNode::dump();
}

void Texture::triangulate(CCPointVector &in, CCPointVector &out)
{
    /// convertion from CCPoint to p2t::Point
    vector<p2t::Point*> polyline;
    for (const CCPoint &p : in) {
        polyline.push_back(new p2t::Point(p.x, p.y));
    }

    ///  Create CDT and add primary polyline
    /* NOTE: polyline must be a simple polygon. The polyline's points
     constitute constrained edges. No repeat points!!! */
    p2t::CDT cdt(polyline);

    cdt.Triangulate();

    for (p2t::Triangle *triangle : cdt.GetTriangles()) {
        for (int i = 0; i < 3; ++i) {
            const p2t::Point &p = *triangle->GetPoint(i);
            out.push_back(ccp(p.x,p.y));
        }
    }

    Texture::freeContainer(polyline);
}

void Texture::simplifyPolygon(std::vector<b2Vec2> &polygon)
{
    ClipperLib::Path in;
    for (int i = 0; i < polygon.size(); ++i)
        in.push_back(ClipperLib::IntPoint(polygon.at(i).x * 1024,polygon.at(i).y * 1024));

    /// Simplify the polygon and turns complex polygon into simple polygon
    ClipperLib::Paths out;
    ClipperLib::SimplifyPolygon(in, out, ClipperLib::pftEvenOdd);

    ClipperLib::Path path = out.at(0);          /// TODO: manage all polygons

    /// Convert ClipperLib::IntPoint back to b2Vec2
    polygon.clear();
    for (const ClipperLib::IntPoint &p : path)
        polygon.push_back(b2Vec2(((double)p.X) / 1024.f, ((double)p.Y) / 1024.f));
}

NS_PIX2D_END
