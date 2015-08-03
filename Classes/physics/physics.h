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

#ifndef PIX2D_PHYSICS_H
#define PIX2D_PHYSICS_H

#include "forwards.h"

#include "physics/touch.h"
#include "physics/contact.h"
#include "physics/userdata.h"
#include "body/base/physicnode.h"
#include "bindings/luahelper.h"

/// Include the following because of friend classes
#include "layer/physicslayer.h"

#include <micropather/micropather.h>

/// Don't use neither macro or global variable for the Pixel to meter ratio but rather the function Physics::PTM_ratio()
/// #define PTM_RATIO 32.f
/// extern float PTM_RATIO;

NS_PIX2D_BEGIN

//////////////////////////// Ray Cast Listener ////////////////////////////////
struct LuaRayCastInfo
{
    PhysicNode *node;    /// Might be nil if the fixture has no PhysicNode
    b2Fixture *fixture;
    b2Vec2 point;
    b2Vec2 normal;
    float fraction;
    float rc;           /// The Lua function must set this field to -1 to filter, 0 to terminate, fraction to clip the ray for closest hit, 1 to continue
};

class LuaRayCast : public b2RayCastCallback
{
public:
    LuaRayCast(int lo);
    ~LuaRayCast();
    /// Implement b2RayCastCallBack
    virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
protected:
    int mHandler;
    LuaHelper *lua;
};

//////////////////////////// struct PhysicsDef ////////////////////////////////

struct PhysicsDef {
    CCScene *scene;             /// The target scene
    float unit;               /// World unit in *meters*
    b2Vec2 size;                /// World size in *units*
    b2Vec2 pos;                 /// World coordinates origin
    b2Vec2 gravity;             /// World gravity
    bool continuousPhysics;
    bool allowSleeping;

    PhysicsDef()
    : scene(nullptr)
    , unit(1.f)
    , size(.0f, .0f)
    , pos(.0f, .0f)
    , gravity(.0f, .0f)
    , continuousPhysics(false)
    , allowSleeping(true)
    {}
};

//////////////////////////// class Physics ////////////////////////////////

class Physics {
public:

    /// Friend classes
    friend class PhysicsLayer;

    /// collision group filter
    enum GroupIndex {
        kBoundaryLeft       = 1,
        kBoundaryTop        = 2,
        kBoundaryRight      = 3,
        kBoundaryBottom     = 4
    };

    /// collision category filter
    enum CategoryBits {
        kNoCollision    = 0,
        /*
        kHook           = 1L << 0,
        kHero           = 1L << 1,
        kCoin           = 1L << 2,
        kGoal           = 1L << 3,
        kTool           = 1L << 4
        */
    };

    /** @brief Create the singleton instance. If exists the instance is destroyed first. */
    static Physics * create(const PhysicsDef &def);

    /// Helpers to check from Lua scripts if pix2d or cocos2d is compiled in debug mode.
    inline static bool isPix2dDebug();         /// Returns true if COCOS2D_CONSOLE_DEBUG > 0 (only used by pix2d)
    inline static bool isCocos2dDebug();       /// Returns true if COCOS2D_DEBUG > 0 (used by pix2d and cocos2d)

    //////////////////////////// Singletons acess //////////////////////////

    /** @brief Get this physics instance */
    static Physics *shared() { assert(smInstance); return smInstance; }
    /** brief Get the box2d physics world instance */
    b2World *world() { return mWorld; }
    const b2World *world() const { return mWorld; }
    /** Dummy static body always available at coordinate 0,0 for other bodies (e.g. create joints) */
    b2Body *dummy() { return mDummy; }
    /** @brief Access the level graph */
    Graph *graph() { return mGraph; }
    /** @brief Access the contact listener */
    ContactListener* contactListener() { return mContactListener; }
    /** @brief Access the touch listener */
    TouchListener* touchListener() { return mTouchListener; }
    /** @brief Access to the physics layer where all physics sprite should be drawn */
    PhysicsLayer *layer() { return mPhysicsLayer; }
    b2Vec2 getGravity() { return mWorld->GetGravity(); }

    /** @brief destroy a body/fixture/joint or cocos2d physic node as soon as possible.
     @warning The node is marked for destruction and the destruction is delayed if called inside the physic
     world step method (b2World::Step) or during the collisions notification phase (ContactListener::notifyCollisions).
     Otherwise it's destroyed immediately. */
    void removePhysicNode(PhysicNode *node);
    void removeBody(b2Body *body, bool deteUserData = true);
    void removeFixture(b2Fixture *fixture, bool deteUserData = true);
    void removeJoint(b2Joint *joint, bool deteUserData = true);

