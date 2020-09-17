#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

namespace soo
{
struct Properties
{
    float length;
    bool isArrow;
};

// TODO: Dandelion must be a new class in soolibs
struct Dandelion
{
    ofVec2f center;
    float radius;
    ofVec2f ellipseCenter;
    ofVec2f ellipseDimensions;
    std::vector<Particle<Properties>> lines;

    // TODO: line lenght shall depend on the distance to the circle
    // TODO: two lines should never overlap
    void initRandomLines(unsigned int n, unsigned int arrowsPercentage)
    {
        lines.resize(n);
        for(auto i = 0; i < n; i++)
        {
            Particle<Properties> line;

            line.position = ellipseCenter;
            line.setRandomDirection();
            line.properties.length = ofRandom(radius / 3, 5 * radius / 3);
            line.properties.isArrow = false;
            if(ofRandom(100) < arrowsPercentage)
                line.properties.isArrow = true;

            lines[i] = line;
        }
    }

    void draw()
    {
        ofBackground(ofColor::white);
        ofSetColor(ofColor::black);

        // Draw the circle
        ofNoFill();
        ofDrawCircle(center, radius);

        // Draw the ellipse
        ofPushMatrix();
        {
            float w = ellipseDimensions.x;
            float h = ellipseDimensions.y;

            ofTranslate(ellipseCenter);
            ofRotateZDeg(35.f);

            ofFill();
            ofDrawEllipse(0, 0, w, h);
        }
        ofPopMatrix();

        // Draw the lines
        for(auto& line : lines)
        {
            ofVec3f start = ofVec3f(ellipseCenter.x, ellipseCenter.y, 0.f);
            ofVec3f end = start + line.properties.length * ofVec3f(line.direction.x, line.direction.y, 0.f);

            if(line.properties.isArrow)
                ofDrawArrow(start, end, 5);

            else
                ofDrawLine(start, end);
        }
    }
};
} // namespace soo

class ofApp : public ofBaseApp
{
private:
    // Frames Exporter
    soo::FramesExporter framesExporter;

    soo::Dandelion dandelion;

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
};
