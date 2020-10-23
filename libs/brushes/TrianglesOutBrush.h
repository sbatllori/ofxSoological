#pragma once

#include "Brush.h"
#include "shapes/Triangle.h"

namespace soo {

class TrianglesOutBrush : Brush {
 public:
  TrianglesOutBrush(const Triangle& reference_triangle, const int num_triangles,
                    const int min_offset_to_center,
                    const int max_offset_to_center, const ofColor& color,
                    const ofColor& target_color, const int alpha)
      : reference_triangle_(reference_triangle),
        num_triangles_(num_triangles),
        min_offset_to_center_(min_offset_to_center),
        max_offset_to_center_(max_offset_to_center),
        color_(color),
        target_color_(target_color),
        alpha_(alpha) {}

  void draw(const ofVec2f& center) const;

 private:
  Triangle reference_triangle_;
  int num_triangles_;
  int min_offset_to_center_;
  int max_offset_to_center_;

  ofColor color_;
  ofColor target_color_;
  int alpha_;
};
}  // namespace soo
