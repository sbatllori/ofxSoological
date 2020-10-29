#pragma once

#include "ofMain.h"

namespace soo {

using Node = std::shared_ptr<ofNode>;
using Nodes = std::vector<Node>;

class DragonCurve {
 public:
  void GenerateRecursive(unsigned int iteration) {
    if (iteration == 0) {
      return;
    }
    GenerateNextIteration();
    GenerateRecursive(--iteration);
  }

 public:
  Node GenerateNode(const ofVec3f& position) {
    Node node = std::make_shared<ofNode>();
    node->setPosition(position);
    return node;
  }

  Node GenerateNode(const ofVec3f& position, const Node& parent) {
    Node node = std::make_shared<ofNode>();
    node->setParent(*parent);
    node->setGlobalPosition(position);
    return node;
  }

  void AddNode(const Node& node) {
    nodes_.push_back(node);
    line_.addVertex(node->getGlobalPosition());
  }

  void Init() {
    Node root = GenerateNode({0, 0, 0});
    Node node = GenerateNode({edge_length_, 0, 0}, root);

    AddNode(root);
    AddNode(node);
  }

  void GenerateNextIteration() {
    if (nodes_.empty()) {
      Init();
    } else {
      Nodes nodes_copy;
      Node root = nodes_.back();

      auto reverse_copy_nodes_from_index = nodes_.size() - 2;
      for (int i{reverse_copy_nodes_from_index}; i >= 0; i--) {
        Node node = GenerateNode(nodes_[i]->getGlobalPosition(), root);
        nodes_copy.push_back(node);
      }

      root->rotateDeg(rotation_angle_, {0, 0, 1});

      for (auto& node : nodes_copy) {
        AddNode(node);
      }
    }
  }

  //  void GenerateNextIteration_cool_stuff_but_not_dragon() {
  //    // https://en.wikipedia.org/wiki/L%C3%A9vy_C_curve
  //    // Notes: more cool stuff iterating on the rotation z sign -1 1 -1 1 etc
  //    ofPolyline line_copy{line_};
  //    auto pivot = line_copy.getVertices().back();

  //    line_copy.translate({0, 0});
  //    line_copy.rotateDeg(rotation_angle_, {0, 0, 1});
  //    line_copy.translate(pivot);

  //    line_.addVertices(line_copy.getVertices());
  //  }

 public:
  float edge_length_ = 100.f;
  float rotation_angle_ = 90.f;
  Nodes nodes_;
  ofPolyline line_;
};
}  // namespace soo
