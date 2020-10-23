#include "TrianglesOutBrush.h"

namespace soo {
void TrianglesOutBrush::draw(const ofVec2f& center) const {
  for (int _{0}; _ < num_triangles_; _++) {
    // Copy the reference triangle coordinates
    ofVec2f A(reference_triangle_.A());
    ofVec2f B(reference_triangle_.B());
    ofVec2f C(reference_triangle_.C());

    // Apply to the vertices a random rotation around the origin
    float degrees = ofRandom(360);
    A.rotate(degrees);
    B.rotate(degrees);
    C.rotate(degrees);

    // Translate the vertices to the center of the brush, applying a random
    // offset in the new triangle direction (after applying the rotation), so
    // that the triangle is pointing outside.
    ofVec2f offset(ofRandom(min_offset_to_center_, max_offset_to_center_), 0.f);
    offset.rotate(degrees);
    A += center + offset;
    B += center + offset;
    C += center + offset;

    // Compute a linear interpolation of the two colors to paint the triangle
    // Fix: colors need to be copied for lerp to work properly
    ofColor color(color_), target_color(target_color_);
    ofColor interpolated_color = color.lerp(target_color, ofRandom(1.0f));
    ofSetColor(interpolated_color, alpha_);
    ofFill();
    ofDrawTriangle(A, B, C);
  }
}
}  // namespace soo
