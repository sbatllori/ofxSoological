#pragma once

#include "Brush.h"
#include "shapes/Triangle.h"

namespace soo {

struct GenerateTriangleParams;
struct GenerateColorParams;

class TrianglesOutBrush : public Brush {
 public:
  TrianglesOutBrush() = default;

  TrianglesOutBrush(const Triangle& reference_triangle, const int num_triangles,
                    const int min_offset_to_center,
                    const int max_offset_to_center, const ofColor& color,
                    const ofColor& target_color, const int alpha);

  TrianglesOutBrush(const GenerateTriangleParams& triangle_params,
                    const GenerateColorParams& color_params);

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

struct GenerateTriangleParams {
  Triangle reference_triangle_;
  int num_triangles_;
  int min_offset_to_center_;
  int max_offset_to_center_;

  GenerateTriangleParams& reference_triangle(
      const Triangle& reference_triangle) {
    reference_triangle_ = reference_triangle;
    return *this;
  }

  GenerateTriangleParams& num_triangles(const int num_triangles) {
    num_triangles_ = num_triangles;
    return *this;
  }

  GenerateTriangleParams& min_offset_to_center(const int min_offset_to_center) {
    min_offset_to_center_ = min_offset_to_center;
    return *this;
  }

  GenerateTriangleParams& max_offset_to_center(const int max_offset_to_center) {
    max_offset_to_center_ = max_offset_to_center;
    return *this;
  }
};

struct GenerateColorParams {
  ofColor color_;
  ofColor target_color_;
  int alpha_;

  GenerateColorParams& color(const ofColor& color) {
    color_ = color;
    return *this;
  }

  GenerateColorParams& target_color(const ofColor& target_color) {
    target_color_ = target_color;
    return *this;
  }

  GenerateColorParams& alpha(const int alpha) {
    alpha_ = alpha;
    return *this;
  }
};

}  // namespace soo
