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

#ifndef PIX2D_EFFECTLAYER_H
#define PIX2D_EFFECTLAYER_H

#include "forwards.h"

NS_PIX2D_BEGIN

/**
 @brief Provide real-time and static post-processing.
 See. http://en.wikibooks.org/wiki/OpenGL_Programming/Post-Processing and http://open.gl/framebuffers

 Real-time post-processing:
 1. Create one of PostProcessing sub-class (e.g. Pixelation, FastBlur...) providing a target node and size.
 2. Retain the object
 3. Schedule the PostProcessing::refresh to refresh the buffer (e.g. call it in CCNode::update).
 4. Call getFrameBuffer and add the CCRenderTexture to the scene to draw the effect
 5. Release the object once not needed

 Static post-processing:
 1. Create the Pixelation, FastBlur object
 2. Call `capture` and add the CCRenderTexture to the scene

 @note To apply an effect to the whole scene just pass CCDirector::getRunningScene() and the screen size
 to the `create` methode.

 @bug Real-time FastBlur seems unstable (tested in Lua)

 @todo Investigate performance improvement by downsample the framebuffer (Downsample the image by x4, apply the filter and upsampled afterward).
 */
class PostProcessing : public CCObject {
protected:
    PostProcessing();
    virtual ~PostProcessing();
    CREATE_FUNC_P2(PostProcessing, create, CCNode *, const CCSize &);
public:
    virtual CCRenderTexture *capture();
    virtual CCRenderTexture *getFrameBuffer() { return mFBO; }
    virtual void refresh(bool clean);
    /// Clear the buffer with color
    void clear(const ccColor4F &color) { mFBO->clear(color.r, color.g, color.b, color.a); }
protected:
    /// init method
    virtual bool init(CCNode *node, const CCSize &size);
    /// Create a FBO
    CCRenderTexture *createFrameBuffer(const CCSize &size);
    /// shaders factory
    /// For some reason we can't get the shader from the cache and set the uniforms.
    /// So we have to create the shaders on the fly.
    CCGLProgram *createShader(const std::string &vertexShader,const std::string &fragmentShader);
protected:
    CCSize mFBOSize;
    CCNode *mTargetNode;
    CCRenderTexture *mFBO;
};

////////////////////// Double Buffer PostProcessing /////////////////////////

/** Post-processing requiring two Frame Buffer (e.g. vertical and horizontal blur) */
class DoublePostProcessing : public PostProcessing {
protected:
    DoublePostProcessing();
    ~DoublePostProcessing();
public:
    virtual CCRenderTexture *capture();
    virtual void refresh(bool clean);
    virtual CCRenderTexture *getFrameBuffer() { return mBuffer->getFrameBuffer(); }
protected:
    bool init(CCNode *node, const CCSize &size);
protected:
    PostProcessing *mBuffer;
};

////////////////////// PIXELATION /////////////////////////
class Pixelation : public PostProcessing {
protected:
    Pixelation() : PostProcessing() {}
    virtual ~Pixelation() {}
    CCGLProgram *getPixelationShader(const CCSize &size);
public:
    CREATE_FUNC_P4(Pixelation, create, CCNode *, const CCSize &, float, float);
    bool init(CCNode *node, const CCSize &size, float width, float height);
};

////////////////////// GRAYSCALE /////////////////////////
class Grayscale : public PostProcessing {
protected:
    Grayscale() : PostProcessing() {}
    virtual ~Grayscale() {}
public:
    CREATE_FUNC_P2(Grayscale, create, CCNode *, const CCSize &);
    bool init(CCNode *node, const CCSize &size);
};

////////////////////// FAST BLUR //////////////////////
/// two-pass optmimized Blur. Faster than gaussian blur and but less quality.
/// http://www.sunsetlakesoftware.com/2013/10/21/optimizing-gaussian-blurs-mobile-gpu
class FastBlur : public DoublePostProcessing {
protected:
    FastBlur() : DoublePostProcessing() {}
    virtual ~FastBlur() {}
    /// Create either a horizontal (xStep > 0 && yStep == 0) or vertical (xStep == 0 && yStep > 0) Fast Blur shader.
    CCGLProgram *getFastBlurShader(const float xStep, const float yStep);
public:
    CREATE_FUNC_P3(FastBlur, create, CCNode *, const CCSize &, float);
    bool init(CCNode *node, const CCSize & size, float radius);
};

////////////////////// GAUSSIAN BLUR //////////////////////
/// Two-passes Gaussian Blur. See https://github.com/mattdesl/lwjgl-basics/wiki/ShaderLesson5
class GaussianBlur : public DoublePostProcessing {
protected:
    GaussianBlur() : DoublePostProcessing() {}
    virtual ~GaussianBlur() {}
    /// Create either a horizontal (xStep > 0 && yStep == 0) or vertical (xStep == 0 && yStep > 0) Fast Blur shader.
    CCGLProgram *getGaussianBlurShader(const float xStep, const float yStep);
public:
    CREATE_FUNC_P3(GaussianBlur, create, CCNode *, const CCSize &, float);
    bool init(CCNode *node, const CCSize & size, float radius);
};

NS_PIX2D_END
#endif // PIX2D_EFFECTLAYER_H
