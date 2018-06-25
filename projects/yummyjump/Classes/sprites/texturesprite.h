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

#ifndef PIX2D_TEXTURESPRITE_H
#define PIX2D_TEXTURESPRITE_H

#include "forwards.h"

NS_PIX2D_BEGIN

/**
 * @brief The texture use a custom shader to scroll/translate the texture but the scrolling does not work when color uniform is used (see shader). Update: Is this still true? To be investigated.
 */

class TextureSprite : public CCNodeRGBA, public CCTextureProtocol {
public:
    explicit TextureSprite();
    virtual ~TextureSprite();

    /**
     * @brief Create a texture polygon.
     * @param p1 texture filename
     * @param p2 polygon vertices. There must be at least 3 point (triangle). Shape should be triangulated before calling this (see Texture::triangulate)
     * @warning the vertices vector must not contain duplicated points
     */
    CREATE_FUNC_P2(TextureSprite, create, std::string &, CCPointVector &);

    /**
     * @brief Create a squared texture sprite
     * @param p1 texture filename
     * @param p2 upper bound (top left corner)
     * @param p3 lower bound (bottom right corner)
     */
    CREATE_FUNC_P3(TextureSprite, createWithAABB, std::string &, const CCPoint &, const CCPoint &);

    bool init(std::string &texFileName, CCPointVector &vertices);
    bool init(std::string &texFileName, const CCPoint &upperBound, const CCPoint &lowerBound);

    /// implement CCTextureProtocol
    virtual void setBlendFunc(ccBlendFunc blendFunc) { m_sBlendFunc = blendFunc; }
    virtual ccBlendFunc getBlendFunc(void) { return m_sBlendFunc; }
    virtual CCTexture2D* getTexture(void) { return mTexture2D; }
    virtual void setTexture(CCTexture2D *texture);

    /// Overide functions inherited from CCNodeRGBA
    virtual void setOpacity(GLubyte opacity);
    virtual void setColor(const ccColor3B& color);
    virtual void updateDisplayedColor(const ccColor3B& parentColor);
    virtual void updateDisplayedOpacity(GLubyte parentOpacity);

    void updateBlendFunc();

    /// GL_CLAMP_TO_BORDER not supported in OpenGL ES therefore  this is not really relevant
    void setRepeat(bool horizontal, bool vertical);

    virtual void draw();

    /** @brief Translate the texture coordinate. Can be used for a scrolling effect */
    void translateTexCoord(float u, float v);

    void addAABBPolygon(const CCPoint& p1, const CCPoint& p2);
    void addPolygon(const CCPointVector &points);

    CCSize getTextureSize() const { return mTexSize; }

protected:
    CCVertexVector mVertexPos;
    CCTexCoordVector mTexCoords;
    // GLint mColorLocation;
    CCTexture2D *mTexture2D;
    CCSize mTexSize;
    ccBlendFunc m_sBlendFunc;

    /// Uniforms
    CCPoint mTime;
    ccColor4F mColor;

    /// Uniforms location
    GLint mColorLocation;
    GLint mTimeLocation;
};

NS_PIX2D_END
#endif // PIX2D_SpriteTexture_H
