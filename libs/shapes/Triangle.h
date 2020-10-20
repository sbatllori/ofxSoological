#pragma once

#include "ofMain.h"

namespace soo {

class TriangleVertices {
 public:
  ofVec2f v1_;
  ofVec2f v2_;
  ofVec2f v3_;

  TriangleVertices() = default;
  bool Generate(const ofVec2f v1, const ofVec2f v2, const ofVec2f v3);
  bool Generate(const float edge_length_1, const float edge_length_2,
                const float edge_length_3);

 private:
  bool TriangleInequalityTheorem(const float edge_length_1,
                                 const float edge_length_2,
                                 const float edge_length_3);
};

class Triangle {
 public:
  Triangle(const TriangleVertices& vertices) : vertices_(vertices) {}

  const ofVec2f v1() const { return vertices_.v1_; }
  const ofVec2f v2() const { return vertices_.v2_; }
  const ofVec2f v3() const { return vertices_.v3_; }

 private:
  TriangleVertices vertices_;
};
}  // namespace soo
