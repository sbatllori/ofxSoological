#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "shapes/Spirograph.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  soo::Spirograph spirograph_;
  ofVec3f previous_brush_position_;

  // GUI
  ofxPanel gui_;
  ofxIntSlider frame_rate_;
  ofxFloatSlider radius_1_;
  ofxFloatSlider radius_2_;
  ofxFloatSlider angle_0_;
  ofxFloatSlider angle_1_;
  ofxIntSlider transparency_;
  ofxFloatSlider width_;
};
