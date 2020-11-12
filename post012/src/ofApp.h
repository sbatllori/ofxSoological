#pragma once

#include "ofMain.h"

struct Particle {
  ofVec2f center_;
  float radius_;
  ofVec2f direction_;
  float speed_;
  ofColor color_;

  void draw() const {
    ofNoFill();
    ofSetColor(color_, 10);
    ofDrawCircle(center_, radius_);
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const std::string bg_image_path_ = "012_background.jpg";
  ofImage bg_image_;

  const std::string mask_path_ = "012_mask.jpg";
  ofImage mask_;
  ofRectangle mask_bbox_;

  std::vector<Particle> particles_;
};
