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

#pragma once
#ifndef PIX2D_VISIBLERECT_H
#define PIX2D_VISIBLERECT_H

#include "forwards.h"

NS_PIX2D_BEGIN

class VisibleRect
{
public:
    static CCRect rect();
    static inline CCSize size() { return CCEGLView::sharedOpenGLView()->getVisibleSize(); }
    static inline CCSize sizeInPixel() { return CCDirector::sharedDirector()->getWinSizeInPixels(); }
    static inline CCPoint origin() { return CCEGLView::sharedOpenGLView()->getVisibleOrigin(); }

    /** @brief normalized size of the screen (e.g. sizeAt(0.5,0.5) will return half screen width and height) */
    static CCSize sizeAt(float s, float t);
    /** @brief Get point on the screen using normalized value. pointAt(0.5,0.5) will return the center of the screen. */
    static float pointAtY(float t);
    static float pointAtX(float s);
    /** Lua: returns two values */
    static void pointAt(float *s, float *y);
    static CCPoint pointAt(const CCPoint &p);

    static CCPoint left();
    static CCPoint right();
    static CCPoint top();
    static CCPoint bottom();
    static CCPoint center();
    static CCPoint leftTop();
    static CCPoint rightTop();
    static CCPoint leftBottom();
    static CCPoint rightBottom();
private:
    static void lazyInit();
    static CCRect s_visibleRect;
};

NS_PIX2D_END

#endif /* PIX2D_VISIBLERECT_H */
