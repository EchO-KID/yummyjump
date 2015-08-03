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

#ifndef PIX2D_USERDATA_H
#define PIX2D_USERDATA_H

#include "forwards.h"

NS_PIX2D_BEGIN

///////////////////////////// UserData /////////////////////////////

/** @brief Physics entity user data */
struct UserData
{
    bool autorelease;           /// automatically released the user data when the body/fixture/joint is detroyed
    bool markedForDestruction;  /// This physics entity is marked to be destroyed as soon as possible

    /// Constructor
    UserData()
    : autorelease(true)
    , markedForDestruction(false)
    {}
};

///////////////////////////// BodyData /////////////////////////////
/** @brief Body user data */
struct BodyData : public UserData
{
    PhysicNode *physicCocosNode;       /// Pointer to the physic cocos2d CCNode
    /// Constructor
    BodyData()
    : UserData()
    , physicCocosNode(nullptr)
    {}
};

///////////////////////////// FixtureData /////////////////////////////
/** @brief Fixture user data */
struct FixtureData : public UserData
{
    /// Constructor
    FixtureData()
    : UserData()
    {}
};

///////////////////////////// JointData /////////////////////////////
/** @brief Joint user data */
struct JointData : public UserData
{
    /// Constructor
    JointData()
    : UserData()
    {}
};

NS_PIX2D_END
#endif // PIX2D_USERDATA_H
