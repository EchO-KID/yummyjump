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

#ifndef PIX2D_IRISWIPE_H
#define PIX2D_IRISWIPE_H

#include "forwards.h"

NS_PIX2D_BEGIN

/**
 @brief Iris wipe transition implemented using a cliping node. It can be used in
 as a closing or opening transition.
 @warning in order to get CCClippingNode to work opengl stencil must be enabled.
 iOS: edit AppController.mm and set depthFormat to GL_DEPTH24_STENCIL8_OES (default is GL_DEPTH_COMPONENT16)
 Android: edit src/com/voodoocactus/games/gameplay.java and set the view config as follow: glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
 */
class IrisWipe : public CCClippingNode
{
public:
    IrisWipe();
    virtual ~IrisWipe();
    /// End position, opening/closing mode, color, start/end clipping radius
    static IrisWipe *create(float x, float y, bool opening, ccColor4F &color,float start,float end,float duration);
    static IrisWipe *create(const CCPoint &center, bool opening, ccColor4F &color,float start,float end,float duration);
    bool init(const CCPoint &center, bool opening, ccColor4F &color,float start,float end,float duration);

    /** Lua script callback that will be called when the iris wipe transition is done */
    bool registerCallbackHandler(int handler);
    void unregisterCallbackHandler();
protected:
    /// @brief call when the iris wipe effect did finish
    void callback();
protected:
    int mHandler;
};

NS_PIX2D_END

#endif /* PIX2D_IRISWIPE_H */
