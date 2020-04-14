#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

namespace soo
{
struct Properties
{
    ofColor color;
    float radius = 10.f; // constant radius for particles
    float speed = 3.f; // constant speed for particles
};
} // namespace soo

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    soo::FramesExporter framesExporter;

    // Main circle
    soo::Particle<soo::Properties> circle;

    // Particles
    std::vector<soo::Particle<soo::Properties>> particles;
};
