#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Load image
    image.load(imagePath);
    w = image.getWidth() / 6;
    h = image.getHeight() / 6;
    image.resize(w, h);

    // Canvas settings
    ofSetWindowShape(w, h);

    // Load shaders
    shader.load("shaders/shader");
}

//--------------------------------------------------------------
void
ofApp::update()
{}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofBackground(255);

    shader.begin();
    image.draw(0, 0);
    shader.end();
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
