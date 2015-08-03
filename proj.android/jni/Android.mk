LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# support for C++11
LOCAL_CFLAGS := -std=gnu++11

LOCAL_MODULE := cocos2dlua_shared

LOCAL_CPP_EXTENSION := .cc .cpp .cxx

LOCAL_MODULE_FILENAME := libcocos2dlua

LOCAL_SRC_FILES := hellolua/main.cpp \
../../Classes/AppDelegate.cpp \
../../Classes/bindings/custom_bindings.cpp \
../../Classes/bindings/luahelper.cpp \
../../Classes/body/base/box.cpp \
../../Classes/body/base/chain.cpp \
../../Classes/body/base/circle.cpp \
../../Classes/body/base/physicnode.cpp \
../../Classes/body/base/texture.cpp \
../../Classes/body/boundary.cpp \
../../Classes/body/rope.cpp \
../../Classes/body/vrope/vpoint.cpp \
../../Classes/body/vrope/vrope.cpp \
../../Classes/body/vrope/vstick.cpp \
../../Classes/ccb/cocosbuilderlua.cpp \
../../Classes/common/assets.cpp \
../../Classes/common/notifications.cpp \
../../Classes/common/settings.cpp \
../../Classes/common/visiblerect.cpp \
../../Classes/geom.cpp \
../../Classes/io/touchgrabber.cpp \
../../Classes/layer/physicslayer.cpp \
../../Classes/layer/toolbox.cpp \
../../Classes/platform/android/native.cpp \
../../Classes/nodes/actiontweenlua.cpp \
../../Classes/nodes/custommenuitem.cpp \
../../Classes/nodes/drawnode.cpp \
../../Classes/nodes/nodeutil.cpp \
../../Classes/nodes/opacitynode.cpp \
../../Classes/nodes/particlequad.cpp \
../../Classes/nodes/postprocessing.cpp \
../../Classes/physics/action.cpp \
../../Classes/physics/contact.cpp \
../../Classes/physics/graph.cpp \
../../Classes/physics/path.cpp \
../../Classes/physics/physics.cpp \
../../Classes/physics/touch.cpp \
../../Classes/physics/userdata.cpp \
../../Classes/sprites/iriswipe.cpp \
../../Classes/sprites/texturesprite.cpp \
../../libs/clipper/clipper.cpp \
../../libs/micropather/micropather.cpp \
../../libs/poly2tri/common/shapes.cc \
../../libs/poly2tri/sweep/advancing_front.cc \
../../libs/poly2tri/sweep/cdt.cc \
../../libs/poly2tri/sweep/sweep.cc \
../../libs/poly2tri/sweep/sweep_context.cc \
../../Classes/console/command.cpp \
../../Classes/console/console.cpp \
../../Classes/console/luaconsole.cpp \
../../Classes/console/tolua/command.cpp \
../../Classes/debug/debuglayer.cpp \
../../libs/B2DebugDraw/B2DebugDrawLayer.cpp \
../../libs/B2DebugDraw/GLES-Render.cpp \
../../libs/LuaSocket/auxiliar.c \
../../libs/LuaSocket/buffer.c \
../../libs/LuaSocket/except.c \
../../libs/LuaSocket/inet.c \
../../libs/LuaSocket/io.c \
../../libs/LuaSocket/luasocket.c \
../../libs/LuaSocket/mime.c \
../../libs/LuaSocket/options.c \
../../libs/LuaSocket/select.c \
../../libs/LuaSocket/serial.c \
../../libs/LuaSocket/tcp.c \
../../libs/LuaSocket/timeout.c \
../../libs/LuaSocket/udp.c \
../../libs/LuaSocket/unix.c \
../../libs/LuaSocket/usocket.c \
../../libs/AES/AES.cpp \
../../libs/b64/cdecode.c \
../../libs/b64/cencode.c \
../../libs/android-ifaddrs/ifaddrs.h \ # include the header file instead of the source file because libwebsocket already provided definitions for getifaddrs/freeifaddrs

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
            $(LOCAL_PATH)/../../libs \
            $(LOCAL_PATH)/../../libs/android-ifaddrs \

LOCAL_STATIC_LIBRARIES := curl_static_prebuilt

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_lua_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)
$(call import-module,CocosDenshion/android)
$(call import-module,scripting/lua/proj.android)
$(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)
$(call import-module,extensions)
$(call import-module,external/Box2D)
$(call import-module,external/chipmunk)
