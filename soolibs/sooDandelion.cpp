#include "sooDandelion.h"

namespace soo
{

void
Dandelion::generate(ofVec2f bboxTopLeftCorner, float bboxEdgeLength)
{
    // Define the bouding box
    showBbox = true;
    bbox = ofRectangle(bboxTopLeftCorner.x, bboxTopLeftCorner.y, bboxEdgeLength, bboxEdgeLength);

    // Define the circle a bit to the left and bottom of the center of the bounding box
    circleRadius = 0.6f * bboxEdgeLength / 2.f;
    circleCenter.x = bboxTopLeftCorner.x + 0.45f * bboxEdgeLength;
    circleCenter.y = bboxTopLeftCorner.y + 0.55f * bboxEdgeLength;

    // Define the ellipse a bit to the left and bottom of the center of the circle
    ellipseCenter.x = circleCenter.x - 0.2f * circleRadius;
    ellipseCenter.y = circleCenter.y + 0.2f * circleRadius;
    ellipseDimensions.x = 0.8f * circleRadius;
    ellipseDimensions.y = 0.5f * circleRadius;

    // Define the lines
    int n = bboxEdgeLength / 5;
    lines.resize(n);
    for(auto i = 0; i < n; i++)
    {
        DandelionLine line;

        // The origin of the line is set to the center of the ellipse
        line.position = ellipseCenter;

        // Set a random direction to the line
        line.setRandomDirection();

        // Adjust the line length depending on where the direction is pointing to:
        // - 1st quadrant of the circle (+, -): longer x, longer y
        // - 2nd quadrant of the circle (-, -): shorter x, longer y
        // - 3rd quadrant of the circle (-, +): shorter x, shorter y
        // - 4rt quadrant of the circle (+, +): longer x, shorter y
        const float minFactor = 0.5f;
        float maxFactor;
        if(line.direction.y < 0)
        {
            // 1st quadrant
            if(line.direction.x >= 0)
                maxFactor = 1.7f;

            // 2nd quadrant
            else
                maxFactor = 1.25f;
        }
        else
        {
            // 3rd quadrant
            if(line.direction.x < 0)
                maxFactor = 1.1f;

            // 4rt quadrant
            else
                maxFactor = 1.25;
        }

        line.properties.length = ofRandom(minFactor, maxFactor) * circleRadius;

        // Set some lines to be arrows:
        // - up to 75% of the the longest lines
        // - up to 10% of the rest of the lines
        line.properties.isArrow = false;
        if((line.properties.length > 0.9f * maxFactor * circleRadius && ofRandom(100) < 75) || ofRandom(100) < 10)
            line.properties.isArrow = true;

        lines[i] = line;
    }
}

void
Dandelion::drawBoundingBox()
{
    if(showBbox)
        ofDrawRectangle(bbox);
}

void
Dandelion::drawCircle()
{
    ofDrawCircle(circleCenter, circleRadius);
}

void
Dandelion::drawTrunk()
{
    ofVec2f bboxBottomLeftCorner = ofVec2f(bbox.x, bbox.y + bbox.height);
    ofDrawLine(bboxBottomLeftCorner, ellipseCenter);
}

void
Dandelion::drawEllipse()
{
    ofPushMatrix();
    ofTranslate(ellipseCenter);
    ofRotateZDeg(45.f);
    ofDrawEllipse(0, 0, ellipseDimensions.x, ellipseDimensions.y);
    ofPopMatrix();
}

void
Dandelion::drawLines()
{
    for(auto& line : lines)
    {
        auto start = ofVec3f(line.position.x, line.position.y, 0.f);
        auto end = start + line.properties.length * ofVec3f(line.direction.x, line.direction.y, 0.f);

        if(line.properties.isArrow)
            ofDrawArrow(start, end, 0.04f * circleRadius);

        else
            ofDrawLine(start, end);
    }
}

void
Dandelion::drawBoundingBox(float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    drawBoundingBox();
    ofPopMatrix();
}
void
Dandelion::drawCircle(float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    drawCircle();
    ofPopMatrix();
}
void
Dandelion::drawTrunk(float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    drawTrunk();
    ofPopMatrix();
}
void
Dandelion::drawEllipse(float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    drawEllipse();
    ofPopMatrix();
}
void
Dandelion::drawLines(float x, float y)
{
    ofPushMatrix();
    ofTranslate(x, y);
    drawLines();
    ofPopMatrix();
}

void
Dandelion::showBoundingBox()
{
    showBbox = true;
}

void
Dandelion::hideBoundingBox()
{
    showBbox = false;
}

ofVec2f
Dandelion::getCenter()
{
    return circleCenter;
}

}; // namespace soo
