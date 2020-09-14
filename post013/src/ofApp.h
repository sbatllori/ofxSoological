#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
private:
    // Background
    int bgX;

    ofColor currentColor;
    const ofColor myBlue = ofColor(112, 198, 255); //ofColor(163, 218, 255);
    const ofColor myPink = ofColor(255, 135, 221); //ofColor(255, 199, 239);

    // Characters
    int deg;
    bool rotate;
    ofTrueTypeFont font;
    const string fontName = "FreeSans.ttf";

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

private:
    void switchCurrentColor()
    {
        (currentColor == myBlue) ? currentColor = myPink : currentColor = myBlue;
        ofSetColor(currentColor);
    }
};
