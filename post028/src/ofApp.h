#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kHMargin_{-100};
  std::vector<int> t0_values_;
  std::vector<int> t_values_;
};
