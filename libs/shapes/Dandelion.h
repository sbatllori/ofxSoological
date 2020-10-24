#pragma once

#include "ofMain.h"

namespace soo {

namespace dandelion {

struct Line {
  ofVec2f origin_;
  ofVec2f direction_;
  float length_;
  bool is_arrow_;
};

}  // namespace dandelion

class Dandelion {
 public:
  Dandelion(ofVec2f bbox_top_left_corner, float bbox_edge_length);
  const ofVec2f center() const {
    return ofVec2f{bbox_.x + bbox_.width / 2.f, bbox_.y + bbox_.height / 2.f};
  }

  void DrawBbox(float x = 0.f, float y = 0.f) const;
  void DrawCircle(float x = 0.f, float y = 0.f) const;
  void DrawTrunk(float x = 0.f, float y = 0.f) const;
  void DrawEllipse(float x = 0.f, float y = 0.f) const;
  void DrawLines(float x = 0.f, float y = 0.f) const;

 private:
  ofRectangle bbox_;

  ofVec2f circle_center_;
  float circle_radius_;

  ofVec2f ellipse_center_;
  float ellipse_width_;
  float ellipse_height_;

  std::vector<dandelion::Line> lines;
};
}  // namespace soo
