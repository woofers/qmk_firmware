#!/usr/bin/env bash

STATUS=$(./keyboard_path.sh $1)
if [ "$?" != 0 ]; then
  ./keyboard_list.sh "build"
  exit 1
fi
echo $STATUS

qmk compile -kb $STATUS -km jaxson
