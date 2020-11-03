#pragma once

#include "ofMain.h"

struct WaterColorDrop {
  ofVec2f position_;
  float radius_;
  ofVec2f direction_;
  float speed_;
  unsigned int alpha_;
  bool active_;

  void draw(ofColor& color) {
    color.a = alpha_;
    ofSetColor(color);
    ofDrawCircle(position_, radius_);
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  ofImage image_;
  const std::string kImagePath_ = "MaddalenaDoni.jpg";

  std::vector<WaterColorDrop> drops_;
};
