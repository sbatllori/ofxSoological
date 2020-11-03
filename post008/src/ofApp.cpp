#include "ofApp.h"
#include "soo_export.h"
#include "soo_motion.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Load the image from which to simulate the water color drop effect
  image_.load(kImagePath_);

  // Canvas settings
  ofSetBackgroundAuto(false);
  ofBackground(255);
  ofSetFrameRate(30);
  ofSetCircleResolution(72);
  ofSetWindowShape(static_cast<int>(image_.getWidth()),
                   static_cast<int>(image_.getHeight()));

  // Initialize the water color drops:
  // - The initial position should be on the top of the canvas
  // - Drops should fall vertically
  // - Up to 10% of the drops are bigger thant the rest
  constexpr int kNumDrops = 250;
  drops_.reserve(kNumDrops);

  std::generate_n(std::back_inserter(drops_), kNumDrops, []() {
    WaterColorDrop drop;

    drop.active_ = true;
    drop.position_ = {ofRandomWidth(), 0};
    drop.direction_ = {0, 1};

    bool up_to_10_percent = ofRandom(100) < 10;
    if (up_to_10_percent) {
      drop.radius_ = ofRandom(5, 30);
      drop.speed_ = drop.radius_ / 5.f;
      drop.alpha_ = 5;
    } else {
      drop.radius_ = ofRandom(5, 10);
      drop.speed_ = ofRandom(.1f, 2.f);
      drop.alpha_ = 10;
    }

    return drop;
  });
}

//--------------------------------------------------------------
void ofApp::update() {
  // Update the active drops, so that they continue falling down the canvas with
  // a bit of random noise on the motion to simulate its natural stroke.
  for (auto& drop : drops_) {
    if (drop.active_) {
      const ofVec2f next_step = soo::motion::UniformLinear(
          drop.position_, drop.direction_, drop.speed_);
      drop.position_ = next_step + ofRandom(-1, 1) * ofNoise(drop.position_);

      // Deactivate the drop if it reached the end of the canvas
      bool outside = drop.position_.y /*- drop.radius_*/ > ofGetHeight();
      if (outside) {
        drop.active_ = false;
      }
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  // Draw each drop with the color of the correspondent pixel on the image
  for (const auto& drop : drops_) {
    if (drop.active_) {
      ofColor color{image_.getColor(drop.position_.x, drop.position_.y)};
      drop.draw(color);
    }
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
