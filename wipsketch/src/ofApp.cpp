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
}

//--------------------------------------------------------------
void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(0);

  // The moon
  const ofVec2f moon{200, 100};
  const float moon_radius{40};

  ofFill();
  ofSetColor(ofColor::white);
  ofDrawCircle(200, 100, moon_radius);

  const int light_layers = 3;
  for (int i{light_layers}; i > 0; i--) {
    ofSetColor(ofColor::white, 10 * (light_layers - i + 1));
    ofDrawCircle(moon, moon_radius + 7 * i);
  }

  // The waves
  for (int t{0}; t < ofGetWidth(); t++) {
    for (int line{0}; line < 51; line++) {
      const float wave_frequency_amount = (line + 2) % 5;

      const auto p = f_sin(t, 0.25f * wave_frequency_amount,
                           25.f * sin(ofGetElapsedTimef() + line));

      const auto color = soo::colors::GetBlendedColor(
          wave_frequency_amount, 0, 4, soo::colors::orange_and_teal);

      const float y = p.y + 250 + 25 * line;

      ofFill();
      ofSetColor(color);
      ofDrawCircle(p.x, y, 2);

      ofSetColor(color, 200);
      ofDrawRectangle(p.x, y, 2, ofGetHeight());

      // The moon light on the waves
      const float light_width = 0.5f * moon_radius + 3.f * line;
      if (moon.x - light_width <= p.x && p.x <= moon.x + light_width) {
        ofSetColor(ofColor::white, 220);
        ofDrawRectangle(p.x, y, 2, 6);
        ofSetColor(ofColor::white, 180);
        ofDrawRectangle(p.x, y + 10, 2, 3);
        ofDrawRectangle(p.x, y + 18, 2, 2);
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
