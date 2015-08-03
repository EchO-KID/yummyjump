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

#ifndef PIX2D_PHYSICNODE_H
#define PIX2D_PHYSICNODE_H

#include "forwards.h"
#include "common/settings.h"

NS_PIX2D_BEGIN

/////////////////////////// CustomSprite ///////////////////////////

/** @brief custom sprite implementing tween action (custom actions) */
class CustomSprite : public CCSprite, public CCActionTweenDelegate
{
public:
    CustomSprite();
    virtual ~CustomSprite();

    // CREATE_FUNC(CustomSprite);

    static CustomSprite* create(const char *pszFilename);
    static CustomSprite* createWithSpriteFrameName(const char *pszSpriteFrameName);
    /// static CustomSprite* createWithTexture(CCTexture2D *pTexture);

    /** Set the quad (tex coords, vertex coords and color) information. Allow sprite "deformation". */
    inline void setQuad(const ccV3F_C4B_T2F_Quad quad) { m_sQuad = quad; }

    void convertToNodeSpaceNormalize(float *x, float *y);

    /** @brief register the script handler `lo` to handle CCTweenAction */
    void registerTweenActionHandler(int lo);
    void unregisterTweenActionHandler();
    virtual void updateTweenAction(float value, const char* key);

protected:
    int mTweenActionHandler;
};

/////////////////////////// PhysicNode ///////////////////////////

struct PhysicNodeDef
{
    int uid;
    int tag;
    int zorder;

    b2FixtureDef fixture;   /// DEPRECATED
    b2BodyDef body;         /// DEPRECATED

    b2BodyType body_type;       /// the body type (b2_dynamicBody, b2_kinematicBody or b2_staticBody)
    std::string sprite;         /// create the sprite from file
    std::string frame;          /// create the sprite from a spritesheet (CCSpriteFrameCache)
    b2Vec2 pos;                 /// position in the map (not position in meters or pixels)
    float angle;                /// body angle in radian
    bool is_sensor;             /// the fixture is a sensor
    float restitution;
    float density;
    float friction;

    /// collision filter (box2d low level)
    unsigned short category;
    unsigned short mask;
    signed short group;

    PhysicNodeDef()
    : body_type(b2_staticBody)
    /// BUG FIX: rope becomes “untouchable” erratically due to uninitialized density.
    /// Density must be initialized to avoid side effects. If not it gets garbage value which might be
    /// huge leading to broken joint.
    , density(.0f)
    , tag(0)
    , uid(0)
    , zorder(0)
    , is_sensor(false)
    , category(0x0001)
    , mask(0xFFFF)
    , group(0)
    , angle(.0f)
    {}
};

/** @brief A cocos2d physics node that encapsulates a Box2D body and CustomSprite. */
class PhysicNode : public CCNodeRGBA {
public:

    /// tags for physic nodes
    enum tag {
        kBoundaryTag = 1,
        kMaxTag
    };

    /** @brief construct a physic node with auto-generated unique id */
    explicit PhysicNode();

    /** @brief construct a physic node with the provided unique id. Client code must check the validity of the uid */
    explicit PhysicNode(const int uid);

    /** @brief destructor */
    virtual ~PhysicNode();

    /** @brief Initialize the physics using definition */
    virtual bool init(const PhysicNodeDef &def);

    /** @brief ensable/disable the movable property of this node (can be moved with the b2MouseJoint) */
    void movable(bool value) { mIsMovable = value; }
    bool isMovable() const { return mIsMovable; }

    /** @brief print node's configuration to the standard output */
    virtual void dump();

    void setGravityScale(float scale) { mBody->SetGravityScale(scale); }
    float getGravityScale() { return mBody->GetGravityScale(); }

    b2BodyType getBodyType() { return mBody->GetType(); }
    void setBodyType(b2BodyType type) { mBody->SetType(type); }

    /** @brief returns the node's unique id */
    virtual int getUniqueId() const { return mUniqueId; }

    /** @brief access the physics body. Can be nil. */
    b2Body *body() const { return mBody; }

    /** @brief returns the custom sprite child (can be nil). */
    CustomSprite *getSprite() { return dynamic_cast<CustomSprite *>(getChildByTag(settings::kTagPhysicsNodeSprite)); }

