#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(900);
    framesExporter.setActive(false);

    // Canvas settings
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);
    ofSetLineWidth(4);

    dandelion.center = ofVec2f(0, 0);
    dandelion.radius = 200;
    dandelion.ellipseCenter = ofVec2f(-30, 50);
    dandelion.ellipseDimensions = ofVec2f(130, 90);
    dandelion.initRandomLines(20, 70);
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofPushMatrix();
    {
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        dandelion.draw();
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{
    if(key == 's')
    {
        glReadBuffer(GL_FRONT); // HACK: only needed on windows, when using ofSetAutoBackground(false)
        ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
    }
}

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
