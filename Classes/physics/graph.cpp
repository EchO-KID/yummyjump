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

#include "graph.h"

NS_PIX2D_BEGIN

Graph::Graph(unsigned int width, unsigned int height)
: sx(width)
, sy(height)
, mMap(sx * sy)
{
    mPather = new micropather::MicroPather(this);
}

Graph::~Graph()
{
    delete mPather;
}

void Graph::update(uint32_t i, uint32_t j,const NodeType type)
{
    MapNodeInfo info;
    info.type = type;
    int index = j * sx + i;
    mMap[index] = info;
}

int Graph::solve(const b2Vec2 &s, const b2Vec2 &d, std::vector<b2Vec2> &outputPath)
{
    float totalCost = 0;

    int start = (long int)coordToNode(s.x, s.y);
    int end = (long int)coordToNode(d.x, d.y);

    if (! (start > -1  && start < mMap.size()) ) {
        CCLOGERROR("start position must be between 0 and %lu but is %d", mMap.size(), start);
        return -1;
    } else if (! (end > -1 && end < mMap.size()) ) {
        CCLOGERROR("end position must be between 0 and %lu but is %d", mMap.size(), end);
        return -1;
    }

    CCLOG("try to solve from %d (%.2fx%.2f) to %d (%.2fx%.2f)", start, s.x, s.y, end, d.x, d.y);

    int result = mPather->Solve((void*)start, (void*)end, &mPath, &totalCost);

    switch (result) {
        case micropather::MicroPather::SOLVED:
            CCLOG("Path has been solved (SOLVED).");
            {
                uint32_t i, j;
                int pathSize = mPath.size();
                for(int k = 0; k < pathSize; ++k) {
                    nodeToCoord(mPath[k], &i, &j);
                    outputPath.push_back(b2Vec2(i, j));
                }
            }
            return kSolved;
            break;
        case micropather::MicroPather::NO_SOLUTION:
            CCLOG("Cannot resolve the path (NO_SOLUTION)");
            return kNoSolution;
        case micropather::MicroPather::START_END_SAME:
            CCLOG("Start and end position are the same (START_END_SAME).");
            return kStartEndSame;
        default:
            CCAssert(false, "Unknown solve result");
    }
}

float Graph::LeastCostEstimate(void* nodeStart, void* nodeEnd)
{
    uint32_t xStart, yStart, xEnd, yEnd;
    nodeToCoord(nodeStart, &xStart, &yStart);
    nodeToCoord(nodeEnd, &xEnd, &yEnd);

    int dx = xStart - xEnd;
    int dy = yStart - yEnd;
    return (float) sqrt((double)(dx*dx) + (double)(dy*dy));
}

void Graph::AdjacentCost(void* node, MP_VECTOR< micropather::StateCost > *neighbors)
{
    uint32_t i, j;
    nodeToCoord(node, &i, &j);

    const int cost[8] = { 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f, 1.0f, 1.41f };
    const int dx[8] = { 1, 1, 0, -1, -1, -1, 0, 1 };
    const int dy[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };

    for( int d=0; d<8; ++d ) {
        int nx = i + dx[d];
        int ny = j + dy[d];

        if (passable(nx, ny)) {
            micropather::StateCost nodeCost = { coordToNode(nx, ny), cost[d] };
            neighbors->push_back( nodeCost );
        }
/*** @todo investigate infinite cost
        else {
            micropather::StateCost nodeCost = { coordToNode(nx, ny), FLT_MAX };
            neighbors->push_back(nodeCost);
        }
*/
    }
}

void Graph::dump()
{
    printf("Graph map [%dx%d]\n", sx, sy);
    /// Start to print from the last row
    for (int j = sy-1; j >= 0; --j) {
        printf("[");
        for (int i = 0; i < sx; ++i) {
            int index = j * sx + i;
            std::cout << (char)mMap[index].type;
        }
        printf("]\n");
    }
}

void Graph::PrintStateInfo(void* state)
{
    uint32_t x, y;
    nodeToCoord(state, &x, &y);
    printf("state (%lu): %dx%d\n", (long int)state, x, y);
}

void Graph::nodeToCoord(void *node, uint32_t *i, uint32_t *j) const
{
    int index = (long int)node;
    *j = index / sx;
    *i = index - (*j) * sx;
}

void* Graph::coordToNode(uint32_t i, uint32_t j) const
{
    return (void*) (j * sx + i);
}

bool Graph::passable(uint32_t i, uint32_t j) const
{
    if (i < sx && j < sy) {
        int index = j * sx + i;
        //CCLOG("%dx%d (%d) %c", i, j, index, (char)mMap[index].type);
        switch (mMap[index].type) {
            case kEmpty:
                return true;
            default:
                return false;
        }
    }
    //CCLOG("Out of map (%dx%d)", i, j);
    return false;
}


NS_PIX2D_END
