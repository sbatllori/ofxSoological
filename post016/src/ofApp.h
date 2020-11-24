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
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void mouseEntered(int x, int y);
  void mouseExited(int x, int y);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);

 private:
  soo::Spirograph spirograph_;
  ofVec3f previous_brush_position_;

  // GUI
  bool hide_gui_;
  ofxPanel gui_;

  ofxIntSlider frame_rate_;

  ofxFloatSlider radius_1_;
  ofxFloatSlider radius_2_;

  ofxFloatSlider angle_0_;
  ofxFloatSlider angle_1_;

  ofxFloatSlider stroke_width_;
  ofxColorSlider color_;
};
