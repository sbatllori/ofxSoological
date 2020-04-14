#!bin/bash

echo "[SOO INFO] This script needs to be run from the POSTXXX folder."

DATA=bin/data
FRAMES=$DATA/frames
OUTPUT=$DATA/output.gif

echo "[SOO INFO] Will read frames from: "$FRAMES
echo "[SOO INFO] Will export gif to: "$OUTPUT

ffmpeg -i $FRAMES/f%08d.png -vf palettegen $DATA/palette.png
ffmpeg -i $FRAMES/f%08d.png -i $DATA/palette.png -lavfi paletteuse $OUTPUT
