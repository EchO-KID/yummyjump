/*
** Lua binding: command
** Generated automatically by tolua++-1.0.92 on Fri Sep 12 19:24:44 2014.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_command_open (lua_State* tolua_S);

#include "console/command.h"
#include "console/console.h"
#include "console/luaconsole.h"
#include "debug/debuglayer.h"

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_std__vector_std__string_ (lua_State* tolua_S)
{
 std::vector<std::string>* self = (std::vector<std::string>*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}

static int tolua_collect_pix2d_console__Command (lua_State* tolua_S)
{
 pix2d_console::Command* self = (pix2d_console::Command*) tolua_tousertype(tolua_S,1,0);
	Mtolua_delete(self);
	return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"pix2d_console::Console");
 tolua_usertype(tolua_S,"pix2d_console::Command");
 tolua_usertype(tolua_S,"pix2d::DebugSettings");
 tolua_usertype(tolua_S,"CCNode");
 tolua_usertype(tolua_S,"std::vector<std::string>");
 tolua_usertype(tolua_S,"pix2d_console::LuaConsole");
}

/* method: clear of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__clear00
static int tolua_command_std_vector_std__string__clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::vector<std::string>* self = (std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
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

/* method: size of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__size00
static int tolua_command_std_vector_std__string__size00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::vector<std::string>* self = (const std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
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

/* method: operator[] of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string___geti00
static int tolua_command_std_vector_std__string___geti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const std::vector<std::string>* self = (const std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   const std::string tolua_ret = (const std::string)  self->operator[](index);
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

/* method: operator&[] of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string___seti00
static int tolua_command_std_vector_std__string___seti00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::vector<std::string>* self = (std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
  std::string tolua_value = ((std::string)  tolua_tocppstring(tolua_S,3,0));
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

/* method: operator[] of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string___geti01
static int tolua_command_std_vector_std__string___geti01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  std::vector<std::string>* self = (std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
  int index = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator[]'", NULL);
#endif
  {
   std::string tolua_ret = (std::string)  self->operator[](index);
   tolua_pushcppstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_command_std_vector_std__string___geti00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: push_back of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__push_back00
static int tolua_command_std_vector_std__string__push_back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::vector<std::string>* self = (std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
  std::string val = ((std::string)  tolua_tocppstring(tolua_S,2,0));
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

/* method: new of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__new00
static int tolua_command_std_vector_std__string__new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::vector<std::string>* tolua_ret = (std::vector<std::string>*)  Mtolua_new((std::vector<std::string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::vector<std::string>");
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

/* method: new_local of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__new00_local
static int tolua_command_std_vector_std__string__new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   std::vector<std::string>* tolua_ret = (std::vector<std::string>*)  Mtolua_new((std::vector<std::string>)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"std::vector<std::string>");
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

/* method: delete of class  std::vector<std::string> */
#ifndef TOLUA_DISABLE_tolua_command_std_vector_std__string__delete00
static int tolua_command_std_vector_std__string__delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"std::vector<std::string>",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  std::vector<std::string>* self = (std::vector<std::string>*)  tolua_tousertype(tolua_S,1,0);
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

