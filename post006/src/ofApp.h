#pragma once

#include "fractals/DragonCurve.h"
#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  const float kRotationAngle_ = 90.f;
  const unsigned int kIterations_ = 10;
  soo::DragonCurve curve_;
};
