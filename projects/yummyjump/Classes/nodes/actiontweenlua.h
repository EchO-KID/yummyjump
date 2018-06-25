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

#ifndef PIX2D_ACTIONTWEENLUA_H
#define PIX2D_ACTIONTWEENLUA_H

#include "forwards.h"

NS_PIX2D_BEGIN

class ActionTweenLua : public CCActionInterval
{
public:
    ActionTweenLua();
    virtual ~ActionTweenLua();
    /**
     * @brief creates and initializes the action with the property name (key),
     * the from and to parameters, and the Lua script handler.
     */
    static ActionTweenLua* create(float aDuration, const char* key, float from, float to, int handler);

    bool initWithDuration(float aDuration, const char* key, float from, float to,int handler);

    void startWithTarget(CCNode *pTarget);
    void update(float dt);

    /// Not implemented
    /// ActionTweenLua* reverse();

protected:
    std::string m_strKey;
    float m_fFrom, m_fTo;
    float m_fDelta;
    int mHandler;
};

NS_PIX2D_END

#endif /* PIX2D_ACTIONTWEENLUA_H */
