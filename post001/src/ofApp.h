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
private:
    // Frames exporter
    soo::FramesExporter framesExporter;

    // Main circle
    soo::Particle<soo::Properties> circle;

    // Particles
    std::vector<soo::Particle<soo::Properties>> particles;

    // TODO extract color palette to a separate soolib
    // Color palette
    std::vector<int> colorPalette{0x8DF4A4, 0x67E4AA, 0x72D6BF, 0x7EC6CC, 0x86B3D3, 0x849DD6, 0x7D87D9, 0x7C74DA,
                                  0x8067D8, 0x6D4FD8, 0xA1F798, 0xA0E792, 0xC3D59F, 0xDAC0A7, 0xE2A9AF, 0xE090B9,
                                  0xD976C2, 0xCE5FC8, 0xC34FCE, 0xC139CE, 0xCEF9AD, 0xC8E17B, 0xE0CB6D, 0xEDB066,
                                  0xF5926E, 0xF4727D, 0xEC5589, 0xE14192, 0xD5379C, 0xC3268A};

public:
    void setup();
    void update();
    void draw();
};
