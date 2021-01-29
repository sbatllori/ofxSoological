#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kRadius_{20};
  const int kNumValues{1000};
  std::vector<int> values_;
};