/* method: close of class  pix2d_console::Console */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Console_close00
static int tolua_command_pix2d_console_Console_close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Console* self = (pix2d_console::Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'close'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->close();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: create of class  pix2d_console::LuaConsole */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_LuaConsole_create00
static int tolua_command_pix2d_console_LuaConsole_create00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d_console::LuaConsole",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* ip = ((const char*)  tolua_tostring(tolua_S,2,0));
  int port = ((int)  tolua_tonumber(tolua_S,3,0));
  {
   pix2d_console::LuaConsole* tolua_ret = (pix2d_console::LuaConsole*)  pix2d_console::LuaConsole::create(ip,port);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d_console::LuaConsole");
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

/* method: new of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_new00
static int tolua_command_pix2d_console_Command_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d_console::Command* tolua_ret = (pix2d_console::Command*)  Mtolua_new((pix2d_console::Command)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d_console::Command");
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

/* method: new_local of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_new00_local
static int tolua_command_pix2d_console_Command_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d_console::Command* tolua_ret = (pix2d_console::Command*)  Mtolua_new((pix2d_console::Command)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d_console::Command");
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

/* method: delete of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_delete00
static int tolua_command_pix2d_console_Command_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
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

/* method: refreshAssets of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_refreshAssets00
static int tolua_command_pix2d_console_Command_refreshAssets00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_iscppstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::vector<std::string>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
  std::string repo = ((std::string)  tolua_tocppstring(tolua_S,2,0));
  std::vector<std::string>* assets = ((std::vector<std::string>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'refreshAssets'", NULL);
#endif
  {
   self->refreshAssets(repo,*assets);
   tolua_pushcppstring(tolua_S,(const char*)repo);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'refreshAssets'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebugParams of class  pix2d_console::Command */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_console_Command_setDebugParams00
static int tolua_command_pix2d_console_Command_setDebugParams00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"pix2d_console::Command",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  pix2d_console::Command* self = (pix2d_console::Command*)  tolua_tousertype(tolua_S,1,0);
  bool showPhysicsDraw = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool showStats = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool zoomOutScene = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugParams'", NULL);
#endif
  {
   self->setDebugParams(showPhysicsDraw,showStats,zoomOutScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setDebugParams'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getInstance of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_command_pix2d_DebugSettings_getInstance00
static int tolua_command_pix2d_DebugSettings_getInstance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"pix2d::DebugSettings",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   pix2d::DebugSettings* tolua_ret = (pix2d::DebugSettings*)  pix2d::DebugSettings::getInstance();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"pix2d::DebugSettings");
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

/* get function: showPhysicsDraw of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__DebugSettings_showPhysicsDraw
static int tolua_get_pix2d__DebugSettings_showPhysicsDraw(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'showPhysicsDraw'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->showPhysicsDraw);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: showPhysicsDraw of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__DebugSettings_showPhysicsDraw
static int tolua_set_pix2d__DebugSettings_showPhysicsDraw(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'showPhysicsDraw'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->showPhysicsDraw = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: showStats of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__DebugSettings_showStats
static int tolua_get_pix2d__DebugSettings_showStats(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'showStats'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->showStats);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: showStats of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__DebugSettings_showStats
static int tolua_set_pix2d__DebugSettings_showStats(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'showStats'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->showStats = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: zoomOutScene of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_get_pix2d__DebugSettings_zoomOutScene
static int tolua_get_pix2d__DebugSettings_zoomOutScene(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zoomOutScene'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->zoomOutScene);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: zoomOutScene of class  pix2d::DebugSettings */
#ifndef TOLUA_DISABLE_tolua_set_pix2d__DebugSettings_zoomOutScene
static int tolua_set_pix2d__DebugSettings_zoomOutScene(lua_State* tolua_S)
{
  pix2d::DebugSettings* self = (pix2d::DebugSettings*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'zoomOutScene'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->zoomOutScene = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_command_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_module(tolua_S,"std",0);
  tolua_beginmodule(tolua_S,"std");
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"vector_std__string_","std::vector<std::string>","",tolua_collect_std__vector_std__string_);
   #else
   tolua_cclass(tolua_S,"vector_std__string_","std::vector<std::string>","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"vector_std__string_");
    tolua_function(tolua_S,"clear",tolua_command_std_vector_std__string__clear00);
    tolua_function(tolua_S,"size",tolua_command_std_vector_std__string__size00);
    tolua_function(tolua_S,".geti",tolua_command_std_vector_std__string___geti00);
    tolua_function(tolua_S,".seti",tolua_command_std_vector_std__string___seti00);
    tolua_function(tolua_S,".geti",tolua_command_std_vector_std__string___geti01);
    tolua_function(tolua_S,"push_back",tolua_command_std_vector_std__string__push_back00);
    tolua_function(tolua_S,"new",tolua_command_std_vector_std__string__new00);
    tolua_function(tolua_S,"new_local",tolua_command_std_vector_std__string__new00_local);
    tolua_function(tolua_S,".call",tolua_command_std_vector_std__string__new00_local);
    tolua_function(tolua_S,"delete",tolua_command_std_vector_std__string__delete00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"pix2d_console",0);
  tolua_beginmodule(tolua_S,"pix2d_console");
   tolua_cclass(tolua_S,"Console","pix2d_console::Console","CCNode",NULL);
   tolua_beginmodule(tolua_S,"Console");
    tolua_function(tolua_S,"close",tolua_command_pix2d_console_Console_close00);
   tolua_endmodule(tolua_S);
   tolua_cclass(tolua_S,"LuaConsole","pix2d_console::LuaConsole","pix2d_console::Console",NULL);
   tolua_beginmodule(tolua_S,"LuaConsole");
    tolua_function(tolua_S,"create",tolua_command_pix2d_console_LuaConsole_create00);
   tolua_endmodule(tolua_S);
   #ifdef __cplusplus
   tolua_cclass(tolua_S,"Command","pix2d_console::Command","",tolua_collect_pix2d_console__Command);
   #else
   tolua_cclass(tolua_S,"Command","pix2d_console::Command","",NULL);
   #endif
   tolua_beginmodule(tolua_S,"Command");
    tolua_function(tolua_S,"new",tolua_command_pix2d_console_Command_new00);
    tolua_function(tolua_S,"new_local",tolua_command_pix2d_console_Command_new00_local);
    tolua_function(tolua_S,".call",tolua_command_pix2d_console_Command_new00_local);
    tolua_function(tolua_S,"delete",tolua_command_pix2d_console_Command_delete00);
    tolua_function(tolua_S,"refreshAssets",tolua_command_pix2d_console_Command_refreshAssets00);
    tolua_function(tolua_S,"setDebugParams",tolua_command_pix2d_console_Command_setDebugParams00);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
  tolua_module(tolua_S,"pix2d",0);
  tolua_beginmodule(tolua_S,"pix2d");
   tolua_cclass(tolua_S,"DebugSettings","pix2d::DebugSettings","",NULL);
   tolua_beginmodule(tolua_S,"DebugSettings");
    tolua_function(tolua_S,"getInstance",tolua_command_pix2d_DebugSettings_getInstance00);
    tolua_variable(tolua_S,"showPhysicsDraw",tolua_get_pix2d__DebugSettings_showPhysicsDraw,tolua_set_pix2d__DebugSettings_showPhysicsDraw);
    tolua_variable(tolua_S,"showStats",tolua_get_pix2d__DebugSettings_showStats,tolua_set_pix2d__DebugSettings_showStats);
    tolua_variable(tolua_S,"zoomOutScene",tolua_get_pix2d__DebugSettings_zoomOutScene,tolua_set_pix2d__DebugSettings_zoomOutScene);
   tolua_endmodule(tolua_S);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_command (lua_State* tolua_S) {
 return tolua_command_open(tolua_S);
};
#endif

