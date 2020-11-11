#include "DragonCurve.h"

namespace soo {

void DragonCurve::Init() {
  // Reset the dragon curve data
  nodes_.clear();
  line_.clear();

  // Add the first segment
  const Node root = GenerateNode({0, 0, 0});
  const Node node = GenerateNode({edge_length_, 0, 0}, root);

  AddNode(root);
  AddNode(node);
}

void DragonCurve::Iterate() {
  // The last added node is the pivot point for the rotatin
  Node pivot = nodes_.back();

  // Copy all the nodes in reverse order, setting the pivot as the parent
  std::vector<Node> nodes_copy;
  nodes_copy.reserve(nodes_.size() - 1);

  std::transform(++nodes_.rbegin(), nodes_.rend(),
                 std::back_inserter(nodes_copy),
                 [this, &pivot](const Node& node) {
                   return GenerateNode(node->getGlobalPosition(), pivot);
                 });

  // Rotate all the pivot child nodes (i.e. all the copied nodes)
  pivot->rotateDeg(rotation_angle_, {0, 0, 1});

  // Add the copied and rotated nodes to the dragon curve
  for (const auto& node : nodes_copy) {
    AddNode(node);
  }
}

Node DragonCurve::GenerateNode(const ofVec3f& position) {
  Node node = std::make_shared<ofNode>();
  node->setPosition(position);
  return node;
}

Node DragonCurve::GenerateNode(const ofVec3f& position, const Node& parent) {
  Node node = std::make_shared<ofNode>();
  node->setParent(*parent);
  node->setGlobalPosition(position);
  return node;
}

void DragonCurve::AddNode(const Node& node) {
  nodes_.push_back(node);
  line_.addVertex(node->getGlobalPosition());
}

}  // namespace soo
