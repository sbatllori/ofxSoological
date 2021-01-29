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
    const float wave_frequency = 5.f;
    const float wave_length = 200.f;

    const float f = sin(wave_frequency * ofDegToRad(t));  // y = sin(x)
    const float f_min = -1;
    const float f_max = 1;

    const float x = t;
    const float y = ofMap(f, f_min, f_max, 0, wave_length);

    ofColor color;
    const float hue = ofMap(x, -kRadius_, ofGetWidth() + kRadius_, 0, 255);
    float const sat = 255;
    const float bri = 255;
    color.setHsb(hue, sat, bri, 50);

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
