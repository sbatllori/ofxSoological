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
    void drawTrunk();
    void drawEllipse();
    void drawLines();

    void drawBoundingBox(float x, float y);
    void drawCircle(float x, float y);
    void drawTrunk(float x, float y);
    void drawEllipse(float x, float y);
    void drawLines(float x, float y);

    void showBoundingBox();
    void hideBoundingBox();

    ofVec2f getCenter();

}; // Dandelion
}; // namespace soo
