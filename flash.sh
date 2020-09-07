#!/usr/bin/env bash

STATUS=$(./keyboard_path.sh $1)
if [ "$?" != 0 ]; then
  ./keyboard_list.sh "flash"
  exit 1
fi
echo $STATUS

make $STATUS:jaxson:dfu
