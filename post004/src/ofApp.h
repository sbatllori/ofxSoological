#pragma once

#include "ofMain.h"
#include "sooDeformedCircle.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

struct StarProperties
{
    float radius;
};

using Star = soo::Particle<StarProperties>;
using Stars = std::vector<Star>;

using Rock = soo::DeformedCircle;
using Rocks = std::vector<Rock>;

class ofApp : public ofBaseApp
{
private:
    // Frames exporter
    soo::FramesExporter framesExporter;

    // Text
    const string text = "  CUANDO ME INSPIRÁIS TODAS\nA LA VEZ, NUNCA QUIERO ELEGIR.";
    const string fontName = "Fishfingers.ttf";
    ofTrueTypeFont font;

    // Scene
    ofPath sky;
    Stars stars;
    Rocks ground;
    Rock flyingRock, fire;

public:
    void setup();
    void update();
    void draw();
};
