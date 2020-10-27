#pragma once

#include "ofMain.h"
#include "shapes/DeformedLayeredCircle.h"

using Rock = soo::DeformedLayeredCircle;

struct Star {
  ofVec2f center_;
  float radius_;
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  const string kFontName_ = "Fishfingers.ttf";
  ofTrueTypeFont font_;

  const string kText_ =
      "  CUANDO ME INSPIRÁIS TODAS\nA LA VEZ, NUNCA QUIERO ELEGIR.";

  ofPath sky_border_;
  std::vector<Star> stars_;

  Rock flying_rock_;
  Rock fire_rock_;
  std::vector<Rock> ground_rocks_;
};
