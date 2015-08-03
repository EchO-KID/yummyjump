#!/bin/sh
# vim: use <CTRL-V><Tab> in "insert mode" to insert tab when expandtab option is ON
# We set the cocos2dx.target ant properties from the command line so we can set conditional properties in build.xml
all: bump
	ln -sf Application.mk_DEBUG jni/Application.mk && \
	./build_native.sh && \
	ant debug -Dcocos2dx.target=DEBUG && \
	adb install -r bin/gameplay-debug.apk && \
	adb shell am start -n com.voodoocactus.games/com.voodoocactus.games.gameplay && \
	adb logcat -c && adb logcat | grep cocos2d

release: bump
	ln -sf Application.mk_RELEASE jni/Application.mk && \
	./build_native.sh && \
	ant release -Dcocos2dx.target=RELEASE && \
	adb install -r bin/gameplay-release.apk && \
	adb shell am start -n com.voodoocactus.games/com.voodoocactus.games.gameplay && \
	adb logcat | grep cocos2d

bump:	
	cd ../tools; ./bump_version.py -l ../Resources/lua/version.lua -m ../proj.android/AndroidManifest.xml; cd ../proj.android
clean: 
	./build_native.sh clean && ant clean

log:
	adb logcat | grep cocos2d

restart:
	adb install -r bin/gameplay-debug.apk && \
	adb shell am start -n com.voodoocactus.games/com.voodoocactus.games.gameplay && \
	adb logcat | grep cocos2d

clear:
	adb shell pm clear com.voodoocactus.games
