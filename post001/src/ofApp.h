#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    soo::FramesExporterPtr framesExporter;

    // Main circle
    soo::Particle circle;

    // Particles
    std::vector<soo::Particle> particles;
};
