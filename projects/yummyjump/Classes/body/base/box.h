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

#ifndef PIX2D_BOX_H
#define PIX2D_BOX_H

#include "forwards.h"
#include "tolua++.h"
#include "CCLuaValue.h"
#include "body/base/physicnode.h"

NS_PIX2D_BEGIN

struct BoxDef : public PhysicNodeDef
{
    b2Vec2 size; /// Box size map unit
    b2Vec2 center; /// Local center of the box in map unit

    BoxDef()
    : size(1.f,1.f)
    , center(.0f,.0f)
    {}
};

/** @brief A physic node with a simple Box shape */
class Box : public PhysicNode {
public:
    explicit Box(int uid);
    explicit Box(const BoxDef &def);
    virtual ~Box();
    static Box *create(const BoxDef &def);

    /**
     * @brief Create a box from a Lua table
     * @param the Lua table (aka int in C)
     */
    /// static Box *create(lua_Object lo);

    virtual bool init(const BoxDef &def);

    virtual void drawDebugShape(const ccColor4F &color);

    b2PolygonShape *getBoxShape() { return static_cast<b2PolygonShape *>(mBody->GetFixtureList()->GetShape()); }
};

NS_PIX2D_END
#endif // PIX2D_BOX_H
