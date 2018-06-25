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

#ifndef PIX2D_FORWARDS_H
#define PIX2D_FORWARDS_H

/// Include both cocos2d and box2d globally
#include <cocos2d.h>
#include <Box2D/Box2D.h>

/// Using cocos2d namespace
USING_NS_CC;

#include "global.h"

/// Forward declarations
class VRope;    /// Not in the pix2d namespace

NS_PIX2D_BEGIN

/// Typedef
/// typedef unsigned int uid_t;
/// typedef unsigned coord_t;
typedef std::vector<b2Vec2> b2Vec2Path;
typedef std::vector<CCPoint> CCPointVector;         /// A point vector
typedef std::vector<ccVertex3F>  CCVertexVector;    /// A 3 floats vectex vector
typedef std::vector<ccTex2F> CCTexCoordVector;      /// A 2 floats texture coordinates vector
typedef std::vector<ccColor4B> CCColorVector;

/// Geometry
class LineBezier;
class QuadBezier;
class CubicBezier;
class BezierPath;

/// Physics
struct BodyData;
struct FixtureData;
struct JointData;
class Physics;
class Graph;

/// Scenes
/// class LevelLoader;

/// Sprite
class TextureSprite;

/// Layers
class PhysicsLayer;
class TextureLayer;

/// Base bodies
class PhysicNode;
class Circle;
class Box;

/// bodies
class Boundary;
// class Hero;
class Rope;
// class Coin;
// class Clay;
// class Soft;
// class Path;
// class Bezier;

/// Delegate interface
class TouchDelegate;
class ContactDelegate;

/// io

/// Notifications
class NotificationData;

NS_PIX2D_END

#endif // PIX2D_FORWARDS_H
