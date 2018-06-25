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
 
#ifndef PIX2D_GRAPH_H
#define PIX2D_GRAPH_H

#include "forwards.h"
#include <micropather/micropather.h>

NS_PIX2D_BEGIN

class Graph : public micropather::Graph {
public:

    enum NodeType {
        kUnknown        = 0,
        kEmpty          = (int)'.',
        // kHero           = (int)'1',
        // kGoal           = (int)'X',
        kSolidGround    = (int)'#',
        //kCoin           = (int)'*',
        //kRope           = (int)'@',
    };

    enum ResultCode {
        kSolved,
        kNoSolution,
        kStartEndSame,
    };

    struct MapNodeInfo {
        NodeType type;
        /// Constructor
        MapNodeInfo()
        : type(kEmpty)
        {}
    };

    explicit Graph(unsigned int width, unsigned int height);
    virtual ~Graph();

    void update(uint32_t i, uint32_t j, const NodeType type);

    /** @brief solve a path from the source 's' to the destination 'd'. Push the path result in outputPath. Return either kSolved,KNoSolution or kStartEndSame */
    int solve(const b2Vec2 &s, const b2Vec2 &d, std::vector<b2Vec2> &outputPath);

    /// implement micropather::Graph
    virtual float LeastCostEstimate(void* nodeStart, void* nodeEnd);
    virtual void AdjacentCost(void* state, MP_VECTOR< micropather::StateCost > *neighbors);
    virtual void PrintStateInfo(void* state);

    CCSize getSize() const { return CCSizeMake(sx,sy); }
    /// Lua optimized getSize()
    void getSize(float *width,float *height) const { *width = sx; *height = sy; }

    /** @brief node to coordinate convertion */
    void nodeToCoord(void *node, uint32_t *i, uint32_t *j) const;
    /** @brief coordinate to node convertion */
    void* coordToNode(uint32_t i, uint32_t j) const;
    /** @brief check if the map is "passable" at the coordinate i and j */
    bool passable(uint32_t i, uint32_t j) const;
    /** @brief print the map status */
    void dump();

private:
    /// map size MUST be declared before the map vector
    unsigned int sx;    /// Map width
    unsigned int sy;    /// Map height
    std::vector<MapNodeInfo> mMap;

    micropather::MicroPather* mPather;
    micropather::MPVector<void* > mPath;
};

NS_PIX2D_END
#endif // PIX2D_GRAPH_H
