#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp
{
private:
    int bgX;

    ofColor currentColor;
    ofColor myBlue = ofColor(163, 218, 255);
    ofColor myPink = ofColor(255, 199, 239);

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
        if(currentColor == myBlue)
            currentColor = myPink;
        else
            currentColor = myBlue;

        ofSetColor(currentColor);
    }
};
