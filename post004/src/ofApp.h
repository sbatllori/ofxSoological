#pragma once

#include "ofMain.h"

namespace soo
{

class DeformedCircle
{
public:
    ofPath path;

    ofVec2f position;
    int numCorners;
    std::vector<float> radiusPerCorner;

    DeformedCircle() = default;

    DeformedCircle(const ofVec2f _position,
                   const int _numCorners,
                   const std::vector<float>& _radiusPerCorner,
                   const float epsilon = 0.5)
        : position(_position)
        , numCorners(_numCorners)
        , radiusPerCorner(_radiusPerCorner)
    {

        // The first two points are really close and have the same radius
        float r = radiusPerCorner[0];
        addPolarPoint(r, 0);
        addPolarPoint(r, ofDegToRad(epsilon));

        // Add the points in between
        for(int i = 1; i < numCorners; i++)
            addPolarPoint(radiusPerCorner[i], (1.f * i) / numCorners);

        // Close the path
        addPolarPoint(r, ofDegToRad(epsilon));
        addPolarPoint(r, 0);

        setDefaultPathDrawingConfig();
    }

private:
    void
    setDefaultPathDrawingConfig()
    {
        path.setFilled(true);
        path.setFillColor(ofColor(255));
        path.setStrokeColor(ofColor(0, 0, 0, 255));
        path.setStrokeWidth(2);
        path.setCurveResolution(72);
    }

    void
    addPolarPoint(const float r, const float theta)
    {
        ofVec2f p = polarToCartesian(r, theta);
        path.curveTo(p);
    }

    ofVec2f
    polarToCartesian(const float r, const float theta)
    {
        auto x = position.x + r * cos(TWO_PI * theta);
        auto y = position.y + r * sin(TWO_PI * theta);
        return ofVec2f(x, y);
    }
};
} // namespace soo

using DeformedCirclePtr = std::shared_ptr<soo::DeformedCircle>;
using Shape = std::vector<DeformedCirclePtr>;

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    std::vector<Shape> shapes;
};
