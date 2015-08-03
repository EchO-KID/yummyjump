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
/// Inspired by lib2geom

#ifndef PIX2D_GEOM_H
#define PIX2D_GEOM_H

#include "forwards.h"

NS_PIX2D_BEGIN

/// DEPRECATED Now use Lua path2D library

/** @brief 2D axis enumeration (X or Y). */
enum Dim2 { X=0, Y=1 };
typedef double Coord;

class BezierCurve {
public:
    BezierCurve(unsigned int order)
    : mPoints(order+1)
    , mOrder(order)
    {}

    CCPoint pointAt(double t) const;
    const CCPoint &point(unsigned int i) const { return mPoints[i]; }
    unsigned order() const { return mOrder; }

    CCPoint initialPoint() const { return mPoints.front(); }
    CCPoint finalPoint() const { return mPoints.back(); }

    std::vector<Coord> valueAndDerivatives(Coord t, unsigned n_derivs) const;

    inline Coord valueAt(Dim2 c, double t) const;
protected:
    std::vector<CCPoint> mPoints;
    unsigned int mOrder;
};

/// @brief Construct an order-1 bezier (linear Bézier)
class LineBezier  : public BezierCurve {
public:
    LineBezier(CCPoint c0, CCPoint c1)
    : BezierCurve(1) {
        mPoints[0] = c0;
        mPoints[1] = c1;
    }
};

/// @brief Construct an order-2 bezier (quadratic Bézier)
class QuadBezier  : public BezierCurve {
public:
    QuadBezier(CCPoint c0, CCPoint c1, CCPoint c2)
    : BezierCurve(2) {
        mPoints[0] = c0;
        mPoints[1] = c1;
        mPoints[2] = c2;
    }
};

/// @brief Construct an order-3 bezier (cubic Bézier)
class CubicBezier : public BezierCurve {
public:
    CubicBezier(CCPoint c0, CCPoint c1, CCPoint c2, CCPoint c3)
    : BezierCurve(3) {
        mPoints[0] = c0;
        mPoints[1] = c1;
        mPoints[2] = c2;
        mPoints[3] = c3;
    }
};

/// @brief Series of continuous bezier curves
class BezierPath : public std::vector<BezierCurve> {
public:
    BezierPath()
    : mClosed(true)
    {}
    void close(bool value = true) { mClosed = value; }
    bool closed() const { return mClosed; }
    bool empty() const { return (size() == 0); }
    CCPoint initialPoint() const { return front().initialPoint(); }
    CCPoint finalPoint() const { return back().finalPoint(); }
    /// @brief return the point at time `t`. Time must range between 0 and path' size.
    /// For instance, iterating with t[0.0,1.0] will get points on the first curve of the path.
    /// If the path has 3 curves then t[0.0,3.0] will get points from all the 3 curves
    CCPoint pointAt(double t) const;
protected:
    bool mClosed;
};

NS_PIX2D_END
#endif // PIX2D_GEOM_H
