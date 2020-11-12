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
  main_circle_.radius_ = 400.f;
  main_circle_.center_ = ofVec2f{ofGetWidth() / 2.f, ofGetHeight() / 2.f};

  // Define particles
  // - Initialize the particles in a square inside the main circle
  // - Assign a random direction to them
  // - Assign a random color from the color palette to them
  constexpr auto num_particles = 1000l;
  particles_.reserve(num_particles);

  const float in_circle = 0.5f * main_circle_.radius_;

  std::generate_n(
      std::back_inserter(particles_), num_particles, [this, in_circle]() {
        Particle particle;

        particle.center_ =
            main_circle_.center_ + ofVec2f{ofRandom(-in_circle, in_circle),
                                           ofRandom(-in_circle, in_circle)};

        particle.direction_ = soo::vectors::GetRandomUnitVec2();

        particle.color_.setHex(color_palette_[static_cast<unsigned long>(
            ofRandom(color_palette_.size()))]);

        return particle;
      });
}

void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());

  // Constraint the particles to be inside the main circle. If the next step is
  // going to make a particle cross the border, then change its direction to the
  // inside of the circle.
  for (auto& particle : particles_) {
    const ofVec2f next_step = soo::motion::UniformLinear(
        particle.center_, particle.direction_, particle.speed_);

    const bool next_step_inside =
        soo::inside::InCircle(next_step, main_circle_.center_,
                              main_circle_.radius_ - particle.radius_);

    next_step_inside ? particle.center_ = next_step
                     : particle.direction_.rotate(ofRandom(160, 200));
  }
}

void ofApp::draw() {
  // Draw the main circle
  ofNoFill();
  ofSetColor(200);
  ofSetLineWidth(2);
  ofDrawCircle(main_circle_.center_, main_circle_.radius_);

  // Draw the particles
  for (const auto& particle : particles_) {
    if (draw_colors_) {
      // Draw colors
      ofFill();
      ofSetColor(particle.color_);
      ofDrawCircle(particle.center_, particle.radius_);
    }

    if (draw_geometry_) {
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
