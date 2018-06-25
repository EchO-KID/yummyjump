#!/bin/sh
cd /Users/lzubiaur/Dev/cocos2d/cocos2d-x-cocos2d-x-2.2.1/projects/gameplay/Resources/lua
/usr/local/bin/lua -e "require('editorconvert')():init('$1'):convert(true)" >> ../../tools/logs/editorconvert.log 2>&1
