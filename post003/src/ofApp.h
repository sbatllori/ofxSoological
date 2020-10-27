#pragma once

#include "ofMain.h"

struct Cell {
  ofVec2f top_left_corner_;
  float width_;
  float height_;

  ofColor current_color_;
  ofColor final_color_;
  bool is_final_color_set_ = false;
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

 private:
  const int kNumRows_ = 9, kNumColumns_ = 9;
  std::vector<Cell> cells_;
  std::vector<int> unset_indices_;
  const std::vector<std::pair<int, int>> shape_indices_ = {
      {2, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 4},
      {4, 5}, {5, 6}, {6, 2}, {6, 6}, {7, 3}, {7, 4}, {7, 5}};

  std::vector<ofColor> available_colors_;
};
