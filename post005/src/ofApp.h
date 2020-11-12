#pragma once

#include "ofMain.h"
#include "soo_intersection.h"

struct Line {
  float x_start_;
  float x_end_;
  float y_value_;
  ofPath path_;

  void DefineStraight() {
    path_.clear();

    // Horizontal path from the start of the line to the end of the line
    path_.moveTo(x_start_, y_value_);
    path_.lineTo(x_end_, y_value_);
  }

  void DefineBezierSegments(const vector<ofVec2f>& bezier_points) {
    path_.clear();

    // The path initiates on the starting point of the line
    path_.moveTo(x_start_, y_value_);

    // For each pair of bezier points, draw a bezier segment connecting the
    // points, and a straight horizontal line between the bezier segments
    for (unsigned long i{0}; i < bezier_points.size() - 1; i += 2) {
      // Define the end and starting points of the bezier segment
      const float bezier_x_start = bezier_points[i].x;
      const float bezier_x_end = bezier_points[i + 1].x;

      // Horizontal segment to the start of the bezier segment
      path_.lineTo(bezier_x_start, y_value_);

      // Bezier line in the bezier segment (with dynamic values for the bezier
      // intensity depending on the length of the bezier segment)
      const float dx = 20;
      const float dy = (bezier_x_end - bezier_x_start) / 10;
      path_.bezierTo(bezier_x_start - dx, y_value_ - dy, bezier_x_end + dx,
                     y_value_ - dy, bezier_x_end, y_value_);
    }

    // Horizontal segment to the end of the line
    path_.lineTo(x_end_, y_value_);
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  const std::string font_name_ = "FreeSans.ttf";
  ofTrueTypeFont font_;

  const uint32_t char_ = '5';
  ofPolyline char_contour_;

  const float kMovingStep_ = -2.f;
  const float kHorizontalMargin_ = 0;
  const float kVerticalMargin_ = 0;
  std::vector<Line> lines_;
};
