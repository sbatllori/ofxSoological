#pragma once

#include "ofMain.h"

class SpirographNode {
 public:
  SpirographNode() = default;
  SpirographNode(const ofVec3f& position) { node_.setGlobalPosition(position); }

  SpirographNode(const ofVec3f& position, SpirographNode* parent) {
    node_.setParent(parent->node_);
    node_.setPosition(position);
  }

  auto global_position() const { return node_.getGlobalPosition(); }
  const float& rotate_deg() const { return rotate_deg_; }
  void set_rotate_deg(const float rotate_deg) { rotate_deg_ = rotate_deg; }

  void RotateZ() { node_.rotateDeg(rotate_deg_, {0, 0, 1}); }
  bool IsCicleStart() const {
    const float angle = node_.getOrientationEulerDeg().z;
    const float epsilon = 0.001f;
    return abs(angle) < epsilon;
  }

 private:
  ofNode node_;
  float rotate_deg_;
};

struct Spirograph {
  std::vector<SpirographNode*> nodes_;
  ofVec3f previous_brush_position_;
  ofColor color_;

  auto brush_position() const { return nodes_.back()->global_position(); }
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
  std::vector<Spirograph> spirographs_;
};
