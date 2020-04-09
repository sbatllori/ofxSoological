#!bin/bash

# ffmpeg -i bin/data/frames/f%08d.png -c:a aac -b:a 256k -ar 44100 -c:v libx264 -pix_fmt yuv420p -preset faster -tune stillimage -shortest bin/data/output.mp4

# Only video settings, no audio
# -i: input
# -r: video frame rate (fps)
# -crf: quality (0 = best)
ffmpeg \
-i bin/data/frames/f%08d.png \
-r 30 \
-crf 24 \
-c:v libx264 \
-pix_fmt yuv420p \
bin/data/output.mp4
