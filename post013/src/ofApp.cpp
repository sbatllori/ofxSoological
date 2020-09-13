#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Canvas settings
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofSetFrameRate(160);
    ofSetCircleResolution(72);

    bgX = 0;
    currentColor = myBlue;
}

//--------------------------------------------------------------
void
ofApp::update()
{
    bgX++;
    if(bgX == ofGetWidth())
    {
        bgX = 0;
        switchCurrentColor();
    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofFill();

    if(bgX <= ofGetWidth() / 2)
    {
        switchCurrentColor();
        ofDrawRectangle(0, 0, ofGetWidth() / 2, ofGetHeight());

        switchCurrentColor();
        ofDrawRectangle(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

        ofDrawRectangle(0, 0, bgX, ofGetHeight());
    }
    else
    {
        switchCurrentColor();
        ofDrawRectangle(ofGetWidth() / 2, 0, bgX - ofGetWidth() / 2, ofGetHeight());
        switchCurrentColor();
    }
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{}

//--------------------------------------------------------------
void
ofApp::keyReleased(int key)
{}

//--------------------------------------------------------------
void
ofApp::mouseMoved(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mouseEntered(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::mouseExited(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::windowResized(int w, int h)
{}

//--------------------------------------------------------------
void
ofApp::gotMessage(ofMessage msg)
{}

//--------------------------------------------------------------
void
ofApp::dragEvent(ofDragInfo dragInfo)
{}
