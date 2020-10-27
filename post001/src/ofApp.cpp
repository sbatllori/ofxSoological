#include "ofApp.h"
#include "soo_export.h"
#include "soo_inside.h"
#include "soo_motion.h"
#include "soo_vectors.h"

void ofApp::setup() {
  // Setup constant canvas parameters
  ofSetFrameRate(30);
  ofBackground(0);
  ofSetCircleResolution(72);

  // Define main circle
  main_circle_.radius_ = 400;
  main_circle_.center_ = ofVec2f{ofGetWidth() / 2.f, ofGetHeight() / 2.f};

  // Define particles
  constexpr unsigned long kNumParticles = 1000;
  particles_.reserve(kNumParticles);

  std::generate_n(std::back_inserter(particles_), kNumParticles, [this]() {
    Particle particle;

    // Initiate the particle in a square inside the main circle
    const float kInBoundary = 0.5f * main_circle_.radius_;
    particle.center_.x =
        main_circle_.center_.x + ofRandom(-kInBoundary, kInBoundary);
    particle.center_.y =
        main_circle_.center_.y + ofRandom(-kInBoundary, kInBoundary);

    // Assign a random direction to it
    particle.direction_ = soo::vectors::GetRandomUnitVec2();

    // Assign a random color from the color palette to it
    const auto color_idx =
        static_cast<unsigned long>(ofRandom(kColorPalette_.size()));
    particle.color_.setHex(kColorPalette_[color_idx]);

    return particle;
  });
}

void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());

  // Constraint the particles to be inside the main circle. If the next step is
  // going to make a particle cross the border, then change its direction so
  // that it moves to the inside
  for (auto& particle : particles_) {
    auto next_step = soo::motion::UniformLinear(
        particle.center_, particle.direction_, particle.speed_);

    const bool next_step_inside =
        soo::inside::InCircle(next_step, main_circle_.center_,
                              main_circle_.radius_ - particle.radius_);

    if (!next_step_inside) {
      // Change the direction if the particle is about to cross the border
      particle.direction_.rotate(ofRandom(160, 200));

      next_step = soo::motion::UniformLinear(
          particle.center_, particle.direction_, particle.speed_);
    }

    // Move the particle
    particle.center_ = next_step;
  }
}

void ofApp::draw() {
  // Draw the main circle
  ofNoFill();
  ofSetColor(200);
  ofSetLineWidth(2);
  ofDrawCircle(main_circle_.center_, main_circle_.radius_);

  // Draw the particles
  for (auto& particle : particles_) {
    if (kDrawColors_) {
      // Draw colors
      ofFill();
      ofSetColor(particle.color_);
      ofDrawCircle(particle.center_, particle.radius_);
    }

    if (kDrawGeometry_) {
      // Draw geometry
      //      ofFill();
      //      ofSetLineWidth(0.5);
      //      ofSetColor(0, 0, 0, 150);
      //      ofDrawCircle(particle.center_, particle.radius_);

      ofNoFill();
      ofSetColor(255, 0, 0);
      ofDrawCircle(particle.center_, particle.radius_);

      const ofVec3f start{particle.center_.x, particle.center_.y, 0};
      const ofVec3f direction{particle.direction_.x, particle.direction_.y, 0};
      const ofVec3f end = start + (1.15f * particle.radius_) * direction;
      ofDrawArrow(start, end);
    }
  }
}