    /** @brief awake the body b and attached bodies */
    static void awakeBody(b2Body *b);

    ////////////////////////// Low level body creation helpers ///////////////////////////
    /// ... TODO

    ////////////////////////// Low level joint creation helpers ///////////////////////////
    b2PrismaticJoint *createPrismaticJoint(PhysicNode *nodeA, PhysicNode *nodeB);
    b2PrismaticJoint *createPrismaticJoint(b2Body *bodyA, b2Body *bodyB);

    /// Create joints helpers
    /// Note that bodies should have a density higher than zero to work correcty with revolute joint.
    static b2RevoluteJoint *createRevoluteJoint(b2Body *bodyA, b2Body *bodyB, const b2Vec2 &anchor);
    /// Lower/upper angle in radian
    static b2RevoluteJoint *createRevoluteJoint(b2Body *bodyA, b2Body *bodyB, const b2Vec2 &localA, const b2Vec2 &local,bool enableLimit = false, float lowerAngle = .0f, float upperAngle = .0f);

    b2RopeJoint *createRopeJoint(b2Body *bodyA, b2Body *bodyB, b2Vec2 anchorA, b2Vec2 anchorB);
    b2RopeJoint *createRopeJoint(b2Body *bodyA, b2Body *bodyB);

    ///////////////////////// High level joint creation helpers ///////////////////////////
    b2RopeJoint *createRopeJoint(PhysicNode *nodeA,PhysicNode *nodeB, b2Vec2 anchorA, b2Vec2 anchorB);
    b2RopeJoint *createRopeJoint(PhysicNode *nodeA,PhysicNode *nodeB);

    b2RevoluteJoint *createRevoluteJoint(PhysicNode *nodeA, PhysicNode *nodeB);
    /// anchor is a world point
    b2RevoluteJoint *createRevoluteJointWithAnchor(PhysicNode *nodeA, PhysicNode *nodeB, const b2Vec2 &anchor);
    b2RevoluteJoint *createRevoluteJointWithLimit(PhysicNode *a, PhysicNode *b, const b2Vec2 &anchor, float lower, float upper);
    void removeRevoluteJoint(PhysicNode *nodeA, PhysicNode *nodeB);
    b2DistanceJoint *createDistanceJoint(PhysicNode *nodeA, PhysicNode *nodeB, const b2Vec2 &anchorA, const b2Vec2 &anchorB, float frequency = 4.f, float damping = .5f);
    b2DistanceJoint *createDistanceJointWithLength(PhysicNode *nodeA, PhysicNode *nodeB, float length, float frequency = 4.f, float damping = 5.f);
    b2WeldJoint *createWeldJoint(PhysicNode *nodeA,PhysicNode *nodeB,const b2Vec2 &anchorA,const b2Vec2 &anchorB,float frequency = 4.f,float damping = .5f);

    void createPrismaticJoint(PhysicNode *node,const b2Vec2 &start,const b2Vec2 &end);
    void createFrictionJoint(PhysicNode *nodeA,float maxForce);

    ////////////////////// Ray Cast ////////////////////////
    /// Ray cast the world using a Lua callback
    void rayCast(int lo, const b2Vec2& point1, const b2Vec2& point2) const;
    /// http://www.iforce2d.net/b2dtut/projected-trajectory
    /// TODO remove hardcoded values from the methodes below
    /// basic trajectory 'point at timestep n' formula
    b2Vec2 getTrajectoryPoint(const b2Vec2& startingPosition,const b2Vec2& startingVelocity, float n);
    /// find the initial velocity necessary to reach a specified maximum height
    float calculateVerticalVelocityForHeight(float desiredHeight);
    /// find out how many timesteps it will take for projectile to reach maximum height
    float getTimestepsToTop(const b2Vec2& startingVelocity);
    /// find out the maximum height for this parabola
    float getMaxHeight(const b2Vec2& startingPosition, const b2Vec2& startingVelocity);

    /// Pixels to meters
    static double pixelToMeter(double p);
    static b2Vec2 pixelToMeter(float x, float y);
    static b2Vec2 pixelToMeter(const CCPoint &p);

    /// Meters to pixels
    static double meterToPixel(double p);
    static CCPoint meterToPixel(double x, double y);
    static CCPoint meterToPixel(const b2Vec2 &v);

