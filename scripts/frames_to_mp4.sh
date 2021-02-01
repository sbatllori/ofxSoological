#!bin/bash

echo "[SOO INFO] This script needs to be run from the POSTXXX folder."

FRAMES=bin/data/frames
OUTPUT=bin/data/output.mp4

echo "[SOO INFO] Will read frames from: "$FRAMES
echo "[SOO INFO] Will export mp4 to: "$OUTPUT


# ffmpeg -i bin/data/frames/f%08d.png -c:a aac -b:a 256k -ar 44100 -c:v libx264 -pix_fmt yuv420p -preset faster -tune stillimage -shortest bin/data/output.mp4

# Only video settings, no audio
# -i: input
# -r: video frame rate (fps)
# -crf: quality (0 = best)
ffmpeg \
-i $FRAMES/f%08d.png \
-r 30 \
-crf 19.5 \
-c:v libx264 \
-filter:v "setpts=0.65*PTS" \
-pix_fmt yuv420p \
$OUTPUT

# -filter:v "setpts=3*PTS" \
# -filter:v ":minterpolate='mi_mode=mci:mc_mode=aobmc:vsbmc=1:fps=120'" \
