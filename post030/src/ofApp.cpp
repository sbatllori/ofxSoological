#include "ofApp.h"
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
  ofBackground(color_settings_.background_);
}

//--------------------------------------------------------------
void ofApp::update() {
  // soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Draw the moon
  const ofVec2f moon_center{200, 100};
  const float moon_radius{40};
  const int moonlight_layers{3};

  ofFill();
  ofSetColor(color_settings_.moon_);
  ofDrawCircle(moon_center, moon_radius);

  for (int i{moonlight_layers}; i > 0; i--) {
    ofSetColor(color_settings_.moon_, 10 * (moonlight_layers - i + 1));
    ofDrawCircle(moon_center, moon_radius + 7 * i);
  }

  // Draw the waves: cross all the waves simulateously, starting from the left
  // side of the screen and moving to the right
  for (int t{0}; t < ofGetWidth(); t++) {  // horizontal cross
    for (int row{0}; row < 51; row++) {    // vertical cross
      // Define the parameters of the current wave point:
      // - the frecuency (equal for the whole row)
      // - the position
      // - the vertical translation
      // - the color
      const float wave_frequency_amount = row % 5;

      const auto position = f_sin(t, 0.25f * wave_frequency_amount,
                                  25.f * sin(ofGetElapsedTimef() + row));

      const float vertical_translation = position.y + 250 + 25 * row;

      const auto color = soo::colors::GetBlendedColor(
          wave_frequency_amount + 3, 0, 4, color_settings_.waves_);

      // Draw the wave point
      // - A circle for the wave outline
      // - A rectangle for the wave filling
      ofFill();
      ofSetColor(color);
      ofDrawCircle(position.x, vertical_translation, 2);

      ofSetColor(color, 200);
      ofDrawRectangle(position.x, vertical_translation, 2, ofGetHeight());

      // Draw the moonlight reflection on the waves: three lines on the top of
      // the waves that are under the moon to simulate the reflection
      const float moonlight_width = 0.5f * moon_radius + 3.f * row;
      if (moon_center.x - moonlight_width <= position.x &&
          position.x <= moon_center.x + moonlight_width) {
        ofSetColor(color_settings_.moon_, 220);
        ofDrawRectangle(position.x, vertical_translation, 2, 6);
        ofSetColor(color_settings_.moon_, 180);
        ofDrawRectangle(position.x, vertical_translation + 10, 2, 3);
        ofDrawRectangle(position.x, vertical_translation + 18, 2, 2);
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
