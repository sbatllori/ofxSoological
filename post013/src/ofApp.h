#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  void SwitchBgColor() {
    bg_color_ = bg_color_ == blue_ ? pink_ : blue_;
    ofSetColor(bg_color_);
  }

  ofColor GetFontColor() {
    ofColor font_color = bg_color_ == blue_ ? ofColor::white : ofColor::black;
    return font_color;
  }

 private:
  const ofColor blue_{112, 198, 255};
  const ofColor pink_{255, 135, 221};

  const std::string kFontName_ = "orange juice 2.0.ttf";
  ofTrueTypeFont font_;

  int bg_vertical_;
  ofColor bg_color_;

  bool rotate_character_;
  int rotation_angle_deg_;
};
