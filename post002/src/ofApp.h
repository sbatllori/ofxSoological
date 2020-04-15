#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

// TODO(refactor): move this to soolibs if similar structures are needed
namespace soo
{
struct Properties
{};

struct Line
{
    ofPath path;
    Particle<Properties> origin;
    float stepLen;
    float angle;
    int sign = 1;
    bool done = false;

    Line() = default;
};

} // namespace soo

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    // Frames Exporter
    soo::FramesExporter framesExporter;

    // Character
    const uint32_t character = '2';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;

    // Character shape
    std::shared_ptr<ofPath> path;
    ofPolyline bottom, end;

    // Lines
    std::vector<soo::Line> lines;

    // Kidline
    soo::Line kidLine;
    bool renderKidLine = false;
};
