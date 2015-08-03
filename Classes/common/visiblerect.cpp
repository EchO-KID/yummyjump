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

#include "common/visiblerect.h"

NS_PIX2D_BEGIN

CCRect VisibleRect::s_visibleRect;

void VisibleRect::lazyInit()
{
    if (s_visibleRect.size.width == 0.0f && s_visibleRect.size.height == 0.0f)
    {
        CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();
        s_visibleRect.origin = pEGLView->getVisibleOrigin();
        s_visibleRect.size = pEGLView->getVisibleSize();
    }
}

CCRect VisibleRect::rect()
{
    lazyInit();
    return CCRectMake(s_visibleRect.origin.x, s_visibleRect.origin.y, s_visibleRect.size.width, s_visibleRect.size.height);
}

float VisibleRect::pointAtY(float t)
{
    return VisibleRect::pointAt(ccp(0,t)).y;
}

float VisibleRect::pointAtX(float s)
{
    return VisibleRect::pointAt(ccp(s,0)).x;
}

void VisibleRect::pointAt(float *s, float *y)
{
    CCPoint p = VisibleRect::pointAt(ccp(*s,*y));
    *s = p.x;
    *y = p.y;
}

CCPoint VisibleRect::pointAt(const CCPoint &p)
{
    lazyInit();
    return s_visibleRect.origin + ccp(s_visibleRect.size.width * p.x, s_visibleRect.size.height * p.y);
}

CCSize VisibleRect::sizeAt(float s, float t)
{
    lazyInit();
    return CCSizeMake(s_visibleRect.size.width * s, s_visibleRect.size.height * t);
}


CCPoint VisibleRect::left()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y + s_visibleRect.size.height / 2);
}

CCPoint VisibleRect::right()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint VisibleRect::top()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::bottom()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y);
}

CCPoint VisibleRect::center()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width/2, s_visibleRect.origin.y+s_visibleRect.size.height/2);
}

CCPoint VisibleRect::leftTop()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::rightTop()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y+s_visibleRect.size.height);
}

CCPoint VisibleRect::leftBottom()
{
    lazyInit();
    return s_visibleRect.origin;
}

CCPoint VisibleRect::rightBottom()
{
    lazyInit();
    return ccp(s_visibleRect.origin.x+s_visibleRect.size.width, s_visibleRect.origin.y);
}

NS_PIX2D_END
