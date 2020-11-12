#pragma once

#include "CurveFractal.h"

namespace soo {

using Node = std::shared_ptr<ofNode>;

class DragonCurve : public CurveFractal {
 public:
  DragonCurve() : CurveFractal() {}
  DragonCurve(const float rotation_angle) : CurveFractal(rotation_angle) {}
  DragonCurve(const float edge_length, const float rotation_angle)
      : CurveFractal(edge_length, rotation_angle) {}

 private:
  void Init();
  void Iterate();

  Node GenerateNode(const ofVec3f& position);
  Node GenerateNode(const ofVec3f& position, const Node& parent);
  void AddNode(const Node& node);

 private:
  std::vector<Node> nodes_;
};
}  // namespace soo
