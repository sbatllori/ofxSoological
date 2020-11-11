#include "Dandelion.h"
#include "soo_vectors.h"

namespace soo {

Dandelion::Dandelion(const ofVec2f& bbox_top_left_corner,
                     const float bbox_edge_length) {
  // Define the bouding box
  bbox_ = ofRectangle(bbox_top_left_corner.x, bbox_top_left_corner.y,
                      bbox_edge_length, bbox_edge_length);

  // Define the circle a bit to the left and bottom of the center of the
  // bounding box
  circle_center_.x = bbox_top_left_corner.x + 0.45f * bbox_edge_length;
  circle_center_.y = bbox_top_left_corner.y + 0.55f * bbox_edge_length;
  circle_radius_ = 0.6f * bbox_edge_length / 2.f;

  // Define the ellipse a bit to the left and bottom of the center of the circle
  ellipse_center_.x = circle_center_.x - 0.2f * circle_radius_;
  ellipse_center_.y = circle_center_.y + 0.2f * circle_radius_;
  ellipse_width_ = 0.8f * circle_radius_;
  ellipse_height_ = 0.5f * circle_radius_;

  // Define the dandelion lines such that:
  // - the origin of the line is set to the center of the ellipse
  // - the direction of the line is random
  // - the line length depends on where the direction is pointing to:
  //   - 1st quadrant of the circle (+, -): longer x, longer y
  //   - 2nd quadrant of the circle (-, -): shorter x, longer y
  //   - 3rd quadrant of the circle (-, +): shorter x, shorter y
  //   - 4th quadrant of the circle (+, +): longer x, shorter y
  // - some of the lines should be arrows:
  //   - up to 75% of the the longest lines can be set as arrows
  //   - up to 10% of the rest of the lines can be set as arrows
  const auto num_lines = static_cast<unsigned long>(bbox_edge_length / 5.f);
  lines_.reserve(num_lines);

  std::generate_n(std::back_inserter(lines_), num_lines, [this]() {
    dandelion::Line line;
    line.origin_ = ellipse_center_;
    line.direction_ = vectors::GetRandomUnitVec2();

    const float x = line.direction_.x;
    const float y = line.direction_.y;
    constexpr float min_factor = 0.5f;
    float max_factor = min_factor;
    max_factor = (x >= 0.f && y < 0.f) ? 1.70f : max_factor;   // 1st q
    max_factor = (x < 0.f && y < 0.f) ? 1.25f : max_factor;    // 2nd q
    max_factor = (x < 0.f && y >= 0.f) ? 1.10f : max_factor;   // 3rd q
    max_factor = (x >= 0.f && y >= 0.f) ? 1.25f : max_factor;  // 4th q
    line.length_ = circle_radius_ * ofRandom(min_factor, max_factor);

    const bool longest_lines = line.length_ > .9f * circle_radius_ * max_factor;
    const bool up_to_75_percent = ofRandom(100) < 75;
    const bool up_to_10_percent = ofRandom(100) < 10;
    line.is_arrow_ = ((longest_lines && up_to_75_percent) || up_to_10_percent)
                         ? true
                         : false;
    return line;
  });
}

void Dandelion::DrawBbox(const float x, const float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofDrawRectangle(bbox_);
  ofPopMatrix();
}

void Dandelion::DrawCircle(const float x, const float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofDrawCircle(circle_center_, circle_radius_);
  ofPopMatrix();
}

void Dandelion::DrawTrunk(const float x, const float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  const ofVec2f bbox_bottom_left_corner{bbox_.x, bbox_.y + bbox_.height};
  ofDrawLine(bbox_bottom_left_corner, ellipse_center_);
  ofPopMatrix();
}

void Dandelion::DrawEllipse(const float x, const float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofPushMatrix();
  ofTranslate(ellipse_center_);
  ofRotateZDeg(45.f);
  ofDrawEllipse(0, 0, ellipse_width_, ellipse_height_);
  ofPopMatrix();
  ofPopMatrix();
}

void Dandelion::DrawLines(const float x, const float y) const {
  ofPushMatrix();
  ofTranslate(x, y);

  for (const auto& line : lines_) {
    const ofVec3f direction{line.direction_.x, line.direction_.y, 0.f};
    const ofVec3f start{line.origin_.x, line.origin_.y, 0.f};
    const ofVec3f end = start + line.length_ * direction;

    line.is_arrow_ ? ofDrawArrow(start, end, 0.04f * circle_radius_)
                   : ofDrawLine(start, end);
  }

  ofPopMatrix();
}

}  // namespace soo
