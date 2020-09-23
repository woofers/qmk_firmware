#!/usr/bin/env bash

KEY=$1
STATUS="none"
if [ "$KEY" == "quefrency" ]; then
  STATUS="keebio/quefrency/rev1"
elif [ "$KEY" == "cospad" ]; then
  STATUS="cospad"
elif [ "$KEY" == "brutal60" ]; then
  STATUS="cannonkeys/an_c"
fi

if [ "$STATUS" == "none" ]; then
  exit 1
fi

echo $STATUS
