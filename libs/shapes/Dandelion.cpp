#include "Dandelion.h"

namespace soo {

Dandelion::Dandelion(ofVec2f bbox_top_left_corner, float bbox_edge_length) {
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
  unsigned long num_lines = static_cast<unsigned long>(bbox_edge_length / 5);
  lines.reserve(num_lines);

  for (unsigned long i{0}; i < num_lines; i++) {
    dandelion::Line line(ellipse_center_);
    line.SetRandomDirection();

    const float x = line.direction().x;
    const float y = line.direction().y;
    constexpr float min_factor = 0.5f;
    float max_factor = min_factor;
    (x >= 0.f && y < 0.f) ? max_factor = 1.7f : false;    // 1st q
    (x < 0.f && y < 0.f) ? max_factor = 1.25f : false;    // 2nd q
    (x < 0.f && y >= 0.f) ? max_factor = 1.1f : false;    // 3rd q
    (x >= 0.f && y >= 0.f) ? max_factor = 1.25f : false;  // 4th q
    line.properties_mutable().length_ =
        circle_radius_ * ofRandom(min_factor, max_factor);

    bool longest_lines =
        line.properties().length_ > .9f * circle_radius_ * max_factor;
    bool up_to_75_percent = ofRandom(100) < 75;
    bool up_to_10_percent = ofRandom(100) < 10;
    line.properties_mutable().is_arrow_ =
        ((longest_lines && up_to_75_percent) || up_to_10_percent) ? true
                                                                  : false;
    lines.push_back(line);
  }
}

void Dandelion::DrawBbox(float x, float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofDrawRectangle(bbox_);
  ofPopMatrix();
}

void Dandelion::DrawCircle(float x, float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofDrawCircle(circle_center_, circle_radius_);
  ofPopMatrix();
}

void Dandelion::DrawTrunk(float x, float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofVec2f bbox_bottom_left_corner = ofVec2f(bbox_.x, bbox_.y + bbox_.height);
  ofDrawLine(bbox_bottom_left_corner, ellipse_center_);
  ofPopMatrix();
}

void Dandelion::DrawEllipse(float x, float y) const {
  ofPushMatrix();
  ofTranslate(x, y);
  ofPushMatrix();
  ofTranslate(ellipse_center_);
  ofRotateZDeg(45.f);
  ofDrawEllipse(0, 0, ellipse_width_, ellipse_height_);
  ofPopMatrix();
  ofPopMatrix();
}

void Dandelion::DrawLines(float x, float y) const {
  ofPushMatrix();
  ofTranslate(x, y);

  for (auto& line : lines) {
    ofVec3f direction{line.direction().x, line.direction().y, 0.f};
    ofVec3f start{line.position().x, line.position().y, 0.f};
    ofVec3f end = start + line.properties().length_ * direction;

    line.properties().is_arrow_
        ? ofDrawArrow(start, end, 0.04f * circle_radius_)
        : ofDrawLine(start, end);
  }

  ofPopMatrix();
}

}  // namespace soo
