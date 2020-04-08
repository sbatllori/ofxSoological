#!bin/bash
ffmpeg -i bin/data/frames/f%08d.png -c:a aac -b:a 256k -ar 44100 -c:v libx264 -pix_fmt yuv420p -preset faster -tune stillimage -shortest bin/data/output.mp4
