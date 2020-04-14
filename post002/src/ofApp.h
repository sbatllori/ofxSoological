#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

// TODO move this to soolibs
namespace soo
{
struct Properties
{};

struct Shape
{
    ofPath path;

    Shape() = default;

    Shape(ofPath& _path)
    {
        path = _path;
    }

    ofRectangle
    getBoundingBox()
    {
        return path.getOutline()[0].getBoundingBox();
    }

    std::vector<ofVec2f>
    getVertices()
    {
        std::vector<ofVec2f> vertices;
        for(auto& v : path.getOutline()[0].getVertices())
        {
            vertices.push_back(ofVec2f(v.x, v.y));
        }
        return vertices;
    }

    bool
    inside(const float x, const float y)
    {
        return path.getOutline()[0].inside(x, y);
    }

    void
    toCenter()
    {
        auto bbox = getBoundingBox();
        float x = ofGetWindowWidth() / 2 - bbox.width / 2 - 50;
        float y = ofGetWindowHeight() / 2 + bbox.height / 2;
        path.translate(ofVec2f(x, y));
    }
};

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
    soo::FramesExporterPtr framesExporter;

    // Character
    const uint32_t character = '2';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;

    // Character shape
    std::unique_ptr<soo::Shape> shape;
    ofPolyline shapeBottom, shapeEnd;

    // Lines
    std::vector<soo::Line> lines;

    // Kidline
    soo::Line kidLine;
    bool renderKidLine = false;
};
