#include "ofApp.h"
#include "soo_color_palettes.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Define random values along the canvas width
  values_.reserve(kNumValues);
  std::generate_n(std::back_inserter(values_), kNumValues, [this]() {
    return static_cast<int>(ofRandom(-kRadius_, ofGetWidth() + kRadius_));
  });
}

//--------------------------------------------------------------
void ofApp::update() {
  // Increase the values in a loop inside the canvas
  for (auto& t : values_) {
    t++;
    t = t == 0 ? -kRadius_ : t;
    t = t % (ofGetWidth() + kRadius_);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0);

  for (const auto& t : values_) {
    // Function to be represented
    const float wave_frequency = 1.5f;
    const float wave_length = 200.f;

    const float f = sin(wave_frequency * ofDegToRad(t));  // y = sin(x)
    const float f_min = -1;
    const float f_max = 1;

    const float x = t;
    const float y = ofMap(f, f_min, f_max, 0, wave_length);

    // Color
    const int palette_size = soo::colors::no_green.size();
    const float color_idx =
        ofMap(x, -kRadius_, ofGetWidth() + kRadius_, 0, 2 * palette_size);
    float integral_f;
    const float fractional = modf(color_idx, &integral_f);
    const int integral = integral_f;

    ofColor color;
    ofColor next_color;
    color.setHex(soo::colors::no_green[integral % palette_size]);
    next_color.setHex(soo::colors::no_green[(integral + 1) % palette_size]);
    color.lerp(next_color, fractional);

    ofSetColor(color);
    ofFill();
    ofDrawCircle(x, y, kRadius_);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
