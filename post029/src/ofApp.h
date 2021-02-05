#pragma once

#include "ofMain.h"
#include "soo_color_palettes.h"

#define SOO_BLACK 0x000000
#define SOO_WHITE 0xffffff
#define SOO_RED 0xc71010
#define SOO_YELLOW 0xffd500
#define SOO_GREEN 0x07704b

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  // Numbers
  ofTrueTypeFont font_;
  ofPolyline top_outline_29_;

  // 3D
  std::vector<ofVec3f> box_sizes_;
  std::vector<ofLight> lights_;

  // 2D
  std::vector<ofRectangle> background_rectangles_;

  // Colors
  soo::colors::Palette color_palette_;

 private:
  void GenerateRandomBoxeSizes();
};
