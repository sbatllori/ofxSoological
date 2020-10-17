#pragma once

#include "ofMain.h"

namespace soo {
template <class Properties>
class Particle {
 public:
  Particle(const ofVec2f& position) : position_(position) {}
  Particle(const ofVec2f& position, ofVec2f& direction)
      : position_(position), direction_(direction.normalize()) {}

  void SetRandomDirection() {
    direction_ = ofVec2f(ofRandom(-1.f, 1.f), ofRandom(-1.f, 1.f)).normalize();
  }

  const ofVec2f& position() const { return position_; }
  const ofVec2f& direction() const { return direction_; }
  const Properties& properties() const { return properties(); }

 private:
  ofVec2f position_;
  ofVec2f direction_;
  Properties properties_;
};
}  // namespace soo
