#include "ofApp.h"
#include "soo_motion.h"
#include "soo_vectors.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofBackground(255);
  ofSetFrameRate(30);

  // Load the character
  font_.load(kFontName_, 800, true, true, true);
  char_contour_ = font_.getCharacterAsPoints(kChar_, true, false);

  kRenderKidLine_ ? setup_kid_line() : setup_lines();
}

//--------------------------------------------------------------
void ofApp::update() { kRenderKidLine_ ? update_kid_line() : update_lines(); }

//--------------------------------------------------------------
void ofApp::draw() {
  bool debug = false;

  ofPushMatrix();
  {
    const ofRectangle& bbox = char_contour_.getOutline()[0].getBoundingBox();
    const float x = ofGetWidth() / 2 - bbox.width / 2 - 50;
    const float y = ofGetHeight() / 2 + bbox.height / 2;
    ofTranslate(x, y);

    if (!debug) {
      kRenderKidLine_ ? draw_kid_line() : draw_lines();

    } else {
      ofSetColor(0);
      char_contour_.draw();

      ofFill();
      const auto& contour_vertices =
          char_contour_.getOutline()[0].getVertices();

      // Green => Start
      ofSetColor(0, 255, 0);
      ofDrawCircle(contour_vertices[65], 10);
      ofDrawCircle(contour_vertices[66], 10);

      // Red => End
      ofSetColor(255, 0, 0);
      ofDrawCircle(contour_vertices[1], 10);
      ofDrawCircle(contour_vertices[2], 10);

      // Blue => Bottom
      ofSetColor(0, 0, 255);
      for (int i{2}; i <= 66; i++) ofDrawCircle(contour_vertices[i], 5);
    }
  }
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::setup_lines() {
  // Save the bottom and the end of the contour separately, in order to manage
  // how the lines shall react when reaching them
  const auto& contour_vertices = char_contour_.getOutline()[0].getVertices();

  ofPath bottom;
  bottom.moveTo(contour_vertices[2]);
  for (unsigned long i{2}; i <= 66; i++) {
    bottom.lineTo(contour_vertices[i]);
  }
  char_bottom_ = bottom.getOutline()[0].getResampledBySpacing(1);

  ofPath end;
  end.moveTo(contour_vertices[1]);
  end.lineTo(contour_vertices[2]);
  char_end_ = end.getOutline()[0].getResampledBySpacing(1);

  // Initialize the lines at the start of the contour
  const ofVec2f& v_origin_left = contour_vertices[66];
  const ofVec2f& v_origin_right = contour_vertices[65];

  constexpr unsigned long kNumLines = 300;
  lines_.reserve(kNumLines);

  std::generate_n(std::back_inserter(lines_), kNumLines,
                  [&v_origin_left, &v_origin_right]() {
                    Line line;

                    // Set line parameters
                    line.position_ =
                        ofVec2f{ofRandom(v_origin_left.x, v_origin_right.x),
                                v_origin_right.y};
                    line.direction_ = soo::vectors::GetRandomUnitVec2();
                    line.step_length_ = 10;
                    line.rotation_angle_ = ofRandom(50, 140);

                    // Initialize the path
                    line.path_.moveTo(line.position_);

                    // Set path properties
                    line.path_.setStrokeColor(ofColor(0, 0, 0, 50));
                    line.path_.setStrokeWidth(2);
                    line.path_.setFilled(false);

                    return line;
                  });
}

void ofApp::update_lines() {
  for (auto& line : lines_) {
    // Check if the line reached the end of the shape
    if (!line.done_) {
      for (const auto& vertex : char_end_) {
        if (line.position_.distance(vertex) < line.step_length_) {
          line.done_ = true;
          break;
        }
      }
    }

    // Grow the line if it did not reach the end of the shape
    if (!line.done_) {
      // If the next step is inside the shape, move forward. Otherwise, change
      // the moving direction in order to continue moving inside the shape
      const ofVec2f next_step = soo::motion::UniformLinear(
          line.position_, line.direction_, line.step_length_);

      const bool next_step_inside =
          char_contour_.getOutline()[0].inside(next_step.x, next_step.y);

      if (next_step_inside) {
        line.AddPosition(next_step);
      }

      // else if (line.path_.getOutline()[0].getVertices().size() > 1) {
      else {
        line.rotation_angle_sign_ = 1;

        // If we are close to the bottom of the shape, we need to change the
        // sign of the rotation angle. Note that when initializing the lines we
        // are gonna be close to the bottom since the lines origin at the
        // bottom. Skip that case by checking that the path has more than the
        // initial position registered.
        if (line.path_.getOutline()[0].getVertices().size() > 1) {
          for (const auto& vertex : char_bottom_) {
            if (next_step.distance(vertex) < line.step_length_) {
              line.rotation_angle_sign_ = -1;
              break;
            }
          }
        }
        line.direction_.rotate(line.rotation_angle_sign_ *
                               line.rotation_angle_);
      }
    }
  }
}

void ofApp::draw_lines() {
  for (auto& line : lines_) {
    line.path_.draw();
  }
}

//--------------------------------------------------------------
void ofApp::setup_kid_line() {
  const auto& contour_vertices = char_contour_.getOutline()[0].getVertices();

  // Set line parameters
  kid_line_.position_ = contour_vertices[65];
  kid_line_.direction_ = soo::vectors::GetRandomUnitVec2();
  kid_line_.step_length_ = 5;

  // Initialize the path
  kid_line_.path_.moveTo(kid_line_.position_);

  // Set path properties
  kid_line_.path_.setStrokeColor(ofColor(200, 100, 100, 100));
  kid_line_.path_.setStrokeWidth(10);
  kid_line_.path_.setFilled(false);
}

void ofApp::update_kid_line() {
  // The next step must be inside the shape and the closest possible to the
  // shape contour
  ofVec2f next_step = kid_line_.position_;
  do {
    kid_line_.position_ = next_step;
    next_step = soo::motion::UniformLinear(next_step, kid_line_.direction_,
                                           kid_line_.step_length_);
  } while (char_contour_.getOutline()[0].inside(next_step.x, next_step.y));

  kid_line_.AddPosition(kid_line_.position_);
  kid_line_.direction_ = soo::vectors::GetRandomUnitVec2();
}

void ofApp::draw_kid_line() { kid_line_.path_.draw(); }
