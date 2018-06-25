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

#ifndef PIX2D_TEXTURE_H
#define PIX2D_TEXTURE_H

#include "forwards.h"
#include "body/base/physicnode.h"

NS_PIX2D_BEGIN

struct TextureDef : public PhysicNodeDef
{
    /**
     * @brief The shape points. The vector must contain at least 2 points. If only 2 points (upper-left and bottom-right) are provided
     * then a rectangle shaped body will be created. To construct a rotated square polygon just provide 2
     * points and then change the body's angle. More than 2 vertices polygons will be triangulated and
     * produce a body with more than one fixture.
     * @warning points must not repeat
     */
    std::vector<b2Vec2> vertices;   /// Polygon vertice in MAP INDICES
    std::string texture;            /// The texture filename
    bool simplify;                  /// Flag to call simplify before creating the polygon

    TextureDef()
    : simplify(false)
    {}
};

class Texture : public PhysicNode {
public:
    explicit Texture(int uid);
    virtual ~Texture();
    static Texture *create(TextureDef &def);
    virtual bool init(TextureDef &def);
    virtual void dump();

    /** @brief Add a new vertices to the existing one. Redundant points are not allowed! */
    void addVertices(std::vector<b2Vec2> vertices);

    static void simplifyPolygon(std::vector<b2Vec2> &polygon);

    TextureSprite *getTextureSprite() { return mTextureSprite; }

    /** Helper method to triangulate a polygon */
    static void triangulate(CCPointVector &in, CCPointVector &out);

protected:
    bool createAABBTexture(TextureDef &deg);
    bool createTriangulatedTexture(TextureDef &deg);
    void triangulate(const std::vector<b2Vec2> &vertices, CCPointVector &points);
    void aabb(const std::vector<b2Vec2> &vertices, CCPoint &upperbound, CCPoint &lowerbound);
    template <class T> static void freeContainer(T &cntr);
protected:
    TextureSprite *mTextureSprite;
    /// Since we can add fixture later we have to keep filter and fixture definition
    b2Filter mFilter;
    b2FixtureDef mFixtureDef;
};

NS_PIX2D_END
#endif // PIX2D_TEXTURE_H
