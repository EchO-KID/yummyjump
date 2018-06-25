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

#include "physics.h"
#include "geom.h"
#include "graph.h"
#include "body/boundary.h"
#include "bindings/luahelper.h"

#if COCOS2D_CONSOLE_DEBUG > 0
# include "debug/debuglayer.h"
# include "console/luaconsole.h"
#endif

NS_PIX2D_BEGIN

//////////////////////////// Ray Cast Listener ////////////////////////////////
LuaRayCast::LuaRayCast(int lo)
: lua(LuaHelper::getInstance())
{
    mHandler = lo;
}

LuaRayCast::~LuaRayCast()
{
    lua->releaseFunction(mHandler);
}

float32 LuaRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
    LuaRayCastInfo info;
    info.node = fixture->GetBody()->GetUserData() ? static_cast<PhysicNode *>(fixture->GetBody()->GetUserData()) : nullptr;
    info.fixture = fixture;
    info.point.Set(point.x,point.y);
    info.normal.Set(normal.x,normal.y);
    info.fraction = fraction;
    lua->pushUserType(&info, "pix2d::LuaRayCastInfo");
    lua->executeFunction(mHandler, 1);
    return info.rc;
}

//////////////////////////// Physics ////////////////////////////////

struct DestroyInfo
{
    union {
        b2Body *pBody;
        b2Fixture *pFixture;
        b2Joint *pJoint;
    };
    // bool deleteUserData;
};

Physics *Physics::smInstance = nullptr;

Physics::Physics(const PhysicsDef &def)
: mWorld(nullptr)
, mScene(def.scene)
, mRatio(.0f)
, mDummy(nullptr)
, mGraph(nullptr)
, mUnit(def.unit)
, mPosition(def.pos)
, mSizeUnits(def.size)
, mSize(def.size.x * def.unit, def.size.y * def.unit)
, mSizePixel(.0f, .0f)
, mGravity(def.gravity)
, mIsPaused(false)
, mNextUniqueId(0)
, mPhysicsLayer(nullptr)
{}

Physics::~Physics()
{
    CCLOG("destroy the physics world...");

    /// Disable and destroy the contact listener object
    /// WARNING: This must be done before destroying the world
    mWorld->SetContactListener(nullptr);
    CC_SAFE_DELETE(mContactListener);

    /// Destroy the physics world
    destroyPhysicWorld();

    /// Destroy the graph
    CC_SAFE_DELETE(mGraph);

    /// Destroy the touch listener
    CC_SAFE_DELETE(mTouchListener);
}

Physics *Physics::create(const PhysicsDef &def)
{
    if (smInstance) {
        CC_SAFE_DELETE(smInstance);
    }

    smInstance = new Physics(def);
    if (smInstance && smInstance->init()) {
        return smInstance;
    }

    CC_SAFE_DELETE(smInstance);
    return nullptr;
}