    /// Map unit (index) to meters
    /** @brief Convert map units to box2d meters. The origin is the bottom left corner of the map block. */
    static b2Vec2 unitToMeter(float i, float j);

    /**
     * @brief Convert map units to box2d meters using custom origin.
     * ox and oy are normalized offset so 0,0 is the bottom left corner.
     * 1,1 is the top right corner and 0.5,0.5 is the center of the block
     */
    static b2Vec2 unitToMeter(float i, float j, float ox, float oy);
    inline static b2Vec2 unitToMeter(const b2Vec2 &v);
    /** @brief Convert map units to box2d meters. The origin is the center of the map block. */
    inline static b2Vec2 unitToMeterCenter(const b2Vec2 &v);
    inline static b2Vec2 unitToMeterCenter(float i, float j);

    /// Meters to map units
    static b2Vec2 meterToUnit(const b2Vec2 &v);
    /** @brief Helper for lua. Returs both converted x and y. */
    static void meterToUnit(float *x, float *y);

    /// Units to pixels shortcut
    inline static CCPoint unitToPixel(float i, float j);
    inline static CCPoint unitToPixelCenter(float i, float j);
    inline static CCPoint unitToPixel(const b2Vec2 &v);
    inline static CCPoint unitToPixelCenter(const b2Vec2 &v);
    /**
     * To use this method in lua:
     * local x,y = pix2d.Physics:pixelToUnit(x,y)
     */
    inline static void pixelToUnit(float *x, float *y);

    /// Physics properties
    float unit() const { return mUnit; }
    float getUnitInPixel() const { return meterToPixel(mUnit); }
    b2Vec2 position() const { return mPosition; }
    inline void positionInPixel(float *x, float *y);
    b2Vec2 size() const { return mSize; }
    CCSize sizePixel() const { return mSizePixel; }
    b2Vec2 sizeUnits() const { return mSizeUnits; }
    bool isPaused() { return mIsPaused; }
    inline void pause() { mIsPaused = true; }
    inline void resume() { mIsPaused = false; }

    /** Get the pixel-to-meter ratio */
    float PTM_ratio() { return mRatio; }

    int getNextUniqueId() { return ++mNextUniqueId; }

    /** @brief Add a CCNode to the physics layer */
    void addNode(CCNode *node);
    void addNode(CCNode *node, int zorder);
    void addNode(CCNode *node, int zorder, int tag);
    /** @brief Returns the target scene which might not be the current running scene if the physics scene is being loaded */
    inline CCScene* getScene() { return mScene; }

    inline static void setDefaultBackgroundColor(float r, float g, float b, float a);
    inline static ccColor4F getDefaultBackgroundColor();

protected:

    void updateNextUniqueId(int uid) { if (uid > mNextUniqueId) mNextUniqueId = uid; }

    /** @brief Notify physics node about collisions */
    inline void notifyCollisions() { mContactListener->notifyCollisions(); }

    /** @brief Destroy all physics entities marked for destruction. This must be called outside the physics world step method! */
    void destroyPhysicWorld();
    void destroyPendingBodies();
    void destroyPendingFixtures();
    void destroyPendingJoints();
    void destroyPendingPhysicNodes();

    /**
     @brief Actually destroy the body and attached fixtures and joints. User data is also destroyed if autorelease is enabled.
     @warning These should not be called directly.
     */
    void destroyBody(b2Body *body);
    void destroyJoint(b2Joint *joint);
    void destroyFixture(b2Fixture *fixture);

private:
    /// Private constructor/destructor
    explicit Physics(const PhysicsDef &def);
    virtual ~Physics();
    /// Initilize method
    bool init();

    /// Reference to the physics layer
    PhysicsLayer *mPhysicsLayer;

private:
    struct DestroyInfo {
        union {
            b2Body *body;
            b2Fixture *fixture;
            b2Joint *joint;
        };
        // bool deleteUserData;
    };

///////////////////// Private Fields /////////////////////

private:
    /// The singleton instance
    static Physics *smInstance;

    /// The target scene. Might not be the current running scene (aka CCDirector::sharedDirector()->getRunningScene())
    CCScene *mScene;

    /// Physic Nodes marked to be destroyed
    std::vector<PhysicNode *> mDestroyNodes;

    /// Pending bodies to be destroyed
    std::vector<DestroyInfo> mDestroyBodies;
    std::vector<DestroyInfo> mDestroyFixtures;
    std::vector<DestroyInfo> mDestroyJoints;

