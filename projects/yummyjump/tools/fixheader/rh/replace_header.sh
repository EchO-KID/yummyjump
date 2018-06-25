#!/bin/bash
SOURCE_DIR=`dirname $0`
if [ $# != 1 ]; then
    echo "Usage: replace_header.sh <file>"
    exit 1
fi

# cat $SOURCE_DIR/header.template > $SOURCE_DIR/tmp
FILENAME=`echo "$1" | awk -F/ '{print $(NF)}'`
sed "s/__FILE__/$FILENAME/g" $SOURCE_DIR/header.template > $SOURCE_DIR/tmp
cat $1 | awk -f $SOURCE_DIR/remove_header.awk >> $SOURCE_DIR/tmp
mv $SOURCE_DIR/tmp $1