bool Physics::init()
{
    /// Figures out the pixel-to-meter ratio:
    /// ratio = pixels / meters
    /// In multi-resolution support we must use the size in points (and not in pixels aka getWinSizeInPixels)
    mRatio = CCDirector::sharedDirector()->getVisibleSize().width / mSize.x;
    /// TODO: The world size map to the screen (actually the design resolution).
    /// If we want the world to be bigger than the screen we must provide:
    /// 1. The whole world size in units
    /// 2. The screen size in units

    CCLOG("Pixel to meter ratio: %f", mRatio);

    /// The physics world size in pixels
    mSizePixel.setSize(meterToPixel(mSize.x), meterToPixel(mSize.y));

    /// Create the physics world
    mWorld = new b2World(mGravity);
    /// mWorld->SetContinuousPhysics(true); /// @todo investigate continuous physics
    /// mWorld->SetAllowSleeping(false);

    /// Create the dummy static body
    {
        b2BodyDef bd;
        bd.type = b2_staticBody;
        bd.position.SetZero();

        b2CircleShape circle;
        circle.m_p.Set(mPosition.x, mPosition.y);
        circle.m_radius = .1f;

        b2FixtureDef fd;
        fd.shape = &circle;
        fd.filter.maskBits = 0; /// No collision

        mDummy = mWorld->CreateBody(&bd);
        mDummy->CreateFixture(&fd);
    }

    /// World map and path finder support
    /*
    mGraph = new Graph(*this);

    if (!mGraph) {
        CCLOGERROR("Cannot create the graph map");
        return false;
    }
    */

    /// Set the contact listener
    mContactListener = new ContactListener();
    mWorld->SetContactListener(mContactListener);

    /// Create the touch listener
    mTouchListener = new TouchListener();

    /// Set black as default background color
    setDefaultBackgroundColor(.0f, .0f, .0f, .0f);

#if COCOS2D_CONSOLE_DEBUG > 0
    /// TODO Creating the debug layer is a performance bootleneck.
    /// Pass the physics world and the level data as string
    if (DebugLayer *debug = DebugLayer::create(mWorld))
        mScene->addChild(debug, settings::kZOrderDebugLayer, settings::kTagDebugLayer);
    else
        CCLOGERROR("Cannot create debug layer");
#endif

    /// Create the physics layer and add it to the scene
    if (PhysicsLayer *layer = PhysicsLayer::create(mWorld)) {
        mPhysicsLayer = layer;
        mScene->addChild(mPhysicsLayer, settings::kZOrderPhysicsLayer, settings::kTagPhysicsLayer);
    } else {
        CCLOGERROR("ERROR: Can't create the physics layer.");
        return false;
    }

    return true;
}

double Physics::meterToPixel(double p)
{
    return p * Physics::shared()->mRatio;
}

double Physics::pixelToMeter(double p)
{
    return p / Physics::shared()->mRatio;
}

cocos2d::CCPoint Physics::meterToPixel(double x, double y)
{
    return ccpMult(ccp(x,y), Physics::shared()->mRatio);
}

cocos2d::CCPoint Physics::meterToPixel(const b2Vec2 &v)
{
    return ccpMult(ccp(v.x,v.y), Physics::shared()->mRatio);
}

b2Vec2 Physics::pixelToMeter(const CCPoint &p)
{
    float r = Physics::shared()->mRatio;
    return b2Vec2(p.x / r, p.y / r);
}

b2Vec2 Physics::pixelToMeter(float x, float y)
{
    return Physics::pixelToMeter(CCPoint(x,y));
}

b2Vec2 Physics::unitToMeter(float i, float j, float ox, float oy)
{
    float32 u = Physics::shared()->mUnit;
    b2Vec2 p = Physics::shared()->mPosition;
    return b2Vec2((u * i) + (u * ox) + p.x, (u * j) + (u * oy) + p.y);
}

b2Vec2 Physics::unitToMeter(float i, float j)
{
    float32 u = Physics::shared()->mUnit;
    b2Vec2 p = Physics::shared()->mPosition;
    return b2Vec2(u * i + p.x, u * j + p.y);
}

void Physics::meterToUnit(float *x, float *y)
{
    b2Vec2 v = Physics::meterToUnit(b2Vec2(*x,*y));
    *x = v.x;
    *y = v.y;
}

b2Vec2 Physics::meterToUnit(const b2Vec2 &v)
{
    b2Vec2 s = Physics::shared()->mSize;
    b2Vec2 u = Physics::shared()->mSizeUnits;
    return b2Vec2((v.x / s.x) * u.x, (v.y / s.y) * u.y);
}

void Physics::awakeBody(b2Body *b)
{
    if (!b) return;

    if (!b->IsAwake())
        b->SetAwake(true);

    b2JointEdge *edge = b->GetJointList();

    while (edge) {
        if(!edge->other->IsAwake())
            edge->other->SetAwake(true);
        edge = edge->next;
    }
}

void Physics::removePhysicNode(PhysicNode *node)
{
    node->setMarkedForDestruction(true);
    if (mWorld->IsLocked() || mContactListener->isLocked())
        mDestroyNodes.push_back(node);
    else
        node->removeFromParentAndCleanup(true);
}

void Physics::removeBody(b2Body *body, bool deleteUserData)
{
    if (body->GetUserData())
        static_cast<BodyData *>(body->GetUserData())->markedForDestruction = true;
    if (mWorld->IsLocked() || mContactListener->isLocked()) {
        DestroyInfo info;
        info.body = body;
        /*
         if (body->GetUserData()) {
         BodyData *bd = static_cast<BodyData *>(body->GetUserData());
         bd->autorelease = deleteUserData;
         }
         */
        mDestroyBodies.push_back(info);
    } else
        destroyBody(body);
}

