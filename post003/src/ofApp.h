#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"

namespace soo
{
struct Cell
{
    ofVec2f origin;
    float w, h;
    ofColor color;
    ofColor finalColor = ofColor(20);
    bool isFinalColorSet = false;
};
} // namespace soo

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

    soo::FramesExporter framesExporter;

    int nRows = 9, nColumns = 9;
    std::vector<ofColor> randomColors;
    std::stack<int> unsetIndices;
    std::vector<soo::Cell> cells;
    std::vector<std::pair<int, int>> shapeIndices = {
        {2, 2}, {1, 3}, {1, 4}, {1, 5}, {2, 6}, {3, 6}, {4, 4}, {4, 5}, {5, 6}, {6, 2}, {6, 6}, {7, 3}, {7, 4}, {7, 5}};
};
