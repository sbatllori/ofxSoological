#pragma once

#include "ofMain.h"

namespace soo {

using Node = std::shared_ptr<ofNode>;

class DragonCurve {
 public:
  DragonCurve();
  DragonCurve(const float rotation_angle);
  DragonCurve(const float edge_length, const float rotation_angle);

  void GenerateRecursive(unsigned int iteration);
  void GenerateNextIteration();

  void draw(const float margin = 50.f);

 private:
  void Init();
  void Iterate();

  Node GenerateNode(const ofVec3f& position);
  Node GenerateNode(const ofVec3f& position, const Node& parent);
  void AddNode(const Node& node);

 private:
  float edge_length_;
  float rotation_angle_;
  std::vector<Node> nodes_;
  ofPolyline line_;
};
}  // namespace soo
