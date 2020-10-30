#include "DragonCurve.h"

namespace soo {

DragonCurve::DragonCurve() : edge_length_(10.f), rotation_angle_(90.f) {}

DragonCurve::DragonCurve(const float rotation_angle)
    : edge_length_(10.f), rotation_angle_(rotation_angle) {}

DragonCurve::DragonCurve(const float edge_length, const float rotation_angle)
    : edge_length_(edge_length), rotation_angle_(rotation_angle) {}

void DragonCurve::GenerateRecursive(unsigned int iteration) {
  if (iteration > 0) {
    GenerateNextIteration();
    GenerateRecursive(--iteration);
  }
}

void DragonCurve::GenerateNextIteration() {
  nodes_.empty() ? Init() : Iterate();
}

void DragonCurve::draw(const float margin) {
  ofPushMatrix();
  {
    const ofRectangle& bbox = line_.getBoundingBox();

    // Define scaling parameters
    float scaleFactor = bbox.width > bbox.height
                            ? (ofGetWidth() - 2 * margin) / bbox.width
                            : (ofGetHeight() - 2 * margin) / bbox.height;

    // Define translation parameters
    float x = ofGetWidth() / 2 - scaleFactor * (bbox.x + bbox.width / 2);
    float y = ofGetHeight() / 2 - scaleFactor * (bbox.y + bbox.height / 2);

    ofTranslate(x, y);
    ofScale(scaleFactor);

    line_.draw();
  }
  ofPopMatrix();
}

void DragonCurve::Init() {
  // Reset the dragon curve data
  nodes_.clear();
  line_.clear();

  // Add the first segment
  Node root = GenerateNode({0, 0, 0});
  Node node = GenerateNode({edge_length_, 0, 0}, root);

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
  for (auto& node : nodes_copy) {
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
