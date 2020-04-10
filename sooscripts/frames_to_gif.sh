#!bin/bash

echo "[SOO INFO] This script needs to be run from the POSTXXX folder."

FRAMES_LOOP=bin/data/frames_loop
OUTPUT=bin/data/loop.gif

echo "[SOO INFO] Will read frames from: "$FRAMES_LOOP
echo "[SOO INFO] Will export gif to: "$OUTPUT

ffmpeg -i $FRAMES_LOOP/f%08d.png $OUTPUT
