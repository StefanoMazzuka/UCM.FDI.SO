#!/bin/bash

MPOINT="./mount-point"

rm -R -f temp
mkdir temp

echo "Copying file 1"
cp ./src/fuseLib.c ./temp/fuseLib.c
cp ./temp/fuseLib.c $MPOINT/fuseLib.c
read -p "Press enter..."

echo "Copying file 2"
cp ./src/myFS.h ./temp/myFS.h
cp ./temp/myFS.h $MPOINT/myFS.h
read -p "Press enter..."

./my-fsck virtual-disk

diff -q ./src/fuseLib.c $MPOINT/fuseLib.c
diff -q ./src/myFS.h $MPOINT/myFS.h

truncate -s -4096 ./temp/fuseLib.c
truncate -s -4096  $MPOINT/fuseLib.c

./my-fsck virtual-disk

diff -q ./src/fuseLib.c $MPOINT/fuseLib.c

cp ./src/myFS.c $MPOINT/myFS.c

./my-fsck virtual-disk

diff -q ./src/myFS.c $MPOINT/myFS.c

truncate -s +8192 ./temp/myFS.h
truncate -s +8192  $MPOINT/myFS.h

./my-fsck virtual-disk

diff -q ./src/myFS.h $MPOINT/myFS.h
