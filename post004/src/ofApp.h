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
  // Text
  const string kText =
      "  CUANDO ME INSPIRÁIS TODAS\nA LA VEZ, NUNCA QUIERO ELEGIR.";
  const string kFontName = "Fishfingers.ttf";
  ofTrueTypeFont font_;

  // Sky
  ofPath sky_border_;
  std::vector<Star> stars_;

  // Rocks
  Rock flying_rock_;
  Rock fire_rock_;
  std::vector<Rock> ground_rocks_;
};