void Physics::removeFixture(b2Fixture *fixture, bool deleteUserData)
{
    if (fixture->GetUserData())
        static_cast<FixtureData *>(fixture->GetUserData())->markedForDestruction = true;
    if (mWorld->IsLocked() || mContactListener->isLocked()) {
        DestroyInfo info;
        info.fixture = fixture;
        mDestroyFixtures.push_back(info);
    } else
        destroyFixture(fixture);
}

void Physics::removeJoint(b2Joint *joint, bool deleteUserData)
{
    if (joint->GetUserData())
        static_cast<JointData *>(joint->GetUserData())->markedForDestruction = true;
    if (mWorld->IsLocked() || mContactListener->isLocked()) {
        DestroyInfo info;
        info.joint = joint;
        mDestroyJoints.push_back(info);
    } else
        destroyJoint(joint);
}

void Physics::destroyPhysicWorld()
{
    b2Body* body = mWorld->GetBodyList();
    while (body) {
        b2Body *next = body->GetNext();
        destroyBody(body);
        body = next;
    }
    /// Delete physic world
    CC_SAFE_DELETE(mWorld);
}

void Physics::destroyPendingBodies()
{
    size_t count = mDestroyBodies.size();
    for (int i=0; i < count; ++i)
        destroyBody(mDestroyBodies.at(i).body);
    mDestroyBodies.clear();
}

void Physics::destroyPendingPhysicNodes()
{
    size_t count = mDestroyNodes.size();
    for (int i=0; i < count; ++i)
        mDestroyNodes.at(i)->removeFromParentAndCleanup(true);
    mDestroyNodes.clear();
}

b2PrismaticJoint *Physics::createPrismaticJoint(b2Body *bodyA, b2Body *bodyB)
{
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(bodyA, bodyB, bodyA->GetWorldCenter(), bodyB->GetWorldCenter());
    jointDef.lowerTranslation = -10.f;
    jointDef.upperTranslation = .0f;
    jointDef.enableLimit = true;
    jointDef.maxMotorForce = 1.0f;
    jointDef.motorSpeed = 10.0f;
    jointDef.enableMotor = true;
    return static_cast<b2PrismaticJoint *>(mWorld->CreateJoint(&jointDef));
}

b2PrismaticJoint *Physics::createPrismaticJoint(PhysicNode *nodeA, PhysicNode *nodeB)
{
    if (nodeA->body() && nodeB->body())
        return createPrismaticJoint(nodeA->body(), nodeB->body());
    return nullptr;
}

b2RevoluteJoint *Physics::createRevoluteJoint(b2Body *bodyA, b2Body *bodyB, const b2Vec2 &localA, const b2Vec2 &localB, bool enableLimit, float lowerAngle, float upperAngle)
{
    b2RevoluteJointDef jd;
    jd.collideConnected = false;
    jd.bodyA = bodyA;
    jd.bodyB = bodyB;
    jd.enableMotor = false;
    jd.enableLimit = enableLimit;
    jd.lowerAngle = lowerAngle;
    jd.upperAngle = upperAngle;
    jd.localAnchorA.Set(localA.x, localA.y);
    jd.localAnchorB.Set(localB.x, localB.y);
    jd.referenceAngle = bodyB->GetAngle() - bodyA->GetAngle();
    return static_cast<b2RevoluteJoint *>(Physics::shared()->world()->CreateJoint(&jd));
}

b2RevoluteJoint *Physics::createRevoluteJoint(b2Body *bodyA, b2Body *bodyB, const b2Vec2 &anchor)
{
    b2RevoluteJointDef jd;
    jd.collideConnected = false;
    jd.Initialize(bodyA, bodyB, anchor);
    return static_cast<b2RevoluteJoint *>(Physics::shared()->world()->CreateJoint(&jd));
}

b2RopeJoint *Physics::createRopeJoint(b2Body *bodyA, b2Body *bodyB)
{
    return createRopeJoint(bodyA, bodyB, b2Vec2_zero, b2Vec2_zero);
}

