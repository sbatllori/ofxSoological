#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  ofTrueTypeFont font_;
  ofPolyline top_outline_29_;
};
