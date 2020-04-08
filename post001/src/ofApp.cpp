#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    framesExporter = FramesExporterPtr(new FramesExporter(15));
    framesExporter->setActive(true);
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter->update(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    float x = 4 * ofGetElapsedTimeMillis() / 100 + 70;
    float y = ofGetHeight() / 2;

    ofSetBackgroundColor(200, 0, 0);
    ofSetCircleResolution(72);
    ofSetColor(255);

    ofDrawCircle(x, y, 50);
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
