#include "Triangle.h"

namespace soo {

bool TriangleVertices::Generate(const ofVec2f v1, const ofVec2f v2,
                                const ofVec2f v3) {
  // Compute the length of the edges
  float edge_length_1 = v2.distance(v3);
  float edge_length_2 = v1.distance(v3);
  float edge_length_3 = v1.distance(v2);

  // Check if the given vertices define a triangle
  if (TriangleInequalityTheorem(edge_length_1, edge_length_2, edge_length_3)) {
    v1_ = v1;
    v2_ = v2;
    v3_ = v3;
    return true;
  }
  return false;
}

bool TriangleVertices::Generate(const float edge_length_1,
                                const float edge_length_2,
                                const float edge_length_3) {
  // Check if the given edges could define a triangle
  if (TriangleInequalityTheorem(edge_length_1, edge_length_2, edge_length_3)) {
    // Define the triangle with the edge_1 centered at the origin as the base of
    // the triangle, and v1 as the top vertex:
    //
    //             v1
    //            .   .
    //    edge_3 .      . edge_2
    //          .         .
    //         v2..(0,0)..v3
    //            edge_1

    // v2 : from the origin, half of edge_1 to the left
    v2_.x = -edge_length_1 / 2.f;
    v2_.y = 0.f;

    // v3 : from the origin, half of edge_1 to the right
    v3_.x = edge_length_1 / 2.f;
    v3_.y = 0.f;

    // v1 = (v2_.x + x, h):
    //
    //    |       v1
    //    |      . . .
    //  h |     .  .   .
    //    |    .   .     .
    //    |  v2.........v3
    //       ------
    //         x
    //
    // Applying the Pithagorean Theorem we obtain the equation system:
    //      x^2 + h^2 = edge_3^2
    //      (edge_1 - x)^2 + h^2 = edge_2^2
    float x = (std::pow(edge_length_1, 2) - std::pow(edge_length_2, 2) +
               std::pow(edge_length_3, 2)) /
              (2.f * edge_length_1);
    float h = std::sqrt(std::pow(edge_length_3, 2) - std::pow(x, 2));
    v1_.x = v2_.x + x;
    v1_.y = h;

    return true;
  }
  return false;
}

bool TriangleVertices::TriangleInequalityTheorem(const float edge_length_1,
                                                 const float edge_length_2,
                                                 const float edge_length_3) {
  if (edge_length_1 <= 0) return false;
  if (edge_length_2 <= 0) return false;
  if (edge_length_3 <= 0) return false;
  if (edge_length_1 + edge_length_2 <= edge_length_3) return false;
  if (edge_length_1 + edge_length_3 <= edge_length_2) return false;
  if (edge_length_2 + edge_length_3 <= edge_length_1) return false;
  return true;
}
}  // namespace soo
