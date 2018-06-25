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

#include "geom.h"

NS_PIX2D_BEGIN

inline Coord BezierCurve::valueAt(Dim2 c, double t) const {
    int n = order();
    double u, bc, tn, tmp;
    int i;
    u = 1.0 - t;
    bc = 1;
    tn = 1;
    tmp = (c == X ? mPoints[0].x : mPoints[0].y) * u;
    for(i=1; i<n; i++){
        tn = tn*t;
        bc = bc*(n-i+1)/i;
        tmp = (tmp + tn * bc * (c == X ? mPoints[i].x : mPoints[i].y)) * u;
    }
    return (tmp + tn * t * (c == X ? mPoints[n].x : mPoints[n].y));
}

CCPoint BezierCurve::pointAt(double t) const
{
    return CCPoint(valueAt(X, t), valueAt(Y, t));
}

CCPoint BezierPath::pointAt(double t) const
{
    unsigned int sz = size();
    if ( closed() ) ++sz;
    CCAssert(!(t < 0 || t > sz),"parameter t out of bounds");
    if ( empty() ) return initialPoint(); // naked moveto
    double k, lt = modf(t, &k);
    unsigned int i = static_cast<unsigned int>(k);
    if ( i == sz )
    {
        --i;
        lt = 1;
    }
    return (*this)[i].pointAt(lt);
}

NS_PIX2D_END
