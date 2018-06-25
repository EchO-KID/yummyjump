#!/bin/sh
pushd ../Resources/lua
find ../../Assets/TiledMap -name "S*E*.json" | while read line; do
    echo $line
    /usr/local/bin/lua -e "require('editorconvert')():init('$line'):convert(false)"
done
popd
