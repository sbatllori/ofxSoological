#pragma once

#include "ofMain.h"
#include "soo_color_palettes.h"

#define SOO_BLACK 0x222222
#define SOO_WHITE 0xffffff
#define SOO_RED 0xc71010
#define SOO_YELLOW 0xffd500
#define SOO_GREEN 0x07704b

using vec2 = glm::vec2;
using vec3 = glm::vec3;

struct Params {
  // Colors
  static constexpr int kBlack{45};
  static constexpr int kWhite{48};
  static constexpr int kRed{5};
  static constexpr int kYellow{2};
  static constexpr int kGreen{1};

  // 2D background
  static constexpr unsigned long kRectangles{2000};
  static constexpr vec2 kMinRectangleSize{10, 10};
  static constexpr vec2 kMaxRectangleSize{70, 70};
  static constexpr int kAlpha{100};

  // 3D scene
  static constexpr int kOutlineSpacing{10};
  static constexpr vec3 kMinBoxSize{20, 20, 20};
  static constexpr vec3 kMaxBoxSize{50, 100, 50};
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 private:
  // Colors
  soo::colors::Palette color_palette_;

  // 2D background
  std::vector<ofRectangle> rectangles_;

  // 3D scene
  ofTrueTypeFont font_;
  ofPolyline top_outline_29_;
  std::vector<ofVec3f> boxes_;
  std::vector<ofLight> lights_;

 private:
  void ResetRandomRectangles();
  void ResetRandomBoxes();
};
