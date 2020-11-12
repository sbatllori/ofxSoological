#pragma once

#include "CurveFractal.h"

namespace soo {

class LevyCCurve : public CurveFractal {
 public:
  LevyCCurve() : CurveFractal() {}
  LevyCCurve(const float rotation_angle) : CurveFractal(rotation_angle) {}
  LevyCCurve(const float edge_length, const float rotation_angle)
      : CurveFractal(edge_length, rotation_angle) {}

 private:
  void Init();
  void Iterate();
};
}  // namespace soo
