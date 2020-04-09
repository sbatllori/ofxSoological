#pragma once

#include "ofMain.h"

namespace soo
{
struct Particle
{
    float radius;
    float speed;
    ofVec2f centre;
    ofVec2f direction;
    ofColor color;

    Particle() = default;

    void
    setRandomDirection()
    {
        float x = ofRandom(-1, 1);
        float y = ofRandom(-1, 1);
        direction = speed * (ofVec2f(x, y)).normalize();
    }
};
} // namespace soo
