#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "shapes/Spirograph.h"
#include "soo_noise.h"

struct Layer {
  soo::Spirograph spirograph_;
  ofVec3f previous_brush_position_{0, 0, 0};
  std::function<void(const Layer&)> draw_;

  Layer() {
    draw_ = [](const Layer&) { std::cout << "Not implemented\n"; };
  }

  void draw() const { draw_(*this); }
};

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
  std::vector<Layer> layers_;

  bool is_noise_drawn_ = false;
  std::vector<soo::Noise> screen_noise_;
};
