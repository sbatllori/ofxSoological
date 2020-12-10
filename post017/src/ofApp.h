#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kWidth_ = 960;
  const int kHeight_ = 540;
  ofVideoGrabber camera_;

  ofShader shader_;
};
