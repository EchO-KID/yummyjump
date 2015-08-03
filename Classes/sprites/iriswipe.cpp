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

#include "sprites/iriswipe.h"
#include "common/visiblerect.h"
#include "bindings/luahelper.h"

NS_PIX2D_BEGIN

IrisWipe::IrisWipe()
: CCClippingNode()
, mHandler(-1)
{}

IrisWipe::~IrisWipe()
{
    unregisterCallbackHandler();
}

IrisWipe *IrisWipe::create(float x, float y, bool opening, ccColor4F &color, float start, float end,float duration)
{
    return IrisWipe::create(ccp(x,y), opening, color, start , end, duration);
}

IrisWipe *IrisWipe::create(const CCPoint &center, bool opening, ccColor4F &color, float start, float end,float duration)
{
    IrisWipe *pRet = new IrisWipe();
    if (pRet and pRet->init(center, opening, color, start, end,duration)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool IrisWipe::init(const CCPoint &p, bool opening, ccColor4F &color, float start, float end,float duration)
{
    CCPoint origin = p;
    CCPoint dest = VisibleRect::center();
    float fadeTo = 0;

    if (opening == false) { /// Closing mode
        origin = VisibleRect::center();
        dest = p;
        fadeTo = 255;
    }

    std::vector<CCPoint> vertices;
    float precision = .2f;
    double cir = 2 * M_PI; /// circle circumference
    for (float a = .0f; a < cir; a += precision) {
        float x = start * cos(a);
        float y = start * sin(a);
        vertices.push_back(ccp(x,y));
    }
    /// Create the clipping stencil
    CCDrawNode *stencil = CCDrawNode::create();
    stencil->drawPolygon(&vertices[0], vertices.size(), color, 0, color);
    stencil->setAnchorPoint(ccp(.5f,.5f));
    stencil->setPosition(origin);
    CCClippingNode::init(stencil);

    /// Run opening/closing actions
    stencil->runAction(CCSequence::createWithTwoActions(
                        CCScaleTo::create(duration,end),
                        CCCallFunc::create(this, callfunc_selector(IrisWipe::callback))));
    stencil->runAction(CCMoveTo::create(duration,dest));

    /// Add a black layer over the whole screen
    /// CCLayerColor *layer = CCLayerColor::create(ccc4BFromccc4F(color));
    /// layer->runAction(CCFadeTo::create(duration/2,fadeTo));
    addChild(CCLayerColor::create(ccc4BFromccc4F(color)));

    setInverted(true);

    return true;
}

bool IrisWipe::registerCallbackHandler(int handler)
{
    mHandler = handler;
    return true;
}

void IrisWipe::callback()
{
    if (mHandler > -1 )
        LuaHelper::getInstance()->executeFunction(mHandler, 0);
}

void IrisWipe::unregisterCallbackHandler()
{
    LuaHelper::getInstance()->releaseFunction(mHandler);
}

NS_PIX2D_END
