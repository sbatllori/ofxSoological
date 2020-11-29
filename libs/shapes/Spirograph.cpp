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
  return 2.f * rotate_deg_ < angle && angle < 4.f * rotate_deg_;
}

bool Spirograph::IsCicleStart() const {
  bool is_cicle_start = true;
  std::for_each(nodes_.begin(), --nodes_.end(),
                [&is_cicle_start](const auto& node) {
                  is_cicle_start = is_cicle_start && node->IsCicleStart();
                });
  return is_cicle_start;
}

void Spirograph::AddNode(const ofVec3f& position, const float rotate_deg,
                         const bool is_child) {
  SpirographNode* node =
      is_child ? new SpirographNode(position, rotate_deg, nodes_.back())
               : new SpirographNode(position, rotate_deg);
  nodes_.push_back(node);
}
}  // namespace soo