    /** @brief Draw the body shape using box2d debug draw */
    virtual void drawDebugShape(const ccColor4F &color) { CC_UNUSED_PARAM(color); }

    bool isSensor() { return mBody->GetFixtureList()->IsSensor(); }

    void setMarkedForDestruction(bool value) { mMarkedForDestruction = value; }
    bool isMarkedForDestruction() { return mMarkedForDestruction; }

    ////////////////////  Physics methodes //////////////////////
    /** @brief The physic position in meter. Same as Physic::pixelToMeter(this->getPosition()) */
    void setBodyPosition(float x, float y)  { mBody->SetTransform(b2Vec2(x,y),mBody->GetAngle()); }
    /** Set the body rotation. Angle is in radian */
    void setBodyRotation(float a)           { mBody->SetTransform(mBody->GetPosition(), a); }
    const b2Vec2& getBodyPosition()         { return mBody->GetPosition(); }
    const b2Vec2& getBodyCenter()           { return mBody->GetWorldCenter(); }
    void setFixedRotation(bool value)       { mBody->SetFixedRotation(value); }

    b2Vec2 getWorldPoint(const b2Vec2 &localPoint) const { return mBody->GetWorldPoint(localPoint); }
    b2Vec2 getLocalPoint(const b2Vec2 &worldPoint) const { return mBody->GetLocalPoint(worldPoint); }
    b2Vec2 getLocalVector(const b2Vec2 &worldVector) const { return mBody->GetLocalVector(worldVector); }
    b2Vec2 getWorldVector(const b2Vec2 &localVector) const { return mBody->GetWorldVector(localVector); }

    void setSleepingAllowed(bool value) { mBody->SetSleepingAllowed(value); }

    /// For ToLua Binding
    /*
    void getBodyPosition(float *x, float *y) { b2Vec2 p = mBody->GetPosition(); *x = p.x; *y = p.y; }
    void getBodyCenter(float *x, float *y)   { b2Vec2 p = mBody->GetWorldCenter(); *x = p.x; *y = p.y; }
    */
    float getAngle()                        { return mBody->GetAngle();             }
    float getMass()                         { return mBody->GetMass();              }
    void setMass(float value);
    b2Vec2 getLinearVelocity()              { return mBody->GetLinearVelocity();    }
    float getIntertia()                     { return mBody->GetInertia();           }
    void setAngularVelocity(float value)    { mBody->SetAngularVelocity(value);     }
    float getAngularVelocity()              { return mBody->GetAngularVelocity();   }
    void setAngularDamping(float d)         { mBody->SetAngularDamping(d);          }
    void setLinearDamping(float d)          { mBody->SetLinearDamping(d);           }
    /** Set direct linear velocity to the body */
    void setLinearVelocity(const b2Vec2 &v) { mBody->SetLinearVelocity(v);          }
    /** @brief apply a linear impulse at the center of mass */
    void applyLinearImpulse(float x, float y);
    /** @brief Apply a force at the center of mass */
    void applyForceToCenter(float x, float y);

    void setBullet(bool value) { mBody->SetBullet(value); }
    bool isBullet() { return mBody->IsBullet(); }
    /** @brief Set the collision filter for all the fixture for this physic body */
    void setCollisionFilter(unsigned short category, unsigned short mask, signed short group);
    void setCollisionCategory(unsigned short category);
    void setCollisionMask(unsigned short mask);
    void setCollisionGroup(signed short group);

    /// convenient function to return 3 parameters in Lua
    void getCollisionFilter(unsigned short *category, unsigned short *mask, signed short *group);


    /// Ray cast. If not ray casting agains chain shapes then you can leave childIndex to zero
    bool rayCast(b2RayCastOutput* output, const b2RayCastInput& input, int childIndex = 0)
        { return mBody->GetFixtureList()->RayCast(output, input, childIndex);  }

protected:
    BodyData* createBodyData();
    BodyData* createBodyData(PhysicNode *node);

protected:
    b2Body *mBody;          /// The box2d physic body
    const int mUniqueId;
    bool mIsMovable;
    bool mMarkedForDestruction;
    b2Filter mOldFilter;
};

NS_PIX2D_END
#endif // PIX2D_PHYSICNODE_H