b2RopeJoint *Physics::createRopeJoint(b2Body *bodyA, b2Body *bodyB, b2Vec2 anchorA, b2Vec2 anchorB)
{
    /// Create the rope joint
    b2RopeJointDef ropeDef;
    ropeDef.localAnchorA = anchorA;
    ropeDef.localAnchorB = anchorB;
    ropeDef.bodyA = bodyA;
    ropeDef.bodyB = bodyB;
    /// ropeDef.maxLength = b2Distance(bodyA->GetPosition(), bodyB->GetPosition());
    /// ropeDef.maxLength = b2Distance(bodyB->GetWorldPoint(anchorB),bodyA->GetWorldPoint(anchorA));
    ropeDef.maxLength = (bodyA->GetWorldPoint(anchorA) - bodyB->GetWorldPoint(anchorB)).Length();
    /// maxLength must be larger than b2_linearSlop or the joint will have no effect
    ropeDef.maxLength = ropeDef.maxLength > b2_linearSlop ? ropeDef.maxLength : b2_linearSlop;
    return static_cast<b2RopeJoint *>(mWorld->CreateJoint(&ropeDef));
}

b2RopeJoint *Physics::createRopeJoint(PhysicNode *nodeA,PhysicNode *nodeB, b2Vec2 anchorA, b2Vec2 anchorB)
{
    return createRopeJoint(nodeA->body(),nodeB->body(),anchorA,anchorB);
}

b2RopeJoint *Physics::createRopeJoint(PhysicNode *nodeA,PhysicNode *nodeB)
{
    return createRopeJoint(nodeA->body(),nodeB->body(),b2Vec2_zero,b2Vec2_zero);
}

void Physics::createPrismaticJoint(PhysicNode *node,const b2Vec2 &start,const b2Vec2 &end)
{
    b2PrismaticJointDef pd;
    pd.bodyA = Physics::shared()->dummy();
    pd.bodyB = node->body();

    pd.localAxisA = end - start;
    pd.localAxisA.Normalize();

    pd.collideConnected = false;

    pd.localAnchorA = node->body()->GetWorldCenter();
    pd.localAnchorB = Physics::shared()->dummy()->GetWorldCenter();

    pd.enableLimit = true;
    pd.lowerTranslation = -b2Distance(node->body()->GetPosition(),start);
    pd.upperTranslation = b2Distance(end,node->body()->GetPosition());

    world()->CreateJoint(&pd);
}

void Physics::createFrictionJoint(PhysicNode *nodeA,float maxForce)
{
    b2FrictionJointDef jd;
    jd.bodyA = nodeA->body();
    jd.bodyB = Physics::shared()->dummy();
    jd.collideConnected = false;
    jd.maxForce = maxForce;
    Physics::shared()->world()->CreateJoint(&jd);
}

void Physics::destroyBody(b2Body *body)
{
    /// Destroy body's user data and cancel contact delegates
    if (body->GetUserData()) {
        BodyData *data = static_cast<BodyData *>(body->GetUserData());
        /// We don't cancel contact delegate for the physics node attached to this body
        /// because the physics node might have many bodies and might want to still receive contact notifications
        /// However the physics node MUST cancel all contact delegate once it's released/destroyed
        /*****
        if (data->physicCocosNode)
            contactListener()->cancelAllContactDelegate(data->physicCocosNode);
        *****/
        /// We *MUST* reset the user data to nil so the contact listener will no more notified contact delegates that had registered
        /// This is mandatory because box2d will send a "end-contact" to the contact
        /// listener when a fixture is destroy and is touching another body (see b2Body::DestroyFixture and b2ContactManager::Destroy)
        body->SetUserData(nullptr);
        /// Release the user data
        if (data->autorelease) delete data;
    }

    /// Destroy attached fixtures
    b2Fixture *fixture = body->GetFixtureList();
    while (fixture) {
        b2Fixture *next = fixture->GetNext();
        if (fixture->GetUserData()) {
            FixtureData *data = static_cast<FixtureData *>(fixture->GetUserData());
            if (data->autorelease) delete data;
            fixture->SetUserData(nullptr);
        }
        // No need to destroy the fixture here. Will be destroy with the body.
        // body->DestroyFixture(fixture);
        fixture = next;
    }
    /// Destroy attached joints
    b2JointEdge *edge = body->GetJointList();
    while (edge) {
        if (edge->joint->GetUserData()) {
            JointData *data = static_cast<JointData *>(edge->joint->GetUserData());
            if (data->autorelease) delete data;
            edge->joint->SetUserData(nullptr);
        }
        // No need to destroy the joint here. Will be destroy with the body.
        // mWorld->DestroyJoint(edge->joint);
        edge = edge->next;
    }

    /// Destroy the body
    mWorld->DestroyBody(body);
}

