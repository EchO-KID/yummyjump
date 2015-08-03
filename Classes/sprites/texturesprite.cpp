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

#include "texturesprite.h"
#include "common/settings.h"
#include "common/visiblerect.h"

#include "poly2tri/poly2tri.h"
#include "clipper/clipper.hpp"

NS_PIX2D_BEGIN

TextureSprite::TextureSprite()
: mTime(CCPointZero)
, mTexture2D(nullptr)
{
    mColor = ccc4f(1.f, 1.f, 1.f, 1.f);
}

TextureSprite::~TextureSprite()
{
    CC_SAFE_RELEASE_NULL(mTexture2D);
}

/**
 * AABB: upperBound is top left corner. lowerBound is bottom right corner
 *
 *  v5.---.v4   .v2
 *    |  /     /|
 *    | /     / |
 *    |/     /  |
 *  v3.   v0.---.v1
 */

bool TextureSprite::init(std::string &texFileName, const CCPoint &upperBound, const CCPoint &lowerBound)
{
    CCPointVector vertices;

    vertices.push_back(ccp(upperBound.x,lowerBound.y)); /// v0
    vertices.push_back(lowerBound);                     /// v1
    vertices.push_back(ccp(lowerBound.x,upperBound.y)); /// v2

    vertices.push_back(ccp(upperBound.x,lowerBound.y)); /// v3
    vertices.push_back(ccp(lowerBound.x,upperBound.y)); /// v4
    vertices.push_back(upperBound);                     /// v5

    return TextureSprite::init(texFileName, vertices);
}

bool TextureSprite::init(std::string &texFileName, CCPointVector  &vertices)
{
    /// Load the texture from file
    if (texFileName.length() == 0) {
        CCLOGERROR("Invalid texture filename (empty string)");
        return false;
    }

    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(texFileName.c_str());
    if (!texture) {
        CCLOGERROR("ERROR: Can't load texture: '%s'", texFileName.c_str());
        return false;
    }
    setTexture(texture);
    /// Enable texture repeat. Horizontal and vertical repeat enabled by default.
    setRepeat(true, true);

    /// Create the shader program
    CCGLProgram *shader = CCShaderCache::sharedShaderCache()->programForKey(settings::kShader_PositionTexture_uColor_uTime);
    mColorLocation = glGetUniformLocation(shader->getProgram(), "u_color");
    mTimeLocation = glGetUniformLocation(shader->getProgram(), "u_time");

    setShaderProgram(shader);

    addPolygon(vertices);

    /* Seems that there's no need to call the init method again when the app is back to foreground (like CCDrawNode.cpp).
     * Only reload shaders is mandatory (see proj.android/jni/hellolua/main.cpp).
     */
    /*
#if CC_ENABLE_CACHE_TEXTURE_DATA > 0
     CCNotificationCenter::sharedNotificationCenter()->addObserver(this,
                                callfuncO_selector(TextureSprite::listenBackToForeground),
                                EVENT_COME_TO_FOREGROUND,
                                NULL);
#endif
     */

    return true;
}

void TextureSprite::setOpacity(GLubyte opacity)
{
    CCNodeRGBA::setOpacity(opacity);
    mColor = ccc4f(_displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f);
}

void TextureSprite::setColor(const ccColor3B& color)
{
    CCNodeRGBA::setColor(color);
    mColor = ccc4f(_displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f);
}

void TextureSprite::updateDisplayedColor(const ccColor3B& parentColor)
{
    CCNodeRGBA::updateDisplayedColor(parentColor);
    mColor = ccc4f(_displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f);
}

void TextureSprite::updateDisplayedOpacity(GLubyte parentOpacity)
{
    CCNodeRGBA::updateDisplayedOpacity(parentOpacity);
    mColor = ccc4f(_displayedColor.r/255.f, _displayedColor.g/255.f, _displayedColor.b/255.f, _displayedOpacity/255.f);
}

void TextureSprite::updateBlendFunc()
{
    m_sBlendFunc.src = CC_BLEND_SRC;
    m_sBlendFunc.dst = CC_BLEND_DST;
    setOpacityModifyRGB(true);
}

void TextureSprite::setTexture(CCTexture2D *texture)
{
    if (texture != mTexture2D) {
        CC_SAFE_RETAIN(texture);
        CC_SAFE_RELEASE(mTexture2D);
        mTexture2D = texture;
        /// Since we use multi-resolution we need to get the texture size in points (not pixels)
        /// mTexSize = mTexture2D->getContentSizeInPixels();
        mTexSize = mTexture2D->getContentSize();
        updateBlendFunc();
    }
}

void TextureSprite::setRepeat(bool horizontal, bool vertical)
{
    GLint repeatH = horizontal ? GL_REPEAT : GL_CLAMP_TO_EDGE; /// GL_CLAMP_TO_BORDER is not supported in OpenGL ES
    GLint repeatV = vertical ? GL_REPEAT : GL_CLAMP_TO_EDGE;
    ccTexParams params = { GL_LINEAR, GL_LINEAR, repeatH, repeatV };
    mTexture2D->setTexParameters(&params);
}

void TextureSprite::addAABBPolygon(const CCPoint& upperBound, const CCPoint& lowerBound)
{
    CCPointVector vertices;

    vertices.push_back(ccp(upperBound.x,lowerBound.y)); /// v0
    vertices.push_back(lowerBound);                     /// v1
    vertices.push_back(ccp(lowerBound.x,upperBound.y)); /// v2

    vertices.push_back(ccp(upperBound.x,lowerBound.y)); /// v3
    vertices.push_back(ccp(lowerBound.x,upperBound.y)); /// v4
    vertices.push_back(upperBound);                     /// v5

    addPolygon(vertices);
}

void TextureSprite::addPolygon(const CCPointVector &points)
{
    /// copy vertices positions and texture coordinates
    for (const CCPoint &p : points) {
        /// The vertices position in pixel
        mVertexPos.push_back(vertex3(p.x, p.y, .0f));   /// x y z
        /// The texture is loaded upside down by OpenGL. (1 - Y coord) will swap the texture Y coordinate.
        mTexCoords.push_back(tex2(p.x / mTexSize.width, 1 - (p.y / mTexSize.height)));
    }
}

void TextureSprite::translateTexCoord(float u, float v)
{
    /// scrolling implemented using shader (see http://stackoverflow.com/questions/10847985/glsl-shader-that-scroll-texture )
    mTime.x = u;
    mTime.y = v;
}

void TextureSprite::draw()
{
    if (!m_bVisible) return;

    CC_NODE_DRAW_SETUP();

    ccGLBlendFunc(m_sBlendFunc.src, m_sBlendFunc.dst);

    ccGLBindTexture2D(mTexture2D->getName());
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);

    /// Time offset
    getShaderProgram()->setUniformLocationWith2f(mTimeLocation, mTime.x, mTime.y);
    /// Color
    getShaderProgram()->setUniformLocationWith4f(mColorLocation, mColor.r, mColor.g, mColor.b, mColor.a);
    /// Vertex
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, sizeof(ccVertex3F), (void*)&mVertexPos[0]);
    /// Texture coord.
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(ccTex2F), (void*)&mTexCoords[0]);
    /// Available mode: GL_TRIANGLES, GL_TRIANGLES_STRIP and GL_TRIANGLE_FAN
    glDrawArrays(GL_TRIANGLES, 0, mVertexPos.size());

    /// Do NOT call glFlush or performance will decrease drastically!
    /// glFlush();

    CHECK_GL_ERROR_DEBUG();

    CC_INCREMENT_GL_DRAWS(1);
}

NS_PIX2D_END
