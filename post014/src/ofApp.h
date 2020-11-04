#pragma once

#include "ofMain.h"
#include "shapes/Dandelion.h"
#include "soo_noise.h"

//--------------------------------------------------------------
// Helper structs to draw different scenes
//--------------------------------------------------------------
struct DrawDandelion {
  static void draw(const soo::Dandelion& dandelion, const ofColor& stroke_color,
                   const ofColor& bbox_stroke_color,
                   const ofColor& bbox_background_color,
                   const ofVec2f& p = {0, 0}) {
    ofSetColor(bbox_background_color);

    ofFill();
    ofSetLineWidth(3);
    dandelion.DrawBbox(p.x, p.y);

    ofSetColor(stroke_color);

    ofSetLineWidth(2);
    dandelion.DrawLines(p.x, p.y);

    ofFill();
    ofSetLineWidth(2);
    dandelion.DrawEllipse(p.x, p.y);

    ofNoFill();
    ofSetLineWidth(4);
    dandelion.DrawCircle(p.x, p.y);

    ofSetLineWidth(4);
    dandelion.DrawTrunk(p.x, p.y);

    ofSetColor(bbox_stroke_color);

    ofNoFill();
    ofSetLineWidth(3);
    dandelion.DrawBbox(p.x, p.y);
  }

  static void BlackOnWhite(const soo::Dandelion& dandelion,
                           const ofVec2f& p = {0, 0}) {
    draw(dandelion, ofColor::black, ofColor::black, ofColor::white, p);
  }

  static void RedOnWhiteNoBbox(const soo::Dandelion& dandelion,
                               const ofVec2f& p = {0, 0}) {
    draw(dandelion, ofColor{200, 0, 0}, ofColor{0, 0, 0, 0}, ofColor::white, p);
  }
  static void WhiteOnBlack(const soo::Dandelion& dandelion,
                           const ofVec2f& p = {0, 0}) {
    draw(dandelion, ofColor::white, ofColor{255, 200, 0}, ofColor::black, p);
  }

  static ofVec2f TransformHFlip(const soo::Dandelion& dandelion) {
    ofVec2f pivot;
    pivot.x = dandelion.center().x;
    pivot.y = dandelion.center().y;

    ofTranslate(pivot);
    ofRotateZDeg(270);

    return pivot;
  }
};

struct DandelionGrid {
  int kExternalMargin_;
  int kInternalMargin_;
  int kNCellsPerAxe_;
  std::vector<soo::Dandelion> dandelions_;

  virtual void draw() const = 0;
};

struct Composition1 : DandelionGrid {
  Composition1() {
    kExternalMargin_ = 30;
    kInternalMargin_ = 20;
    kNCellsPerAxe_ = 5;
  }

  void draw() const {
    constexpr int kOtherIdx = 8;

    for (int i{0}; i < dandelions_.size(); i++) {
      if (i != kOtherIdx) {
        DrawDandelion::BlackOnWhite(dandelions_[i]);
      }
    }

    const auto& dandelion = dandelions_[kOtherIdx];
    ofPushMatrix();
    ofVec2f pivot = DrawDandelion::TransformHFlip(dandelion);
    DrawDandelion::RedOnWhiteNoBbox(dandelion, -pivot);
    ofPopMatrix();
  }
};

struct Composition2 : DandelionGrid {
  Composition2() {
    kExternalMargin_ = 250;
    kInternalMargin_ = 50;
    kNCellsPerAxe_ = 1;
  }

  void draw() const {
    for (const auto& dandelion : dandelions_) {
      DrawDandelion::BlackOnWhite(dandelion);
    }
  }
};

struct Composition3 : DandelionGrid {
  Composition3() {
    kExternalMargin_ = 200;
    kInternalMargin_ = 200;
    kNCellsPerAxe_ = 2;
  }

  void draw() const {
    for (const auto& dandelion : dandelions_) {
      DrawDandelion::BlackOnWhite(dandelion);
    }
  }
};

struct Composition4 : DandelionGrid {
  Composition4() {
    kExternalMargin_ = 300;
    kInternalMargin_ = 20;
    kNCellsPerAxe_ = 2;
  }

  void draw() const {
    constexpr int kOtherIdx = 3;

    for (int i{0}; i < dandelions_.size(); i++) {
      if (i != kOtherIdx) {
        DrawDandelion::BlackOnWhite(dandelions_[i]);
      }
    }

    const auto& dandelion = dandelions_[kOtherIdx];
    ofPushMatrix();
    ofVec2f pivot = DrawDandelion::TransformHFlip(dandelion);
    DrawDandelion::WhiteOnBlack(dandelion, -pivot);
    ofPopMatrix();
  }
};

struct Composition5 : DandelionGrid {
  Composition5() {
    kExternalMargin_ = 200;
    kInternalMargin_ = 50;
    kNCellsPerAxe_ = 1;
  }

  void draw() const {
    for (const auto& dandelion : dandelions_) {
      ofPushMatrix();
      ofVec2f pivot = DrawDandelion::TransformHFlip(dandelion);
      DrawDandelion::WhiteOnBlack(dandelion, -pivot);
      ofPopMatrix();
    }
  }
};

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);

 private:
  // Dandelion Grid
  Composition1 grid_;

  // Screen Noise
  constexpr static float kBlackNoisePercent_ = 0.7f;
  constexpr static float kWhiteNoisePercent_ = 0.3f;
  soo::Noise black_noise_;
  soo::Noise white_noise_;
};
