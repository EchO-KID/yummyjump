#!/bin/sh
echo Press enter to continue
read
osascript <<EOF
tell application "iTerm"
    activate
    tell application "iTerm"
        tell application "System Events" to keystroke "t" using command down
        tell application "System Events" to keystroke "D" using command down
        tell application "System Events" to keystroke "d" using command down
    end tell
end tell
EOF
cd /Users/lzubiaur/Dev/cocos2d/cocos2d-x-cocos2d-x-2.2.1/projects/gameplay
pushd tools
make startproxy
make startdevicelog
popd
cd Resources/lua; vi
