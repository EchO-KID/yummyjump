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

#ifndef PIX2D_GLOBAL_H
#define PIX2D_GLOBAL_H

/////////////////// Namespace ///////////////////
#define NS_PIX2D_BEGIN                     namespace pix2d {
#define NS_PIX2D_END                       }
#define USING_NS_PIX2D                     using namespace pix2d

#if !defined(CXX_11) || __cplusplus < 201103
# define nullptr 0
# define override
# define constexpr
#endif // C++11

#define CREATE_FUNC_P1(__TYPE__,__NAME__, __P1__) \
static __TYPE__* __NAME__(__P1__ p1) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(p1)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define CREATE_FUNC_P2(__TYPE__, __NAME__, __P1__, __P2__) \
static __TYPE__* __NAME__(__P1__ p1, __P2__ p2) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(p1, p2)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define CREATE_FUNC_P3(__TYPE__, __NAME__, __P1__, __P2__, __P3__) \
static __TYPE__* __NAME__(__P1__ p1, __P2__ p2, __P3__ p3) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(p1, p2, p3)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define CREATE_FUNC_P4(__TYPE__, __NAME__, __P1__, __P2__, __P3__, __P4__) \
static __TYPE__* __NAME__(__P1__ p1, __P2__ p2, __P3__ p3, __P4__ p4) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(p1, p2, p3, p4)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#define CREATE_FUNC_P5(__TYPE__, __NAME__, __P1__, __P2__, __P3__, __P4__, __P5__) \
static __TYPE__* __NAME__(__P1__ p1, __P2__ p2, __P3__ p3, __P4__ p4, __P5__ p5) \
{ \
    __TYPE__ *pRet = new __TYPE__(); \
    if (pRet && pRet->init(p1, p2, p3, p4, p5)) { \
        pRet->autorelease(); \
        return pRet; \
    } else { \
        delete pRet; \
        pRet = NULL; \
        return NULL; \
    } \
}

#endif // PIX2D_GLOBAL_H
