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

#include "nodes/postprocessing.h"
#include "common/visiblerect.h"
#include "common/settings.h"

NS_PIX2D_BEGIN

///////////////////////// PostProcessing /////////////////////////

PostProcessing::PostProcessing()
: mFBO(nullptr)
, mTargetNode(nullptr)
{}

PostProcessing::~PostProcessing()
{
    /// CCLOG("Dealloc PostProcessing...");
    CC_SAFE_RELEASE(mFBO);
    CC_SAFE_RELEASE(mTargetNode);
}

CCRenderTexture *PostProcessing::createFrameBuffer(const CCSize &size)
{
    if (CCRenderTexture *render = CCRenderTexture::create(size.width, size.height,kCCTexture2DPixelFormat_RGBA8888)) {
        render->setPosition(VisibleRect::center());
        render->getSprite()->getTexture()->setAntiAliasTexParameters();
        render->retain();
        return render;
    }
    return nullptr;
}

bool PostProcessing::init(CCNode *node, const CCSize &size)
{
    CCAssert(node, "Node can't be nil");
    mFBOSize = size;
    (mTargetNode = node)->retain();
    return node != nullptr && (mFBO = createFrameBuffer(size))  != nullptr;
}

CCGLProgram *PostProcessing::createShader(const std::string &vertexShader,const std::string &fragmentShader)
{
    CCGLProgram *shader = new CCGLProgram();
    shader->autorelease();
    shader->initWithVertexShaderFilename(vertexShader.c_str(), fragmentShader.c_str());
    shader->addAttribute(kCCAttributeNamePosition, kCCVertexAttrib_Position);
    shader->addAttribute(kCCAttributeNameColor, kCCVertexAttrib_Color);
    shader->addAttribute(kCCAttributeNameTexCoord, kCCVertexAttrib_TexCoords);
    shader->link();
    shader->updateUniforms();
    return shader;
}

void PostProcessing::refresh(bool clean)
{
    clean ? mFBO->beginWithClear(0.f, 0.f, 0.f, 0.f) : mFBO->begin();
    mTargetNode->visit();
    mFBO->end();
}

CCRenderTexture *PostProcessing::capture()
{
    PostProcessing *buffer = PostProcessing::create(mFBO, mFBOSize);
    if (!buffer) {
        CCLOGERROR("Can't allocate the Frame Buffer");
        return mFBO;
    }
    buffer->retain();
    /// Capture the node
    refresh(false);
    /// Render to the Frame buffer
    buffer->refresh(false);
    buffer->release();
    /// Return the effect filter result
    return buffer->getFrameBuffer();
}

////////////////////// Double Buffer PostProcessing /////////////////////////
DoublePostProcessing::DoublePostProcessing()
: PostProcessing()
, mBuffer(nullptr)
{}

DoublePostProcessing::~DoublePostProcessing()
{
    CC_SAFE_RELEASE(mBuffer);
}

bool DoublePostProcessing::init(CCNode *node, const CCSize &size)
{
    if (!PostProcessing::init(node, size)) return false;
    mBuffer = PostProcessing::create(mFBO, mFBOSize);
    CC_SAFE_RETAIN(mBuffer);
    return (mBuffer != nullptr);
}

CCRenderTexture *DoublePostProcessing::capture()
{
    /// Capture the node
    /*
    float scale = mTargetNode->getScale();
    mTargetNode->setScale(scale / 2.0);
    */
    mFBO->begin();
    mTargetNode->visit();
    mFBO->end();
    ///mTargetNode->setScale(scale);

    /// Apply the first shader
    mBuffer->getFrameBuffer()->begin();
    mFBO->visit();
    mBuffer->getFrameBuffer()->end();

    /// Apply the second shader
    mFBO->begin(); // Should clean the buffer ? TODO
    mBuffer->getFrameBuffer()->visit();
    mFBO->end();
    //mFBO->setScale(2.0);

    /// Reset the default shader
    mFBO->getSprite()->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
    return mFBO;
}

void DoublePostProcessing::refresh(bool clean)
{
    /// Capture the target node
    PostProcessing::refresh(clean);
    /// Apply the first shader
    mBuffer->refresh(clean);
    /// Second shader will be applied when the FBO will be actually drawn
}

////////////////////// PIXELATION /////////////////////////
bool Pixelation::init(CCNode *node, const CCSize &size, float width, float height)
{
    if (!PostProcessing::init(node,size)) return  false;
    mFBO->getSprite()->setShaderProgram(getPixelationShader(CCSizeMake(width, height)));
    return true;
}

