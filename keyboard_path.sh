#!/usr/bin/env bash

KEY=$1
STATUS="none"
if [ "$KEY" == "quefrency" ]; then
  STATUS="keebio/quefrency/rev1"
elif [ "$KEY" == "cospad" ]; then
  STATUS="cospad"
fi

if [ "$STATUS" == "none" ]; then
  exit 1
fi

echo $STATUS
