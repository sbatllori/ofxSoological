#pragma once

#include "ofMain.h"
#include "shapes/DeformedLayeredCircle.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  const int kWidth_ = 960;
  const int kHeight_ = 540;
  ofVideoGrabber video_grabber_;

  ofPath shape_1_;
  ofPath shape_7_;
  std::vector<soo::DeformedLayeredCircle> strokes_;
  std::vector<soo::DeformedLayeredCircle> holes_;

  ofShader glitch_shader_;
  ofShader stroke_shader_;
  ofShader hole_shader_;
};
