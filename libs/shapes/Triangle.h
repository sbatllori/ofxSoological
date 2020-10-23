#pragma once

#include "ofMain.h"

namespace soo {

class TriangleVertices {
 public:
  ofVec2f A_;
  ofVec2f B_;
  ofVec2f C_;

  TriangleVertices() = default;
  bool Generate(const ofVec2f& A, const ofVec2f& B, const ofVec2f& C);
  bool Generate(const float edge_a_length, const float edge_b_length,
                const float edge_c_length);

 private:
  bool TriangleInequalityTheorem(const float edge_a_length,
                                 const float edge_b_length,
                                 const float edge_c_length);
};

class Triangle {
 public:
  Triangle(const TriangleVertices& vertices) : vertices_(vertices) {}

  const ofVec2f A() const { return vertices_.A_; }
  const ofVec2f B() const { return vertices_.B_; }
  const ofVec2f C() const { return vertices_.C_; }

 private:
  TriangleVertices vertices_;
};
}  // namespace soo
