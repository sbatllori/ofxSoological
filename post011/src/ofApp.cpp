#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(700);
    framesExporter.setActive(false);

    // Background
    backgroundImage.load("DSC05554.jpg");
    auto w = backgroundImage.getWidth() / 6;
    auto h = backgroundImage.getHeight() / 6;
    backgroundImage.resize(w, h);
    ofSetWindowShape(w, h);

    // Load model
    meshL.load("one.ply");
    meshR.load("one.ply");
    rotation = 0;
    cam.setTarget({0, 0, 0});
    cam.setDistance(8);

    // Load shaders
    shader.load("shaders/shader");
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    rotation += 0.01;
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    backgroundImage.draw(0, 0);

    ofEnableDepthTest();
    shader.begin();
    //    shader.setUniform1f("time", ofGetElapsedTimef());

    cam.begin();
    ofPushMatrix();
    {
        ofTranslate({-2, 0});
        ofRotateYDeg(rotation);
        meshL.draw();
    }
    ofPopMatrix();
    ofPushMatrix();
    {
        ofTranslate({2, 0});
        ofRotateYDeg(-rotation);
        meshR.draw();
    }
    ofPopMatrix();
    cam.end();

    shader.end();
    ofDisableDepthTest();
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
