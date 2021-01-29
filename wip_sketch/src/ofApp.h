#pragma once

#include "ofMain.h"
#include "soo_color_palettes.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kRadius_{20};
  const int kNumValues_{500};
  std::vector<int> values_;

  const soo::colors::Palette color_palette{soo::colors::blues_of_the_sea};

 private:
  ofColor GetBlendedColor(const float t, const int palette_loops = 1);
};
