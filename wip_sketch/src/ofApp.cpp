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

ofColor GetBlendedColor(const float t, const soo::colors::Palette& palette,
                        const float margin = 0.f,
                        const float palette_loops = 1.f) {
  // Get the continuous color index corresponding to the given value
  // - Use its integral part to determine the current base color of the palette
  // - Use its fractional part to determine the amount of blending
  const float idx = ofMap(t, margin, ofGetWidth() - margin, 0,
                          palette_loops * (palette.size() - 1));
  float integral_f;
  const float fractional = modf(idx, &integral_f);
  const int integral = integral_f;

  // Get the colors corresponding to the current and the next position
  ofColor color;
  color.setHex(palette[integral % palette.size()]);

  ofColor next_color;
  next_color.setHex(palette[(integral + 1) % palette.size()]);

  // Mix the colors with the corresponding amount
  color.lerp(next_color, fractional);

  return color;
}

}  // namespace

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofBackground(0);
  ofSetFrameRate(60);
  ofSetCircleResolution(72);

  // Define random values along the canvas width
  for (int i{kHMargin_}; i < ofGetWidth() - kHMargin_; i++) {
    values_.push_back(i);
    init_values_.push_back(i);
  }
}

//--------------------------------------------------------------
void ofApp::update() {
  if (0 < ofGetFrameNum() && ofGetFrameNum() <= 200) {
    //    soo::SaveFrame(ofGetFrameNum());
  }

  // Make the values loop inside values range
  for (auto& t : values_) {
    t++;
    t = t > ofGetWidth() - kHMargin_ ? kHMargin_ : t;
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofVec2f p;
  ofColor color;
  ofFill();

  // background composition: soft thin lines building a net
  for (int i{0}; i < values_.size(); i++) {
    const auto& t = values_[i];
    const auto& t0 = init_values_[i];

    // ===>
    for (int i{0}; i < 50; i++) {
      p = f_sin(t0, 1.5f - .1f * i, 150.f);
      color = GetBlendedColor(-t, soo::colors::blues_of_the_sea, kHMargin_,
                              i * 0.1 + 1);

      ofSetColor(color.r, color.g, color.b, 20);
      ofDrawCircle(p.x, p.y - 150 + 20 * i, 5);
    }
    // <===
  }

  // foreground composition: thiker lines
  for (int i{0}; i < values_.size(); i++) {
    const auto& t = values_[i];
    const auto& t0 = init_values_[i];

    color = GetBlendedColor(-t, soo::colors::blues_of_the_sea, kHMargin_, 5.f);
    ofSetColor(color.r, color.g, color.b, 70);

    // ===>
    p = f_sin(t0, .5f, 50.f);
    ofDrawCircle(p.x, p.y + 50, 10);
    // <===

    // ===>
    p = f_sin(t0, .5f, 10.f);
    ofDrawCircle(p.x, p.y + 85, 10);
    // <===

    // ===>
    p = f_sin(t0, .5f, 100.f);
    ofDrawCircle(p.x, p.y + 40, 7);
    // <===

    // ===>
    p = f_sin(t0, .5f, 130.f);
    ofDrawCircle(p.x, p.y + 30, 5);
    // <===

    // ===>
    p = f_sin(t0, .5f, 250.f);
    ofDrawCircle(p.x, p.y + 100, 100);
    // <===

    // ===>
    for (int i{0}; i < 8; i++) {
      p = f_sin(t0, 1.5f - .2f * i, 150.f - 10.f * i);
      ofDrawCircle(p.x, p.y + 350 + 60 * i, 20 - 2 * i);
    }
    // <===

    // ===>
    for (int i{0}; i < 3; i++) {
      const float sign = i % 2 == 0 ? 1.f : -1.f;
      p = f_sin(t0, sign * 3.5f, 30.f + 20.f * i);
      ofDrawCircle(p.x, p.y + 850 + 15 * i, 6 - 2 * i);
    }
    // <===

    // ===>
    p = f_sin(t0, 1.f, 100.f);
    ofDrawCircle(p.x, ofGetHeight() - p.y, 80);
    // <===
  }

  //  for (int i{0}; i < values_.size(); i++) {
  //    const auto& t = values_[i];
  //    const auto& t0 = init_values_[i];

  //    color =
  //        GetBlendedColor(t, soo::colors::shiny_black_gradient,
  //        kHMargin_, 5.f);
  //    ofSetColor(color.r, color.g, color.b, 10);

  //    // ===>
  //    for (int i{0}; i < 12; i++) {
  //      p = f_sin(t0, i * 1.5f, 40.f * sin((12 - i) * ofGetElapsedTimef()));
  //      ofDrawCircle(p.x, p.y + 40 + i * 100, 2);
  //    }
  //    // <===
  //  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
