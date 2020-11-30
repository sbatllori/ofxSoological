#pragma once

#include "ofMain.h"
#include "shapes/Spirograph.h"
#include "soo_noise.h"

struct Layer {
  soo::Spirograph spirograph_;
  ofVec3f previous_brush_position_{0, 0, 0};
  std::function<void(const Layer&)> draw_ = [](const Layer&) {};

  void draw() const { draw_(*this); }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  bool init_cicle_ = true;
  std::vector<Layer> layers_;

  bool is_noise_drawn_ = false;
  std::vector<soo::Noise> screen_noise_;
};
