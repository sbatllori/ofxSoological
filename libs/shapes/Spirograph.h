#pragma once

#include "ofMain.h"

namespace soo {

class SpirographNode {
 public:
  SpirographNode() = default;
  SpirographNode(const ofVec3f& position, const float rotate_deg);
  SpirographNode(const ofVec3f& position, const float rotate_deg,
                 SpirographNode* parent);

  void set_position(const ofVec3f& position) { node_.setPosition(position); }
  void set_rotate_deg(const float rotate_deg) { rotate_deg_ = rotate_deg; }

  auto global_position() const { return node_.getGlobalPosition(); }
  void RotateZ() { node_.rotateDeg(rotate_deg_, {0, 0, 1}); }
  bool IsCicleStart() const;

 private:
  ofVec3f origin_;
  ofNode node_;
  float rotate_deg_;
};

class Spirograph {
 public:
  Spirograph() = default;

  auto& nodes_mutable() { return nodes_; }
  auto brush_position() const { return nodes_.back()->global_position(); }
  bool IsCicleStart() const;

  void AddNode(const ofVec3f& position, const float rotate_deg,
               const bool is_child = false);

 private:
  std::vector<SpirographNode*> nodes_;
};
}  // namespace soo
