#include "ofApp.h"
#include "soo_export.h"
#include "soo_motion.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofSetBackgroundAuto(false);
  ofBackground(255);
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Load the images and define the bounding box for the mask
  bg_image_.load(kImagePath_);
  mask_.load(kMaskPath_);
  mask_bbox_.set(100, 600, ofGetWidth() - 200, 380);

  // Define the particles
  constexpr int kNumParticles = 500;
  particles_.reserve(kNumParticles);

  std::generate_n(std::back_inserter(particles_), kNumParticles, [this]() {
    // A particle is initialized as follows:
    // - It is located inside the mask
    // - Its direction points up with a bit of horizontal noise
    // - Its color is set to the color of the pixel in the background image
    // corresponding to the initial position of the particle
    // - All particles have the same radius and a similar random speed
    Particle particle;

    float x, y;
    bool in_mask;
    do {
      // Get random points from the interior of the mask bounding box
      x = ofRandom(mask_bbox_.x, mask_bbox_.x + mask_bbox_.width);
      y = ofRandom(mask_bbox_.y, mask_bbox_.y + mask_bbox_.height);

      // Check if the point is in the mask (white part)
      in_mask = mask_.getColor(x, y) == ofColor::white;

    } while (!in_mask);
    particle.center_ = ofVec2f{x, y};
    particle.color_ = bg_image_.getColor(x, y);
    particle.direction_ = ofVec2f{ofRandom(-.1f, .1f), -1}.getNormalized();
    particle.radius_ = 10.f;
    particle.speed_ = ofRandom(.05f, .5f);

    return particle;
  });
}

//--------------------------------------------------------------
void ofApp::update() {
  // The particles move up linearly with a bit of noise on its direction
  for (auto& particle : particles_) {
    const ofVec2f noise{ofRandom(-1, 1) * ofNoise(particle.center_),
                        ofRandom(-1, 1) * ofNoise(particle.center_)};

    //    particle.center_ -= particle.speed_ * (particle.direction_ + noise);
    particle.center_ = soo::motion::UniformLinear(
        particle.center_, particle.direction_ + noise, particle.speed_);
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (ofGetFrameNum() < 10) {
    ofSetColor(255);
    bg_image_.draw(0, 0);
  }

  for (const auto& particle : particles_) {
    particle.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
