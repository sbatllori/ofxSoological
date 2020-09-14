#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Canvas settings
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);

    // Background settings
    bgX = 0;
    bgColor = myPink;

    // Character settings
    ofTrueTypeFont::setGlobalDpi(72);
    font.load(fontName, 650, true, true);
    fontColor = ofColor::white;

    deg = 0;
    rotate = true;
}

//--------------------------------------------------------------
void
ofApp::update()
{
    bgX += 5;
    if(bgX == ofGetWidth())
    {
        bgX = 0;
        switchBgColor();
    }

    if(rotate)
        deg++;

    if(ofRandom(100) < 5)
        switchBgColor();
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    auto w = ofGetWidth();
    auto h = ofGetHeight();

    ofFill();
    ofSetColor(bgColor);
    ofColor picoColor, tresColor;

    // Draw the background
    if(bgX < w / 2)
    {
        switchBgColor();
        ofDrawRectangle(0, 0, w / 2, h);
        (bgColor == myBlue) ? picoColor = ofColor::white : picoColor = ofColor::black;

        switchBgColor();
        ofDrawRectangle(w / 2, 0, w / 2, h);
        (bgColor == myBlue) ? tresColor = ofColor::white : tresColor = ofColor::black;

        ofDrawRectangle(0, 0, bgX, h);
    }
    else
    {
        ofDrawRectangle(0, 0, w / 2, h);
        ofDrawRectangle(w / 2, 0, w / 2, h);
        (bgColor == myBlue) ? picoColor = ofColor::white : picoColor = ofColor::black;
        (bgColor == myBlue) ? tresColor = ofColor::white : tresColor = ofColor::black;

        switchBgColor();
        ofDrawRectangle(w / 2, 0, bgX - w / 2, h);
        switchBgColor();
    }

    // Draw the characters
    int d = 80;
    ofPushMatrix();
    {
        ofRectangle bbox = font.getStringBoundingBox("<", 0, 0);
        ofTranslate(w / 2 - bbox.width / 2 - d, h / 2);
        ofRotateZDeg(deg);

        ofSetColor(picoColor);
        font.drawString("<", -bbox.width / 2, bbox.height / 2);
    }
    ofPopMatrix();

    ofPushMatrix();
    {
        ofRectangle bbox = font.getStringBoundingBox("3", 0, 0);
        ofTranslate(w / 2 + d, h / 2 + bbox.height / 2);

        ofSetColor(tresColor);
        font.drawString("3", 0, 0);
    }
    ofPopMatrix();

    //    ofDrawLine(0, h / 2, w, h / 2);
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

    if(key == 'r')
    {
        rotate = !rotate;
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
