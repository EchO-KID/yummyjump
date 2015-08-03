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

#include "nodes/actiontweenlua.h"
#include "bindings/luahelper.h"

NS_PIX2D_BEGIN

ActionTweenLua::ActionTweenLua()
: CCActionInterval()
, mHandler(0)
{}

ActionTweenLua::~ActionTweenLua()
{
    LuaHelper::getInstance()->releaseFunction(mHandler);
}

ActionTweenLua* ActionTweenLua::create(float aDuration, const char* key, float from, float to, int handler)
{
    ActionTweenLua* pRet = new ActionTweenLua();
    if (pRet && pRet->initWithDuration(aDuration, key, from, to,handler))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ActionTweenLua::initWithDuration(float aDuration, const char* key, float from, float to, int handler)
{
    if (CCActionInterval::initWithDuration(aDuration))
    {
        m_strKey = key;
        m_fTo = to;
        m_fFrom = from;
        mHandler = handler;
        return true;
    }

    return false;
}

void ActionTweenLua::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    m_fDelta = m_fTo - m_fFrom;
}

void ActionTweenLua::update(float dt)
{
    LuaHelper::getInstance()->pushFloat(m_fTo  - m_fDelta * (1 - dt));
    LuaHelper::getInstance()->pushString(m_strKey.c_str());
    LuaHelper::getInstance()->executeFunction(mHandler, 2);
    ///dynamic_cast<ActionTweenLuaDelegate*>(m_pTarget)->updateTweenAction(m_fTo  - m_fDelta * (1 - dt), m_strKey.c_str());
}

/*
ActionTweenLua* ActionTweenLua::reverse()
{
    return ActionTweenLua::create(m_fDuration, m_strKey.c_str(), m_fTo, m_fFrom, mHandler);
}
*/

NS_PIX2D_END
