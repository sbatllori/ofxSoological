#pragma once

#include "ofMain.h"

namespace soo
{

struct Line
{
    ofPath path;
    std::vector<ofVec2f> intersectionPoints;
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

    // Window dimensions
    float w, h;

    // Character
    const uint32_t character = '5';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;
    ofPath characterPath;

    // Lines
    size_t numLines;
    std::vector<soo::Line> lines;
    std::vector<ofPath> bezierLines;
};
