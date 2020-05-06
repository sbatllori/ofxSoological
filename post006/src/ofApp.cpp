#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{

    ofSetFrameRate(30);
    ofSetBackgroundColor(255);
    ofSetColor(0);
    ofSetLineWidth(2);

    dragonCurve.generate(12);
}

//--------------------------------------------------------------
void
ofApp::update()
{}

//--------------------------------------------------------------
void
ofApp::draw()
{

    ofPushMatrix();
    {
        ofRectangle bbox = dragonCurve.line.getBoundingBox();
        float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2);
        float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2);
        ofTranslate(x, y);

        //        ofNoFill();
        //        ofDrawRectangle(bbox);

        dragonCurve.line.draw();
    }
    ofPopMatrix();
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