void Physics::destroyPendingFixtures()
{
    size_t count = mDestroyFixtures.size();
    for (int i=0; i < count; ++i)
        destroyFixture(mDestroyFixtures.at(i).fixture);
    mDestroyFixtures.clear();
}

void Physics::destroyPendingJoints()
{
    size_t count = mDestroyJoints.size();
    for (int i=0; i < count; ++i)
        destroyJoint(mDestroyJoints.at(i).joint);
    mDestroyJoints.clear();
}

void Physics::destroyJoint(b2Joint *joint)
{
    if (joint->GetUserData()) {
        JointData *data = static_cast<JointData *>(joint->GetUserData());
        if (data->autorelease) delete data;
    }
    mWorld->DestroyJoint(joint);
}

void Physics::destroyFixture(b2Fixture *fixture)
{
    if (fixture->GetUserData()) {
        FixtureData *data = static_cast<FixtureData *>(fixture->GetUserData());
        if (data->autorelease) delete data;
    }
    fixture->GetBody()->DestroyFixture(fixture);
}

b2DistanceJoint *Physics::createDistanceJointWithLength(PhysicNode *nodeA, PhysicNode *nodeB, float length, float frequency, float damping)
{
    b2DistanceJointDef def;
    def.bodyA = nodeA->body();
    def.bodyB = nodeB->body();
    /// def.localAnchorA = b2Vec2_zero;
    /// def.localAnchorB = b2Vec2_zero;
    def.length = unitToMeter(length,0).x;
    def.collideConnected = false;
    def.frequencyHz = frequency;
    def.dampingRatio = damping;
    return static_cast<b2DistanceJoint *>(mWorld->CreateJoint(&def));
}

b2DistanceJoint *Physics::createDistanceJoint(PhysicNode *nodeA, PhysicNode *nodeB, const b2Vec2 &anchorA, const b2Vec2 &anchorB, float frequency, float damping)
{
    b2DistanceJointDef def;
    def.bodyA = nodeA->body();
    def.bodyB = nodeB->body();
    def.localAnchorA = anchorA;
    def.localAnchorB = anchorB;
    def.length = (def.bodyB->GetWorldPoint(def.localAnchorB) - def.bodyA->GetWorldPoint(def.localAnchorA)).Length();
    def.collideConnected = false;
    def.frequencyHz = frequency;
    def.dampingRatio = damping;
    return static_cast<b2DistanceJoint *>(mWorld->CreateJoint(&def));
}

b2WeldJoint *Physics::createWeldJoint(PhysicNode *nodeA,PhysicNode *nodeB,const b2Vec2 &anchorA,const b2Vec2 &anchorB,float frequency,float damping)
{
    b2WeldJointDef def;
    def.bodyA = nodeA->body();
    def.bodyB = nodeB->body();
    def.localAnchorA = anchorA;
    def.localAnchorB = anchorB;
    def.dampingRatio = damping;
    def.frequencyHz = frequency;
    def.collideConnected = false;
    return static_cast<b2WeldJoint *>(mWorld->CreateJoint(&def));
}

b2RevoluteJoint *Physics::createRevoluteJoint(PhysicNode *nodeA, PhysicNode *nodeB)
{
    return Physics::createRevoluteJoint(nodeA->body(), nodeB->body(), nodeA->body()->GetLocalCenter(), nodeB->body()->GetLocalCenter());
}

b2RevoluteJoint *Physics::createRevoluteJointWithAnchor(PhysicNode *nodeA, PhysicNode *nodeB, const b2Vec2 &anchor)
{
    return Physics::createRevoluteJoint(nodeA->body(), nodeB->body(), nodeA->body()->GetLocalPoint(anchor), nodeB->body()->GetLocalPoint(anchor),false,0,0);
}

