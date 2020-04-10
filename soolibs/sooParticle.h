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

    void setRandomDirection();
};

} // namespace soo
