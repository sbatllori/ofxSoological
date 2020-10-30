#pragma once

#include "ofMain.h"

namespace soo {

class LevyCCurve {
 public:
  LevyCCurve();
  LevyCCurve(const float rotation_angle);
  LevyCCurve(const float edge_length, const float rotation_angle);

  void GenerateRecursive(unsigned int iteration);
  void GenerateNextIteration();

  void draw(const float margin = 50.f);

 private:
  void Init();
  void Iterate();

 private:
  float edge_length_;
  float rotation_angle_;
  ofPolyline line_;
};
}  // namespace soo
