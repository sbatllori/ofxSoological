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

ofColor ofApp::GetBlendedColor(const float t, const int palette_loops) {
  const int size = color_palette.size();

  // Get the continuous color index corresponding to the given value
  // - Use its integral part to determine the current base color of the palette
  // - Use its fractional part to determine the amount of blending between the
  // current base color of the palette and the next one
  const float idx = ofMap(t, -kRadius_, ofGetWidth() + kRadius_, 0,
                          palette_loops * (size - 1));

  float integral_f;
  const float fractional = modf(idx, &integral_f);
  const int integral = integral_f;

  // Get the color corresponding to the current position
  ofColor color;
  color.setHex(color_palette[integral % size]);

  // Get the color corresponding to the next position
  ofColor next_color;
  next_color.setHex(color_palette[(integral + 1) % size]);

  // Mix the colors with the corresponding amount
  color.lerp(next_color, fractional);

  return color;
}

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Define random values along the canvas width
  values_.reserve(kNumValues_);
  std::generate_n(std::back_inserter(values_), kNumValues_, [this]() {
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
  ofBackground(237, 211, 178);
  ofFill();

  for (const auto& t : values_) {
    for (int i{0}; i < 10; i++) {
      // Function to be represented
      const ofVec2f p = f_sin(t, -0.5f * (i + 1), 50.f);
      const float x = p.x;
      const float y = p.y + 150 + i * 90;

      // Color
      const ofColor color = GetBlendedColor(t, i % 4 + 2);

      // Draw
      ofSetColor(color.r, color.g, color.b, 100);
      ofDrawCircle(x, y, kRadius_);

      ofSetColor(color.r, color.g, color.b, 5);
      ofDrawCircle(x, y, 1.25f * kRadius_);
      ofDrawCircle(x, y, 1.5f * kRadius_);
      ofDrawCircle(x, y, 2.5f * kRadius_);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