b2RevoluteJoint *Physics::createRevoluteJointWithLimit(PhysicNode *nodeA, PhysicNode *nodeB, const b2Vec2 &anchor, float lower, float upper)
{
    return Physics::createRevoluteJoint(nodeA->body(), nodeB->body(), nodeA->body()->GetLocalPoint(anchor), nodeB->body()->GetLocalPoint(anchor),true,lower,upper);
}

void Physics::removeRevoluteJoint(PhysicNode *nodeA, PhysicNode *nodeB)
{
    b2JointEdge *edge = nodeA->body()->GetJointList();
    while( edge ) {
        if (edge->joint->GetBodyB() == nodeB->body()) {
            b2JointEdge *tmp = edge->next;
            removeJoint(edge->joint);
            edge = tmp;
            continue;
        }
        edge = edge->next;
    }
}

void Physics::addNode(CCNode *node)
{
    CC_ASSERT(node); /// Try to add a nil node
    if (node)
        mPhysicsLayer->addChild(node);
}

void Physics::addNode(CCNode *node, int zorder)
{
    CC_ASSERT(node); /// Try to add a nil node
    if (node)
        mPhysicsLayer->addChild(node, zorder);

}

void Physics::addNode(CCNode *node, int zorder, int tag)
{
    CC_ASSERT(node); /// Try to add a nil node
    if (node)
        mPhysicsLayer->addChild(node, zorder, tag);

}

void Physics::rayCast(int lo, const b2Vec2& point1, const b2Vec2& point2) const
{
    LuaRayCast callback(lo);
    mWorld->RayCast(&callback, point1, point2);
}

/// http://www.iforce2d.net/b2dtut/projected-trajectory

b2Vec2 Physics::getTrajectoryPoint(const b2Vec2& startingPosition,const b2Vec2& startingVelocity, float n)
{
    //velocity and gravity are given per second but we want time step values here
    float t = 1 / 60.0f; // seconds per time step (at 60fps)
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * mWorld->GetGravity(); // m/s/s

    return startingPosition + n * stepVelocity + 0.5f * (n*n+n) * stepGravity;
}

float Physics::calculateVerticalVelocityForHeight(float desiredHeight)
{
    if ( desiredHeight <= 0 )
        return 0; //wanna go down? just let it drop

    //gravity is given per second but we want time step values here
    float t = 1 / 60.0f;
    b2Vec2 stepGravity = t * t * mWorld->GetGravity(); // m/s/s

    //quadratic equation setup (ax² + bx + c = 0)
    float a = 0.5f / stepGravity.y;
    float b = 0.5f;
    float c = desiredHeight;

    //check both possible solutions
    float quadraticSolution1 = ( -b - b2Sqrt( b*b - 4*a*c ) ) / (2*a);
    float quadraticSolution2 = ( -b + b2Sqrt( b*b - 4*a*c ) ) / (2*a);

    //use the one which is positive
    float v = quadraticSolution1;
    if ( v < 0 )
        v = quadraticSolution2;

    //convert answer back to seconds
    return v * 60.0f;
}

//find out how many timesteps it will take for projectile to reach maximum height
float Physics::getTimestepsToTop(const b2Vec2& startingVelocity )
{
    float t = 1 / 60.0f;
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * mWorld->GetGravity(); // m/s/s

    float n = -stepVelocity.y / stepGravity.y - 1;

    return n;
}

//find out the maximum height for this parabola
float Physics::getMaxHeight(const b2Vec2& startingPosition,const b2Vec2& startingVelocity )
{
    if ( startingVelocity.y < 0 )
        return startingPosition.y;

    float t = 1 / 60.0f;
    b2Vec2 stepVelocity = t * startingVelocity; // m/s
    b2Vec2 stepGravity = t * t * mWorld->GetGravity(); // m/s/s

    float n = -stepVelocity.y / stepGravity.y - 1;

    return startingPosition.y + n * stepVelocity.y + 0.5f * (n*n+n) * stepGravity.y;
}

NS_PIX2D_END
