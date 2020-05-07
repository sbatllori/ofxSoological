#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    unsigned int it = 10;
    framesExporter.setStartAndEnd(2, 3);
    framesExporter.setActive(false);

    ofSetFrameRate(30);
    ofSetBackgroundColor(255);
    ofSetColor(0);
    ofSetLineWidth(1.5);

    dragonCurve = std::make_shared<soo::DragonCurve>(5);
    dragonCurve->generateRecursive(it);
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
    dragonCurve->drawStatic();
}
