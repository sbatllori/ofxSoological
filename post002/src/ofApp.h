#pragma once

#include "ofMain.h"

struct Line {
  ofVec2f position_;
  ofVec2f direction_;
  float step_length_;
  float rotation_angle_;
  int rotation_angle_sign_ = 1;
  bool done_ = false;

  ofPath path_;

  void AddPosition(const ofVec2f& p) {
    position_ = p;
    path_.lineTo(p);
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  void setup_lines();
  void update_lines();
  void draw_lines();

  void setup_kid_line();
  void update_kid_line();
  void draw_kid_line();

 private:
  const std::string kFontName_ = "FreeSans.ttf";
  ofTrueTypeFont font_;

  const uint32_t kChar_ = '2';
  ofPath char_contour_;
  ofPolyline char_bottom_;
  ofPolyline char_end_;

  const bool kRenderKidLine_ = false;
  std::vector<Line> lines_;
  Line kid_line_;
};
