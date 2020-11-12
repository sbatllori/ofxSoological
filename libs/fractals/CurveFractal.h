#pragma once

#include "ofMain.h"

namespace soo {

class CurveFractal {
 public:
  CurveFractal();
  CurveFractal(const float rotation_angle);
  CurveFractal(const float edge_length, const float rotation_angle);

  virtual void GenerateRecursive(unsigned int iteration);
  virtual void GenerateNextIteration();

  virtual void draw(const float margin = 50.f) const;

 protected:
  virtual void Init() = 0;
  virtual void Iterate() = 0;

 protected:
  float edge_length_;
  float rotation_angle_;
  ofPolyline line_;
};
}  // namespace soo
