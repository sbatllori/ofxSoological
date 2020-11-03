#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const std::string kImagePath_ = "DSC05554.jpg";
  ofImage image_;
  ofShader shader_;
};
