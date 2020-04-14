#pragma once

#include "ofMain.h"

namespace soo
{
template <class Properties>
struct Particle
{
    ofVec2f position;
    ofVec2f direction;
    Properties properties;

    Particle() = default;

    void setRandomDirection(const float _speed = 1.f)
    {
        float x = ofRandom(-1, 1);
        float y = ofRandom(-1, 1);
        direction = _speed * (ofVec2f(x, y)).normalize();
    }
};

} // namespace soo
