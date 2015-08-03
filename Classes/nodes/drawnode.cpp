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

#include "nodes/drawnode.h"

NS_PIX2D_BEGIN

void DrawNode::drawPolygon(std::vector<CCPoint> &points, const ccColor4F &fillColor, float borderWidth, const ccColor4F &borderColor)
{
    CCDrawNode::drawPolygon(&points[0], points.size(), fillColor, borderWidth, borderColor);
}

void DrawNode::drawCircle(const CCPoint &center, float radius, float precision, float borderWidth, const ccColor4F &fillColor, const ccColor4F &pathColor)
{
    std::vector<CCPoint> vertex;
    double cir = 2 * M_PI; /// circle circumference
    for (float a = .0f; a < cir; a += precision) {
        float x = center.x + radius * cos(a);
        float y = center.y + radius * sin(a);
        vertex.push_back(ccp(x,y));
    }
    CCDrawNode::drawPolygon(&vertex[0], vertex.size(), fillColor, borderWidth, pathColor);
}

NS_PIX2D_END
