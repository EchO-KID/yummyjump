/*
** Lua binding: custom_bindings
** Generated automatically by tolua++-1.0.92 on Fri Nov 28 22:19:04 2014.
*/

/// Copyright (c) 2014 pix2d.com
/// Custom tolua binding

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace CocosDenshion;



#include "geom.h"
#include "AppDelegate.h"
#include "platform/pix2d_platform.h"
#include "body/base/physicnode.h"
#include "body/base/box.h"
#include "body/base/chain.h"
#include "body/base/circle.h"
#include "body/base/texture.h"
#include "body/rope.h"
#include "body/boundary.h"
#include "box2d/box2d.h"
#include "ccb/cocosbuilderlua.h"
#include "common/visiblerect.h"
#include "common/assets.h"
#include "io/touchgrabber.h"
#include "layer/physicslayer.h"
#include "nodes/custommenuitem.h"
#include "nodes/actiontweenlua.h"
#include "nodes/nodeutil.h"
#include "nodes/opacitynode.h"
#include "nodes/particlequad.h"
#include "nodes/postprocessing.h"
#include "nodes/drawnode.h"
#include "physics/physics.h"
#include "physics/action.h"
#include "physics/graph.h"
#include "physics/contact.h"
#include "physics/touch.h"
#include "sprites/texturesprite.h"
#include "sprites/iriswipe.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_vector_pix2d__BezierCurve_ (lua_State* tolua_S)
{
 vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_float32 (lua_State* tolua_S)
{
 float32* self = (float32*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2RayCastInput (lua_State* tolua_S)
{
 b2RayCastInput* self = (b2RayCastInput*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__ChainDef (lua_State* tolua_S)
{
 pix2d::ChainDef* self = (pix2d::ChainDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_GLfloat (lua_State* tolua_S)
{
 GLfloat* self = (GLfloat*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__CircleDef (lua_State* tolua_S)
{
 pix2d::CircleDef* self = (pix2d::CircleDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2Vec2 (lua_State* tolua_S)
{
 b2Vec2* self = (b2Vec2*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ccColor4F (lua_State* tolua_S)
{
 ccColor4F* self = (ccColor4F*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_vector_string_ (lua_State* tolua_S)
{
 vector<string>* self = (vector<string>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__CubicBezier (lua_State* tolua_S)
{
 pix2d::CubicBezier* self = (pix2d::CubicBezier*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__BezierPath (lua_State* tolua_S)
{
 pix2d::BezierPath* self = (pix2d::BezierPath*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__ContactInfo (lua_State* tolua_S)
{
 pix2d::ContactInfo* self = (pix2d::ContactInfo*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_vector_b2Vec2_ (lua_State* tolua_S)
{
 vector<b2Vec2>* self = (vector<b2Vec2>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__QuadBezier (lua_State* tolua_S)
{
 pix2d::QuadBezier* self = (pix2d::QuadBezier*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_vector_CCPoint_ (lua_State* tolua_S)
{
 vector<CCPoint>* self = (vector<CCPoint>*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__TextureDef (lua_State* tolua_S)
{
 pix2d::TextureDef* self = (pix2d::TextureDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__TouchInfo (lua_State* tolua_S)
{
 pix2d::TouchInfo* self = (pix2d::TouchInfo*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__RopeDef (lua_State* tolua_S)
{
 pix2d::RopeDef* self = (pix2d::RopeDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__PhysicsDef (lua_State* tolua_S)
{
 pix2d::PhysicsDef* self = (pix2d::PhysicsDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__LineBezier (lua_State* tolua_S)
{
 pix2d::LineBezier* self = (pix2d::LineBezier*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__BoxDef (lua_State* tolua_S)
{
 pix2d::BoxDef* self = (pix2d::BoxDef*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_CCSize (lua_State* tolua_S)
{
 CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__Graph (lua_State* tolua_S)
{
 pix2d::Graph* self = (pix2d::Graph*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_b2RayCastOutput (lua_State* tolua_S)
{
 b2RayCastOutput* self = (b2RayCastOutput*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_pix2d__BezierCurve (lua_State* tolua_S)
{
 pix2d::BezierCurve* self = (pix2d::BezierCurve*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"float32");
 tolua_usertype(tolua_S,"pix2d::CustomMenuItemToggle");
 tolua_usertype(tolua_S,"pix2d::CustomMenuItem");
 tolua_usertype(tolua_S,"pix2d::OpacityNode");
 tolua_usertype(tolua_S,"pix2d::CircleDef");
 tolua_usertype(tolua_S,"pix2d::Native");
 tolua_usertype(tolua_S,"pix2d::SplineTo");
 tolua_usertype(tolua_S,"pix2d::Pixelation");
 tolua_usertype(tolua_S,"pix2d::QueryMap");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"pix2d::Circle");
 tolua_usertype(tolua_S,"pix2d::Box");
 tolua_usertype(tolua_S,"CCSpriteBatchNode");
 tolua_usertype(tolua_S,"b2FixtureDef");
 tolua_usertype(tolua_S,"pix2d::ParticleQuad");
 tolua_usertype(tolua_S,"pix2d::BezierCurve");
 tolua_usertype(tolua_S,"pix2d::GaussianBlur");
 tolua_usertype(tolua_S,"CCDrawNode");
 tolua_usertype(tolua_S,"private cocos2d::CCApplication");
 tolua_usertype(tolua_S,"vector<pix2d::BezierCurve>");
 tolua_usertype(tolua_S,"b2DistanceJoint");
 tolua_usertype(tolua_S,"pix2d::LuaRayCastInfo");
 tolua_usertype(tolua_S,"CCClippingNode");
 tolua_usertype(tolua_S,"b2RayCastOutput");
 tolua_usertype(tolua_S,"ccColor4F");
 tolua_usertype(tolua_S,"pix2d::Grayscale");
 tolua_usertype(tolua_S,"pix2d::CustomLabelTTF");
 tolua_usertype(tolua_S,"pix2d::PostProcessing");
 tolua_usertype(tolua_S,"b2CircleShape");
 tolua_usertype(tolua_S,"b2RevoluteJoint");
 tolua_usertype(tolua_S,"pix2d::Boundary");
 tolua_usertype(tolua_S,"vector<CCPoint>");
 tolua_usertype(tolua_S,"b2BodyDef");
 tolua_usertype(tolua_S,"ccBlendFunc");
 tolua_usertype(tolua_S,"pix2d::TouchGrabber");
 tolua_usertype(tolua_S,"pix2d::RopeDef");
 tolua_usertype(tolua_S,"b2RopeJoint");
 tolua_usertype(tolua_S,"pix2d::LineBezier");
 tolua_usertype(tolua_S,"CCMenuItemToggle");
 tolua_usertype(tolua_S,"CCSprite");
 tolua_usertype(tolua_S,"CCPointArray");
 tolua_usertype(tolua_S,"pix2d::Graph");
 tolua_usertype(tolua_S,"CCEvent");
 tolua_usertype(tolua_S,"pix2d::CircleTo");
 tolua_usertype(tolua_S,"CCPoint");
 tolua_usertype(tolua_S,"pix2d::MoveTo");
 tolua_usertype(tolua_S,"CCLayer");
 tolua_usertype(tolua_S,"CCActionTweenDelegate");
 tolua_usertype(tolua_S,"pix2d::PhysicNode");
 tolua_usertype(tolua_S,"pix2d::TouchInfo");
 tolua_usertype(tolua_S,"GLfloat");
 tolua_usertype(tolua_S,"pix2d::PhysicsLayer");
 tolua_usertype(tolua_S,"pix2d::TouchListener");
 tolua_usertype(tolua_S,"CCCardinalSplineTo");
 tolua_usertype(tolua_S,"CCTouch");
 tolua_usertype(tolua_S,"pix2d::Action");
 tolua_usertype(tolua_S,"pix2d::ContactListener");
 tolua_usertype(tolua_S,"pix2d::CustomMenuItemFont");
 tolua_usertype(tolua_S,"pix2d::ActionTweenLua");
 tolua_usertype(tolua_S,"pix2d::ContactInfo");
 tolua_usertype(tolua_S,"AppDelegate");
 tolua_usertype(tolua_S,"vector<b2Vec2>");
 tolua_usertype(tolua_S,"CCMenuItemFont");
 tolua_usertype(tolua_S,"CCActionTween");
 tolua_usertype(tolua_S,"CCRect");
 tolua_usertype(tolua_S,"pix2d::Physics");
 tolua_usertype(tolua_S,"CCScene");
 tolua_usertype(tolua_S,"pix2d::PhysicsDef");
 tolua_usertype(tolua_S,"b2Fixture");
 tolua_usertype(tolua_S,"pix2d::Rope");
 tolua_usertype(tolua_S,"CCActionInterval");
 tolua_usertype(tolua_S,"pix2d::VisibleRect");
 
 tolua_usertype(tolua_S,"CCObject");
 tolua_usertype(tolua_S,"CCParticleBatchNode");
 tolua_usertype(tolua_S,"CCParticleSystemQuad");
 tolua_usertype(tolua_S,"pix2d::CustomSprite");
 tolua_usertype(tolua_S,"pix2d::Chain");
 tolua_usertype(tolua_S,"pix2d::DrawNode");
 tolua_usertype(tolua_S,"pix2d::DoublePostProcessing");
 tolua_usertype(tolua_S,"b2RayCastInput");
 tolua_usertype(tolua_S,"pix2d::ChainDef");
 tolua_usertype(tolua_S,"pix2d::IrisWipe");
 tolua_usertype(tolua_S,"pix2d::TextureSprite");
 tolua_usertype(tolua_S,"b2Vec2");
 tolua_usertype(tolua_S,"pix2d::PhysicNodeDef");
 tolua_usertype(tolua_S,"vector<string>");
 tolua_usertype(tolua_S,"CCMenuItem");
 tolua_usertype(tolua_S,"b2Joint");
 tolua_usertype(tolua_S,"pix2d::Texture");
 tolua_usertype(tolua_S,"pix2d::TextureDef");
 tolua_usertype(tolua_S,"b2World");
 tolua_usertype(tolua_S,"pix2d::NodeUtil");
 tolua_usertype(tolua_S,"pix2d::BoxDef");
 tolua_usertype(tolua_S,"pix2d::CocosBuilderLua");
 tolua_usertype(tolua_S,"ccV3F_C4B_T2F_Quad");
 tolua_usertype(tolua_S,"pix2d::FastBlur");
 tolua_usertype(tolua_S,"pix2d::CubicBezier");
 tolua_usertype(tolua_S,"CCNodeRGBA");
 tolua_usertype(tolua_S,"pix2d::BezierPath");
 tolua_usertype(tolua_S,"pix2d::QuadBezier");
 tolua_usertype(tolua_S,"CCRenderTexture");
 tolua_usertype(tolua_S,"CCLabelTTF");
 tolua_usertype(tolua_S,"CCSize");
 tolua_usertype(tolua_S,"b2WeldJoint");
 tolua_usertype(tolua_S,"b2Body");
 tolua_usertype(tolua_S,"CCMenuItemImage");
 tolua_usertype(tolua_S,"pix2d::Assets");
}

/* method: create of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_create00
static int tolua_custom_bindings_CCClippingNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCClippingNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCClippingNode* tolua_ret = (CCClippingNode*)  CCClippingNode::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCClippingNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_create01
static int tolua_custom_bindings_CCClippingNode_create01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCClippingNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CCNode* pStencil = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   CCClippingNode* tolua_ret = (CCClippingNode*)  CCClippingNode::create(pStencil);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCClippingNode");
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_CCClippingNode_create00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStencil of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_getStencil00
static int tolua_custom_bindings_CCClippingNode_getStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCClippingNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCClippingNode* self = (const CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStencil'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getStencil();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStencil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStencil of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_setStencil00
static int tolua_custom_bindings_CCClippingNode_setStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCClippingNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
  CCNode* pStencil = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStencil'", NULL);
#endif
  {
   self->setStencil(pStencil);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStencil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAlphaThreshold of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_getAlphaThreshold00
static int tolua_custom_bindings_CCClippingNode_getAlphaThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCClippingNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCClippingNode* self = (const CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAlphaThreshold'", NULL);
#endif
  {
   GLfloat tolua_ret = (GLfloat)  self->getAlphaThreshold();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((GLfloat)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"GLfloat");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(GLfloat));
     tolua_pushusertype(tolua_S,tolua_obj,"GLfloat");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAlphaThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAlphaThreshold of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_setAlphaThreshold00
static int tolua_custom_bindings_CCClippingNode_setAlphaThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCClippingNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"GLfloat",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
  GLfloat fAlphaThreshold = *((GLfloat*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAlphaThreshold'", NULL);
#endif
  {
   self->setAlphaThreshold(fAlphaThreshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAlphaThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isInverted of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_isInverted00
static int tolua_custom_bindings_CCClippingNode_isInverted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCClippingNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCClippingNode* self = (const CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isInverted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isInverted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isInverted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setInverted of class  CCClippingNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCClippingNode_setInverted00
static int tolua_custom_bindings_CCClippingNode_setInverted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCClippingNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCClippingNode* self = (CCClippingNode*)  tolua_tousertype(tolua_S,1,0);
  bool bInverted = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setInverted'", NULL);
#endif
  {
   self->setInverted(bInverted);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setInverted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCActionTween */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCActionTween_create00
static int tolua_custom_bindings_CCActionTween_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCActionTween",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float aDuration = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,0));
  float from = ((float)  tolua_tonumber(tolua_S,4,0));
  float to = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   CCActionTween* tolua_ret = (CCActionTween*)  CCActionTween::create(aDuration,key,from,to);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCActionTween");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_create00
static int tolua_custom_bindings_CCDrawNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCDrawNode* tolua_ret = (CCDrawNode*)  CCDrawNode::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDrawNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawDot of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_drawDot00
static int tolua_custom_bindings_CCDrawNode_drawDot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* pos = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  const ccColor4F* color = ((const ccColor4F*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawDot'", NULL);
#endif
  {
   self->drawDot(*pos,radius,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawDot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawSegment of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_drawSegment00
static int tolua_custom_bindings_CCDrawNode_drawSegment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* from = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  const CCPoint* to = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  const ccColor4F* color = ((const ccColor4F*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawSegment'", NULL);
#endif
  {
   self->drawSegment(*from,*to,radius,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawSegment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawQuadraticBezier of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_drawQuadraticBezier00
static int tolua_custom_bindings_CCDrawNode_drawQuadraticBezier00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* from = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  const CCPoint* control = ((const CCPoint*)  tolua_tousertype(tolua_S,3,0));
  const CCPoint* to = ((const CCPoint*)  tolua_tousertype(tolua_S,4,0));
  unsigned int segments = ((unsigned int)  tolua_tonumber(tolua_S,5,0));
  const ccColor4F* color = ((const ccColor4F*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawQuadraticBezier'", NULL);
#endif
  {
   self->drawQuadraticBezier(*from,*control,*to,segments,*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawQuadraticBezier'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_clear00
static int tolua_custom_bindings_CCDrawNode_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_getBlendFunc00
static int tolua_custom_bindings_CCDrawNode_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CCDrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCDrawNode* self = (const CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  CCDrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_CCDrawNode_setBlendFunc00
static int tolua_custom_bindings_CCDrawNode_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CCDrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCDrawNode* self = (CCDrawNode*)  tolua_tousertype(tolua_S,1,0);
  const ccBlendFunc* blendFunc = ((const ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(*blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_new00
static int tolua_custom_bindings_b2Vec2_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2Vec2* tolua_ret = (b2Vec2*)  Mtolua_new((b2Vec2)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_new00_local
static int tolua_custom_bindings_b2Vec2_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2Vec2* tolua_ret = (b2Vec2*)  Mtolua_new((b2Vec2)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_new01
static int tolua_custom_bindings_b2Vec2_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   b2Vec2* tolua_ret = (b2Vec2*)  Mtolua_new((b2Vec2)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Vec2");
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_b2Vec2_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_new01_local
static int tolua_custom_bindings_b2Vec2_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   b2Vec2* tolua_ret = (b2Vec2*)  Mtolua_new((b2Vec2)(x,y));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_b2Vec2_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZero of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_SetZero00
static int tolua_custom_bindings_b2Vec2_SetZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZero'", NULL);
#endif
  {
   self->SetZero();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Set of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2Vec2_Set00
static int tolua_custom_bindings_b2Vec2_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2Vec2",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: x of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_get_b2Vec2_x
static int tolua_get_b2Vec2_x(lua_State* tolua_S)
{
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: x of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_set_b2Vec2_x
static int tolua_set_b2Vec2_x(lua_State* tolua_S)
{
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: y of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_get_b2Vec2_y
static int tolua_get_b2Vec2_y(lua_State* tolua_S)
{
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: y of class  b2Vec2 */
#ifndef TOLUA_DISABLE_tolua_set_b2Vec2_y
static int tolua_set_b2Vec2_y(lua_State* tolua_S)
{
  b2Vec2* self = (b2Vec2*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReactionForce of class  b2DistanceJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2DistanceJoint_GetReactionForce00
static int tolua_custom_bindings_b2DistanceJoint_GetReactionForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2DistanceJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2DistanceJoint* self = (b2DistanceJoint*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReactionForce'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetReactionForce(inv_dt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReactionForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReactionTorque of class  b2DistanceJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2DistanceJoint_GetReactionTorque00
static int tolua_custom_bindings_b2DistanceJoint_GetReactionTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2DistanceJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2DistanceJoint* self = (b2DistanceJoint*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReactionTorque'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetReactionTorque(inv_dt);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReactionTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnchorA of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetAnchorA00
static int tolua_custom_bindings_b2RevoluteJoint_GetAnchorA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnchorA'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetAnchorA();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnchorA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnchorB of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetAnchorB00
static int tolua_custom_bindings_b2RevoluteJoint_GetAnchorB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnchorB'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetAnchorB();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnchorB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalAnchorA of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorA00
static int tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalAnchorA'", NULL);
#endif
  {
   const b2Vec2& tolua_ret = (const b2Vec2&)  self->GetLocalAnchorA();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const b2Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalAnchorA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLocalAnchorB of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorB00
static int tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLocalAnchorB'", NULL);
#endif
  {
   const b2Vec2& tolua_ret = (const b2Vec2&)  self->GetLocalAnchorB();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const b2Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLocalAnchorB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReferenceAngle of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetReferenceAngle00
static int tolua_custom_bindings_b2RevoluteJoint_GetReferenceAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReferenceAngle'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetReferenceAngle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReferenceAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetJointAngle of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetJointAngle00
static int tolua_custom_bindings_b2RevoluteJoint_GetJointAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetJointAngle'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetJointAngle();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetJointAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetJointSpeed of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetJointSpeed00
static int tolua_custom_bindings_b2RevoluteJoint_GetJointSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetJointSpeed'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetJointSpeed();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetJointSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLimitEnabled of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_IsLimitEnabled00
static int tolua_custom_bindings_b2RevoluteJoint_IsLimitEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLimitEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLimitEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLimitEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableLimit of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_EnableLimit00
static int tolua_custom_bindings_b2RevoluteJoint_EnableLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2RevoluteJoint* self = (b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableLimit'", NULL);
#endif
  {
   self->EnableLimit(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLowerLimit of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetLowerLimit00
static int tolua_custom_bindings_b2RevoluteJoint_GetLowerLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLowerLimit'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetLowerLimit();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLowerLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUpperLimit of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetUpperLimit00
static int tolua_custom_bindings_b2RevoluteJoint_GetUpperLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUpperLimit'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetUpperLimit();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUpperLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLimits of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_SetLimits00
static int tolua_custom_bindings_b2RevoluteJoint_SetLimits00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2RevoluteJoint* self = (b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float lower = ((float)  tolua_tonumber(tolua_S,2,0));
  float upper = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLimits'", NULL);
#endif
  {
   self->SetLimits(lower,upper);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLimits'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMotorEnabled of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_IsMotorEnabled00
static int tolua_custom_bindings_b2RevoluteJoint_IsMotorEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMotorEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMotorEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMotorEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableMotor of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_EnableMotor00
static int tolua_custom_bindings_b2RevoluteJoint_EnableMotor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2RevoluteJoint* self = (b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableMotor'", NULL);
#endif
  {
   self->EnableMotor(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableMotor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMotorSpeed of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_SetMotorSpeed00
static int tolua_custom_bindings_b2RevoluteJoint_SetMotorSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2RevoluteJoint* self = (b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float speed = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMotorSpeed'", NULL);
#endif
  {
   self->SetMotorSpeed(speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMotorSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMotorSpeed of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetMotorSpeed00
static int tolua_custom_bindings_b2RevoluteJoint_GetMotorSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMotorSpeed'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetMotorSpeed();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMotorSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxMotorTorque of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_SetMaxMotorTorque00
static int tolua_custom_bindings_b2RevoluteJoint_SetMaxMotorTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  b2RevoluteJoint* self = (b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float torque = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxMotorTorque'", NULL);
#endif
  {
   self->SetMaxMotorTorque(torque);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxMotorTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxMotorTorque of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetMaxMotorTorque00
static int tolua_custom_bindings_b2RevoluteJoint_GetMaxMotorTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxMotorTorque'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetMaxMotorTorque();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxMotorTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReactionForce of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetReactionForce00
static int tolua_custom_bindings_b2RevoluteJoint_GetReactionForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReactionForce'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->GetReactionForce(inv_dt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReactionForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReactionTorque of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetReactionTorque00
static int tolua_custom_bindings_b2RevoluteJoint_GetReactionTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReactionTorque'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetReactionTorque(inv_dt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReactionTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMotorTorque of class  b2RevoluteJoint */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RevoluteJoint_GetMotorTorque00
static int tolua_custom_bindings_b2RevoluteJoint_GetMotorTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const b2RevoluteJoint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2RevoluteJoint* self = (const b2RevoluteJoint*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMotorTorque'", NULL);
#endif
  {
   float32 tolua_ret = (float32)  self->GetMotorTorque(inv_dt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((float32)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(float32));
     tolua_pushusertype(tolua_S,tolua_obj,"float32");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMotorTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p1 of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_get_b2RayCastInput_p1
static int tolua_get_b2RayCastInput_p1(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p1'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->p1,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p1 of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_set_b2RayCastInput_p1
static int tolua_set_b2RayCastInput_p1(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p1'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p1 = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: p2 of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_get_b2RayCastInput_p2
static int tolua_get_b2RayCastInput_p2(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p2'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->p2,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: p2 of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_set_b2RayCastInput_p2
static int tolua_set_b2RayCastInput_p2(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'p2'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->p2 = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: maxFraction of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_get_b2RayCastInput_maxFraction
static int tolua_get_b2RayCastInput_maxFraction(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxFraction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->maxFraction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: maxFraction of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_set_b2RayCastInput_maxFraction
static int tolua_set_b2RayCastInput_maxFraction(lua_State* tolua_S)
{
  b2RayCastInput* self = (b2RayCastInput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'maxFraction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->maxFraction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RayCastInput_new00
static int tolua_custom_bindings_b2RayCastInput_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2RayCastInput",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2RayCastInput* tolua_ret = (b2RayCastInput*)  Mtolua_new((b2RayCastInput)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RayCastInput");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  b2RayCastInput */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RayCastInput_new00_local
static int tolua_custom_bindings_b2RayCastInput_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2RayCastInput",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2RayCastInput* tolua_ret = (b2RayCastInput*)  Mtolua_new((b2RayCastInput)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RayCastInput");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: normal of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_get_b2RayCastOutput_normal
static int tolua_get_b2RayCastOutput_normal(lua_State* tolua_S)
{
  b2RayCastOutput* self = (b2RayCastOutput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->normal,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: normal of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_set_b2RayCastOutput_normal
static int tolua_set_b2RayCastOutput_normal(lua_State* tolua_S)
{
  b2RayCastOutput* self = (b2RayCastOutput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->normal = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fraction of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_get_b2RayCastOutput_fraction
static int tolua_get_b2RayCastOutput_fraction(lua_State* tolua_S)
{
  b2RayCastOutput* self = (b2RayCastOutput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fraction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fraction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fraction of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_set_b2RayCastOutput_fraction
static int tolua_set_b2RayCastOutput_fraction(lua_State* tolua_S)
{
  b2RayCastOutput* self = (b2RayCastOutput*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fraction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fraction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RayCastOutput_new00
static int tolua_custom_bindings_b2RayCastOutput_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2RayCastOutput",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2RayCastOutput* tolua_ret = (b2RayCastOutput*)  Mtolua_new((b2RayCastOutput)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RayCastOutput");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  b2RayCastOutput */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_b2RayCastOutput_new00_local
static int tolua_custom_bindings_b2RayCastOutput_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"b2RayCastOutput",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   b2RayCastOutput* tolua_ret = (b2RayCastOutput*)  Mtolua_new((b2RayCastOutput)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RayCastOutput");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__clear00
static int tolua_custom_bindings_vector_string__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__size00
static int tolua_custom_bindings_vector_string__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<string>* self = (const vector<string>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string___geti00
static int tolua_custom_bindings_vector_string___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<string>* self = (const vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const string tolua_ret = (const string)  self->operator[](index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string___seti00
static int tolua_custom_bindings_vector_string___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  string tolua_value = ((string)  tolua_tocppstring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string___geti01
static int tolua_custom_bindings_vector_string___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   string tolua_ret = (string)  self->operator[](index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_vector_string___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__push_back00
static int tolua_custom_bindings_vector_string__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
  string val = ((string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__new00
static int tolua_custom_bindings_vector_string__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<string>* tolua_ret = (vector<string>*)  Mtolua_new((vector<string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<string>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__new00_local
static int tolua_custom_bindings_vector_string__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<string>* tolua_ret = (vector<string>*)  Mtolua_new((vector<string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<string>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  vector<string> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_string__delete00
static int tolua_custom_bindings_vector_string__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<string>* self = (vector<string>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__clear00
static int tolua_custom_bindings_vector_CCPoint__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<CCPoint>* self = (vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__size00
static int tolua_custom_bindings_vector_CCPoint__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<CCPoint>* self = (const vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint___geti00
static int tolua_custom_bindings_vector_CCPoint___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<CCPoint>* self = (const vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const CCPoint tolua_ret = (const CCPoint)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"const CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint___seti00
static int tolua_custom_bindings_vector_CCPoint___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<CCPoint>* self = (vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  CCPoint tolua_value = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint___geti01
static int tolua_custom_bindings_vector_CCPoint___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  vector<CCPoint>* self = (vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_vector_CCPoint___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__push_back00
static int tolua_custom_bindings_vector_CCPoint__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<CCPoint>* self = (vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
  CCPoint val = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__new00
static int tolua_custom_bindings_vector_CCPoint__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<CCPoint>* tolua_ret = (vector<CCPoint>*)  Mtolua_new((vector<CCPoint>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<CCPoint>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__new00_local
static int tolua_custom_bindings_vector_CCPoint__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<CCPoint>* tolua_ret = (vector<CCPoint>*)  Mtolua_new((vector<CCPoint>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<CCPoint>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  vector<CCPoint> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_CCPoint__delete00
static int tolua_custom_bindings_vector_CCPoint__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<CCPoint>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<CCPoint>* self = (vector<CCPoint>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__clear00
static int tolua_custom_bindings_vector_b2Vec2__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<b2Vec2>* self = (vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__size00
static int tolua_custom_bindings_vector_b2Vec2__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<b2Vec2>* self = (const vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2___geti00
static int tolua_custom_bindings_vector_b2Vec2___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<b2Vec2>* self = (const vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const b2Vec2 tolua_ret = (const b2Vec2)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"const b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2___seti00
static int tolua_custom_bindings_vector_b2Vec2___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<b2Vec2>* self = (vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  b2Vec2 tolua_value = *((b2Vec2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2___geti01
static int tolua_custom_bindings_vector_b2Vec2___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  vector<b2Vec2>* self = (vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_vector_b2Vec2___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__push_back00
static int tolua_custom_bindings_vector_b2Vec2__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<b2Vec2>* self = (vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2 val = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__new00
static int tolua_custom_bindings_vector_b2Vec2__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<b2Vec2>* tolua_ret = (vector<b2Vec2>*)  Mtolua_new((vector<b2Vec2>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<b2Vec2>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__new00_local
static int tolua_custom_bindings_vector_b2Vec2__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<b2Vec2>* tolua_ret = (vector<b2Vec2>*)  Mtolua_new((vector<b2Vec2>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<b2Vec2>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  vector<b2Vec2> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_b2Vec2__delete00
static int tolua_custom_bindings_vector_b2Vec2__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<b2Vec2>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<b2Vec2>* self = (vector<b2Vec2>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__clear00
static int tolua_custom_bindings_vector_pix2d__BezierCurve__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__size00
static int tolua_custom_bindings_vector_pix2d__BezierCurve__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<pix2d::BezierCurve>* self = (const vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   int tolua_ret = (int)  self->size();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve___geti00
static int tolua_custom_bindings_vector_pix2d__BezierCurve___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const vector<pix2d::BezierCurve>* self = (const vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const pix2d::BezierCurve tolua_ret = (const pix2d::BezierCurve)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((pix2d::BezierCurve)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"const pix2d::BezierCurve");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(const pix2d::BezierCurve));
     tolua_pushusertype(tolua_S,tolua_obj,"const pix2d::BezierCurve");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.geti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator&[] of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve___seti00
static int tolua_custom_bindings_vector_pix2d__BezierCurve___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"pix2d::BezierCurve",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  pix2d::BezierCurve tolua_value = *((pix2d::BezierCurve*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator&[]'", NULL);
#endif
  self->operator[](index) =  tolua_value;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.seti'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator[] of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve___geti01
static int tolua_custom_bindings_vector_pix2d__BezierCurve___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   pix2d::BezierCurve tolua_ret = (pix2d::BezierCurve)  self->operator[](index);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((pix2d::BezierCurve)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"pix2d::BezierCurve");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(pix2d::BezierCurve));
     tolua_pushusertype(tolua_S,tolua_obj,"pix2d::BezierCurve");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_vector_pix2d__BezierCurve___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__push_back00
static int tolua_custom_bindings_vector_pix2d__BezierCurve__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"pix2d::BezierCurve",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
  pix2d::BezierCurve val = *((pix2d::BezierCurve*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'push_back'", NULL);
#endif
  {
   self->push_back(val);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'push_back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__new00
static int tolua_custom_bindings_vector_pix2d__BezierCurve__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<pix2d::BezierCurve>* tolua_ret = (vector<pix2d::BezierCurve>*)  Mtolua_new((vector<pix2d::BezierCurve>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<pix2d::BezierCurve>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__new00_local
static int tolua_custom_bindings_vector_pix2d__BezierCurve__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   vector<pix2d::BezierCurve>* tolua_ret = (vector<pix2d::BezierCurve>*)  Mtolua_new((vector<pix2d::BezierCurve>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"vector<pix2d::BezierCurve>");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  vector<pix2d::BezierCurve> */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_vector_pix2d__BezierCurve__delete00
static int tolua_custom_bindings_vector_pix2d__BezierCurve__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"vector<pix2d::BezierCurve>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<pix2d::BezierCurve>* self = (vector<pix2d::BezierCurve>*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  AppDelegate */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_AppDelegate_registerScriptHandler00
static int tolua_custom_bindings_AppDelegate_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AppDelegate",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AppDelegate* self = (AppDelegate*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(lo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_getInstance00
static int tolua_custom_bindings_pix2d_Native_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::Native* tolua_ret = (pix2d::Native*)  pix2d::Native::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Native");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInstance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: openURL of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_openURL00
static int tolua_custom_bindings_pix2d_Native_openURL00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
  const char* pszUrl = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'openURL'", NULL);
#endif
  {
   self->openURL(pszUrl);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'openURL'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: hideAd of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_hideAd00
static int tolua_custom_bindings_pix2d_Native_hideAd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'hideAd'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->hideAd();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'hideAd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: showAd of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_showAd00
static int tolua_custom_bindings_pix2d_Native_showAd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'showAd'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->showAd();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'showAd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: exitApp of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_exitApp00
static int tolua_custom_bindings_pix2d_Native_exitApp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'exitApp'", NULL);
#endif
  {
   self->exitApp();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'exitApp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerAdMobScriptHandler of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_registerAdMobScriptHandler00
static int tolua_custom_bindings_pix2d_Native_registerAdMobScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerAdMobScriptHandler'", NULL);
#endif
  {
   self->registerAdMobScriptHandler(lo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerAdMobScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterAdMobScriptHandler of class  pix2d::Native */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Native_unregisterAdMobScriptHandler00
static int tolua_custom_bindings_pix2d_Native_unregisterAdMobScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Native",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Native* self = (pix2d::Native*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterAdMobScriptHandler'", NULL);
#endif
  {
   self->unregisterAdMobScriptHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterAdMobScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  pix2d::BezierCurve */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierCurve_pointAt00
static int tolua_custom_bindings_pix2d_BezierCurve_pointAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierCurve",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierCurve* self = (const pix2d::BezierCurve*)  tolua_tousertype(tolua_S,1,0);
  double t = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAt'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->pointAt(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: point of class  pix2d::BezierCurve */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierCurve_point00
static int tolua_custom_bindings_pix2d_BezierCurve_point00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierCurve",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierCurve* self = (const pix2d::BezierCurve*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'point'", NULL);
#endif
  {
   const CCPoint& tolua_ret = (const CCPoint&)  self->point(i);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CCPoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'point'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: order of class  pix2d::BezierCurve */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierCurve_order00
static int tolua_custom_bindings_pix2d_BezierCurve_order00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierCurve",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierCurve* self = (const pix2d::BezierCurve*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'order'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->order();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'order'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialPoint of class  pix2d::BezierCurve */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierCurve_initialPoint00
static int tolua_custom_bindings_pix2d_BezierCurve_initialPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierCurve",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierCurve* self = (const pix2d::BezierCurve*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->initialPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: finalPoint of class  pix2d::BezierCurve */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierCurve_finalPoint00
static int tolua_custom_bindings_pix2d_BezierCurve_finalPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierCurve",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierCurve* self = (const pix2d::BezierCurve*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'finalPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->finalPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'finalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::LineBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_LineBezier_new00
static int tolua_custom_bindings_pix2d_LineBezier_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::LineBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   pix2d::LineBezier* tolua_ret = (pix2d::LineBezier*)  Mtolua_new((pix2d::LineBezier)(c0,c1));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::LineBezier");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::LineBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_LineBezier_new00_local
static int tolua_custom_bindings_pix2d_LineBezier_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::LineBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  {
   pix2d::LineBezier* tolua_ret = (pix2d::LineBezier*)  Mtolua_new((pix2d::LineBezier)(c0,c1));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::LineBezier");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::QuadBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_QuadBezier_new00
static int tolua_custom_bindings_pix2d_QuadBezier_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::QuadBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint c2 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  {
   pix2d::QuadBezier* tolua_ret = (pix2d::QuadBezier*)  Mtolua_new((pix2d::QuadBezier)(c0,c1,c2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::QuadBezier");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::QuadBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_QuadBezier_new00_local
static int tolua_custom_bindings_pix2d_QuadBezier_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::QuadBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint c2 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  {
   pix2d::QuadBezier* tolua_ret = (pix2d::QuadBezier*)  Mtolua_new((pix2d::QuadBezier)(c0,c1,c2));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::QuadBezier");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::CubicBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CubicBezier_new00
static int tolua_custom_bindings_pix2d_CubicBezier_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CubicBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint c2 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  CCPoint c3 = *((CCPoint*)  tolua_tousertype(tolua_S,5,0));
  {
   pix2d::CubicBezier* tolua_ret = (pix2d::CubicBezier*)  Mtolua_new((pix2d::CubicBezier)(c0,c1,c2,c3));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::CubicBezier");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::CubicBezier */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CubicBezier_new00_local
static int tolua_custom_bindings_pix2d_CubicBezier_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CubicBezier",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCPoint c0 = *((CCPoint*)  tolua_tousertype(tolua_S,2,0));
  CCPoint c1 = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint c2 = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  CCPoint c3 = *((CCPoint*)  tolua_tousertype(tolua_S,5,0));
  {
   pix2d::CubicBezier* tolua_ret = (pix2d::CubicBezier*)  Mtolua_new((pix2d::CubicBezier)(c0,c1,c2,c3));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::CubicBezier");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_new00
static int tolua_custom_bindings_pix2d_BezierPath_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::BezierPath* tolua_ret = (pix2d::BezierPath*)  Mtolua_new((pix2d::BezierPath)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::BezierPath");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_new00_local
static int tolua_custom_bindings_pix2d_BezierPath_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::BezierPath* tolua_ret = (pix2d::BezierPath*)  Mtolua_new((pix2d::BezierPath)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::BezierPath");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: close of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_close00
static int tolua_custom_bindings_pix2d_BezierPath_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::BezierPath* self = (pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   self->close(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: closed of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_closed00
static int tolua_custom_bindings_pix2d_BezierPath_closed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierPath* self = (const pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'closed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->closed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'closed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: empty of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_empty00
static int tolua_custom_bindings_pix2d_BezierPath_empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierPath* self = (const pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'empty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: initialPoint of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_initialPoint00
static int tolua_custom_bindings_pix2d_BezierPath_initialPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierPath* self = (const pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'initialPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->initialPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'initialPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: finalPoint of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_finalPoint00
static int tolua_custom_bindings_pix2d_BezierPath_finalPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierPath* self = (const pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'finalPoint'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->finalPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'finalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  pix2d::BezierPath */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BezierPath_pointAt00
static int tolua_custom_bindings_pix2d_BezierPath_pointAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::BezierPath",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BezierPath* self = (const pix2d::BezierPath*)  tolua_tousertype(tolua_S,1,0);
  double t = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pointAt'", NULL);
#endif
  {
   CCPoint tolua_ret = (CCPoint)  self->pointAt(t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CocosBuilderLua */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CocosBuilderLua_create00
static int tolua_custom_bindings_pix2d_CocosBuilderLua_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CocosBuilderLua",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !toluafix_isfunction(tolua_S,4,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* filename = ((const char*)  tolua_tostring(tolua_S,2,0));
  LUA_FUNCTION assignMemberHandler = (  toluafix_ref_function(tolua_S,3,0));
  LUA_FUNCTION animationHandler = (  toluafix_ref_function(tolua_S,4,0));
  {
   CCNode* tolua_ret = (CCNode*)  pix2d::CocosBuilderLua::create(filename,assignMemberHandler,animationHandler);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerLoaders of class  pix2d::CocosBuilderLua */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CocosBuilderLua_registerLoaders00
static int tolua_custom_bindings_pix2d_CocosBuilderLua_registerLoaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CocosBuilderLua",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::CocosBuilderLua::registerLoaders();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerLoaders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pauseSchedulerAndActions of class  pix2d::NodeUtil */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_NodeUtil_pauseSchedulerAndActions00
static int tolua_custom_bindings_pix2d_NodeUtil_pauseSchedulerAndActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::NodeUtil",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::NodeUtil::pauseSchedulerAndActions(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pauseSchedulerAndActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resumeSchedulerAndActions of class  pix2d::NodeUtil */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_NodeUtil_resumeSchedulerAndActions00
static int tolua_custom_bindings_pix2d_NodeUtil_resumeSchedulerAndActions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::NodeUtil",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::NodeUtil::resumeSchedulerAndActions(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resumeSchedulerAndActions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::DrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_DrawNode_create00
static int tolua_custom_bindings_pix2d_DrawNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::DrawNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::DrawNode* tolua_ret = (pix2d::DrawNode*)  pix2d::DrawNode::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::DrawNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawPolygon of class  pix2d::DrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_DrawNode_drawPolygon00
static int tolua_custom_bindings_pix2d_DrawNode_drawPolygon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::DrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<CCPoint>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::DrawNode* self = (pix2d::DrawNode*)  tolua_tousertype(tolua_S,1,0);
  vector<CCPoint>* points = ((vector<CCPoint>*)  tolua_tousertype(tolua_S,2,0));
  const ccColor4F* fillColor = ((const ccColor4F*)  tolua_tousertype(tolua_S,3,0));
  float borderWidth = ((float)  tolua_tonumber(tolua_S,4,0));
  const ccColor4F* borderColor = ((const ccColor4F*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawPolygon'", NULL);
#endif
  {
   self->drawPolygon(*points,*fillColor,borderWidth,*borderColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawPolygon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: drawCircle of class  pix2d::DrawNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_DrawNode_drawCircle00
static int tolua_custom_bindings_pix2d_DrawNode_drawCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::DrawNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const ccColor4F",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,7,&tolua_err) || !tolua_isusertype(tolua_S,7,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::DrawNode* self = (pix2d::DrawNode*)  tolua_tousertype(tolua_S,1,0);
  const CCPoint* center = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  float precision = ((float)  tolua_tonumber(tolua_S,4,0));
  float borderWidth = ((float)  tolua_tonumber(tolua_S,5,0));
  const ccColor4F* fillColor = ((const ccColor4F*)  tolua_tousertype(tolua_S,6,0));
  const ccColor4F* pathColor = ((const ccColor4F*)  tolua_tousertype(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'drawCircle'", NULL);
#endif
  {
   self->drawCircle(*center,radius,precision,borderWidth,*fillColor,*pathColor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'drawCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: capture of class  pix2d::PostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PostProcessing_capture00
static int tolua_custom_bindings_pix2d_PostProcessing_capture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PostProcessing",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PostProcessing* self = (pix2d::PostProcessing*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'capture'", NULL);
#endif
  {
   CCRenderTexture* tolua_ret = (CCRenderTexture*)  self->capture();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCRenderTexture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'capture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameBuffer of class  pix2d::PostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PostProcessing_getFrameBuffer00
static int tolua_custom_bindings_pix2d_PostProcessing_getFrameBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PostProcessing",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PostProcessing* self = (pix2d::PostProcessing*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameBuffer'", NULL);
#endif
  {
   CCRenderTexture* tolua_ret = (CCRenderTexture*)  self->getFrameBuffer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCRenderTexture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: refresh of class  pix2d::PostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PostProcessing_refresh00
static int tolua_custom_bindings_pix2d_PostProcessing_refresh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PostProcessing",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PostProcessing* self = (pix2d::PostProcessing*)  tolua_tousertype(tolua_S,1,0);
  bool clean = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refresh'", NULL);
#endif
  {
   self->refresh(clean);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refresh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clear of class  pix2d::PostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PostProcessing_clear00
static int tolua_custom_bindings_pix2d_PostProcessing_clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PostProcessing",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccColor4F",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PostProcessing* self = (pix2d::PostProcessing*)  tolua_tousertype(tolua_S,1,0);
  const ccColor4F* color = ((const ccColor4F*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clear'", NULL);
#endif
  {
   self->clear(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getFrameBuffer of class  pix2d::DoublePostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_DoublePostProcessing_getFrameBuffer00
static int tolua_custom_bindings_pix2d_DoublePostProcessing_getFrameBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::DoublePostProcessing",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::DoublePostProcessing* self = (pix2d::DoublePostProcessing*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getFrameBuffer'", NULL);
#endif
  {
   CCRenderTexture* tolua_ret = (CCRenderTexture*)  self->getFrameBuffer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCRenderTexture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getFrameBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: refresh of class  pix2d::DoublePostProcessing */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_DoublePostProcessing_refresh00
static int tolua_custom_bindings_pix2d_DoublePostProcessing_refresh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::DoublePostProcessing",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::DoublePostProcessing* self = (pix2d::DoublePostProcessing*)  tolua_tousertype(tolua_S,1,0);
  bool clean = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refresh'", NULL);
#endif
  {
   self->refresh(clean);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refresh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Pixelation */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Pixelation_create00
static int tolua_custom_bindings_pix2d_Pixelation_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Pixelation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,3,0));
  float width = ((float)  tolua_tonumber(tolua_S,4,0));
  float height = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   pix2d::Pixelation* tolua_ret = (pix2d::Pixelation*)  pix2d::Pixelation::create(node,*size,width,height);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Pixelation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Grayscale */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Grayscale_create00
static int tolua_custom_bindings_pix2d_Grayscale_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Grayscale",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCSize",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,3,0));
  {
   pix2d::Grayscale* tolua_ret = (pix2d::Grayscale*)  pix2d::Grayscale::create(node,*size);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Grayscale");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::FastBlur */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_FastBlur_create00
static int tolua_custom_bindings_pix2d_FastBlur_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::FastBlur",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   pix2d::FastBlur* tolua_ret = (pix2d::FastBlur*)  pix2d::FastBlur::create(node,*size,radius);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::FastBlur");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::GaussianBlur */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_GaussianBlur_create00
static int tolua_custom_bindings_pix2d_GaussianBlur_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::GaussianBlur",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const CCSize",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  const CCSize* size = ((const CCSize*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   pix2d::GaussianBlur* tolua_ret = (pix2d::GaussianBlur*)  pix2d::GaussianBlur::create(node,*size,radius);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::GaussianBlur");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_new00
static int tolua_custom_bindings_pix2d_Graph_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Graph",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int width = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int height = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::Graph* tolua_ret = (pix2d::Graph*)  Mtolua_new((pix2d::Graph)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Graph");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_new00_local
static int tolua_custom_bindings_pix2d_Graph_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Graph",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned int width = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int height = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::Graph* tolua_ret = (pix2d::Graph*)  Mtolua_new((pix2d::Graph)(width,height));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Graph");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: update of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_update00
static int tolua_custom_bindings_pix2d_Graph_update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Graph",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Graph* self = (pix2d::Graph*)  tolua_tousertype(tolua_S,1,0);
  unsigned int i = ((unsigned int)  tolua_tonumber(tolua_S,2,0));
  unsigned int j = ((unsigned int)  tolua_tonumber(tolua_S,3,0));
  const pix2d::Graph::NodeType type = ((const pix2d::Graph::NodeType) (int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'update'", NULL);
#endif
  {
   self->update(i,j,type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: solve of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_solve00
static int tolua_custom_bindings_pix2d_Graph_solve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Graph",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"vector<b2Vec2>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Graph* self = (pix2d::Graph*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* s = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  const b2Vec2* d = ((const b2Vec2*)  tolua_tousertype(tolua_S,3,0));
  vector<b2Vec2>* outputPath = ((vector<b2Vec2>*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'solve'", NULL);
#endif
  {
   int tolua_ret = (int)  self->solve(*s,*d,*outputPath);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'solve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSize of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_getSize00
static int tolua_custom_bindings_pix2d_Graph_getSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Graph",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Graph* self = (const pix2d::Graph*)  tolua_tousertype(tolua_S,1,0);
  float width = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSize'", NULL);
#endif
  {
   self->getSize(&width,&height);
   tolua_pushnumber(tolua_S,(lua_Number)width);
   tolua_pushnumber(tolua_S,(lua_Number)height);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dump of class  pix2d::Graph */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Graph_dump00
static int tolua_custom_bindings_pix2d_Graph_dump00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Graph",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Graph* self = (pix2d::Graph*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dump'", NULL);
#endif
  {
   self->dump();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dump'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: font of class  pix2d::Assets */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Assets_font00
static int tolua_custom_bindings_pix2d_Assets_font00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Assets",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Assets::FontTag tag = ((pix2d::Assets::FontTag) (int)  tolua_tonumber(tolua_S,2,0));
  {
   const char* tolua_ret = (const char*)  pix2d::Assets::font(tag);
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'font'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: fontSize of class  pix2d::Assets */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Assets_fontSize00
static int tolua_custom_bindings_pix2d_Assets_fontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Assets",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Assets::FontSizeTag tag = ((pix2d::Assets::FontSizeTag) (int)  tolua_tonumber(tolua_S,2,0));
  {
   float tolua_ret = (float)  pix2d::Assets::fontSize(tag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'fontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: writeTextFile of class  pix2d::Assets */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Assets_writeTextFile00
static int tolua_custom_bindings_pix2d_Assets_writeTextFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Assets",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const string filename = ((const string)  tolua_tocppstring(tolua_S,2,0));
  const string text = ((const string)  tolua_tocppstring(tolua_S,3,0));
  {
   bool tolua_ret = (bool)  pix2d::Assets::writeTextFile(filename,text);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
   tolua_pushcppstring(tolua_S,(const char*)text);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'writeTextFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: readTextFile of class  pix2d::Assets */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Assets_readTextFile00
static int tolua_custom_bindings_pix2d_Assets_readTextFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Assets",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const string filename = ((const string)  tolua_tocppstring(tolua_S,2,0));
  bool encrypted = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   string tolua_ret = (string)  pix2d::Assets::readTextFile(filename,encrypted);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'readTextFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: load of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_load00
static int tolua_custom_bindings_pix2d_TouchGrabber_load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
  const string filename = ((const string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'load'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->load(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: save of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_save00
static int tolua_custom_bindings_pix2d_TouchGrabber_save00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
  const string filename = ((const string)  tolua_tocppstring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'save'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->save(filename);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushcppstring(tolua_S,(const char*)filename);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'save'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: play of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_play00
static int tolua_custom_bindings_pix2d_TouchGrabber_play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'play'", NULL);
#endif
  {
   self->play();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: stop of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_stop00
static int tolua_custom_bindings_pix2d_TouchGrabber_stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'stop'", NULL);
#endif
  {
   self->stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: record of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_record00
static int tolua_custom_bindings_pix2d_TouchGrabber_record00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'record'", NULL);
#endif
  {
   self->record(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'record'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isRecording of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_isRecording00
static int tolua_custom_bindings_pix2d_TouchGrabber_isRecording00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isRecording'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isRecording();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isRecording'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPlaying of class  pix2d::TouchGrabber */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchGrabber_isPlaying00
static int tolua_custom_bindings_pix2d_TouchGrabber_isPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchGrabber",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchGrabber* self = (pix2d::TouchGrabber*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::OpacityNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_OpacityNode_create00
static int tolua_custom_bindings_pix2d_OpacityNode_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::OpacityNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::OpacityNode* tolua_ret = (pix2d::OpacityNode*)  pix2d::OpacityNode::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::OpacityNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacity of class  pix2d::OpacityNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_OpacityNode_setOpacity00
static int tolua_custom_bindings_pix2d_OpacityNode_setOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::OpacityNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::OpacityNode* self = (pix2d::OpacityNode*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacity'", NULL);
#endif
  {
   self->setOpacity(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CustomMenuItem */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomMenuItem_create00
static int tolua_custom_bindings_pix2d_CustomMenuItem_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CustomMenuItem",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"CCNode",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCNode* normalSprite = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  CCNode* selectedSprite = ((CCNode*)  tolua_tousertype(tolua_S,3,0));
  CCNode* disabledSprite = ((CCNode*)  tolua_tousertype(tolua_S,4,NULL));
  {
   pix2d::CustomMenuItem* tolua_ret = (pix2d::CustomMenuItem*)  pix2d::CustomMenuItem::create(normalSprite,selectedSprite,disabledSprite);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomMenuItem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerScriptHandler of class  pix2d::CustomMenuItem */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomMenuItem_registerScriptHandler00
static int tolua_custom_bindings_pix2d_CustomMenuItem_registerScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::CustomMenuItem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::CustomMenuItem* self = (pix2d::CustomMenuItem*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerScriptHandler'", NULL);
#endif
  {
   self->registerScriptHandler(lo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CustomLabelTTF */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomLabelTTF_create00
static int tolua_custom_bindings_pix2d_CustomLabelTTF_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CustomLabelTTF",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::CustomLabelTTF* tolua_ret = (pix2d::CustomLabelTTF*)  pix2d::CustomLabelTTF::create();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomLabelTTF");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CustomMenuItemFont */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomMenuItemFont_create00
static int tolua_custom_bindings_pix2d_CustomMenuItemFont_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CustomMenuItemFont",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* text = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* fontname = ((const char*)  tolua_tostring(tolua_S,3,0));
  unsigned int fontsize = ((unsigned int)  tolua_tonumber(tolua_S,4,0));
  {
   pix2d::CustomMenuItemFont* tolua_ret = (pix2d::CustomMenuItemFont*)  pix2d::CustomMenuItemFont::create(text,fontname,fontsize);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomMenuItemFont");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CustomMenuItemToggle */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomMenuItemToggle_create00
static int tolua_custom_bindings_pix2d_CustomMenuItemToggle_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CustomMenuItemToggle",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCMenuItem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCMenuItem* item = ((CCMenuItem*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::CustomMenuItemToggle* tolua_ret = (pix2d::CustomMenuItemToggle*)  pix2d::CustomMenuItemToggle::create(item);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomMenuItemToggle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_create00
static int tolua_custom_bindings_pix2d_TextureSprite_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"vector<CCPoint>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string texFileName = ((string)  tolua_tocppstring(tolua_S,2,0));
  vector<CCPoint>* vertices = ((vector<CCPoint>*)  tolua_tousertype(tolua_S,3,0));
  {
   pix2d::TextureSprite* tolua_ret = (pix2d::TextureSprite*)  pix2d::TextureSprite::create(texFileName,*vertices);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::TextureSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithAABB of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_createWithAABB00
static int tolua_custom_bindings_pix2d_TextureSprite_createWithAABB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"CCPoint",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  string texFileName = ((string)  tolua_tocppstring(tolua_S,2,0));
  CCPoint upperBound = *((CCPoint*)  tolua_tousertype(tolua_S,3,0));
  CCPoint lowerBound = *((CCPoint*)  tolua_tousertype(tolua_S,4,0));
  {
   pix2d::TextureSprite* tolua_ret = (pix2d::TextureSprite*)  pix2d::TextureSprite::createWithAABB(texFileName,upperBound,lowerBound);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::TextureSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithAABB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: translateTexCoord of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_translateTexCoord00
static int tolua_custom_bindings_pix2d_TextureSprite_translateTexCoord00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TextureSprite* self = (pix2d::TextureSprite*)  tolua_tousertype(tolua_S,1,0);
  float u = ((float)  tolua_tonumber(tolua_S,2,0));
  float v = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'translateTexCoord'", NULL);
#endif
  {
   self->translateTexCoord(u,v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'translateTexCoord'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setRepeat of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_setRepeat00
static int tolua_custom_bindings_pix2d_TextureSprite_setRepeat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TextureSprite* self = (pix2d::TextureSprite*)  tolua_tousertype(tolua_S,1,0);
  bool horizontal = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool vertical = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setRepeat'", NULL);
#endif
  {
   self->setRepeat(horizontal,vertical);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setRepeat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTextureSize of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_getTextureSize00
static int tolua_custom_bindings_pix2d_TextureSprite_getTextureSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::TextureSprite* self = (const pix2d::TextureSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextureSize'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->getTextureSize();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextureSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_setBlendFunc00
static int tolua_custom_bindings_pix2d_TextureSprite_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TextureSprite* self = (pix2d::TextureSprite*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc blendFunc = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(blendFunc);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  pix2d::TextureSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureSprite_getBlendFunc00
static int tolua_custom_bindings_pix2d_TextureSprite_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TextureSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TextureSprite* self = (pix2d::TextureSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::ActionTweenLua */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ActionTweenLua_create00
static int tolua_custom_bindings_pix2d_ActionTweenLua_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ActionTweenLua",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !toluafix_isfunction(tolua_S,6,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float aDuration = ((float)  tolua_tonumber(tolua_S,2,0));
  const char* key = ((const char*)  tolua_tostring(tolua_S,3,0));
  float from = ((float)  tolua_tonumber(tolua_S,4,0));
  float to = ((float)  tolua_tonumber(tolua_S,5,0));
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,6,0));
  {
   pix2d::ActionTweenLua* tolua_ret = (pix2d::ActionTweenLua*)  pix2d::ActionTweenLua::create(aDuration,key,from,to,handler);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::ActionTweenLua");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithSpriteFrameName of class  pix2d::CustomSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomSprite_createWithSpriteFrameName00
static int tolua_custom_bindings_pix2d_CustomSprite_createWithSpriteFrameName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CustomSprite",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* pszSpriteFrameName = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   pix2d::CustomSprite* tolua_ret = (pix2d::CustomSprite*)  pix2d::CustomSprite::createWithSpriteFrameName(pszSpriteFrameName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithSpriteFrameName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerTweenActionHandler of class  pix2d::CustomSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomSprite_registerTweenActionHandler00
static int tolua_custom_bindings_pix2d_CustomSprite_registerTweenActionHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::CustomSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::CustomSprite* self = (pix2d::CustomSprite*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerTweenActionHandler'", NULL);
#endif
  {
   self->registerTweenActionHandler(lo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerTweenActionHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterTweenActionHandler of class  pix2d::CustomSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomSprite_unregisterTweenActionHandler00
static int tolua_custom_bindings_pix2d_CustomSprite_unregisterTweenActionHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::CustomSprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::CustomSprite* self = (pix2d::CustomSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterTweenActionHandler'", NULL);
#endif
  {
   self->unregisterTweenActionHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterTweenActionHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setQuad of class  pix2d::CustomSprite */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CustomSprite_setQuad00
static int tolua_custom_bindings_pix2d_CustomSprite_setQuad00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::CustomSprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ccV3F_C4B_T2F_Quad",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::CustomSprite* self = (pix2d::CustomSprite*)  tolua_tousertype(tolua_S,1,0);
  const ccV3F_C4B_T2F_Quad quad = *((const ccV3F_C4B_T2F_Quad*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setQuad'", NULL);
#endif
  {
   self->setQuad(quad);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setQuad'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCActionTweenDelegate__ of class  pix2d::CustomSprite */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__CustomSprite___CCActionTweenDelegate__
static int tolua_get_pix2d__CustomSprite___CCActionTweenDelegate__(lua_State* tolua_S)
{
  pix2d::CustomSprite* self = (pix2d::CustomSprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCActionTweenDelegate__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCActionTweenDelegate*>(self), "CCActionTweenDelegate");
#else
   tolua_pushusertype(tolua_S,(void*)((CCActionTweenDelegate*)self), "CCActionTweenDelegate");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_uid
static int tolua_get_pix2d__PhysicNodeDef_uid(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_uid
static int tolua_set_pix2d__PhysicNodeDef_uid(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tag of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_tag
static int tolua_get_pix2d__PhysicNodeDef_tag(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tag of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_tag
static int tolua_set_pix2d__PhysicNodeDef_tag(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tag = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zorder of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_zorder
static int tolua_get_pix2d__PhysicNodeDef_zorder(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zorder'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->zorder);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zorder of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_zorder
static int tolua_set_pix2d__PhysicNodeDef_zorder(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zorder'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zorder = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixture of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_fixture
static int tolua_get_pix2d__PhysicNodeDef_fixture(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->fixture,"b2FixtureDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixture of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_fixture
static int tolua_set_pix2d__PhysicNodeDef_fixture(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2FixtureDef",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixture = *((b2FixtureDef*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: body of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_body
static int tolua_get_pix2d__PhysicNodeDef_body(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->body,"b2BodyDef");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: body of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_body
static int tolua_set_pix2d__PhysicNodeDef_body(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2BodyDef",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->body = *((b2BodyDef*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: body_type of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_body_type
static int tolua_get_pix2d__PhysicNodeDef_body_type(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body_type'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->body_type);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: body_type of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_body_type
static int tolua_set_pix2d__PhysicNodeDef_body_type(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body_type'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->body_type = ((b2BodyType) (int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sprite of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_sprite
static int tolua_get_pix2d__PhysicNodeDef_sprite(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sprite'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->sprite);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sprite of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_sprite
static int tolua_set_pix2d__PhysicNodeDef_sprite(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sprite'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sprite = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: frame of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_frame
static int tolua_get_pix2d__PhysicNodeDef_frame(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frame'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->frame);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: frame of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_frame
static int tolua_set_pix2d__PhysicNodeDef_frame(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'frame'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->frame = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_pos
static int tolua_get_pix2d__PhysicNodeDef_pos(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->pos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_pos
static int tolua_set_pix2d__PhysicNodeDef_pos(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: angle of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_angle
static int tolua_get_pix2d__PhysicNodeDef_angle(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angle'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->angle);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: angle of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_angle
static int tolua_set_pix2d__PhysicNodeDef_angle(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'angle'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->angle = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: is_sensor of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_is_sensor
static int tolua_get_pix2d__PhysicNodeDef_is_sensor(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'is_sensor'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->is_sensor);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: is_sensor of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_is_sensor
static int tolua_set_pix2d__PhysicNodeDef_is_sensor(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'is_sensor'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->is_sensor = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: restitution of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_restitution
static int tolua_get_pix2d__PhysicNodeDef_restitution(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'restitution'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->restitution);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: restitution of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_restitution
static int tolua_set_pix2d__PhysicNodeDef_restitution(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'restitution'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->restitution = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: density of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_density
static int tolua_get_pix2d__PhysicNodeDef_density(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'density'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->density);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: density of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_density
static int tolua_set_pix2d__PhysicNodeDef_density(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'density'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->density = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: friction of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_friction
static int tolua_get_pix2d__PhysicNodeDef_friction(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'friction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->friction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: friction of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_friction
static int tolua_set_pix2d__PhysicNodeDef_friction(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'friction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->friction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: category of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_unsigned_category
static int tolua_get_pix2d__PhysicNodeDef_unsigned_category(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'category'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->category);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: category of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_unsigned_category
static int tolua_set_pix2d__PhysicNodeDef_unsigned_category(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'category'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->category = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: mask of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_unsigned_mask
static int tolua_get_pix2d__PhysicNodeDef_unsigned_mask(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mask'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->mask);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: mask of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_unsigned_mask
static int tolua_set_pix2d__PhysicNodeDef_unsigned_mask(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'mask'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->mask = ((unsigned short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: group of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicNodeDef_group
static int tolua_get_pix2d__PhysicNodeDef_group(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'group'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->group);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: group of class  pix2d::PhysicNodeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicNodeDef_group
static int tolua_set_pix2d__PhysicNodeDef_group(lua_State* tolua_S)
{
  pix2d::PhysicNodeDef* self = (pix2d::PhysicNodeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'group'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->group = ((signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSprite of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getSprite00
static int tolua_custom_bindings_pix2d_PhysicNode_getSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSprite'", NULL);
#endif
  {
   pix2d::CustomSprite* tolua_ret = (pix2d::CustomSprite*)  self->getSprite();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CustomSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyType of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getBodyType00
static int tolua_custom_bindings_pix2d_PhysicNode_getBodyType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyType'", NULL);
#endif
  {
   b2BodyType tolua_ret = (b2BodyType)  self->getBodyType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBodyType of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setBodyType00
static int tolua_custom_bindings_pix2d_PhysicNode_setBodyType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  b2BodyType type = ((b2BodyType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBodyType'", NULL);
#endif
  {
   self->setBodyType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBodyType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: movable of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_movable00
static int tolua_custom_bindings_pix2d_PhysicNode_movable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'movable'", NULL);
#endif
  {
   self->movable(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'movable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isMovable of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_isMovable00
static int tolua_custom_bindings_pix2d_PhysicNode_isMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicNode* self = (const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isMovable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isMovable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBodyPosition of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setBodyPosition00
static int tolua_custom_bindings_pix2d_PhysicNode_setBodyPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBodyPosition'", NULL);
#endif
  {
   self->setBodyPosition(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBodyPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBodyRotation of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setBodyRotation00
static int tolua_custom_bindings_pix2d_PhysicNode_setBodyRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBodyRotation'", NULL);
#endif
  {
   self->setBodyRotation(a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBodyRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldPoint of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getWorldPoint00
static int tolua_custom_bindings_pix2d_PhysicNode_getWorldPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicNode* self = (const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* localPoint = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getWorldPoint(*localPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalPoint of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getLocalPoint00
static int tolua_custom_bindings_pix2d_PhysicNode_getLocalPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicNode* self = (const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* worldPoint = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getLocalPoint(*worldPoint);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocalPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLocalVector of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getLocalVector00
static int tolua_custom_bindings_pix2d_PhysicNode_getLocalVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicNode* self = (const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* worldVector = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLocalVector'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getLocalVector(*worldVector);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLocalVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getWorldVector of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getWorldVector00
static int tolua_custom_bindings_pix2d_PhysicNode_getWorldVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicNode* self = (const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* localVector = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getWorldVector'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getWorldVector(*localVector);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getWorldVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSleepingAllowed of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setSleepingAllowed00
static int tolua_custom_bindings_pix2d_PhysicNode_setSleepingAllowed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSleepingAllowed'", NULL);
#endif
  {
   self->setSleepingAllowed(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSleepingAllowed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setFixedRotation of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setFixedRotation00
static int tolua_custom_bindings_pix2d_PhysicNode_setFixedRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setFixedRotation'", NULL);
#endif
  {
   self->setFixedRotation(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setFixedRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyPosition of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getBodyPosition00
static int tolua_custom_bindings_pix2d_PhysicNode_getBodyPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyPosition'", NULL);
#endif
  {
   const b2Vec2& tolua_ret = (const b2Vec2&)  self->getBodyPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const b2Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBodyCenter of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getBodyCenter00
static int tolua_custom_bindings_pix2d_PhysicNode_getBodyCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBodyCenter'", NULL);
#endif
  {
   const b2Vec2& tolua_ret = (const b2Vec2&)  self->getBodyCenter();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const b2Vec2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBodyCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setGravityScale of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setGravityScale00
static int tolua_custom_bindings_pix2d_PhysicNode_setGravityScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setGravityScale'", NULL);
#endif
  {
   self->setGravityScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGravityScale of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getGravityScale00
static int tolua_custom_bindings_pix2d_PhysicNode_getGravityScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGravityScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getGravityScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGravityScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngle of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getAngle00
static int tolua_custom_bindings_pix2d_PhysicNode_getAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngle'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAngle();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMass of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getMass00
static int tolua_custom_bindings_pix2d_PhysicNode_getMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMass'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMass();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMass of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setMass00
static int tolua_custom_bindings_pix2d_PhysicNode_setMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMass'", NULL);
#endif
  {
   self->setMass(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLinearVelocity of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setLinearVelocity00
static int tolua_custom_bindings_pix2d_PhysicNode_setLinearVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* v = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLinearVelocity'", NULL);
#endif
  {
   self->setLinearVelocity(*v);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyLinearImpulse of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_applyLinearImpulse00
static int tolua_custom_bindings_pix2d_PhysicNode_applyLinearImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyLinearImpulse'", NULL);
#endif
  {
   self->applyLinearImpulse(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyLinearImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: applyForceToCenter of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_applyForceToCenter00
static int tolua_custom_bindings_pix2d_PhysicNode_applyForceToCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'applyForceToCenter'", NULL);
#endif
  {
   self->applyForceToCenter(x,y);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'applyForceToCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getLinearVelocity of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getLinearVelocity00
static int tolua_custom_bindings_pix2d_PhysicNode_getLinearVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getLinearVelocity'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getLinearVelocity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getIntertia of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getIntertia00
static int tolua_custom_bindings_pix2d_PhysicNode_getIntertia00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIntertia'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getIntertia();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIntertia'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularVelocity of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setAngularVelocity00
static int tolua_custom_bindings_pix2d_PhysicNode_setAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float tolua_var_1 = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularVelocity'", NULL);
#endif
  {
   self->setAngularVelocity(tolua_var_1);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAngularVelocity of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getAngularVelocity00
static int tolua_custom_bindings_pix2d_PhysicNode_getAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAngularVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getAngularVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAngularDamping of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setAngularDamping00
static int tolua_custom_bindings_pix2d_PhysicNode_setAngularDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAngularDamping'", NULL);
#endif
  {
   self->setAngularDamping(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setLinearDamping of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setLinearDamping00
static int tolua_custom_bindings_pix2d_PhysicNode_setLinearDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  float d = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setLinearDamping'", NULL);
#endif
  {
   self->setLinearDamping(d);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionFilter of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setCollisionFilter00
static int tolua_custom_bindings_pix2d_PhysicNode_setCollisionFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  unsigned short category = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  unsigned short mask = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  signed short group = ((signed short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionFilter'", NULL);
#endif
  {
   self->setCollisionFilter(category,mask,group);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionCategory of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setCollisionCategory00
static int tolua_custom_bindings_pix2d_PhysicNode_setCollisionCategory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  unsigned short category = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionCategory'", NULL);
#endif
  {
   self->setCollisionCategory(category);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionCategory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionMask of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setCollisionMask00
static int tolua_custom_bindings_pix2d_PhysicNode_setCollisionMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  unsigned short mask = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionMask'", NULL);
#endif
  {
   self->setCollisionMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCollisionGroup of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setCollisionGroup00
static int tolua_custom_bindings_pix2d_PhysicNode_setCollisionGroup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  signed short group = ((signed short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCollisionGroup'", NULL);
#endif
  {
   self->setCollisionGroup(group);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCollisionGroup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCollisionFilter of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_getCollisionFilter00
static int tolua_custom_bindings_pix2d_PhysicNode_getCollisionFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  unsigned short category = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  unsigned short mask = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  signed short group = ((signed short)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCollisionFilter'", NULL);
#endif
  {
   self->getCollisionFilter(&category,&mask,&group);
   tolua_pushnumber(tolua_S,(lua_Number)category);
   tolua_pushnumber(tolua_S,(lua_Number)mask);
   tolua_pushnumber(tolua_S,(lua_Number)group);
  }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCollisionFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBullet of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_setBullet00
static int tolua_custom_bindings_pix2d_PhysicNode_setBullet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBullet'", NULL);
#endif
  {
   self->setBullet(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isBullet of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_isBullet00
static int tolua_custom_bindings_pix2d_PhysicNode_isBullet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isBullet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isBullet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isBullet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rayCast of class  pix2d::PhysicNode */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicNode_rayCast00
static int tolua_custom_bindings_pix2d_PhysicNode_rayCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2RayCastOutput",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2RayCastInput",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::PhysicNode* self = (pix2d::PhysicNode*)  tolua_tousertype(tolua_S,1,0);
  b2RayCastOutput* output = ((b2RayCastOutput*)  tolua_tousertype(tolua_S,2,0));
  const b2RayCastInput* input = ((const b2RayCastInput*)  tolua_tousertype(tolua_S,3,0));
  int childIndex = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rayCast'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->rayCast(output,*input,childIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rayCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__BoxDef_size
static int tolua_get_pix2d__BoxDef_size(lua_State* tolua_S)
{
  pix2d::BoxDef* self = (pix2d::BoxDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->size,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__BoxDef_size
static int tolua_set_pix2d__BoxDef_size(lua_State* tolua_S)
{
  pix2d::BoxDef* self = (pix2d::BoxDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: center of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__BoxDef_center
static int tolua_get_pix2d__BoxDef_center(lua_State* tolua_S)
{
  pix2d::BoxDef* self = (pix2d::BoxDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'center'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->center,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: center of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__BoxDef_center
static int tolua_set_pix2d__BoxDef_center(lua_State* tolua_S)
{
  pix2d::BoxDef* self = (pix2d::BoxDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'center'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->center = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BoxDef_new00
static int tolua_custom_bindings_pix2d_BoxDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::BoxDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::BoxDef* tolua_ret = (pix2d::BoxDef*)  Mtolua_new((pix2d::BoxDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::BoxDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::BoxDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_BoxDef_new00_local
static int tolua_custom_bindings_pix2d_BoxDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::BoxDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::BoxDef* tolua_ret = (pix2d::BoxDef*)  Mtolua_new((pix2d::BoxDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::BoxDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Box */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Box_create00
static int tolua_custom_bindings_pix2d_Box_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Box",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const pix2d::BoxDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::BoxDef* def = ((const pix2d::BoxDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Box* tolua_ret = (pix2d::Box*)  pix2d::Box::create(*def);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Box");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: radius of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__CircleDef_radius
static int tolua_get_pix2d__CircleDef_radius(lua_State* tolua_S)
{
  pix2d::CircleDef* self = (pix2d::CircleDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->radius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: radius of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__CircleDef_radius
static int tolua_set_pix2d__CircleDef_radius(lua_State* tolua_S)
{
  pix2d::CircleDef* self = (pix2d::CircleDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->radius = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: shape of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__CircleDef_shape
static int tolua_get_pix2d__CircleDef_shape(lua_State* tolua_S)
{
  pix2d::CircleDef* self = (pix2d::CircleDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shape'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->shape,"b2CircleShape");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: shape of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__CircleDef_shape
static int tolua_set_pix2d__CircleDef_shape(lua_State* tolua_S)
{
  pix2d::CircleDef* self = (pix2d::CircleDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'shape'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2CircleShape",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->shape = *((b2CircleShape*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CircleDef_new00
static int tolua_custom_bindings_pix2d_CircleDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CircleDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::CircleDef* tolua_ret = (pix2d::CircleDef*)  Mtolua_new((pix2d::CircleDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::CircleDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::CircleDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CircleDef_new00_local
static int tolua_custom_bindings_pix2d_CircleDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CircleDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::CircleDef* tolua_ret = (pix2d::CircleDef*)  Mtolua_new((pix2d::CircleDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::CircleDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Circle */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Circle_create00
static int tolua_custom_bindings_pix2d_Circle_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Circle",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const pix2d::CircleDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::CircleDef* def = ((const pix2d::CircleDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Circle* tolua_ret = (pix2d::Circle*)  pix2d::Circle::create(*def);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Circle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vertices of class  pix2d::ChainDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ChainDef_vertices
static int tolua_get_pix2d__ChainDef_vertices(lua_State* tolua_S)
{
  pix2d::ChainDef* self = (pix2d::ChainDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vertices'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->vertices,"vector<b2Vec2>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vertices of class  pix2d::ChainDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ChainDef_vertices
static int tolua_set_pix2d__ChainDef_vertices(lua_State* tolua_S)
{
  pix2d::ChainDef* self = (pix2d::ChainDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vertices'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<b2Vec2>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vertices = *((vector<b2Vec2>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::ChainDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ChainDef_new00
static int tolua_custom_bindings_pix2d_ChainDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ChainDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::ChainDef* tolua_ret = (pix2d::ChainDef*)  Mtolua_new((pix2d::ChainDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::ChainDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::ChainDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ChainDef_new00_local
static int tolua_custom_bindings_pix2d_ChainDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ChainDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::ChainDef* tolua_ret = (pix2d::ChainDef*)  Mtolua_new((pix2d::ChainDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::ChainDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Chain */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Chain_create00
static int tolua_custom_bindings_pix2d_Chain_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Chain",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const pix2d::ChainDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::ChainDef* def = ((const pix2d::ChainDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Chain* tolua_ret = (pix2d::Chain*)  pix2d::Chain::create(*def);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Chain");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Boundary */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Boundary_create00
static int tolua_custom_bindings_pix2d_Boundary_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Boundary",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CCRect* rect = ((const CCRect*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Boundary* tolua_ret = (pix2d::Boundary*)  pix2d::Boundary::create(*rect);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Boundary");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: vertices of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TextureDef_vertices
static int tolua_get_pix2d__TextureDef_vertices(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vertices'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->vertices,"vector<b2Vec2>");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: vertices of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TextureDef_vertices
static int tolua_set_pix2d__TextureDef_vertices(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'vertices'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<b2Vec2>",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->vertices = *((vector<b2Vec2>*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: texture of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TextureDef_texture
static int tolua_get_pix2d__TextureDef_texture(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->texture);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: texture of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TextureDef_texture
static int tolua_set_pix2d__TextureDef_texture(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'texture'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->texture = ((string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: simplify of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TextureDef_simplify
static int tolua_get_pix2d__TextureDef_simplify(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'simplify'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->simplify);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: simplify of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TextureDef_simplify
static int tolua_set_pix2d__TextureDef_simplify(lua_State* tolua_S)
{
  pix2d::TextureDef* self = (pix2d::TextureDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'simplify'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->simplify = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureDef_new00
static int tolua_custom_bindings_pix2d_TextureDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TextureDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::TextureDef* tolua_ret = (pix2d::TextureDef*)  Mtolua_new((pix2d::TextureDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::TextureDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::TextureDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TextureDef_new00_local
static int tolua_custom_bindings_pix2d_TextureDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TextureDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::TextureDef* tolua_ret = (pix2d::TextureDef*)  Mtolua_new((pix2d::TextureDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::TextureDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Texture */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Texture_create00
static int tolua_custom_bindings_pix2d_Texture_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Texture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"pix2d::TextureDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TextureDef* def = ((pix2d::TextureDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Texture* tolua_ret = (pix2d::Texture*)  pix2d::Texture::create(*def);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: simplifyPolygon of class  pix2d::Texture */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Texture_simplifyPolygon00
static int tolua_custom_bindings_pix2d_Texture_simplifyPolygon00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Texture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<b2Vec2>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<b2Vec2>* polygon = ((vector<b2Vec2>*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Texture::simplifyPolygon(*polygon);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'simplifyPolygon'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addVertices of class  pix2d::Texture */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Texture_addVertices00
static int tolua_custom_bindings_pix2d_Texture_addVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Texture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<b2Vec2>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Texture* self = (pix2d::Texture*)  tolua_tousertype(tolua_S,1,0);
  vector<b2Vec2> vertices = *((vector<b2Vec2>*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addVertices'", NULL);
#endif
  {
   self->addVertices(vertices);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTextureSprite of class  pix2d::Texture */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Texture_getTextureSprite00
static int tolua_custom_bindings_pix2d_Texture_getTextureSprite00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Texture* self = (pix2d::Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTextureSprite'", NULL);
#endif
  {
   pix2d::TextureSprite* tolua_ret = (pix2d::TextureSprite*)  self->getTextureSprite();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::TextureSprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTextureSprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: triangulate of class  pix2d::Texture */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Texture_triangulate00
static int tolua_custom_bindings_pix2d_Texture_triangulate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Texture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"vector<CCPoint>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"vector<CCPoint>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  vector<CCPoint>* in = ((vector<CCPoint>*)  tolua_tousertype(tolua_S,2,0));
  vector<CCPoint>* out = ((vector<CCPoint>*)  tolua_tousertype(tolua_S,3,0));
  {
   pix2d::Texture::triangulate(*in,*out);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'triangulate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::IrisWipe */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_IrisWipe_create00
static int tolua_custom_bindings_pix2d_IrisWipe_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::IrisWipe",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"ccColor4F",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  bool opening = ((bool)  tolua_toboolean(tolua_S,4,0));
  ccColor4F* color = ((ccColor4F*)  tolua_tousertype(tolua_S,5,0));
  float start = ((float)  tolua_tonumber(tolua_S,6,0));
  float end = ((float)  tolua_tonumber(tolua_S,7,0));
  float duration = ((float)  tolua_tonumber(tolua_S,8,0));
  {
   pix2d::IrisWipe* tolua_ret = (pix2d::IrisWipe*)  pix2d::IrisWipe::create(x,y,opening,*color,start,end,duration);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::IrisWipe");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCallbackHandler of class  pix2d::IrisWipe */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_IrisWipe_registerCallbackHandler00
static int tolua_custom_bindings_pix2d_IrisWipe_registerCallbackHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::IrisWipe",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::IrisWipe* self = (pix2d::IrisWipe*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCallbackHandler'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->registerCallbackHandler(handler);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCallbackHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unregisterCallbackHandler of class  pix2d::IrisWipe */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_IrisWipe_unregisterCallbackHandler00
static int tolua_custom_bindings_pix2d_IrisWipe_unregisterCallbackHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::IrisWipe",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::IrisWipe* self = (pix2d::IrisWipe*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unregisterCallbackHandler'", NULL);
#endif
  {
   self->unregisterCallbackHandler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unregisterCallbackHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStencil of class  pix2d::IrisWipe */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_IrisWipe_getStencil00
static int tolua_custom_bindings_pix2d_IrisWipe_getStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::IrisWipe",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::IrisWipe* self = (pix2d::IrisWipe*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStencil'", NULL);
#endif
  {
   CCDrawNode* tolua_ret = (CCDrawNode*)  self->getStencil();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCDrawNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStencil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::ParticleQuad */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ParticleQuad_create00
static int tolua_custom_bindings_pix2d_ParticleQuad_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ParticleQuad",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCParticleBatchNode",0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCParticleBatchNode* batch = ((CCParticleBatchNode*)  tolua_tousertype(tolua_S,2,0));
  const char* plistfile = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   pix2d::ParticleQuad* tolua_ret = (pix2d::ParticleQuad*)  pix2d::ParticleQuad::create(batch,plistfile);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::ParticleQuad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createStarsExplosion of class  pix2d::ParticleQuad */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion00
static int tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ParticleQuad",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCParticleBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCParticleBatchNode* batch = ((CCParticleBatchNode*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::ParticleQuad* tolua_ret = (pix2d::ParticleQuad*)  pix2d::ParticleQuad::createStarsExplosion(batch);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::ParticleQuad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createStarsExplosion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createStarsExplosion2 of class  pix2d::ParticleQuad */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion200
static int tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ParticleQuad",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCParticleBatchNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CCParticleBatchNode* batch = ((CCParticleBatchNode*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::ParticleQuad* tolua_ret = (pix2d::ParticleQuad*)  pix2d::ParticleQuad::createStarsExplosion2(batch);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::ParticleQuad");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createStarsExplosion2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rect of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_rect00
static int tolua_custom_bindings_pix2d_VisibleRect_rect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCRect tolua_ret = (CCRect)  pix2d::VisibleRect::rect();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCRect));
     tolua_pushusertype(tolua_S,tolua_obj,"CCRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_size00
static int tolua_custom_bindings_pix2d_VisibleRect_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSize tolua_ret = (CCSize)  pix2d::VisibleRect::size();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizeInPixel of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_sizeInPixel00
static int tolua_custom_bindings_pix2d_VisibleRect_sizeInPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCSize tolua_ret = (CCSize)  pix2d::VisibleRect::sizeInPixel();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizeInPixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: origin of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_origin00
static int tolua_custom_bindings_pix2d_VisibleRect_origin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::origin();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'origin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizeAt of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_sizeAt00
static int tolua_custom_bindings_pix2d_VisibleRect_sizeAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
  float t = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCSize tolua_ret = (CCSize)  pix2d::VisibleRect::sizeAt(s,t);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizeAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAtY of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_pointAtY00
static int tolua_custom_bindings_pix2d_VisibleRect_pointAtY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float t = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   float tolua_ret = (float)  pix2d::VisibleRect::pointAtY(t);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAtY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAtX of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_pointAtX00
static int tolua_custom_bindings_pix2d_VisibleRect_pointAtX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   float tolua_ret = (float)  pix2d::VisibleRect::pointAtX(s);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAtX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_pointAt00
static int tolua_custom_bindings_pix2d_VisibleRect_pointAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float s = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::VisibleRect::pointAt(&s,&y);
   tolua_pushnumber(tolua_S,(lua_Number)s);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pointAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pointAt of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_pointAt01
static int tolua_custom_bindings_pix2d_VisibleRect_pointAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CCPoint* p = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::pointAt(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_VisibleRect_pointAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: left of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_left00
static int tolua_custom_bindings_pix2d_VisibleRect_left00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::left();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'left'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: right of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_right00
static int tolua_custom_bindings_pix2d_VisibleRect_right00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::right();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'right'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: top of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_top00
static int tolua_custom_bindings_pix2d_VisibleRect_top00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::top();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'top'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: bottom of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_bottom00
static int tolua_custom_bindings_pix2d_VisibleRect_bottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::bottom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'bottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: center of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_center00
static int tolua_custom_bindings_pix2d_VisibleRect_center00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::center();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'center'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leftTop of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_leftTop00
static int tolua_custom_bindings_pix2d_VisibleRect_leftTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::leftTop();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leftTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rightTop of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_rightTop00
static int tolua_custom_bindings_pix2d_VisibleRect_rightTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::rightTop();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rightTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: leftBottom of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_leftBottom00
static int tolua_custom_bindings_pix2d_VisibleRect_leftBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::leftBottom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'leftBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: rightBottom of class  pix2d::VisibleRect */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_VisibleRect_rightBottom00
static int tolua_custom_bindings_pix2d_VisibleRect_rightBottom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::VisibleRect",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::VisibleRect::rightBottom();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rightBottom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: batch of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_batch_ptr
static int tolua_get_pix2d__RopeDef_batch_ptr(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'batch'",NULL);
#endif
   int nID = (self->batch) ? (int)self->batch->m_uID : -1;
    int* pLuaID = (self->batch) ? &self->batch->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->batch,"CCSpriteBatchNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: batch of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_batch_ptr
static int tolua_set_pix2d__RopeDef_batch_ptr(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'batch'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCSpriteBatchNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->batch = ((CCSpriteBatchNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: uid of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_uid
static int tolua_get_pix2d__RopeDef_uid(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->uid);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uid of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_uid
static int tolua_set_pix2d__RopeDef_uid(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uid'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uid = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: tag of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_tag
static int tolua_get_pix2d__RopeDef_tag(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->tag);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: tag of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_tag
static int tolua_set_pix2d__RopeDef_tag(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'tag'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->tag = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: startpos of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_startpos
static int tolua_get_pix2d__RopeDef_startpos(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startpos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->startpos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: startpos of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_startpos
static int tolua_set_pix2d__RopeDef_startpos(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'startpos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->startpos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: endpos of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_endpos
static int tolua_get_pix2d__RopeDef_endpos(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endpos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->endpos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: endpos of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_endpos
static int tolua_set_pix2d__RopeDef_endpos(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'endpos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->endpos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorFrame of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_anchorFrame
static int tolua_get_pix2d__RopeDef_anchorFrame(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorFrame'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->anchorFrame);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorFrame of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_anchorFrame
static int tolua_set_pix2d__RopeDef_anchorFrame(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorFrame'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchorFrame = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookFrame of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookFrame
static int tolua_get_pix2d__RopeDef_hookFrame(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookFrame'",NULL);
#endif
  tolua_pushcppstring(tolua_S,(const char*)self->hookFrame);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookFrame of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookFrame
static int tolua_set_pix2d__RopeDef_hookFrame(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookFrame'",NULL);
  if (!tolua_iscppstring(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookFrame = ((std::string)  tolua_tocppstring(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: sensorRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_sensorRadius
static int tolua_get_pix2d__RopeDef_sensorRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensorRadius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->sensorRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: sensorRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_sensorRadius
static int tolua_set_pix2d__RopeDef_sensorRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'sensorRadius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->sensorRadius = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_anchorRadius
static int tolua_get_pix2d__RopeDef_anchorRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorRadius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->anchorRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_anchorRadius
static int tolua_set_pix2d__RopeDef_anchorRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorRadius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchorRadius = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookRadius
static int tolua_get_pix2d__RopeDef_hookRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookRadius'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hookRadius);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookRadius of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookRadius
static int tolua_set_pix2d__RopeDef_hookRadius(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookRadius'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookRadius = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorDensity of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_anchorDensity
static int tolua_get_pix2d__RopeDef_anchorDensity(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorDensity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->anchorDensity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorDensity of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_anchorDensity
static int tolua_set_pix2d__RopeDef_anchorDensity(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorDensity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchorDensity = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookRestitution of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookRestitution
static int tolua_get_pix2d__RopeDef_hookRestitution(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookRestitution'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hookRestitution);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookRestitution of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookRestitution
static int tolua_set_pix2d__RopeDef_hookRestitution(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookRestitution'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookRestitution = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookDensity of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookDensity
static int tolua_get_pix2d__RopeDef_hookDensity(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookDensity'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hookDensity);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookDensity of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookDensity
static int tolua_set_pix2d__RopeDef_hookDensity(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookDensity'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookDensity = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookFriction of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookFriction
static int tolua_get_pix2d__RopeDef_hookFriction(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookFriction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->hookFriction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookFriction of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookFriction
static int tolua_set_pix2d__RopeDef_hookFriction(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookFriction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookFriction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: anchorLocalAnchor of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_anchorLocalAnchor
static int tolua_get_pix2d__RopeDef_anchorLocalAnchor(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorLocalAnchor'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->anchorLocalAnchor,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: anchorLocalAnchor of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_anchorLocalAnchor
static int tolua_set_pix2d__RopeDef_anchorLocalAnchor(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'anchorLocalAnchor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->anchorLocalAnchor = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hookLocalAnchor of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__RopeDef_hookLocalAnchor
static int tolua_get_pix2d__RopeDef_hookLocalAnchor(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookLocalAnchor'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->hookLocalAnchor,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hookLocalAnchor of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__RopeDef_hookLocalAnchor
static int tolua_set_pix2d__RopeDef_hookLocalAnchor(lua_State* tolua_S)
{
  pix2d::RopeDef* self = (pix2d::RopeDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hookLocalAnchor'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hookLocalAnchor = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_RopeDef_new00
static int tolua_custom_bindings_pix2d_RopeDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::RopeDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::RopeDef* tolua_ret = (pix2d::RopeDef*)  Mtolua_new((pix2d::RopeDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::RopeDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::RopeDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_RopeDef_new00_local
static int tolua_custom_bindings_pix2d_RopeDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::RopeDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::RopeDef* tolua_ret = (pix2d::RopeDef*)  Mtolua_new((pix2d::RopeDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::RopeDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_create00
static int tolua_custom_bindings_pix2d_Rope_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const pix2d::RopeDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::RopeDef* def = ((const pix2d::RopeDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Rope* tolua_ret = (pix2d::Rope*)  pix2d::Rope::create(*def);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Rope");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAnchor of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_getAnchor00
static int tolua_custom_bindings_pix2d_Rope_getAnchor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAnchor'", NULL);
#endif
  {
   pix2d::Circle* tolua_ret = (pix2d::Circle*)  self->getAnchor();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Circle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAnchor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getHook of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_getHook00
static int tolua_custom_bindings_pix2d_Rope_getHook00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getHook'", NULL);
#endif
  {
   pix2d::Circle* tolua_ret = (pix2d::Circle*)  self->getHook();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Circle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getHook'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getSensor of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_getSensor00
static int tolua_custom_bindings_pix2d_Rope_getSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getSensor'", NULL);
#endif
  {
   pix2d::Circle* tolua_ret = (pix2d::Circle*)  self->getSensor();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Circle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInnerSensor of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_getInnerSensor00
static int tolua_custom_bindings_pix2d_Rope_getInnerSensor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getInnerSensor'", NULL);
#endif
  {
   pix2d::Circle* tolua_ret = (pix2d::Circle*)  self->getInnerSensor();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::Circle");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getInnerSensor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: attach of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_attach00
static int tolua_custom_bindings_pix2d_Rope_attach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'attach'", NULL);
#endif
  {
   self->attach(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'attach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: detach of class  pix2d::Rope */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Rope_detach00
static int tolua_custom_bindings_pix2d_Rope_detach00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Rope",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Rope* self = (pix2d::Rope*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'detach'", NULL);
#endif
  {
   self->detach();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'detach'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: node of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_node_ptr
static int tolua_get_pix2d__LuaRayCastInfo_node_ptr(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node'",NULL);
#endif
   int nID = (self->node) ? (int)self->node->m_uID : -1;
    int* pLuaID = (self->node) ? &self->node->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->node,"pix2d::PhysicNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: node of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_node_ptr
static int tolua_set_pix2d__LuaRayCastInfo_node_ptr(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node'",NULL);
  if (!tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixture of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_fixture_ptr
static int tolua_get_pix2d__LuaRayCastInfo_fixture_ptr(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->fixture,"b2Fixture");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixture of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_fixture_ptr
static int tolua_set_pix2d__LuaRayCastInfo_fixture_ptr(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Fixture",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixture = ((b2Fixture*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: point of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_point
static int tolua_get_pix2d__LuaRayCastInfo_point(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'point'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->point,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: point of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_point
static int tolua_set_pix2d__LuaRayCastInfo_point(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'point'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->point = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: normal of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_normal
static int tolua_get_pix2d__LuaRayCastInfo_normal(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->normal,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: normal of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_normal
static int tolua_set_pix2d__LuaRayCastInfo_normal(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->normal = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fraction of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_fraction
static int tolua_get_pix2d__LuaRayCastInfo_fraction(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fraction'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->fraction);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fraction of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_fraction
static int tolua_set_pix2d__LuaRayCastInfo_fraction(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fraction'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fraction = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rc of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__LuaRayCastInfo_rc
static int tolua_get_pix2d__LuaRayCastInfo_rc(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rc'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->rc);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rc of class  pix2d::LuaRayCastInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__LuaRayCastInfo_rc
static int tolua_set_pix2d__LuaRayCastInfo_rc(lua_State* tolua_S)
{
  pix2d::LuaRayCastInfo* self = (pix2d::LuaRayCastInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rc'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rc = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: scene of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_scene_ptr
static int tolua_get_pix2d__PhysicsDef_scene_ptr(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
#endif
   int nID = (self->scene) ? (int)self->scene->m_uID : -1;
    int* pLuaID = (self->scene) ? &self->scene->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->scene,"CCScene");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: scene of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_scene_ptr
static int tolua_set_pix2d__PhysicsDef_scene_ptr(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'scene'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCScene",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->scene = ((CCScene*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: unit of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_unit
static int tolua_get_pix2d__PhysicsDef_unit(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unit'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->unit);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: unit of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_unit
static int tolua_set_pix2d__PhysicsDef_unit(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'unit'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->unit = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_size
static int tolua_get_pix2d__PhysicsDef_size(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->size,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_size
static int tolua_set_pix2d__PhysicsDef_size(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_pos
static int tolua_get_pix2d__PhysicsDef_pos(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->pos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_pos
static int tolua_set_pix2d__PhysicsDef_pos(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: gravity of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_gravity
static int tolua_get_pix2d__PhysicsDef_gravity(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravity'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->gravity,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: gravity of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_gravity
static int tolua_set_pix2d__PhysicsDef_gravity(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'gravity'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->gravity = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: continuousPhysics of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_continuousPhysics
static int tolua_get_pix2d__PhysicsDef_continuousPhysics(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'continuousPhysics'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->continuousPhysics);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: continuousPhysics of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_continuousPhysics
static int tolua_set_pix2d__PhysicsDef_continuousPhysics(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'continuousPhysics'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->continuousPhysics = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: allowSleeping of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__PhysicsDef_allowSleeping
static int tolua_get_pix2d__PhysicsDef_allowSleeping(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'allowSleeping'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->allowSleeping);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: allowSleeping of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__PhysicsDef_allowSleeping
static int tolua_set_pix2d__PhysicsDef_allowSleeping(lua_State* tolua_S)
{
  pix2d::PhysicsDef* self = (pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'allowSleeping'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->allowSleeping = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicsDef_new00
static int tolua_custom_bindings_pix2d_PhysicsDef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::PhysicsDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::PhysicsDef* tolua_ret = (pix2d::PhysicsDef*)  Mtolua_new((pix2d::PhysicsDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::PhysicsDef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::PhysicsDef */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_PhysicsDef_new00_local
static int tolua_custom_bindings_pix2d_PhysicsDef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::PhysicsDef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::PhysicsDef* tolua_ret = (pix2d::PhysicsDef*)  Mtolua_new((pix2d::PhysicsDef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::PhysicsDef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPix2dDebug of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_isPix2dDebug00
static int tolua_custom_bindings_pix2d_Physics_isPix2dDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  pix2d::Physics::isPix2dDebug();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPix2dDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isCocos2dDebug of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_isCocos2dDebug00
static int tolua_custom_bindings_pix2d_Physics_isCocos2dDebug00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   bool tolua_ret = (bool)  pix2d::Physics::isCocos2dDebug();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isCocos2dDebug'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_create00
static int tolua_custom_bindings_pix2d_Physics_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const pix2d::PhysicsDef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::PhysicsDef* def = ((const pix2d::PhysicsDef*)  tolua_tousertype(tolua_S,2,0));
  {
   pix2d::Physics* tolua_ret = (pix2d::Physics*)  pix2d::Physics::create(*def);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Physics");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: shared of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_shared00
static int tolua_custom_bindings_pix2d_Physics_shared00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::Physics* tolua_ret = (pix2d::Physics*)  pix2d::Physics::shared();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::Physics");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'shared'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: world of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_world00
static int tolua_custom_bindings_pix2d_Physics_world00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'world'", NULL);
#endif
  {
   b2World* tolua_ret = (b2World*)  self->world();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2World");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'world'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dummy of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_dummy00
static int tolua_custom_bindings_pix2d_Physics_dummy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dummy'", NULL);
#endif
  {
   b2Body* tolua_ret = (b2Body*)  self->dummy();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2Body");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dummy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getGravity of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getGravity00
static int tolua_custom_bindings_pix2d_Physics_getGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getGravity'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getGravity();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_addNode00
static int tolua_custom_bindings_pix2d_Physics_addNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_addNode01
static int tolua_custom_bindings_pix2d_Physics_addNode01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zorder = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zorder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_addNode00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: addNode of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_addNode02
static int tolua_custom_bindings_pix2d_Physics_addNode02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CCNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  CCNode* node = ((CCNode*)  tolua_tousertype(tolua_S,2,0));
  int zorder = ((int)  tolua_tonumber(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addNode'", NULL);
#endif
  {
   self->addNode(node,zorder,tag);
  }
 }
 return 0;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_addNode01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: getScene of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getScene00
static int tolua_custom_bindings_pix2d_Physics_getScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getScene'", NULL);
#endif
  {
   CCScene* tolua_ret = (CCScene*)  self->getScene();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCScene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removePhysicNode of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_removePhysicNode00
static int tolua_custom_bindings_pix2d_Physics_removePhysicNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removePhysicNode'", NULL);
#endif
  {
   self->removePhysicNode(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removePhysicNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_removeJoint00
static int tolua_custom_bindings_pix2d_Physics_removeJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"b2Joint",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  b2Joint* joint = ((b2Joint*)  tolua_tousertype(tolua_S,2,0));
  bool deteUserData = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeJoint'", NULL);
#endif
  {
   self->removeJoint(joint,deteUserData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pixelToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_pixelToMeter00
static int tolua_custom_bindings_pix2d_Physics_pixelToMeter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double p = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   double tolua_ret = (double)  pix2d::Physics::pixelToMeter(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pixelToMeter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pixelToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_pixelToMeter01
static int tolua_custom_bindings_pix2d_Physics_pixelToMeter01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::pixelToMeter(x,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_pixelToMeter00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pixelToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_pixelToMeter02
static int tolua_custom_bindings_pix2d_Physics_pixelToMeter02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CCPoint",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const CCPoint* p = ((const CCPoint*)  tolua_tousertype(tolua_S,2,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::pixelToMeter(*p);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_pixelToMeter01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: meterToPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_meterToPixel00
static int tolua_custom_bindings_pix2d_Physics_meterToPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  double p = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   double tolua_ret = (double)  pix2d::Physics::meterToPixel(p);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'meterToPixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: meterToPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_meterToPixel01
static int tolua_custom_bindings_pix2d_Physics_meterToPixel01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::Physics::meterToPixel(x,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_meterToPixel00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: meterToPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_meterToPixel02
static int tolua_custom_bindings_pix2d_Physics_meterToPixel02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const b2Vec2* v = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::Physics::meterToPixel(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_meterToPixel01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToMeter00
static int tolua_custom_bindings_pix2d_Physics_unitToMeter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float i = ((float)  tolua_tonumber(tolua_S,2,0));
  float j = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::unitToMeter(i,j);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unitToMeter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToMeter01
static int tolua_custom_bindings_pix2d_Physics_unitToMeter01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float i = ((float)  tolua_tonumber(tolua_S,2,0));
  float j = ((float)  tolua_tonumber(tolua_S,3,0));
  float ox = ((float)  tolua_tonumber(tolua_S,4,0));
  float oy = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::unitToMeter(i,j,ox,oy);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_unitToMeter00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToMeter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToMeter02
static int tolua_custom_bindings_pix2d_Physics_unitToMeter02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const b2Vec2* v = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::unitToMeter(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_unitToMeter01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToMeterCenter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToMeterCenter00
static int tolua_custom_bindings_pix2d_Physics_unitToMeterCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Vec2* v = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::unitToMeterCenter(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unitToMeterCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToMeterCenter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToMeterCenter01
static int tolua_custom_bindings_pix2d_Physics_unitToMeterCenter01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float i = ((float)  tolua_tonumber(tolua_S,2,0));
  float j = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::unitToMeterCenter(i,j);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_unitToMeterCenter00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: meterToUnit of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_meterToUnit00
static int tolua_custom_bindings_pix2d_Physics_meterToUnit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Vec2* v = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  {
   b2Vec2 tolua_ret = (b2Vec2)  pix2d::Physics::meterToUnit(*v);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'meterToUnit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: meterToUnit of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_meterToUnit01
static int tolua_custom_bindings_pix2d_Physics_meterToUnit01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::Physics::meterToUnit(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_meterToUnit00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: pixelToUnit of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_pixelToUnit00
static int tolua_custom_bindings_pix2d_Physics_pixelToUnit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::Physics::pixelToUnit(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pixelToUnit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToPixel00
static int tolua_custom_bindings_pix2d_Physics_unitToPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float i = ((float)  tolua_tonumber(tolua_S,2,0));
  float j = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::Physics::unitToPixel(i,j);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unitToPixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unitToPixelCenter of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unitToPixelCenter00
static int tolua_custom_bindings_pix2d_Physics_unitToPixelCenter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float i = ((float)  tolua_tonumber(tolua_S,2,0));
  float j = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   CCPoint tolua_ret = (CCPoint)  pix2d::Physics::unitToPixelCenter(i,j);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCPoint)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCPoint));
     tolua_pushusertype(tolua_S,tolua_obj,"CCPoint");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unitToPixelCenter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPrismaticJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createPrismaticJoint00
static int tolua_custom_bindings_pix2d_Physics_createPrismaticJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPrismaticJoint'", NULL);
#endif
  {
   self->createPrismaticJoint(nodeA,nodeB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createPrismaticJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createFrictionJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createFrictionJoint00
static int tolua_custom_bindings_pix2d_Physics_createFrictionJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  float maxForce = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createFrictionJoint'", NULL);
#endif
  {
   self->createFrictionJoint(nodeA,maxForce);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createFrictionJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createRopeJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createRopeJoint00
static int tolua_custom_bindings_pix2d_Physics_createRopeJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  b2Vec2 anchorA = *((b2Vec2*)  tolua_tousertype(tolua_S,4,0));
  b2Vec2 anchorB = *((b2Vec2*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createRopeJoint'", NULL);
#endif
  {
   b2RopeJoint* tolua_ret = (b2RopeJoint*)  self->createRopeJoint(nodeA,nodeB,anchorA,anchorB);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RopeJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createRopeJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createRopeJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createRopeJoint01
static int tolua_custom_bindings_pix2d_Physics_createRopeJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createRopeJoint'", NULL);
#endif
  {
   b2RopeJoint* tolua_ret = (b2RopeJoint*)  self->createRopeJoint(nodeA,nodeB);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RopeJoint");
  }
 }
 return 1;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_createRopeJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: createRevoluteJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createRevoluteJoint00
static int tolua_custom_bindings_pix2d_Physics_createRevoluteJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createRevoluteJoint'", NULL);
#endif
  {
   b2RevoluteJoint* tolua_ret = (b2RevoluteJoint*)  self->createRevoluteJoint(nodeA,nodeB);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RevoluteJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createRevoluteJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createRevoluteJointWithAnchor of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithAnchor00
static int tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithAnchor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* anchor = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createRevoluteJointWithAnchor'", NULL);
#endif
  {
   b2RevoluteJoint* tolua_ret = (b2RevoluteJoint*)  self->createRevoluteJointWithAnchor(nodeA,nodeB,*anchor);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RevoluteJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createRevoluteJointWithAnchor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createRevoluteJointWithLimit of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithLimit00
static int tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* a = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* b = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* anchor = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
  float lower = ((float)  tolua_tonumber(tolua_S,5,0));
  float upper = ((float)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createRevoluteJointWithLimit'", NULL);
#endif
  {
   b2RevoluteJoint* tolua_ret = (b2RevoluteJoint*)  self->createRevoluteJointWithLimit(a,b,*anchor,lower,upper);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2RevoluteJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createRevoluteJointWithLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeRevoluteJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_removeRevoluteJoint00
static int tolua_custom_bindings_pix2d_Physics_removeRevoluteJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeRevoluteJoint'", NULL);
#endif
  {
   self->removeRevoluteJoint(nodeA,nodeB);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeRevoluteJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDistanceJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createDistanceJoint00
static int tolua_custom_bindings_pix2d_Physics_createDistanceJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* anchorA = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
  const b2Vec2* anchorB = ((const b2Vec2*)  tolua_tousertype(tolua_S,5,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,6,4.f));
  float damping = ((float)  tolua_tonumber(tolua_S,7,.5f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createDistanceJoint'", NULL);
#endif
  {
   b2DistanceJoint* tolua_ret = (b2DistanceJoint*)  self->createDistanceJoint(nodeA,nodeB,*anchorA,*anchorB,frequency,damping);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2DistanceJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDistanceJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createDistanceJointWithLength of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createDistanceJointWithLength00
static int tolua_custom_bindings_pix2d_Physics_createDistanceJointWithLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  float length = ((float)  tolua_tonumber(tolua_S,4,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,5,4.f));
  float damping = ((float)  tolua_tonumber(tolua_S,6,5.f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createDistanceJointWithLength'", NULL);
#endif
  {
   b2DistanceJoint* tolua_ret = (b2DistanceJoint*)  self->createDistanceJointWithLength(nodeA,nodeB,length,frequency,damping);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2DistanceJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createDistanceJointWithLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWeldJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createWeldJoint00
static int tolua_custom_bindings_pix2d_Physics_createWeldJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  pix2d::PhysicNode* nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* anchorA = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
  const b2Vec2* anchorB = ((const b2Vec2*)  tolua_tousertype(tolua_S,5,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,6,4.f));
  float damping = ((float)  tolua_tonumber(tolua_S,7,.5f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createWeldJoint'", NULL);
#endif
  {
   b2WeldJoint* tolua_ret = (b2WeldJoint*)  self->createWeldJoint(nodeA,nodeB,*anchorA,*anchorB,frequency,damping);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"b2WeldJoint");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWeldJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createPrismaticJoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_createPrismaticJoint01
static int tolua_custom_bindings_pix2d_Physics_createPrismaticJoint01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  const b2Vec2* start = ((const b2Vec2*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* end = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'createPrismaticJoint'", NULL);
#endif
  {
   self->createPrismaticJoint(node,*start,*end);
  }
 }
 return 0;
tolua_lerror:
 return tolua_custom_bindings_pix2d_Physics_createPrismaticJoint00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: rayCast of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_rayCast00
static int tolua_custom_bindings_pix2d_Physics_rayCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  const b2Vec2* point1 = ((const b2Vec2*)  tolua_tousertype(tolua_S,3,0));
  const b2Vec2* point2 = ((const b2Vec2*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'rayCast'", NULL);
#endif
  {
   self->rayCast(lo,*point1,*point2);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'rayCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTrajectoryPoint of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getTrajectoryPoint00
static int tolua_custom_bindings_pix2d_Physics_getTrajectoryPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  const b2Vec2* startingPosition = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  const b2Vec2* startingVelocity = ((const b2Vec2*)  tolua_tousertype(tolua_S,3,0));
  float n = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTrajectoryPoint'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getTrajectoryPoint(*startingPosition,*startingVelocity,n);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTrajectoryPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: calculateVerticalVelocityForHeight of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_calculateVerticalVelocityForHeight00
static int tolua_custom_bindings_pix2d_Physics_calculateVerticalVelocityForHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  float desiredHeight = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'calculateVerticalVelocityForHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->calculateVerticalVelocityForHeight(desiredHeight);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'calculateVerticalVelocityForHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getTimestepsToTop of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getTimestepsToTop00
static int tolua_custom_bindings_pix2d_Physics_getTimestepsToTop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2* startingVelocity = ((b2Vec2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getTimestepsToTop'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getTimestepsToTop(*startingVelocity);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getTimestepsToTop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMaxHeight of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getMaxHeight00
static int tolua_custom_bindings_pix2d_Physics_getMaxHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"b2Vec2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  b2Vec2* startingPosition = ((b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  b2Vec2* startingVelocity = ((b2Vec2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMaxHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMaxHeight(*startingPosition,*startingVelocity);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMaxHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: contactListener of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_contactListener00
static int tolua_custom_bindings_pix2d_Physics_contactListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'contactListener'", NULL);
#endif
  {
   pix2d::ContactListener* tolua_ret = (pix2d::ContactListener*)  self->contactListener();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::ContactListener");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'contactListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: touchListener of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_touchListener00
static int tolua_custom_bindings_pix2d_Physics_touchListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'touchListener'", NULL);
#endif
  {
   pix2d::TouchListener* tolua_ret = (pix2d::TouchListener*)  self->touchListener();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::TouchListener");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'touchListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: layer of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_layer00
static int tolua_custom_bindings_pix2d_Physics_layer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'layer'", NULL);
#endif
  {
   pix2d::PhysicsLayer* tolua_ret = (pix2d::PhysicsLayer*)  self->layer();
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::PhysicsLayer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'layer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: unit of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_unit00
static int tolua_custom_bindings_pix2d_Physics_unit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unit'", NULL);
#endif
  {
   float tolua_ret = (float)  self->unit();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'unit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getUnitInPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getUnitInPixel00
static int tolua_custom_bindings_pix2d_Physics_getUnitInPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getUnitInPixel'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getUnitInPixel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getUnitInPixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: position of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_position00
static int tolua_custom_bindings_pix2d_Physics_position00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'position'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->position();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'position'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: positionInPixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_positionInPixel00
static int tolua_custom_bindings_pix2d_Physics_positionInPixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'positionInPixel'", NULL);
#endif
  {
   self->positionInPixel(&x,&y);
   tolua_pushnumber(tolua_S,(lua_Number)x);
   tolua_pushnumber(tolua_S,(lua_Number)y);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'positionInPixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: size of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_size00
static int tolua_custom_bindings_pix2d_Physics_size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'size'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->size();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'size'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizePixel of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_sizePixel00
static int tolua_custom_bindings_pix2d_Physics_sizePixel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sizePixel'", NULL);
#endif
  {
   CCSize tolua_ret = (CCSize)  self->sizePixel();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((CCSize)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(CCSize));
     tolua_pushusertype(tolua_S,tolua_obj,"CCSize");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizePixel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: sizeUnits of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_sizeUnits00
static int tolua_custom_bindings_pix2d_Physics_sizeUnits00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::Physics* self = (const pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'sizeUnits'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->sizeUnits();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'sizeUnits'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isPaused of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_isPaused00
static int tolua_custom_bindings_pix2d_Physics_isPaused00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isPaused'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isPaused();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isPaused'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: pause of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_pause00
static int tolua_custom_bindings_pix2d_Physics_pause00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'pause'", NULL);
#endif
  {
   self->pause();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'pause'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: resume of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_resume00
static int tolua_custom_bindings_pix2d_Physics_resume00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Physics* self = (pix2d::Physics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'resume'", NULL);
#endif
  {
   self->resume();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'resume'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDefaultBackgroundColor of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_setDefaultBackgroundColor00
static int tolua_custom_bindings_pix2d_Physics_setDefaultBackgroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float r = ((float)  tolua_tonumber(tolua_S,2,0));
  float g = ((float)  tolua_tonumber(tolua_S,3,0));
  float b = ((float)  tolua_tonumber(tolua_S,4,0));
  float a = ((float)  tolua_tonumber(tolua_S,5,0));
  {
   pix2d::Physics::setDefaultBackgroundColor(r,g,b,a);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDefaultBackgroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getDefaultBackgroundColor of class  pix2d::Physics */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Physics_getDefaultBackgroundColor00
static int tolua_custom_bindings_pix2d_Physics_getDefaultBackgroundColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::Physics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ccColor4F tolua_ret = (ccColor4F)  pix2d::Physics::getDefaultBackgroundColor();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccColor4F)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4F");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccColor4F));
     tolua_pushusertype(tolua_S,tolua_obj,"ccColor4F");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getDefaultBackgroundColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: query of class  pix2d::QueryMap */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_QueryMap_query00
static int tolua_custom_bindings_pix2d_QueryMap_query00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::QueryMap",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float width = ((float)  tolua_tonumber(tolua_S,4,0));
  float height = ((float)  tolua_tonumber(tolua_S,5,0));
  int tag = ((int)  tolua_tonumber(tolua_S,6,-1));
  {
   bool tolua_ret = (bool)  pix2d::QueryMap::query(x,y,width,height,tag);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'query'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bodyA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_bodyA_ptr
static int tolua_get_pix2d__ContactInfo_bodyA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyA'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bodyA,"b2Body");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bodyA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_bodyA_ptr
static int tolua_set_pix2d__ContactInfo_bodyA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyA'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Body",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bodyA = ((b2Body*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: bodyB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_bodyB_ptr
static int tolua_get_pix2d__ContactInfo_bodyB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyB'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->bodyB,"b2Body");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: bodyB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_bodyB_ptr
static int tolua_set_pix2d__ContactInfo_bodyB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'bodyB'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Body",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->bodyB = ((b2Body*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixtureA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_fixtureA_ptr
static int tolua_get_pix2d__ContactInfo_fixtureA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixtureA'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->fixtureA,"b2Fixture");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixtureA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_fixtureA_ptr
static int tolua_set_pix2d__ContactInfo_fixtureA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixtureA'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Fixture",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixtureA = ((b2Fixture*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixtureB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_fixtureB_ptr
static int tolua_get_pix2d__ContactInfo_fixtureB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixtureB'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->fixtureB,"b2Fixture");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixtureB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_fixtureB_ptr
static int tolua_set_pix2d__ContactInfo_fixtureB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixtureB'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Fixture",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixtureB = ((b2Fixture*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_pos
static int tolua_get_pix2d__ContactInfo_pos(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->pos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_pos
static int tolua_set_pix2d__ContactInfo_pos(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: localA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_localA
static int tolua_get_pix2d__ContactInfo_localA(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localA'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->localA,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: localA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_localA
static int tolua_set_pix2d__ContactInfo_localA(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localA'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->localA = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: localB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_localB
static int tolua_get_pix2d__ContactInfo_localB(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localB'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->localB,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: localB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_localB
static int tolua_set_pix2d__ContactInfo_localB(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localB'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->localB = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nodeA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_nodeA_ptr
static int tolua_get_pix2d__ContactInfo_nodeA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nodeA'",NULL);
#endif
   int nID = (self->nodeA) ? (int)self->nodeA->m_uID : -1;
    int* pLuaID = (self->nodeA) ? &self->nodeA->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->nodeA,"pix2d::PhysicNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nodeA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_nodeA_ptr
static int tolua_set_pix2d__ContactInfo_nodeA_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nodeA'",NULL);
  if (!tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nodeA = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: nodeB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_nodeB_ptr
static int tolua_get_pix2d__ContactInfo_nodeB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nodeB'",NULL);
#endif
   int nID = (self->nodeB) ? (int)self->nodeB->m_uID : -1;
    int* pLuaID = (self->nodeB) ? &self->nodeB->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->nodeB,"pix2d::PhysicNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nodeB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_nodeB_ptr
static int tolua_set_pix2d__ContactInfo_nodeB_ptr(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nodeB'",NULL);
  if (!tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nodeB = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: groupIndexA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_groupIndexA
static int tolua_get_pix2d__ContactInfo_groupIndexA(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndexA'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->groupIndexA);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: groupIndexA of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_groupIndexA
static int tolua_set_pix2d__ContactInfo_groupIndexA(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndexA'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->groupIndexA = ((signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: groupIndexB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_groupIndexB
static int tolua_get_pix2d__ContactInfo_groupIndexB(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndexB'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->groupIndexB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: groupIndexB of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_groupIndexB
static int tolua_set_pix2d__ContactInfo_groupIndexB(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'groupIndexB'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->groupIndexB = ((signed short)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: isTouching of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__ContactInfo_isTouching
static int tolua_get_pix2d__ContactInfo_isTouching(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isTouching'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->isTouching);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: isTouching of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__ContactInfo_isTouching
static int tolua_set_pix2d__ContactInfo_isTouching(lua_State* tolua_S)
{
  pix2d::ContactInfo* self = (pix2d::ContactInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'isTouching'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->isTouching = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactInfo_new00
static int tolua_custom_bindings_pix2d_ContactInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ContactInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::ContactInfo* tolua_ret = (pix2d::ContactInfo*)  Mtolua_new((pix2d::ContactInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::ContactInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::ContactInfo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactInfo_new00_local
static int tolua_custom_bindings_pix2d_ContactInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::ContactInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::ContactInfo* tolua_ret = (pix2d::ContactInfo*)  Mtolua_new((pix2d::ContactInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::ContactInfo");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelAllNotification of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_cancelAllNotification00
static int tolua_custom_bindings_pix2d_ContactListener_cancelAllNotification00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  const pix2d::PhysicNode* node = ((const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelAllNotification'", NULL);
#endif
  {
   self->cancelAllNotification(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelAllNotification'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelCollisionNotification of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotification00
static int tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotification00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  const pix2d::PhysicNode* node = ((const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelCollisionNotification'", NULL);
#endif
  {
   self->cancelCollisionNotification(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelCollisionNotification'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelCollisionNotificationWithId of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithId00
static int tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  const pix2d::PhysicNode* node = ((const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  int uid = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelCollisionNotificationWithId'", NULL);
#endif
  {
   self->cancelCollisionNotificationWithId(node,uid);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelCollisionNotificationWithId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelCollisionNotificationWithTag of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithTag00
static int tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  const pix2d::PhysicNode* node = ((const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelCollisionNotificationWithTag'", NULL);
#endif
  {
   self->cancelCollisionNotificationWithTag(node,tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelCollisionNotificationWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCollisionNotificationScript of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScript00
static int tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScript00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCollisionNotificationScript'", NULL);
#endif
  {
   int tolua_ret = (int)  self->registerCollisionNotificationScript(lo,node);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCollisionNotificationScript'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCollisionNotificationScriptWithId of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithId00
static int tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithId00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  int uid = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCollisionNotificationScriptWithId'", NULL);
#endif
  {
   int tolua_ret = (int)  self->registerCollisionNotificationScriptWithId(lo,node,uid);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCollisionNotificationScriptWithId'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerCollisionNotificationScriptWithTag of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithTag00
static int tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerCollisionNotificationScriptWithTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->registerCollisionNotificationScriptWithTag(lo,node,tag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerCollisionNotificationScriptWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerEndCollisionNotificationScriptWithTag of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_registerEndCollisionNotificationScriptWithTag00
static int tolua_custom_bindings_pix2d_ContactListener_registerEndCollisionNotificationScriptWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
  int tag = ((int)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerEndCollisionNotificationScriptWithTag'", NULL);
#endif
  {
   int tolua_ret = (int)  self->registerEndCollisionNotificationScriptWithTag(lo,node,tag);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerEndCollisionNotificationScriptWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelEndCollisionNotificationScritpWithTag of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_cancelEndCollisionNotificationScritpWithTag00
static int tolua_custom_bindings_pix2d_ContactListener_cancelEndCollisionNotificationScritpWithTag00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"const pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
  const pix2d::PhysicNode* node = ((const pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
  int tag = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelEndCollisionNotificationScritpWithTag'", NULL);
#endif
  {
   self->cancelEndCollisionNotificationScritpWithTag(node,tag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelEndCollisionNotificationScritpWithTag'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: dump of class  pix2d::ContactListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_ContactListener_dump00
static int tolua_custom_bindings_pix2d_ContactListener_dump00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::ContactListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::ContactListener* self = (pix2d::ContactListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'dump'", NULL);
#endif
  {
   self->dump();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'dump'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: body of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_body_ptr
static int tolua_get_pix2d__TouchInfo_body_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->body,"b2Body");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: body of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_body_ptr
static int tolua_set_pix2d__TouchInfo_body_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Body",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->body = ((b2Body*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: fixture of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_fixture_ptr
static int tolua_get_pix2d__TouchInfo_fixture_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->fixture,"b2Fixture");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: fixture of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_fixture_ptr
static int tolua_set_pix2d__TouchInfo_fixture_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'fixture'",NULL);
  if (!tolua_isusertype(tolua_S,2,"b2Fixture",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->fixture = ((b2Fixture*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pos of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_pos
static int tolua_get_pix2d__TouchInfo_pos(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->pos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pos of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_pos
static int tolua_set_pix2d__TouchInfo_pos(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: localpos of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_localpos
static int tolua_get_pix2d__TouchInfo_localpos(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localpos'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->localpos,"b2Vec2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: localpos of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_localpos
static int tolua_set_pix2d__TouchInfo_localpos(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'localpos'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"b2Vec2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->localpos = *((b2Vec2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: node of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_node_ptr
static int tolua_get_pix2d__TouchInfo_node_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node'",NULL);
#endif
   int nID = (self->node) ? (int)self->node->m_uID : -1;
    int* pLuaID = (self->node) ? &self->node->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->node,"pix2d::PhysicNode");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: node of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_node_ptr
static int tolua_set_pix2d__TouchInfo_node_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node'",NULL);
  if (!tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: touch of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_touch_ptr
static int tolua_get_pix2d__TouchInfo_touch_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touch'",NULL);
#endif
   int nID = (self->touch) ? (int)self->touch->m_uID : -1;
    int* pLuaID = (self->touch) ? &self->touch->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->touch,"CCTouch");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touch of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_touch_ptr
static int tolua_set_pix2d__TouchInfo_touch_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touch'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCTouch",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->touch = ((CCTouch*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: event of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_event_ptr
static int tolua_get_pix2d__TouchInfo_event_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'event'",NULL);
#endif
   int nID = (self->event) ? (int)self->event->m_uID : -1;
    int* pLuaID = (self->event) ? &self->event->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)self->event,"CCEvent");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: event of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_event_ptr
static int tolua_set_pix2d__TouchInfo_event_ptr(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'event'",NULL);
  if (!tolua_isusertype(tolua_S,2,"CCEvent",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->event = ((CCEvent*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: hasMoved of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__TouchInfo_hasMoved
static int tolua_get_pix2d__TouchInfo_hasMoved(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasMoved'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->hasMoved);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: hasMoved of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__TouchInfo_hasMoved
static int tolua_set_pix2d__TouchInfo_hasMoved(lua_State* tolua_S)
{
  pix2d::TouchInfo* self = (pix2d::TouchInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'hasMoved'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->hasMoved = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchInfo_new00
static int tolua_custom_bindings_pix2d_TouchInfo_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TouchInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::TouchInfo* tolua_ret = (pix2d::TouchInfo*)  Mtolua_new((pix2d::TouchInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::TouchInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  pix2d::TouchInfo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchInfo_new00_local
static int tolua_custom_bindings_pix2d_TouchInfo_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::TouchInfo",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::TouchInfo* tolua_ret = (pix2d::TouchInfo*)  Mtolua_new((pix2d::TouchInfo)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::TouchInfo");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: registerTouchScriptHandler of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_registerTouchScriptHandler00
static int tolua_custom_bindings_pix2d_TouchListener_registerTouchScriptHandler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  LUA_FUNCTION lo = (  toluafix_ref_function(tolua_S,2,0));
  pix2d::PhysicNode* target = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'registerTouchScriptHandler'", NULL);
#endif
  {
   self->registerTouchScriptHandler(lo,target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'registerTouchScriptHandler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: cancelTouchDelegate of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_cancelTouchDelegate00
static int tolua_custom_bindings_pix2d_TouchListener_cancelTouchDelegate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"pix2d::PhysicNode",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  pix2d::PhysicNode* node = ((pix2d::PhysicNode*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'cancelTouchDelegate'", NULL);
#endif
  {
   self->cancelTouchDelegate(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'cancelTouchDelegate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: destroyMouseJoint of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_destroyMouseJoint00
static int tolua_custom_bindings_pix2d_TouchListener_destroyMouseJoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'destroyMouseJoint'", NULL);
#endif
  {
   self->destroyMouseJoint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'destroyMouseJoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMouseJointMaxForce of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_setMouseJointMaxForce00
static int tolua_custom_bindings_pix2d_TouchListener_setMouseJointMaxForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMouseJointMaxForce'", NULL);
#endif
  {
   self->setMouseJointMaxForce(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMouseJointMaxForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMouseJointMaxForce of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_getMouseJointMaxForce00
static int tolua_custom_bindings_pix2d_TouchListener_getMouseJointMaxForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMouseJointMaxForce'", NULL);
#endif
  {
   float tolua_ret = (float)  self->getMouseJointMaxForce(value);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMouseJointMaxForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMouseJointFrequency of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_setMouseJointFrequency00
static int tolua_custom_bindings_pix2d_TouchListener_setMouseJointFrequency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMouseJointFrequency'", NULL);
#endif
  {
   self->setMouseJointFrequency(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMouseJointFrequency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMouseJointDamping of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_setMouseJointDamping00
static int tolua_custom_bindings_pix2d_TouchListener_setMouseJointDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::TouchListener* self = (pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMouseJointDamping'", NULL);
#endif
  {
   self->setMouseJointDamping(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMouseJointDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getReactionForce of class  pix2d::TouchListener */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_TouchListener_getReactionForce00
static int tolua_custom_bindings_pix2d_TouchListener_getReactionForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const pix2d::TouchListener",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const pix2d::TouchListener* self = (const pix2d::TouchListener*)  tolua_tousertype(tolua_S,1,0);
  float inv_dt = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getReactionForce'", NULL);
#endif
  {
   b2Vec2 tolua_ret = (b2Vec2)  self->getReactionForce(inv_dt);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((b2Vec2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(b2Vec2));
     tolua_pushusertype(tolua_S,tolua_obj,"b2Vec2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getReactionForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSpeed of class  pix2d::Action */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_Action_setSpeed00
static int tolua_custom_bindings_pix2d_Action_setSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d::Action",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d::Action* self = (pix2d::Action*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSpeed'", NULL);
#endif
  {
   self->setSpeed(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::MoveTo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_MoveTo_create00
static int tolua_custom_bindings_pix2d_MoveTo_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::MoveTo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Vec2* start = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  const b2Vec2* dest = ((const b2Vec2*)  tolua_tousertype(tolua_S,3,0));
  float speed = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   pix2d::MoveTo* tolua_ret = (pix2d::MoveTo*)  pix2d::MoveTo::create(*start,*dest,speed);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::MoveTo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::CircleTo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_CircleTo_create00
static int tolua_custom_bindings_pix2d_CircleTo_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::CircleTo",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const b2Vec2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const b2Vec2* center = ((const b2Vec2*)  tolua_tousertype(tolua_S,2,0));
  float duration = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d::CircleTo* tolua_ret = (pix2d::CircleTo*)  pix2d::CircleTo::create(*center,duration);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::CircleTo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d::SplineTo */
#ifndef TOLUA_DISABLE_tolua_custom_bindings_pix2d_SplineTo_create00
static int tolua_custom_bindings_pix2d_SplineTo_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::SplineTo",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"CCPointArray",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  float duration = ((float)  tolua_tonumber(tolua_S,2,0));
  CCPointArray* points = ((CCPointArray*)  tolua_tousertype(tolua_S,3,0));
  float tension = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   pix2d::SplineTo* tolua_ret = (pix2d::SplineTo*)  pix2d::SplineTo::create(duration,points,tension);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"pix2d::SplineTo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_custom_bindings_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"CCClippingNode","CCClippingNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCClippingNode");
   tolua_function(tolua_S,"create",tolua_custom_bindings_CCClippingNode_create00);
   tolua_function(tolua_S,"create",tolua_custom_bindings_CCClippingNode_create01);
   tolua_function(tolua_S,"getStencil",tolua_custom_bindings_CCClippingNode_getStencil00);
   tolua_function(tolua_S,"setStencil",tolua_custom_bindings_CCClippingNode_setStencil00);
   tolua_function(tolua_S,"getAlphaThreshold",tolua_custom_bindings_CCClippingNode_getAlphaThreshold00);
   tolua_function(tolua_S,"setAlphaThreshold",tolua_custom_bindings_CCClippingNode_setAlphaThreshold00);
   tolua_function(tolua_S,"isInverted",tolua_custom_bindings_CCClippingNode_isInverted00);
   tolua_function(tolua_S,"setInverted",tolua_custom_bindings_CCClippingNode_setInverted00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCActionTween","CCActionTween","CCActionInterval",NULL);
  tolua_beginmodule(tolua_S,"CCActionTween");
   tolua_function(tolua_S,"create",tolua_custom_bindings_CCActionTween_create00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CCDrawNode","CCDrawNode","CCNode",NULL);
  tolua_beginmodule(tolua_S,"CCDrawNode");
   tolua_function(tolua_S,"create",tolua_custom_bindings_CCDrawNode_create00);
   tolua_function(tolua_S,"drawDot",tolua_custom_bindings_CCDrawNode_drawDot00);
   tolua_function(tolua_S,"drawSegment",tolua_custom_bindings_CCDrawNode_drawSegment00);
   tolua_function(tolua_S,"drawQuadraticBezier",tolua_custom_bindings_CCDrawNode_drawQuadraticBezier00);
   tolua_function(tolua_S,"clear",tolua_custom_bindings_CCDrawNode_clear00);
   tolua_function(tolua_S,"getBlendFunc",tolua_custom_bindings_CCDrawNode_getBlendFunc00);
   tolua_function(tolua_S,"setBlendFunc",tolua_custom_bindings_CCDrawNode_setBlendFunc00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"b2Vec2","b2Vec2","",tolua_collect_b2Vec2);
  #else
  tolua_cclass(tolua_S,"b2Vec2","b2Vec2","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"b2Vec2");
   tolua_function(tolua_S,"new",tolua_custom_bindings_b2Vec2_new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_b2Vec2_new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_b2Vec2_new00_local);
   tolua_function(tolua_S,"new",tolua_custom_bindings_b2Vec2_new01);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_b2Vec2_new01_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_b2Vec2_new01_local);
   tolua_function(tolua_S,"SetZero",tolua_custom_bindings_b2Vec2_SetZero00);
   tolua_function(tolua_S,"Set",tolua_custom_bindings_b2Vec2_Set00);
   tolua_variable(tolua_S,"x",tolua_get_b2Vec2_x,tolua_set_b2Vec2_x);
   tolua_variable(tolua_S,"y",tolua_get_b2Vec2_y,tolua_set_b2Vec2_y);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"b2_staticBody",b2_staticBody);
  tolua_constant(tolua_S,"b2_kinematicBody",b2_kinematicBody);
  tolua_constant(tolua_S,"b2_dynamicBody",b2_dynamicBody);
  tolua_cclass(tolua_S,"b2Joint","b2Joint","",NULL);
  tolua_beginmodule(tolua_S,"b2Joint");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2DistanceJoint","b2DistanceJoint","b2Joint",NULL);
  tolua_beginmodule(tolua_S,"b2DistanceJoint");
   tolua_function(tolua_S,"GetReactionForce",tolua_custom_bindings_b2DistanceJoint_GetReactionForce00);
   tolua_function(tolua_S,"GetReactionTorque",tolua_custom_bindings_b2DistanceJoint_GetReactionTorque00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2WeldJoint","b2WeldJoint","b2Joint",NULL);
  tolua_beginmodule(tolua_S,"b2WeldJoint");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"b2RevoluteJoint","b2RevoluteJoint","b2Joint",NULL);
  tolua_beginmodule(tolua_S,"b2RevoluteJoint");
   tolua_function(tolua_S,"GetAnchorA",tolua_custom_bindings_b2RevoluteJoint_GetAnchorA00);
   tolua_function(tolua_S,"GetAnchorB",tolua_custom_bindings_b2RevoluteJoint_GetAnchorB00);
   tolua_function(tolua_S,"GetLocalAnchorA",tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorA00);
   tolua_function(tolua_S,"GetLocalAnchorB",tolua_custom_bindings_b2RevoluteJoint_GetLocalAnchorB00);
   tolua_function(tolua_S,"GetReferenceAngle",tolua_custom_bindings_b2RevoluteJoint_GetReferenceAngle00);
   tolua_function(tolua_S,"GetJointAngle",tolua_custom_bindings_b2RevoluteJoint_GetJointAngle00);
   tolua_function(tolua_S,"GetJointSpeed",tolua_custom_bindings_b2RevoluteJoint_GetJointSpeed00);
   tolua_function(tolua_S,"IsLimitEnabled",tolua_custom_bindings_b2RevoluteJoint_IsLimitEnabled00);
   tolua_function(tolua_S,"EnableLimit",tolua_custom_bindings_b2RevoluteJoint_EnableLimit00);
   tolua_function(tolua_S,"GetLowerLimit",tolua_custom_bindings_b2RevoluteJoint_GetLowerLimit00);
   tolua_function(tolua_S,"GetUpperLimit",tolua_custom_bindings_b2RevoluteJoint_GetUpperLimit00);
   tolua_function(tolua_S,"SetLimits",tolua_custom_bindings_b2RevoluteJoint_SetLimits00);
   tolua_function(tolua_S,"IsMotorEnabled",tolua_custom_bindings_b2RevoluteJoint_IsMotorEnabled00);
   tolua_function(tolua_S,"EnableMotor",tolua_custom_bindings_b2RevoluteJoint_EnableMotor00);
   tolua_function(tolua_S,"SetMotorSpeed",tolua_custom_bindings_b2RevoluteJoint_SetMotorSpeed00);
   tolua_function(tolua_S,"GetMotorSpeed",tolua_custom_bindings_b2RevoluteJoint_GetMotorSpeed00);
   tolua_function(tolua_S,"SetMaxMotorTorque",tolua_custom_bindings_b2RevoluteJoint_SetMaxMotorTorque00);
   tolua_function(tolua_S,"GetMaxMotorTorque",tolua_custom_bindings_b2RevoluteJoint_GetMaxMotorTorque00);
   tolua_function(tolua_S,"GetReactionForce",tolua_custom_bindings_b2RevoluteJoint_GetReactionForce00);
   tolua_function(tolua_S,"GetReactionTorque",tolua_custom_bindings_b2RevoluteJoint_GetReactionTorque00);
   tolua_function(tolua_S,"GetMotorTorque",tolua_custom_bindings_b2RevoluteJoint_GetMotorTorque00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"b2RayCastInput","b2RayCastInput","",tolua_collect_b2RayCastInput);
  #else
  tolua_cclass(tolua_S,"b2RayCastInput","b2RayCastInput","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"b2RayCastInput");
   tolua_variable(tolua_S,"p1",tolua_get_b2RayCastInput_p1,tolua_set_b2RayCastInput_p1);
   tolua_variable(tolua_S,"p2",tolua_get_b2RayCastInput_p2,tolua_set_b2RayCastInput_p2);
   tolua_variable(tolua_S,"maxFraction",tolua_get_b2RayCastInput_maxFraction,tolua_set_b2RayCastInput_maxFraction);
   tolua_function(tolua_S,"new",tolua_custom_bindings_b2RayCastInput_new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_b2RayCastInput_new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_b2RayCastInput_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"b2RayCastOutput","b2RayCastOutput","",tolua_collect_b2RayCastOutput);
  #else
  tolua_cclass(tolua_S,"b2RayCastOutput","b2RayCastOutput","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"b2RayCastOutput");
   tolua_variable(tolua_S,"normal",tolua_get_b2RayCastOutput_normal,tolua_set_b2RayCastOutput_normal);
   tolua_variable(tolua_S,"fraction",tolua_get_b2RayCastOutput_fraction,tolua_set_b2RayCastOutput_fraction);
   tolua_function(tolua_S,"new",tolua_custom_bindings_b2RayCastOutput_new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_b2RayCastOutput_new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_b2RayCastOutput_new00_local);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"vector_string_","vector<string>","",tolua_collect_vector_string_);
  #else
  tolua_cclass(tolua_S,"vector_string_","vector<string>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"vector_string_");
   tolua_function(tolua_S,"clear",tolua_custom_bindings_vector_string__clear00);
   tolua_function(tolua_S,"size",tolua_custom_bindings_vector_string__size00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_string___geti00);
   tolua_function(tolua_S,".seti",tolua_custom_bindings_vector_string___seti00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_string___geti01);
   tolua_function(tolua_S,"push_back",tolua_custom_bindings_vector_string__push_back00);
   tolua_function(tolua_S,"new",tolua_custom_bindings_vector_string__new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_vector_string__new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_vector_string__new00_local);
   tolua_function(tolua_S,"delete",tolua_custom_bindings_vector_string__delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"vector_CCPoint_","vector<CCPoint>","",tolua_collect_vector_CCPoint_);
  #else
  tolua_cclass(tolua_S,"vector_CCPoint_","vector<CCPoint>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"vector_CCPoint_");
   tolua_function(tolua_S,"clear",tolua_custom_bindings_vector_CCPoint__clear00);
   tolua_function(tolua_S,"size",tolua_custom_bindings_vector_CCPoint__size00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_CCPoint___geti00);
   tolua_function(tolua_S,".seti",tolua_custom_bindings_vector_CCPoint___seti00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_CCPoint___geti01);
   tolua_function(tolua_S,"push_back",tolua_custom_bindings_vector_CCPoint__push_back00);
   tolua_function(tolua_S,"new",tolua_custom_bindings_vector_CCPoint__new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_vector_CCPoint__new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_vector_CCPoint__new00_local);
   tolua_function(tolua_S,"delete",tolua_custom_bindings_vector_CCPoint__delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"vector_b2Vec2_","vector<b2Vec2>","",tolua_collect_vector_b2Vec2_);
  #else
  tolua_cclass(tolua_S,"vector_b2Vec2_","vector<b2Vec2>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"vector_b2Vec2_");
   tolua_function(tolua_S,"clear",tolua_custom_bindings_vector_b2Vec2__clear00);
   tolua_function(tolua_S,"size",tolua_custom_bindings_vector_b2Vec2__size00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_b2Vec2___geti00);
   tolua_function(tolua_S,".seti",tolua_custom_bindings_vector_b2Vec2___seti00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_b2Vec2___geti01);
   tolua_function(tolua_S,"push_back",tolua_custom_bindings_vector_b2Vec2__push_back00);
   tolua_function(tolua_S,"new",tolua_custom_bindings_vector_b2Vec2__new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_vector_b2Vec2__new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_vector_b2Vec2__new00_local);
   tolua_function(tolua_S,"delete",tolua_custom_bindings_vector_b2Vec2__delete00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"vector_pix2d__BezierCurve_","vector<pix2d::BezierCurve>","",tolua_collect_vector_pix2d__BezierCurve_);
  #else
  tolua_cclass(tolua_S,"vector_pix2d__BezierCurve_","vector<pix2d::BezierCurve>","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"vector_pix2d__BezierCurve_");
   tolua_function(tolua_S,"clear",tolua_custom_bindings_vector_pix2d__BezierCurve__clear00);
   tolua_function(tolua_S,"size",tolua_custom_bindings_vector_pix2d__BezierCurve__size00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_pix2d__BezierCurve___geti00);
   tolua_function(tolua_S,".seti",tolua_custom_bindings_vector_pix2d__BezierCurve___seti00);
   tolua_function(tolua_S,".geti",tolua_custom_bindings_vector_pix2d__BezierCurve___geti01);
   tolua_function(tolua_S,"push_back",tolua_custom_bindings_vector_pix2d__BezierCurve__push_back00);
   tolua_function(tolua_S,"new",tolua_custom_bindings_vector_pix2d__BezierCurve__new00);
   tolua_function(tolua_S,"new_local",tolua_custom_bindings_vector_pix2d__BezierCurve__new00_local);
   tolua_function(tolua_S,".call",tolua_custom_bindings_vector_pix2d__BezierCurve__new00_local);
   tolua_function(tolua_S,"delete",tolua_custom_bindings_vector_pix2d__BezierCurve__delete00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AppDelegate","AppDelegate","private cocos2d::CCApplication",NULL);
  tolua_beginmodule(tolua_S,"AppDelegate");
   tolua_function(tolua_S,"registerScriptHandler",tolua_custom_bindings_AppDelegate_registerScriptHandler00);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"pix2d",0);
  tolua_beginmodule(tolua_S,"pix2d");
   tolua_cclass(tolua_S,"Native","pix2d::Native","",NULL);
   tolua_beginmodule(tolua_S,"Native");
    tolua_function(tolua_S,"getInstance",tolua_custom_bindings_pix2d_Native_getInstance00);
    tolua_function(tolua_S,"openURL",tolua_custom_bindings_pix2d_Native_openURL00);
    tolua_function(tolua_S,"hideAd",tolua_custom_bindings_pix2d_Native_hideAd00);
    tolua_function(tolua_S,"showAd",tolua_custom_bindings_pix2d_Native_showAd00);
    tolua_function(tolua_S,"exitApp",tolua_custom_bindings_pix2d_Native_exitApp00);
    tolua_function(tolua_S,"registerAdMobScriptHandler",tolua_custom_bindings_pix2d_Native_registerAdMobScriptHandler00);
    tolua_function(tolua_S,"unregisterAdMobScriptHandler",tolua_custom_bindings_pix2d_Native_unregisterAdMobScriptHandler00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"BezierCurve","pix2d::BezierCurve","",tolua_collect_pix2d__BezierCurve);
   #else
   tolua_cclass(tolua_S,"BezierCurve","pix2d::BezierCurve","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"BezierCurve");
    tolua_function(tolua_S,"pointAt",tolua_custom_bindings_pix2d_BezierCurve_pointAt00);
    tolua_function(tolua_S,"point",tolua_custom_bindings_pix2d_BezierCurve_point00);
    tolua_function(tolua_S,"order",tolua_custom_bindings_pix2d_BezierCurve_order00);
    tolua_function(tolua_S,"initialPoint",tolua_custom_bindings_pix2d_BezierCurve_initialPoint00);
    tolua_function(tolua_S,"finalPoint",tolua_custom_bindings_pix2d_BezierCurve_finalPoint00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"LineBezier","pix2d::LineBezier","pix2d::BezierCurve",tolua_collect_pix2d__LineBezier);
   #else
   tolua_cclass(tolua_S,"LineBezier","pix2d::LineBezier","pix2d::BezierCurve",NULL);
   #endif
   tolua_beginmodule(tolua_S,"LineBezier");
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_LineBezier_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_LineBezier_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_LineBezier_new00_local);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"QuadBezier","pix2d::QuadBezier","pix2d::BezierCurve",tolua_collect_pix2d__QuadBezier);
   #else
   tolua_cclass(tolua_S,"QuadBezier","pix2d::QuadBezier","pix2d::BezierCurve",NULL);
   #endif
   tolua_beginmodule(tolua_S,"QuadBezier");
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_QuadBezier_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_QuadBezier_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_QuadBezier_new00_local);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CubicBezier","pix2d::CubicBezier","pix2d::BezierCurve",tolua_collect_pix2d__CubicBezier);
   #else
   tolua_cclass(tolua_S,"CubicBezier","pix2d::CubicBezier","pix2d::BezierCurve",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CubicBezier");
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_CubicBezier_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_CubicBezier_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_CubicBezier_new00_local);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"BezierPath","pix2d::BezierPath","vector<pix2d::BezierCurve>",tolua_collect_pix2d__BezierPath);
   #else
   tolua_cclass(tolua_S,"BezierPath","pix2d::BezierPath","vector<pix2d::BezierCurve>",NULL);
   #endif
   tolua_beginmodule(tolua_S,"BezierPath");
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_BezierPath_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_BezierPath_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_BezierPath_new00_local);
    tolua_function(tolua_S,"close",tolua_custom_bindings_pix2d_BezierPath_close00);
    tolua_function(tolua_S,"closed",tolua_custom_bindings_pix2d_BezierPath_closed00);
    tolua_function(tolua_S,"empty",tolua_custom_bindings_pix2d_BezierPath_empty00);
    tolua_function(tolua_S,"initialPoint",tolua_custom_bindings_pix2d_BezierPath_initialPoint00);
    tolua_function(tolua_S,"finalPoint",tolua_custom_bindings_pix2d_BezierPath_finalPoint00);
    tolua_function(tolua_S,"pointAt",tolua_custom_bindings_pix2d_BezierPath_pointAt00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CocosBuilderLua","pix2d::CocosBuilderLua","CCObject",NULL);
   tolua_beginmodule(tolua_S,"CocosBuilderLua");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CocosBuilderLua_create00);
    tolua_function(tolua_S,"registerLoaders",tolua_custom_bindings_pix2d_CocosBuilderLua_registerLoaders00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"NodeUtil","pix2d::NodeUtil","",NULL);
   tolua_beginmodule(tolua_S,"NodeUtil");
    tolua_function(tolua_S,"pauseSchedulerAndActions",tolua_custom_bindings_pix2d_NodeUtil_pauseSchedulerAndActions00);
    tolua_function(tolua_S,"resumeSchedulerAndActions",tolua_custom_bindings_pix2d_NodeUtil_resumeSchedulerAndActions00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"DrawNode","pix2d::DrawNode","CCDrawNode",NULL);
   tolua_beginmodule(tolua_S,"DrawNode");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_DrawNode_create00);
    tolua_function(tolua_S,"drawPolygon",tolua_custom_bindings_pix2d_DrawNode_drawPolygon00);
    tolua_function(tolua_S,"drawCircle",tolua_custom_bindings_pix2d_DrawNode_drawCircle00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PostProcessing","pix2d::PostProcessing","CCNode",NULL);
   tolua_beginmodule(tolua_S,"PostProcessing");
    tolua_function(tolua_S,"capture",tolua_custom_bindings_pix2d_PostProcessing_capture00);
    tolua_function(tolua_S,"getFrameBuffer",tolua_custom_bindings_pix2d_PostProcessing_getFrameBuffer00);
    tolua_function(tolua_S,"refresh",tolua_custom_bindings_pix2d_PostProcessing_refresh00);
    tolua_function(tolua_S,"clear",tolua_custom_bindings_pix2d_PostProcessing_clear00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"DoublePostProcessing","pix2d::DoublePostProcessing","pix2d::PostProcessing",NULL);
   tolua_beginmodule(tolua_S,"DoublePostProcessing");
    tolua_function(tolua_S,"getFrameBuffer",tolua_custom_bindings_pix2d_DoublePostProcessing_getFrameBuffer00);
    tolua_function(tolua_S,"refresh",tolua_custom_bindings_pix2d_DoublePostProcessing_refresh00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Pixelation","pix2d::Pixelation","pix2d::PostProcessing",NULL);
   tolua_beginmodule(tolua_S,"Pixelation");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Pixelation_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Grayscale","pix2d::Grayscale","pix2d::PostProcessing",NULL);
   tolua_beginmodule(tolua_S,"Grayscale");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Grayscale_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"FastBlur","pix2d::FastBlur","pix2d::DoublePostProcessing",NULL);
   tolua_beginmodule(tolua_S,"FastBlur");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_FastBlur_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"GaussianBlur","pix2d::GaussianBlur","pix2d::DoublePostProcessing",NULL);
   tolua_beginmodule(tolua_S,"GaussianBlur");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_GaussianBlur_create00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Graph","pix2d::Graph","",tolua_collect_pix2d__Graph);
   #else
   tolua_cclass(tolua_S,"Graph","pix2d::Graph","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Graph");
    tolua_constant(tolua_S,"unknown",pix2d::Graph::kUnknown);
    tolua_constant(tolua_S,"empty",pix2d::Graph::kEmpty);
    tolua_constant(tolua_S,"solidGround",pix2d::Graph::kSolidGround);
    tolua_constant(tolua_S,"solved",pix2d::Graph::kSolved);
    tolua_constant(tolua_S,"noSolution",pix2d::Graph::kNoSolution);
    tolua_constant(tolua_S,"startEndSame",pix2d::Graph::kStartEndSame);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_Graph_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_Graph_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_Graph_new00_local);
    tolua_function(tolua_S,"update",tolua_custom_bindings_pix2d_Graph_update00);
    tolua_function(tolua_S,"solve",tolua_custom_bindings_pix2d_Graph_solve00);
    tolua_function(tolua_S,"getSize",tolua_custom_bindings_pix2d_Graph_getSize00);
    tolua_function(tolua_S,"dump",tolua_custom_bindings_pix2d_Graph_dump00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Assets","pix2d::Assets","",NULL);
   tolua_beginmodule(tolua_S,"Assets");
    tolua_constant(tolua_S,"Robot",pix2d::Assets::kRoboto);
    tolua_constant(tolua_S,"Chewy",pix2d::Assets::kChewy);
    tolua_constant(tolua_S,"Tiny",pix2d::Assets::kFontSizeTiny);
    tolua_constant(tolua_S,"Small",pix2d::Assets::kFontSizeSmall);
    tolua_constant(tolua_S,"Medium",pix2d::Assets::kFontSizeMedium);
    tolua_constant(tolua_S,"Large",pix2d::Assets::kFontSizeLarge);
    tolua_constant(tolua_S,"Huge",pix2d::Assets::kFontSizeHuge);
    tolua_function(tolua_S,"font",tolua_custom_bindings_pix2d_Assets_font00);
    tolua_function(tolua_S,"fontSize",tolua_custom_bindings_pix2d_Assets_fontSize00);
    tolua_function(tolua_S,"writeTextFile",tolua_custom_bindings_pix2d_Assets_writeTextFile00);
    tolua_function(tolua_S,"readTextFile",tolua_custom_bindings_pix2d_Assets_readTextFile00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"TouchGrabber","pix2d::TouchGrabber","CCLayer",NULL);
   tolua_beginmodule(tolua_S,"TouchGrabber");
    tolua_function(tolua_S,"load",tolua_custom_bindings_pix2d_TouchGrabber_load00);
    tolua_function(tolua_S,"save",tolua_custom_bindings_pix2d_TouchGrabber_save00);
    tolua_function(tolua_S,"play",tolua_custom_bindings_pix2d_TouchGrabber_play00);
    tolua_function(tolua_S,"stop",tolua_custom_bindings_pix2d_TouchGrabber_stop00);
    tolua_function(tolua_S,"record",tolua_custom_bindings_pix2d_TouchGrabber_record00);
    tolua_function(tolua_S,"isRecording",tolua_custom_bindings_pix2d_TouchGrabber_isRecording00);
    tolua_function(tolua_S,"isPlaying",tolua_custom_bindings_pix2d_TouchGrabber_isPlaying00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"OpacityNode","pix2d::OpacityNode","CCNodeRGBA",NULL);
   tolua_beginmodule(tolua_S,"OpacityNode");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_OpacityNode_create00);
    tolua_function(tolua_S,"setOpacity",tolua_custom_bindings_pix2d_OpacityNode_setOpacity00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CustomMenuItem","pix2d::CustomMenuItem","CCMenuItemImage",NULL);
   tolua_beginmodule(tolua_S,"CustomMenuItem");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CustomMenuItem_create00);
    tolua_function(tolua_S,"registerScriptHandler",tolua_custom_bindings_pix2d_CustomMenuItem_registerScriptHandler00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CustomLabelTTF","pix2d::CustomLabelTTF","CCLabelTTF",NULL);
   tolua_beginmodule(tolua_S,"CustomLabelTTF");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CustomLabelTTF_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CustomMenuItemFont","pix2d::CustomMenuItemFont","CCMenuItemFont",NULL);
   tolua_beginmodule(tolua_S,"CustomMenuItemFont");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CustomMenuItemFont_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CustomMenuItemToggle","pix2d::CustomMenuItemToggle","CCMenuItemToggle",NULL);
   tolua_beginmodule(tolua_S,"CustomMenuItemToggle");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CustomMenuItemToggle_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"TextureSprite","pix2d::TextureSprite","CCNodeRGBA",NULL);
   tolua_beginmodule(tolua_S,"TextureSprite");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_TextureSprite_create00);
    tolua_function(tolua_S,"createWithAABB",tolua_custom_bindings_pix2d_TextureSprite_createWithAABB00);
    tolua_function(tolua_S,"translateTexCoord",tolua_custom_bindings_pix2d_TextureSprite_translateTexCoord00);
    tolua_function(tolua_S,"setRepeat",tolua_custom_bindings_pix2d_TextureSprite_setRepeat00);
    tolua_function(tolua_S,"getTextureSize",tolua_custom_bindings_pix2d_TextureSprite_getTextureSize00);
    tolua_function(tolua_S,"setBlendFunc",tolua_custom_bindings_pix2d_TextureSprite_setBlendFunc00);
    tolua_function(tolua_S,"getBlendFunc",tolua_custom_bindings_pix2d_TextureSprite_getBlendFunc00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ActionTweenLua","pix2d::ActionTweenLua","CCActionInterval",NULL);
   tolua_beginmodule(tolua_S,"ActionTweenLua");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_ActionTweenLua_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CustomSprite","pix2d::CustomSprite","CCSprite",NULL);
   tolua_beginmodule(tolua_S,"CustomSprite");
    tolua_function(tolua_S,"createWithSpriteFrameName",tolua_custom_bindings_pix2d_CustomSprite_createWithSpriteFrameName00);
    tolua_function(tolua_S,"registerTweenActionHandler",tolua_custom_bindings_pix2d_CustomSprite_registerTweenActionHandler00);
    tolua_function(tolua_S,"unregisterTweenActionHandler",tolua_custom_bindings_pix2d_CustomSprite_unregisterTweenActionHandler00);
    tolua_function(tolua_S,"setQuad",tolua_custom_bindings_pix2d_CustomSprite_setQuad00);
    tolua_variable(tolua_S,"__CCActionTweenDelegate__",tolua_get_pix2d__CustomSprite___CCActionTweenDelegate__,NULL);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PhysicNodeDef","pix2d::PhysicNodeDef","",NULL);
   tolua_beginmodule(tolua_S,"PhysicNodeDef");
    tolua_variable(tolua_S,"uid",tolua_get_pix2d__PhysicNodeDef_uid,tolua_set_pix2d__PhysicNodeDef_uid);
    tolua_variable(tolua_S,"tag",tolua_get_pix2d__PhysicNodeDef_tag,tolua_set_pix2d__PhysicNodeDef_tag);
    tolua_variable(tolua_S,"zorder",tolua_get_pix2d__PhysicNodeDef_zorder,tolua_set_pix2d__PhysicNodeDef_zorder);
    tolua_variable(tolua_S,"fixture",tolua_get_pix2d__PhysicNodeDef_fixture,tolua_set_pix2d__PhysicNodeDef_fixture);
    tolua_variable(tolua_S,"body",tolua_get_pix2d__PhysicNodeDef_body,tolua_set_pix2d__PhysicNodeDef_body);
    tolua_variable(tolua_S,"body_type",tolua_get_pix2d__PhysicNodeDef_body_type,tolua_set_pix2d__PhysicNodeDef_body_type);
    tolua_variable(tolua_S,"sprite",tolua_get_pix2d__PhysicNodeDef_sprite,tolua_set_pix2d__PhysicNodeDef_sprite);
    tolua_variable(tolua_S,"frame",tolua_get_pix2d__PhysicNodeDef_frame,tolua_set_pix2d__PhysicNodeDef_frame);
    tolua_variable(tolua_S,"pos",tolua_get_pix2d__PhysicNodeDef_pos,tolua_set_pix2d__PhysicNodeDef_pos);
    tolua_variable(tolua_S,"angle",tolua_get_pix2d__PhysicNodeDef_angle,tolua_set_pix2d__PhysicNodeDef_angle);
    tolua_variable(tolua_S,"is_sensor",tolua_get_pix2d__PhysicNodeDef_is_sensor,tolua_set_pix2d__PhysicNodeDef_is_sensor);
    tolua_variable(tolua_S,"restitution",tolua_get_pix2d__PhysicNodeDef_restitution,tolua_set_pix2d__PhysicNodeDef_restitution);
    tolua_variable(tolua_S,"density",tolua_get_pix2d__PhysicNodeDef_density,tolua_set_pix2d__PhysicNodeDef_density);
    tolua_variable(tolua_S,"friction",tolua_get_pix2d__PhysicNodeDef_friction,tolua_set_pix2d__PhysicNodeDef_friction);
    tolua_variable(tolua_S,"category",tolua_get_pix2d__PhysicNodeDef_unsigned_category,tolua_set_pix2d__PhysicNodeDef_unsigned_category);
    tolua_variable(tolua_S,"mask",tolua_get_pix2d__PhysicNodeDef_unsigned_mask,tolua_set_pix2d__PhysicNodeDef_unsigned_mask);
    tolua_variable(tolua_S,"group",tolua_get_pix2d__PhysicNodeDef_group,tolua_set_pix2d__PhysicNodeDef_group);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PhysicNode","pix2d::PhysicNode","CCNodeRGBA",NULL);
   tolua_beginmodule(tolua_S,"PhysicNode");
    tolua_constant(tolua_S,"boundary",pix2d::PhysicNode::kBoundaryTag);
    tolua_constant(tolua_S,"maxtag",pix2d::PhysicNode::kMaxTag);
    tolua_function(tolua_S,"getSprite",tolua_custom_bindings_pix2d_PhysicNode_getSprite00);
    tolua_function(tolua_S,"getBodyType",tolua_custom_bindings_pix2d_PhysicNode_getBodyType00);
    tolua_function(tolua_S,"setBodyType",tolua_custom_bindings_pix2d_PhysicNode_setBodyType00);
    tolua_function(tolua_S,"movable",tolua_custom_bindings_pix2d_PhysicNode_movable00);
    tolua_function(tolua_S,"isMovable",tolua_custom_bindings_pix2d_PhysicNode_isMovable00);
    tolua_function(tolua_S,"setBodyPosition",tolua_custom_bindings_pix2d_PhysicNode_setBodyPosition00);
    tolua_function(tolua_S,"setBodyRotation",tolua_custom_bindings_pix2d_PhysicNode_setBodyRotation00);
    tolua_function(tolua_S,"getWorldPoint",tolua_custom_bindings_pix2d_PhysicNode_getWorldPoint00);
    tolua_function(tolua_S,"getLocalPoint",tolua_custom_bindings_pix2d_PhysicNode_getLocalPoint00);
    tolua_function(tolua_S,"getLocalVector",tolua_custom_bindings_pix2d_PhysicNode_getLocalVector00);
    tolua_function(tolua_S,"getWorldVector",tolua_custom_bindings_pix2d_PhysicNode_getWorldVector00);
    tolua_function(tolua_S,"setSleepingAllowed",tolua_custom_bindings_pix2d_PhysicNode_setSleepingAllowed00);
    tolua_function(tolua_S,"setFixedRotation",tolua_custom_bindings_pix2d_PhysicNode_setFixedRotation00);
    tolua_function(tolua_S,"getBodyPosition",tolua_custom_bindings_pix2d_PhysicNode_getBodyPosition00);
    tolua_function(tolua_S,"getBodyCenter",tolua_custom_bindings_pix2d_PhysicNode_getBodyCenter00);
    tolua_function(tolua_S,"setGravityScale",tolua_custom_bindings_pix2d_PhysicNode_setGravityScale00);
    tolua_function(tolua_S,"getGravityScale",tolua_custom_bindings_pix2d_PhysicNode_getGravityScale00);
    tolua_function(tolua_S,"getAngle",tolua_custom_bindings_pix2d_PhysicNode_getAngle00);
    tolua_function(tolua_S,"getMass",tolua_custom_bindings_pix2d_PhysicNode_getMass00);
    tolua_function(tolua_S,"setMass",tolua_custom_bindings_pix2d_PhysicNode_setMass00);
    tolua_function(tolua_S,"setLinearVelocity",tolua_custom_bindings_pix2d_PhysicNode_setLinearVelocity00);
    tolua_function(tolua_S,"applyLinearImpulse",tolua_custom_bindings_pix2d_PhysicNode_applyLinearImpulse00);
    tolua_function(tolua_S,"applyForceToCenter",tolua_custom_bindings_pix2d_PhysicNode_applyForceToCenter00);
    tolua_function(tolua_S,"getLinearVelocity",tolua_custom_bindings_pix2d_PhysicNode_getLinearVelocity00);
    tolua_function(tolua_S,"getIntertia",tolua_custom_bindings_pix2d_PhysicNode_getIntertia00);
    tolua_function(tolua_S,"setAngularVelocity",tolua_custom_bindings_pix2d_PhysicNode_setAngularVelocity00);
    tolua_function(tolua_S,"getAngularVelocity",tolua_custom_bindings_pix2d_PhysicNode_getAngularVelocity00);
    tolua_function(tolua_S,"setAngularDamping",tolua_custom_bindings_pix2d_PhysicNode_setAngularDamping00);
    tolua_function(tolua_S,"setLinearDamping",tolua_custom_bindings_pix2d_PhysicNode_setLinearDamping00);
    tolua_function(tolua_S,"setCollisionFilter",tolua_custom_bindings_pix2d_PhysicNode_setCollisionFilter00);
    tolua_function(tolua_S,"setCollisionCategory",tolua_custom_bindings_pix2d_PhysicNode_setCollisionCategory00);
    tolua_function(tolua_S,"setCollisionMask",tolua_custom_bindings_pix2d_PhysicNode_setCollisionMask00);
    tolua_function(tolua_S,"setCollisionGroup",tolua_custom_bindings_pix2d_PhysicNode_setCollisionGroup00);
    tolua_function(tolua_S,"getCollisionFilter",tolua_custom_bindings_pix2d_PhysicNode_getCollisionFilter00);
    tolua_function(tolua_S,"setBullet",tolua_custom_bindings_pix2d_PhysicNode_setBullet00);
    tolua_function(tolua_S,"isBullet",tolua_custom_bindings_pix2d_PhysicNode_isBullet00);
    tolua_function(tolua_S,"rayCast",tolua_custom_bindings_pix2d_PhysicNode_rayCast00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"BoxDef","pix2d::BoxDef","pix2d::PhysicNodeDef",tolua_collect_pix2d__BoxDef);
   #else
   tolua_cclass(tolua_S,"BoxDef","pix2d::BoxDef","pix2d::PhysicNodeDef",NULL);
   #endif
   tolua_beginmodule(tolua_S,"BoxDef");
    tolua_variable(tolua_S,"size",tolua_get_pix2d__BoxDef_size,tolua_set_pix2d__BoxDef_size);
    tolua_variable(tolua_S,"center",tolua_get_pix2d__BoxDef_center,tolua_set_pix2d__BoxDef_center);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_BoxDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_BoxDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_BoxDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Box","pix2d::Box","pix2d::PhysicNode",NULL);
   tolua_beginmodule(tolua_S,"Box");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Box_create00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"CircleDef","pix2d::CircleDef","pix2d::PhysicNodeDef",tolua_collect_pix2d__CircleDef);
   #else
   tolua_cclass(tolua_S,"CircleDef","pix2d::CircleDef","pix2d::PhysicNodeDef",NULL);
   #endif
   tolua_beginmodule(tolua_S,"CircleDef");
    tolua_variable(tolua_S,"radius",tolua_get_pix2d__CircleDef_radius,tolua_set_pix2d__CircleDef_radius);
    tolua_variable(tolua_S,"shape",tolua_get_pix2d__CircleDef_shape,tolua_set_pix2d__CircleDef_shape);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_CircleDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_CircleDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_CircleDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Circle","pix2d::Circle","pix2d::PhysicNode",NULL);
   tolua_beginmodule(tolua_S,"Circle");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Circle_create00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ChainDef","pix2d::ChainDef","pix2d::PhysicNodeDef",tolua_collect_pix2d__ChainDef);
   #else
   tolua_cclass(tolua_S,"ChainDef","pix2d::ChainDef","pix2d::PhysicNodeDef",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ChainDef");
    tolua_variable(tolua_S,"vertices",tolua_get_pix2d__ChainDef_vertices,tolua_set_pix2d__ChainDef_vertices);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_ChainDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_ChainDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_ChainDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Chain","pix2d::Chain","pix2d::PhysicNode",NULL);
   tolua_beginmodule(tolua_S,"Chain");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Chain_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Boundary","pix2d::Boundary","pix2d::PhysicNode",NULL);
   tolua_beginmodule(tolua_S,"Boundary");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Boundary_create00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TextureDef","pix2d::TextureDef","pix2d::PhysicNodeDef",tolua_collect_pix2d__TextureDef);
   #else
   tolua_cclass(tolua_S,"TextureDef","pix2d::TextureDef","pix2d::PhysicNodeDef",NULL);
   #endif
   tolua_beginmodule(tolua_S,"TextureDef");
    tolua_variable(tolua_S,"vertices",tolua_get_pix2d__TextureDef_vertices,tolua_set_pix2d__TextureDef_vertices);
    tolua_variable(tolua_S,"texture",tolua_get_pix2d__TextureDef_texture,tolua_set_pix2d__TextureDef_texture);
    tolua_variable(tolua_S,"simplify",tolua_get_pix2d__TextureDef_simplify,tolua_set_pix2d__TextureDef_simplify);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_TextureDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_TextureDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_TextureDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Texture","pix2d::Texture","pix2d::PhysicNode",NULL);
   tolua_beginmodule(tolua_S,"Texture");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Texture_create00);
    tolua_function(tolua_S,"simplifyPolygon",tolua_custom_bindings_pix2d_Texture_simplifyPolygon00);
    tolua_function(tolua_S,"addVertices",tolua_custom_bindings_pix2d_Texture_addVertices00);
    tolua_function(tolua_S,"getTextureSprite",tolua_custom_bindings_pix2d_Texture_getTextureSprite00);
    tolua_function(tolua_S,"triangulate",tolua_custom_bindings_pix2d_Texture_triangulate00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"IrisWipe","pix2d::IrisWipe","CCClippingNode",NULL);
   tolua_beginmodule(tolua_S,"IrisWipe");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_IrisWipe_create00);
    tolua_function(tolua_S,"registerCallbackHandler",tolua_custom_bindings_pix2d_IrisWipe_registerCallbackHandler00);
    tolua_function(tolua_S,"unregisterCallbackHandler",tolua_custom_bindings_pix2d_IrisWipe_unregisterCallbackHandler00);
    tolua_function(tolua_S,"getStencil",tolua_custom_bindings_pix2d_IrisWipe_getStencil00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ParticleQuad","pix2d::ParticleQuad","CCParticleSystemQuad",NULL);
   tolua_beginmodule(tolua_S,"ParticleQuad");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_ParticleQuad_create00);
    tolua_function(tolua_S,"createStarsExplosion",tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion00);
    tolua_function(tolua_S,"createStarsExplosion2",tolua_custom_bindings_pix2d_ParticleQuad_createStarsExplosion200);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"VisibleRect","pix2d::VisibleRect","",NULL);
   tolua_beginmodule(tolua_S,"VisibleRect");
    tolua_function(tolua_S,"rect",tolua_custom_bindings_pix2d_VisibleRect_rect00);
    tolua_function(tolua_S,"size",tolua_custom_bindings_pix2d_VisibleRect_size00);
    tolua_function(tolua_S,"sizeInPixel",tolua_custom_bindings_pix2d_VisibleRect_sizeInPixel00);
    tolua_function(tolua_S,"origin",tolua_custom_bindings_pix2d_VisibleRect_origin00);
    tolua_function(tolua_S,"sizeAt",tolua_custom_bindings_pix2d_VisibleRect_sizeAt00);
    tolua_function(tolua_S,"pointAtY",tolua_custom_bindings_pix2d_VisibleRect_pointAtY00);
    tolua_function(tolua_S,"pointAtX",tolua_custom_bindings_pix2d_VisibleRect_pointAtX00);
    tolua_function(tolua_S,"pointAt",tolua_custom_bindings_pix2d_VisibleRect_pointAt00);
    tolua_function(tolua_S,"pointAt",tolua_custom_bindings_pix2d_VisibleRect_pointAt01);
    tolua_function(tolua_S,"left",tolua_custom_bindings_pix2d_VisibleRect_left00);
    tolua_function(tolua_S,"right",tolua_custom_bindings_pix2d_VisibleRect_right00);
    tolua_function(tolua_S,"top",tolua_custom_bindings_pix2d_VisibleRect_top00);
    tolua_function(tolua_S,"bottom",tolua_custom_bindings_pix2d_VisibleRect_bottom00);
    tolua_function(tolua_S,"center",tolua_custom_bindings_pix2d_VisibleRect_center00);
    tolua_function(tolua_S,"leftTop",tolua_custom_bindings_pix2d_VisibleRect_leftTop00);
    tolua_function(tolua_S,"rightTop",tolua_custom_bindings_pix2d_VisibleRect_rightTop00);
    tolua_function(tolua_S,"leftBottom",tolua_custom_bindings_pix2d_VisibleRect_leftBottom00);
    tolua_function(tolua_S,"rightBottom",tolua_custom_bindings_pix2d_VisibleRect_rightBottom00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"RopeDef","pix2d::RopeDef","",tolua_collect_pix2d__RopeDef);
   #else
   tolua_cclass(tolua_S,"RopeDef","pix2d::RopeDef","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"RopeDef");
    tolua_variable(tolua_S,"batch",tolua_get_pix2d__RopeDef_batch_ptr,tolua_set_pix2d__RopeDef_batch_ptr);
    tolua_variable(tolua_S,"uid",tolua_get_pix2d__RopeDef_uid,tolua_set_pix2d__RopeDef_uid);
    tolua_variable(tolua_S,"tag",tolua_get_pix2d__RopeDef_tag,tolua_set_pix2d__RopeDef_tag);
    tolua_variable(tolua_S,"startpos",tolua_get_pix2d__RopeDef_startpos,tolua_set_pix2d__RopeDef_startpos);
    tolua_variable(tolua_S,"endpos",tolua_get_pix2d__RopeDef_endpos,tolua_set_pix2d__RopeDef_endpos);
    tolua_variable(tolua_S,"anchorFrame",tolua_get_pix2d__RopeDef_anchorFrame,tolua_set_pix2d__RopeDef_anchorFrame);
    tolua_variable(tolua_S,"hookFrame",tolua_get_pix2d__RopeDef_hookFrame,tolua_set_pix2d__RopeDef_hookFrame);
    tolua_variable(tolua_S,"sensorRadius",tolua_get_pix2d__RopeDef_sensorRadius,tolua_set_pix2d__RopeDef_sensorRadius);
    tolua_variable(tolua_S,"anchorRadius",tolua_get_pix2d__RopeDef_anchorRadius,tolua_set_pix2d__RopeDef_anchorRadius);
    tolua_variable(tolua_S,"hookRadius",tolua_get_pix2d__RopeDef_hookRadius,tolua_set_pix2d__RopeDef_hookRadius);
    tolua_variable(tolua_S,"anchorDensity",tolua_get_pix2d__RopeDef_anchorDensity,tolua_set_pix2d__RopeDef_anchorDensity);
    tolua_variable(tolua_S,"hookRestitution",tolua_get_pix2d__RopeDef_hookRestitution,tolua_set_pix2d__RopeDef_hookRestitution);
    tolua_variable(tolua_S,"hookDensity",tolua_get_pix2d__RopeDef_hookDensity,tolua_set_pix2d__RopeDef_hookDensity);
    tolua_variable(tolua_S,"hookFriction",tolua_get_pix2d__RopeDef_hookFriction,tolua_set_pix2d__RopeDef_hookFriction);
    tolua_variable(tolua_S,"anchorLocalAnchor",tolua_get_pix2d__RopeDef_anchorLocalAnchor,tolua_set_pix2d__RopeDef_anchorLocalAnchor);
    tolua_variable(tolua_S,"hookLocalAnchor",tolua_get_pix2d__RopeDef_hookLocalAnchor,tolua_set_pix2d__RopeDef_hookLocalAnchor);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_RopeDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_RopeDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_RopeDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Rope","pix2d::Rope","CCNode",NULL);
   tolua_beginmodule(tolua_S,"Rope");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Rope_create00);
    tolua_function(tolua_S,"getAnchor",tolua_custom_bindings_pix2d_Rope_getAnchor00);
    tolua_function(tolua_S,"getHook",tolua_custom_bindings_pix2d_Rope_getHook00);
    tolua_function(tolua_S,"getSensor",tolua_custom_bindings_pix2d_Rope_getSensor00);
    tolua_function(tolua_S,"getInnerSensor",tolua_custom_bindings_pix2d_Rope_getInnerSensor00);
    tolua_function(tolua_S,"attach",tolua_custom_bindings_pix2d_Rope_attach00);
    tolua_function(tolua_S,"detach",tolua_custom_bindings_pix2d_Rope_detach00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"LuaRayCastInfo","pix2d::LuaRayCastInfo","",NULL);
   tolua_beginmodule(tolua_S,"LuaRayCastInfo");
    tolua_variable(tolua_S,"node",tolua_get_pix2d__LuaRayCastInfo_node_ptr,tolua_set_pix2d__LuaRayCastInfo_node_ptr);
    tolua_variable(tolua_S,"fixture",tolua_get_pix2d__LuaRayCastInfo_fixture_ptr,tolua_set_pix2d__LuaRayCastInfo_fixture_ptr);
    tolua_variable(tolua_S,"point",tolua_get_pix2d__LuaRayCastInfo_point,tolua_set_pix2d__LuaRayCastInfo_point);
    tolua_variable(tolua_S,"normal",tolua_get_pix2d__LuaRayCastInfo_normal,tolua_set_pix2d__LuaRayCastInfo_normal);
    tolua_variable(tolua_S,"fraction",tolua_get_pix2d__LuaRayCastInfo_fraction,tolua_set_pix2d__LuaRayCastInfo_fraction);
    tolua_variable(tolua_S,"rc",tolua_get_pix2d__LuaRayCastInfo_rc,tolua_set_pix2d__LuaRayCastInfo_rc);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"PhysicsDef","pix2d::PhysicsDef","",tolua_collect_pix2d__PhysicsDef);
   #else
   tolua_cclass(tolua_S,"PhysicsDef","pix2d::PhysicsDef","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"PhysicsDef");
    tolua_variable(tolua_S,"scene",tolua_get_pix2d__PhysicsDef_scene_ptr,tolua_set_pix2d__PhysicsDef_scene_ptr);
    tolua_variable(tolua_S,"unit",tolua_get_pix2d__PhysicsDef_unit,tolua_set_pix2d__PhysicsDef_unit);
    tolua_variable(tolua_S,"size",tolua_get_pix2d__PhysicsDef_size,tolua_set_pix2d__PhysicsDef_size);
    tolua_variable(tolua_S,"pos",tolua_get_pix2d__PhysicsDef_pos,tolua_set_pix2d__PhysicsDef_pos);
    tolua_variable(tolua_S,"gravity",tolua_get_pix2d__PhysicsDef_gravity,tolua_set_pix2d__PhysicsDef_gravity);
    tolua_variable(tolua_S,"continuousPhysics",tolua_get_pix2d__PhysicsDef_continuousPhysics,tolua_set_pix2d__PhysicsDef_continuousPhysics);
    tolua_variable(tolua_S,"allowSleeping",tolua_get_pix2d__PhysicsDef_allowSleeping,tolua_set_pix2d__PhysicsDef_allowSleeping);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_PhysicsDef_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_PhysicsDef_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_PhysicsDef_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Physics","pix2d::Physics","",NULL);
   tolua_beginmodule(tolua_S,"Physics");
    tolua_constant(tolua_S,"kBoundaryLeft",pix2d::Physics::kBoundaryLeft);
    tolua_constant(tolua_S,"kBoundaryTop",pix2d::Physics::kBoundaryTop);
    tolua_constant(tolua_S,"kBoundaryRight",pix2d::Physics::kBoundaryRight);
    tolua_constant(tolua_S,"kBoundaryBottom",pix2d::Physics::kBoundaryBottom);
    tolua_function(tolua_S,"isPix2dDebug",tolua_custom_bindings_pix2d_Physics_isPix2dDebug00);
    tolua_function(tolua_S,"isCocos2dDebug",tolua_custom_bindings_pix2d_Physics_isCocos2dDebug00);
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_Physics_create00);
    tolua_function(tolua_S,"shared",tolua_custom_bindings_pix2d_Physics_shared00);
    tolua_function(tolua_S,"world",tolua_custom_bindings_pix2d_Physics_world00);
    tolua_function(tolua_S,"dummy",tolua_custom_bindings_pix2d_Physics_dummy00);
    tolua_function(tolua_S,"getGravity",tolua_custom_bindings_pix2d_Physics_getGravity00);
    tolua_function(tolua_S,"addNode",tolua_custom_bindings_pix2d_Physics_addNode00);
    tolua_function(tolua_S,"addNode",tolua_custom_bindings_pix2d_Physics_addNode01);
    tolua_function(tolua_S,"addNode",tolua_custom_bindings_pix2d_Physics_addNode02);
    tolua_function(tolua_S,"getScene",tolua_custom_bindings_pix2d_Physics_getScene00);
    tolua_function(tolua_S,"removePhysicNode",tolua_custom_bindings_pix2d_Physics_removePhysicNode00);
    tolua_function(tolua_S,"removeJoint",tolua_custom_bindings_pix2d_Physics_removeJoint00);
    tolua_function(tolua_S,"pixelToMeter",tolua_custom_bindings_pix2d_Physics_pixelToMeter00);
    tolua_function(tolua_S,"pixelToMeter",tolua_custom_bindings_pix2d_Physics_pixelToMeter01);
    tolua_function(tolua_S,"pixelToMeter",tolua_custom_bindings_pix2d_Physics_pixelToMeter02);
    tolua_function(tolua_S,"meterToPixel",tolua_custom_bindings_pix2d_Physics_meterToPixel00);
    tolua_function(tolua_S,"meterToPixel",tolua_custom_bindings_pix2d_Physics_meterToPixel01);
    tolua_function(tolua_S,"meterToPixel",tolua_custom_bindings_pix2d_Physics_meterToPixel02);
    tolua_function(tolua_S,"unitToMeter",tolua_custom_bindings_pix2d_Physics_unitToMeter00);
    tolua_function(tolua_S,"unitToMeter",tolua_custom_bindings_pix2d_Physics_unitToMeter01);
    tolua_function(tolua_S,"unitToMeter",tolua_custom_bindings_pix2d_Physics_unitToMeter02);
    tolua_function(tolua_S,"unitToMeterCenter",tolua_custom_bindings_pix2d_Physics_unitToMeterCenter00);
    tolua_function(tolua_S,"unitToMeterCenter",tolua_custom_bindings_pix2d_Physics_unitToMeterCenter01);
    tolua_function(tolua_S,"meterToUnit",tolua_custom_bindings_pix2d_Physics_meterToUnit00);
    tolua_function(tolua_S,"meterToUnit",tolua_custom_bindings_pix2d_Physics_meterToUnit01);
    tolua_function(tolua_S,"pixelToUnit",tolua_custom_bindings_pix2d_Physics_pixelToUnit00);
    tolua_function(tolua_S,"unitToPixel",tolua_custom_bindings_pix2d_Physics_unitToPixel00);
    tolua_function(tolua_S,"unitToPixelCenter",tolua_custom_bindings_pix2d_Physics_unitToPixelCenter00);
    tolua_function(tolua_S,"createPrismaticJoint",tolua_custom_bindings_pix2d_Physics_createPrismaticJoint00);
    tolua_function(tolua_S,"createFrictionJoint",tolua_custom_bindings_pix2d_Physics_createFrictionJoint00);
    tolua_function(tolua_S,"createRopeJoint",tolua_custom_bindings_pix2d_Physics_createRopeJoint00);
    tolua_function(tolua_S,"createRopeJoint",tolua_custom_bindings_pix2d_Physics_createRopeJoint01);
    tolua_function(tolua_S,"createRevoluteJoint",tolua_custom_bindings_pix2d_Physics_createRevoluteJoint00);
    tolua_function(tolua_S,"createRevoluteJointWithAnchor",tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithAnchor00);
    tolua_function(tolua_S,"createRevoluteJointWithLimit",tolua_custom_bindings_pix2d_Physics_createRevoluteJointWithLimit00);
    tolua_function(tolua_S,"removeRevoluteJoint",tolua_custom_bindings_pix2d_Physics_removeRevoluteJoint00);
    tolua_function(tolua_S,"createDistanceJoint",tolua_custom_bindings_pix2d_Physics_createDistanceJoint00);
    tolua_function(tolua_S,"createDistanceJointWithLength",tolua_custom_bindings_pix2d_Physics_createDistanceJointWithLength00);
    tolua_function(tolua_S,"createWeldJoint",tolua_custom_bindings_pix2d_Physics_createWeldJoint00);
    tolua_function(tolua_S,"createPrismaticJoint",tolua_custom_bindings_pix2d_Physics_createPrismaticJoint01);
    tolua_function(tolua_S,"rayCast",tolua_custom_bindings_pix2d_Physics_rayCast00);
    tolua_function(tolua_S,"getTrajectoryPoint",tolua_custom_bindings_pix2d_Physics_getTrajectoryPoint00);
    tolua_function(tolua_S,"calculateVerticalVelocityForHeight",tolua_custom_bindings_pix2d_Physics_calculateVerticalVelocityForHeight00);
    tolua_function(tolua_S,"getTimestepsToTop",tolua_custom_bindings_pix2d_Physics_getTimestepsToTop00);
    tolua_function(tolua_S,"getMaxHeight",tolua_custom_bindings_pix2d_Physics_getMaxHeight00);
    tolua_function(tolua_S,"contactListener",tolua_custom_bindings_pix2d_Physics_contactListener00);
    tolua_function(tolua_S,"touchListener",tolua_custom_bindings_pix2d_Physics_touchListener00);
    tolua_function(tolua_S,"layer",tolua_custom_bindings_pix2d_Physics_layer00);
    tolua_function(tolua_S,"unit",tolua_custom_bindings_pix2d_Physics_unit00);
    tolua_function(tolua_S,"getUnitInPixel",tolua_custom_bindings_pix2d_Physics_getUnitInPixel00);
    tolua_function(tolua_S,"position",tolua_custom_bindings_pix2d_Physics_position00);
    tolua_function(tolua_S,"positionInPixel",tolua_custom_bindings_pix2d_Physics_positionInPixel00);
    tolua_function(tolua_S,"size",tolua_custom_bindings_pix2d_Physics_size00);
    tolua_function(tolua_S,"sizePixel",tolua_custom_bindings_pix2d_Physics_sizePixel00);
    tolua_function(tolua_S,"sizeUnits",tolua_custom_bindings_pix2d_Physics_sizeUnits00);
    tolua_function(tolua_S,"isPaused",tolua_custom_bindings_pix2d_Physics_isPaused00);
    tolua_function(tolua_S,"pause",tolua_custom_bindings_pix2d_Physics_pause00);
    tolua_function(tolua_S,"resume",tolua_custom_bindings_pix2d_Physics_resume00);
    tolua_function(tolua_S,"setDefaultBackgroundColor",tolua_custom_bindings_pix2d_Physics_setDefaultBackgroundColor00);
    tolua_function(tolua_S,"getDefaultBackgroundColor",tolua_custom_bindings_pix2d_Physics_getDefaultBackgroundColor00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"QueryMap","pix2d::QueryMap","",NULL);
   tolua_beginmodule(tolua_S,"QueryMap");
    tolua_function(tolua_S,"query",tolua_custom_bindings_pix2d_QueryMap_query00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"ContactInfo","pix2d::ContactInfo","",tolua_collect_pix2d__ContactInfo);
   #else
   tolua_cclass(tolua_S,"ContactInfo","pix2d::ContactInfo","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"ContactInfo");
    tolua_variable(tolua_S,"bodyA",tolua_get_pix2d__ContactInfo_bodyA_ptr,tolua_set_pix2d__ContactInfo_bodyA_ptr);
    tolua_variable(tolua_S,"bodyB",tolua_get_pix2d__ContactInfo_bodyB_ptr,tolua_set_pix2d__ContactInfo_bodyB_ptr);
    tolua_variable(tolua_S,"fixtureA",tolua_get_pix2d__ContactInfo_fixtureA_ptr,tolua_set_pix2d__ContactInfo_fixtureA_ptr);
    tolua_variable(tolua_S,"fixtureB",tolua_get_pix2d__ContactInfo_fixtureB_ptr,tolua_set_pix2d__ContactInfo_fixtureB_ptr);
    tolua_variable(tolua_S,"pos",tolua_get_pix2d__ContactInfo_pos,tolua_set_pix2d__ContactInfo_pos);
    tolua_variable(tolua_S,"localA",tolua_get_pix2d__ContactInfo_localA,tolua_set_pix2d__ContactInfo_localA);
    tolua_variable(tolua_S,"localB",tolua_get_pix2d__ContactInfo_localB,tolua_set_pix2d__ContactInfo_localB);
    tolua_variable(tolua_S,"nodeA",tolua_get_pix2d__ContactInfo_nodeA_ptr,tolua_set_pix2d__ContactInfo_nodeA_ptr);
    tolua_variable(tolua_S,"nodeB",tolua_get_pix2d__ContactInfo_nodeB_ptr,tolua_set_pix2d__ContactInfo_nodeB_ptr);
    tolua_variable(tolua_S,"groupIndexA",tolua_get_pix2d__ContactInfo_groupIndexA,tolua_set_pix2d__ContactInfo_groupIndexA);
    tolua_variable(tolua_S,"groupIndexB",tolua_get_pix2d__ContactInfo_groupIndexB,tolua_set_pix2d__ContactInfo_groupIndexB);
    tolua_variable(tolua_S,"isTouching",tolua_get_pix2d__ContactInfo_isTouching,tolua_set_pix2d__ContactInfo_isTouching);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_ContactInfo_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_ContactInfo_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_ContactInfo_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"ContactListener","pix2d::ContactListener","",NULL);
   tolua_beginmodule(tolua_S,"ContactListener");
    tolua_function(tolua_S,"cancelAllNotification",tolua_custom_bindings_pix2d_ContactListener_cancelAllNotification00);
    tolua_function(tolua_S,"cancelCollisionNotification",tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotification00);
    tolua_function(tolua_S,"cancelCollisionNotificationWithId",tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithId00);
    tolua_function(tolua_S,"cancelCollisionNotificationWithTag",tolua_custom_bindings_pix2d_ContactListener_cancelCollisionNotificationWithTag00);
    tolua_function(tolua_S,"registerCollisionNotificationScript",tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScript00);
    tolua_function(tolua_S,"registerCollisionNotificationScriptWithId",tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithId00);
    tolua_function(tolua_S,"registerCollisionNotificationScriptWithTag",tolua_custom_bindings_pix2d_ContactListener_registerCollisionNotificationScriptWithTag00);
    tolua_function(tolua_S,"registerEndCollisionNotificationScriptWithTag",tolua_custom_bindings_pix2d_ContactListener_registerEndCollisionNotificationScriptWithTag00);
    tolua_function(tolua_S,"cancelEndCollisionNotificationScritpWithTag",tolua_custom_bindings_pix2d_ContactListener_cancelEndCollisionNotificationScritpWithTag00);
    tolua_function(tolua_S,"dump",tolua_custom_bindings_pix2d_ContactListener_dump00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"TouchInfo","pix2d::TouchInfo","",tolua_collect_pix2d__TouchInfo);
   #else
   tolua_cclass(tolua_S,"TouchInfo","pix2d::TouchInfo","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"TouchInfo");
    tolua_variable(tolua_S,"body",tolua_get_pix2d__TouchInfo_body_ptr,tolua_set_pix2d__TouchInfo_body_ptr);
    tolua_variable(tolua_S,"fixture",tolua_get_pix2d__TouchInfo_fixture_ptr,tolua_set_pix2d__TouchInfo_fixture_ptr);
    tolua_variable(tolua_S,"pos",tolua_get_pix2d__TouchInfo_pos,tolua_set_pix2d__TouchInfo_pos);
    tolua_variable(tolua_S,"localpos",tolua_get_pix2d__TouchInfo_localpos,tolua_set_pix2d__TouchInfo_localpos);
    tolua_variable(tolua_S,"node",tolua_get_pix2d__TouchInfo_node_ptr,tolua_set_pix2d__TouchInfo_node_ptr);
    tolua_variable(tolua_S,"touch",tolua_get_pix2d__TouchInfo_touch_ptr,tolua_set_pix2d__TouchInfo_touch_ptr);
    tolua_variable(tolua_S,"event",tolua_get_pix2d__TouchInfo_event_ptr,tolua_set_pix2d__TouchInfo_event_ptr);
    tolua_variable(tolua_S,"hasMoved",tolua_get_pix2d__TouchInfo_hasMoved,tolua_set_pix2d__TouchInfo_hasMoved);
    tolua_function(tolua_S,"new",tolua_custom_bindings_pix2d_TouchInfo_new00);
    tolua_function(tolua_S,"new_local",tolua_custom_bindings_pix2d_TouchInfo_new00_local);
    tolua_function(tolua_S,".call",tolua_custom_bindings_pix2d_TouchInfo_new00_local);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"TouchListener","pix2d::TouchListener","",NULL);
   tolua_beginmodule(tolua_S,"TouchListener");
    tolua_function(tolua_S,"registerTouchScriptHandler",tolua_custom_bindings_pix2d_TouchListener_registerTouchScriptHandler00);
    tolua_function(tolua_S,"cancelTouchDelegate",tolua_custom_bindings_pix2d_TouchListener_cancelTouchDelegate00);
    tolua_function(tolua_S,"destroyMouseJoint",tolua_custom_bindings_pix2d_TouchListener_destroyMouseJoint00);
    tolua_function(tolua_S,"setMouseJointMaxForce",tolua_custom_bindings_pix2d_TouchListener_setMouseJointMaxForce00);
    tolua_function(tolua_S,"getMouseJointMaxForce",tolua_custom_bindings_pix2d_TouchListener_getMouseJointMaxForce00);
    tolua_function(tolua_S,"setMouseJointFrequency",tolua_custom_bindings_pix2d_TouchListener_setMouseJointFrequency00);
    tolua_function(tolua_S,"setMouseJointDamping",tolua_custom_bindings_pix2d_TouchListener_setMouseJointDamping00);
    tolua_function(tolua_S,"getReactionForce",tolua_custom_bindings_pix2d_TouchListener_getReactionForce00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"PhysicsLayer","pix2d::PhysicsLayer","CCLayer",NULL);
   tolua_beginmodule(tolua_S,"PhysicsLayer");
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"Action","pix2d::Action","CCActionInterval",NULL);
   tolua_beginmodule(tolua_S,"Action");
    tolua_function(tolua_S,"setSpeed",tolua_custom_bindings_pix2d_Action_setSpeed00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"MoveTo","pix2d::MoveTo","pix2d::Action",NULL);
   tolua_beginmodule(tolua_S,"MoveTo");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_MoveTo_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"CircleTo","pix2d::CircleTo","pix2d::Action",NULL);
   tolua_beginmodule(tolua_S,"CircleTo");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_CircleTo_create00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"SplineTo","pix2d::SplineTo","CCCardinalSplineTo",NULL);
   tolua_beginmodule(tolua_S,"SplineTo");
    tolua_function(tolua_S,"create",tolua_custom_bindings_pix2d_SplineTo_create00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_custom_bindings (lua_State* tolua_S) {
 return tolua_custom_bindings_open(tolua_S);
};
#endif

