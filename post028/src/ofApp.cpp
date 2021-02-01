#include "ofApp.h"
#include "soo_color_palettes.h"
#include "soo_export.h"

namespace {
ofVec2f f_sin(const float t, const float wave_frequency,
              const float wave_length) {
  const float f = sin(wave_frequency * ofDegToRad(t));
  const float f_min = -1;
  const float f_max = 1;

  const float x = t;
  const float y = ofMap(f, f_min, f_max, 0, wave_length);

  return ofVec2f{x, y};
}
}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Define values along the canvas width
  for (int t{kHMargin_}; t < ofGetWidth() - kHMargin_; t++) {
    t_values_.push_back(t);
    t0_values_.push_back(t);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());

  // Make the values loop inside the values range
  for (auto& t : t_values_) {
    t++;
    t = t > ofGetWidth() - kHMargin_ ? kHMargin_ : t;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(20);

  for (int i{0}; i < t_values_.size(); i++) {
    const auto& t = t_values_[i];
    const auto& t0 = t0_values_[i];

    for (int line{0}; line < 15; line++) {
      const auto p = f_sin(t0, 2.5f - .2f * line, 150.f - 10.f * line);
      const auto color = soo::colors::GetBlendedColor(
          -(t + 59 * (line % 3)), kHMargin_, ofGetWidth() - kHMargin_,
          soo::colors::shiny_black_gradient, line % 3 + 2);
      const float r = 20 - .5f * line;

      ofNoFill();
      ofSetColor(color.r, color.g, color.b, 70);
      ofDrawCircle(p.x, p.y + 100 + 60 * line, 1.5f * r);

      ofFill();
      ofSetColor(color.r, color.g, color.b, 20);
      ofDrawCircle(p.x, p.y + 100 + 60 * line, r);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
