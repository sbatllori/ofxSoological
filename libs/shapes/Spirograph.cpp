#include "Spirograph.h"

namespace soo {

SpirographNode::SpirographNode(const ofVec3f& position, const float rotate_deg)
    : rotate_deg_(rotate_deg) {
  node_.setGlobalPosition(position);
}

SpirographNode::SpirographNode(const ofVec3f& position, const float rotate_deg,
                               SpirographNode* parent)
    : rotate_deg_(rotate_deg) {
  node_.setParent(parent->node_);
  node_.setPosition(position);
}

bool SpirographNode::IsCicleStart() const {
  const float angle = node_.getOrientationEulerDeg().z;
  const float epsilon = 0.001f;
  return abs(angle) < epsilon;
}

void Spirograph::AddNode(const ofVec3f& position, const float rotate_deg,
                         const bool is_child) {
  SpirographNode* node =
      is_child ? new SpirographNode(position, rotate_deg, nodes_.back())
               : new SpirographNode(position, rotate_deg);
  nodes_.push_back(node);
}
}  // namespace soo