CCGLProgram *Pixelation::getPixelationShader(const CCSize &size)
{
    CCGLProgram *shader = createShader("shaders/shader_Pixelation.vsh", "shaders/shader_Pixelation.fsh");

    GLuint pixel_w_loc = glGetUniformLocation(shader->getProgram(), "pixel_w");
    shader->setUniformLocationWith1f(pixel_w_loc, size.width);

    GLuint pixel_h_loc = glGetUniformLocation(shader->getProgram(), "pixel_h");
    shader->setUniformLocationWith1f(pixel_h_loc, size.height);

    GLuint rt_w_loc = glGetUniformLocation(shader->getProgram(), "rt_w");
    shader->setUniformLocationWith1f(rt_w_loc, mFBOSize.width);

    GLuint rt_h_loc = glGetUniformLocation(shader->getProgram(), "rt_h");
    shader->setUniformLocationWith1f(rt_h_loc, mFBOSize.width);

    return shader;
}

////////////////////// GRAYSCALE /////////////////////////
bool Grayscale::init(CCNode *node, const CCSize &size)
{
    if (!PostProcessing::init(node,size)) return  false;
    mFBO->getSprite()->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(settings::kShader_Grayscale));
    return true;
}

////////////////////// FAST BLUR //////////////////////
bool FastBlur::init(CCNode *node, const CCSize &size, float radius)
{
    /// CCSize downScaled = size / 2.0;
    if (!DoublePostProcessing::init(node,size)) return false;

    /// Need real pixel size
    /// CCSize sizeInPixel = size * CC_CONTENT_SCALE_FACTOR();
    CCSize sizeInPixel = size;
    sizeInPixel.width *= CCDirector::sharedDirector()->getOpenGLView()->getScaleX();
    sizeInPixel.height *= CCDirector::sharedDirector()->getOpenGLView()->getScaleY();

    /// Horizontal Blur
    mFBO->getSprite()->setShaderProgram(getFastBlurShader(radius / sizeInPixel.width, .0f));
    /// Vertical Blur
    mBuffer->getFrameBuffer()->getSprite()->setShaderProgram(getFastBlurShader(.0f, radius / sizeInPixel.height));
    return true;
}

CCGLProgram* FastBlur::getFastBlurShader(const float xStep, const float yStep)
{
    /// CCGLProgram* shader = CCShaderCache::sharedShaderCache()->programForKey(settings::kShader_FastBlur);
    CCGLProgram *shader = createShader("shaders/shader_FastBlur.vsh", "shaders/shader_FastBlur.fsh");

    GLuint xStepLoc = glGetUniformLocation(shader->getProgram(), "xStep");
    shader->setUniformLocationWith1f(xStepLoc, xStep);

    GLuint yStepLoc = glGetUniformLocation(shader->getProgram(), "yStep");
    shader->setUniformLocationWith1f(yStepLoc, yStep);

    return shader;
}

////////////////////// GAUSSIAN BLUR //////////////////////
CCGLProgram *GaussianBlur::getGaussianBlurShader(const float xStep, const float yStep)
{
    CCGLProgram *shader = createShader("shaders/shader_GaussianBlur.vsh", "shaders/shader_GaussianBlur.fsh");

    GLuint xStepLoc = glGetUniformLocation(shader->getProgram(), "xStep");
    shader->setUniformLocationWith1f(xStepLoc, xStep);

    GLuint yStepLoc = glGetUniformLocation(shader->getProgram(), "yStep");
    shader->setUniformLocationWith1f(yStepLoc, yStep);

    return shader;
}

bool GaussianBlur::init(CCNode *node, const CCSize &size, float radius)
{
    /// CCSize downScaled = size / 2.0;
    if (!DoublePostProcessing::init(node,size)) return false;

    CCSize sizeInPixel = size;
    sizeInPixel.width *= CCDirector::sharedDirector()->getOpenGLView()->getScaleX();
    sizeInPixel.height *= CCDirector::sharedDirector()->getOpenGLView()->getScaleY();

    /// Horizontal Blur
    mFBO->getSprite()->setShaderProgram(getGaussianBlurShader(radius / sizeInPixel.width, .0f));
    /// Vertical Blur
    mBuffer->getFrameBuffer()->getSprite()->setShaderProgram(getGaussianBlurShader(.0f, radius / sizeInPixel.height));
    return true;
}

NS_PIX2D_END
