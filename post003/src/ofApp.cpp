#include "ofApp.h"

namespace {
ofColor GetRandomColor(const std::vector<ofColor>& colors) {
  return colors[static_cast<unsigned long>(ofRandom(0, colors.size()))];
}
}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetBackgroundColor(255);
  ofSetLineWidth(4);

  // Define the available colors for the cells
  const unsigned int kBright = 255;
  const unsigned int kDark = 50;
  available_colors_.push_back(ofColor(kBright, kDark, kDark));    // red-ish
  available_colors_.push_back(ofColor(kDark, kBright, kDark));    // green-ish
  available_colors_.push_back(ofColor(kDark, kDark, kBright));    // blue-ish
  available_colors_.push_back(ofColor(kBright, kBright, kDark));  // yellow-ish

  const ofColor in_final_color = available_colors_[0];  // red-ish
  const ofColor out_final_color = ofColor(20);          // black-ish

  // Initialize a vector of indices, fill it in with the numbers 0 to n (n being
  // the size of the array), and shuffle it. This will allow us to pick each
  // cell only once and in a random order.
  //
  // Notes for the developer:
  //    - resize() initializes the vector with empty pointers and the end()
  //    iterator actually moves, i.e. we can use algorithms that iterate through
  //    an initialized container.
  //    - iota() fills in the vector with sequentially increasing values
  //    starting with 0
  unset_indices_.resize(kNumRows_ * kNumColumns_);
  std::iota(unset_indices_.begin(), unset_indices_.end(), 0);
  std::random_shuffle(unset_indices_.begin(), unset_indices_.end());

  // Initialize the cells
  cells_.reserve(kNumRows_ * kNumColumns_);

  const float width = ofGetWindowWidth() / kNumRows_;
  const float height = ofGetWindowHeight() / kNumColumns_;

  for (int i{0}; i < kNumRows_; i++) {
    for (int j{0}; j < kNumColumns_; j++) {
      Cell cell;

      // Define cell geometry
      cell.top_left_corner_ = ofVec2f(i * width, j * height);
      cell.width_ = width;
      cell.height_ = height;

      // Set a random color to the cell
      cell.current_color_ = GetRandomColor(available_colors_);

      // Set the final color depending on if the cell belongs to the final shape
      const bool is_shape_cell = std::count(
          shape_indices_.begin(), shape_indices_.end(), std::make_pair(j, i));

      cell.final_color_ = is_shape_cell ? in_final_color : out_final_color;

      cells_.push_back(cell);
    }
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  // Update the color of all the cells
  for (auto& cell : cells_) {
    if (ofGetFrameNum() % 3 == 0) {
      cell.current_color_ = cell.is_final_color_set_
                                ? cell.final_color_
                                : GetRandomColor(available_colors_);
    }
  }

  // Pick one of the cells defining the shape, in oder to set the final color to
  // it. Remove the picked cell from the unset cells.
  if (!unset_indices_.empty() && ofGetFrameNum() > 60 &&
      ofGetFrameNum() % 3 == 0) {
    const auto idx = static_cast<unsigned long>(unset_indices_.back());
    cells_[idx].is_final_color_set_ = true;
    unset_indices_.pop_back();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  for (auto& cell : cells_) {
    ofFill();
    ofSetColor(cell.current_color_);
    ofDrawRectangle(cell.top_left_corner_, cell.width_, cell.height_);

    ofNoFill();
    ofSetColor(ofColor::white);
    ofDrawRectangle(cell.top_left_corner_, cell.width_, cell.height_);
  }
}
