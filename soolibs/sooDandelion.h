#pragma once

#include "ofMain.h"
#include "sooParticle.h"

// TODO refactor all to google code style
namespace soo
{
struct DandelionLineProperties;
using DandelionLine = Particle<DandelionLineProperties>;
using DandelionLines = std::vector<DandelionLine>;

struct DandelionLineProperties
{
    float length;
    bool isArrow;
}; // DandelionLineProperties

class Dandelion
{
private:
    // Bounding Box
    ofRectangle bbox;
    bool showBbox;

    // Circle
    float circleRadius;
    ofVec2f circleCenter;

    // Ellipse
    ofVec2f ellipseCenter;
    ofVec2f ellipseDimensions;

    // Lines
    DandelionLines lines;

public:
    Dandelion() = default;

    void generate(ofVec2f bboxTopLeftCorner, float bboxEdgeLength);

    void drawBoundingBox();
    void drawCircle();
    void drawEllipse();
    void drawLines();
    void draw();

    void showBoundingBox();
    void hideBoundingBox();

}; // Dandelion
}; // namespace soo
