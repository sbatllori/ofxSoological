#pragma once

#include "ofMain.h"
#include "soo_color_palettes.h"

struct Particle {
  ofVec2f center_;
  float radius_ = 10.f;
  ofVec2f direction_;
  float speed_ = 3.f;
  ofColor color_;
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  Particle main_circle_;
  std::vector<Particle> particles_;
  const soo::colors::Palette kColorPalette_{soo::colors::procreate_flourish};

  const bool kDrawColors_ = true;
  const bool kDrawGeometry_ = false;
};
