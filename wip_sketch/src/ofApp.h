#pragma once

#define BLUE_BG 0xedd3b2
#define PINK_BG 0x93cea8
#define WHITE_BG 0x181818
#define BLACK_BG 0xffffff
#define YELLOW_BG 0xda96ff

#define BG WHITE_BG

#include "ofMain.h"
#include "ofxGui.h"
#include "soo_color_palettes.h"
#include "soo_noise.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  // GUI
  ofxPanel gui_;
  ofxColorSlider background_color_slider;

  ofColor bg_color_;
  const soo::colors::Palette color_palette_{
      soo::colors::warm_yellow_monochromatic};

  const int kRadius_{20};
  const int kNumValues_{700};
  std::vector<int> values_;

 private:
  ofColor GetBlendedColor(const float t, const int palette_loops = 1);
};
