#include "Triangle.h"

namespace soo {

bool TriangleVertices::Generate(const ofVec2f& A, const ofVec2f& B,
                                const ofVec2f& C) {
  // Compute the length of the edges
  float edge_a_length = B.distance(C);
  float edge_b_length = A.distance(C);
  float edge_c_length = B.distance(A);

  // Check if the given vertices define a triangle
  if (TriangleInequalityTheorem(edge_c_length, edge_b_length, edge_a_length)) {
    A_ = A;
    B_ = B;
    C_ = C;
    return true;
  }
  return false;
}

bool TriangleVertices::Generate(const float edge_a_length,
                                const float edge_b_length,
                                const float edge_c_length) {
  // Check if the given edges could define a triangle
  if (TriangleInequalityTheorem(edge_c_length, edge_b_length, edge_a_length)) {
    // Define the triangle with the edge b centered vertically at the origin,
    // and the B vertex pointing to the right:
    //
    //        A
    //        . .
    //        .   .  c
    //        .     .
    //  b   (0,0)     B
    //        .     .
    //        .   .
    //        . .   a
    //        C

    // A : from the origin, half of b up
    A_.x = 0.f;
    A_.y = edge_b_length / 2.f;

    // C : from the origin, half of b down
    C_.x = 0.f;
    C_.y = -edge_b_length / 2.f;

    // B = (A.x + h, A.y - x):
    //
    //      | A
    //      | . .
    //    x | .   .  c
    //      | .     .
    //     b  .------B
    //        .  h  .
    //        .   .
    //        . .   a
    //        C
    //
    // Applying the Pithagorean Theorem we obtain the equation system:
    //      x^2 + h^2 = c^2
    //      (b - x)^2 + h^2 = a^2
    float x = (std::pow(edge_b_length, 2) - std::pow(edge_a_length, 2) +
               std::pow(edge_c_length, 2)) /
              (2.f * edge_b_length);
    float h = std::sqrt(std::pow(edge_c_length, 2) - std::pow(x, 2));
    B_.x = A_.x + h;
    B_.y = A_.y - x;
    return true;
  }
  return false;
}

bool TriangleVertices::TriangleInequalityTheorem(const float edge_a_length,
                                                 const float edge_b_length,
                                                 const float edge_c_length) {
  if (edge_a_length <= 0) return false;
  if (edge_c_length <= 0) return false;
  if (edge_b_length <= 0) return false;
  if (edge_a_length + edge_b_length <= edge_c_length) return false;
  if (edge_a_length + edge_c_length <= edge_b_length) return false;
  if (edge_b_length + edge_c_length <= edge_a_length) return false;
  return true;
}
}  // namespace soo
