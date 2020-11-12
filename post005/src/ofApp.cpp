#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofBackground(0);
  ofSetFrameRate(30);

  // Load the character and center it on the screen
  font_.load(font_name_, 800, true, true, true);
  char_contour_ =
      font_.getCharacterAsPoints(char_, true, false).getOutline()[0];

  // Translate the shape to be centered vertically and shifted to the left
  // ourside the screen
  const ofRectangle bbox = char_contour_.getBoundingBox();
  const float y = (ofGetHeight() + bbox.height) / 2 - 25;
  char_contour_.translate({-1.2f * bbox.width, y});

  // Define the lines
  constexpr auto num_lines = 39;
  lines_.reserve(num_lines);

  const float distance_between_lines =
      (ofGetHeight() - 2 * kVerticalMargin_) / (num_lines - 1);

  for (int i{0}; i < num_lines; i++) {
    Line line;
    line.x_start_ = kHorizontalMargin_;
    line.x_end_ = ofGetWidth() - kHorizontalMargin_;
    line.y_value_ = i * distance_between_lines + kVerticalMargin_;
    lines_.push_back(line);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  // Update the lines by moving them vertically, recomputing the intersection
  // points and re-defining the paths with bezier segments
  for (auto& line : lines_) {
    // Handle first the extreme cases where a line is going to move outside the
    // screen either from the bottow (too large y value when moving down) or
    // from the top (too small y value when moving up).
    const float upper_margin = kVerticalMargin_;
    const float lower_margin = ofGetHeight() - kVerticalMargin_;

    // Case 1: the lines are moving down
    line.y_value_ = kMovingStep_ > 0 && (line.y_value_ >= lower_margin)
                        ? upper_margin
                        : line.y_value_;

    // Case 2: the lines are moving up
    line.y_value_ = kMovingStep_ < 0 && (line.y_value_ <= upper_margin)
                        ? lower_margin
                        : line.y_value_;

    // Update the vertical position of the line:
    line.y_value_ += kMovingStep_;

    // Find the intersection points between the line and the contour of the
    // loaded shape and define the line path
    const auto intersection_points =
        soo::intersection::HorizontalAxis_ClosedPolyline(line.y_value_,
                                                         char_contour_, 1.f);

    intersection_points.size() > 0
        ? line.DefineBezierSegments(intersection_points)
        : line.DefineStraight();
  }

  // Move the shape horizontally in loops
  const auto bbox = char_contour_.getBoundingBox();
  bbox.x > ofGetWidth()
      ? char_contour_.translate({-ofGetWidth() - bbox.width, 0})
      : char_contour_.translate({5, 0});
}

//--------------------------------------------------------------
void ofApp::draw() {
  for (auto& line : lines_) {
    line.path_.setFilled(false);
    line.path_.setStrokeWidth(2);
    line.path_.setStrokeColor(255 * line.y_value_ / ofGetHeight());
    line.path_.draw();
  }
}
