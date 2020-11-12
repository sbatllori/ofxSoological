#pragma once

#include "brushes/TrianglesOutBrush.h"
#include "ofMain.h"

struct HairyShape {
  ofPolyline contour_;
  soo::TrianglesOutBrush brush_;

  void draw() const {
    const ofVec2f& p = contour_[static_cast<int>(ofRandom(contour_.size()))];
    brush_.draw(p);
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  void GenerateBalls();

 private:
  const std::string font_name_ = "FreeSans.ttf";
  ofTrueTypeFont font_;

  const uint32_t char_ = '7';
  HairyShape seven_;

  const unsigned int kNumBalls_ = 7;
  std::vector<HairyShape> balls_;
};
