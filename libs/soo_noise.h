#pragma once

#include "ofMain.h"

// TODO add unit tests
namespace soo {

struct NoiseParticle {
  ofVec2f position_;
  float radius_;
  float alpha_;
  ofColor color_;
};

struct Noise {
  std::vector<NoiseParticle> particles_;

  void draw() const {
    for (const auto& particle : particles_) {
      ofSetColor({particle.color_, particle.alpha_});
      ofDrawCircle(particle.position_, particle.radius_);
    }
  }
};

struct GenerateNoiseParams {
  int amount_;
  float min_radius_;
  float max_radius_;
  float min_alpha_;
  float max_alpha_;
  ofColor color_;

  GenerateNoiseParams& amount(const int amount) {
    amount_ = amount;
    return *this;
  }

  GenerateNoiseParams& min_radius(const float min_radius) {
    min_radius_ = min_radius;
    return *this;
  }

  GenerateNoiseParams& max_radius(const float max_radius) {
    max_radius_ = max_radius;
    return *this;
  }

  GenerateNoiseParams& min_alpha(const float min_alpha) {
    min_alpha_ = min_alpha;
    return *this;
  }

  GenerateNoiseParams& max_alpha(const float max_alpha) {
    max_alpha_ = max_alpha;
    return *this;
  }

  GenerateNoiseParams& color(const ofColor& color) {
    color_ = color;
    return *this;
  }
};

namespace noise {

inline Noise Rectangle(const ofRectangle& bbox,
                       const GenerateNoiseParams& params) {
  Noise noise;
  noise.particles_.reserve(params.amount_);

  std::generate_n(
      std::back_inserter(noise.particles_), params.amount_, [&bbox, &params]() {
        NoiseParticle particle;
        particle.position_.x = ofRandom(bbox.x, bbox.x + bbox.width);
        particle.position_.y = ofRandom(bbox.y, bbox.y + bbox.height);
        particle.radius_ = ofRandom(params.min_radius_, params.max_radius_);
        particle.alpha_ = ofRandom(params.min_alpha_, params.max_alpha_);
        particle.color_ = params.color_;
        return particle;
      });

  return noise;
}
}  // namespace noise
}  // namespace soo