    float mRatio;           /// Pixel-to-meter ratio
    b2World *mWorld;        /// Box2d world instance
    b2Body *mDummy;
    float mUnit;            /// World's map unit (in box2d meters)
    b2Vec2 mPosition;       /// World's origins (in meters)
    b2Vec2 mSize;           /// World size in meters
    b2Vec2 mSizeUnits;      /// World size in units
    CCSize mSizePixel;      /// World size in pixels
    b2Vec2 mGravity;
    bool mIsPaused;

    /// Contact listener
    ContactListener *mContactListener;
    /// Touch listener
    TouchListener *mTouchListener;
    /// Path finding support
    Graph *mGraph;

    int mNextUniqueId;
};


//////////////////// Inline methods /////////////////////

bool Physics::isPix2dDebug()
{
#if COCOS2D_CONSOLE_DEBUG > 0
    return true;
#else
    return false;
#endif
}

bool Physics::isCocos2dDebug()
{
#if COCOS2D_DEBUG > 0
    return true;
#else
    return false;
#endif
}

b2Vec2 Physics::unitToMeter(const b2Vec2 &v)
{
    return Physics::unitToMeter(v.x, v.y);
}

b2Vec2 Physics::unitToMeterCenter(const b2Vec2 &v)
{
    return Physics::unitToMeterCenter(v.x, v.y);
}

b2Vec2 Physics::unitToMeterCenter(float i, float j)
{
    return unitToMeter(i, j, .5f, .5f);
}

/// Unit to pixel shortcut
CCPoint Physics::unitToPixel(float i, float j)
{
    return meterToPixel(unitToMeter(i, j));
}

CCPoint Physics::unitToPixelCenter(float i, float j)
{
    return meterToPixel(unitToMeterCenter(i, j));
}

CCPoint Physics::unitToPixel(const b2Vec2 &v)
{
    return unitToPixel(v.x,v.y);
}

CCPoint Physics::unitToPixelCenter(const b2Vec2 &v)
{
    return unitToPixelCenter(v.x,v.y);
}

void Physics::pixelToUnit(float *x, float *y)
{
    b2Vec2 v = Physics::meterToUnit(Physics::pixelToMeter(*x, *y));
    *x = v.x;
    *y = v.y;
}

void Physics::positionInPixel(float *x, float *y)
{
    CCPoint p = Physics::meterToPixel(mPosition);
    *x = p.x;
    *y = p.y;
}

void Physics::setDefaultBackgroundColor(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);
}

ccColor4F Physics::getDefaultBackgroundColor()
{
    GLfloat color[4];
    glGetFloatv(GL_COLOR_CLEAR_VALUE, color);
    return ccc4f(color[0],color[1],color[2],color[3]);
}

/// Query the physic world. Return true if a fixture body (actually its AABB) exists in the given AABB.
/// If a tag is passed then returns true if the body attached to the fixture has the same tag number.
/// The tag must be zero or greater. Pass a tag number lower than zero to avoid tag search.
class QueryMap : public b2QueryCallback
{
public:
	explicit QueryMap()
    : flag(false)
    , tag(-1)
    {}

    static bool query(float x, float y,float width, float height,int tag = -1)
    {
        b2Vec2 pos = Physics::unitToMeter(x,y);
        b2Vec2 d = Physics::unitToMeter(width,height);
        b2AABB aabb;
        aabb.lowerBound = pos - d;
        aabb.upperBound = pos + d;

        /// b2Vec2 p1 = Physics::meterToUnit(aabb.lowerBound);
        /// b2Vec2 p2 = Physics::meterToUnit(aabb.upperBound);
        /// CCLOG("lower: %f:%f upper:%f:%f",p1.x,p1.y,p2.x,p2.y);

        QueryMap callback;
        callback.tag = tag;
        Physics::shared()->world()->QueryAABB(&callback, aabb);
        return callback.flag;
    }

	bool ReportFixture(b2Fixture* fixture)
	{
        if (fixture->GetBody()->GetType() != b2_kinematicBody && fixture->IsSensor() == false) {
            if (tag < 0 || (fixture->GetBody()->GetUserData() &&
                 static_cast<BodyData *>(fixture->GetBody()->GetUserData())->physicCocosNode->getTag() == tag)) {
                flag = true;
                return false;
            }
        }
        return true;
    }

    bool flag;
    int tag;
};

NS_PIX2D_END
#endif // PIX2D_PHYSICS_H
