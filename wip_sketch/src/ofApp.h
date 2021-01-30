#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "soo_noise.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kHMargin_{-100};
  std::vector<int> values_;
  std::vector<int> init_values_;
};
