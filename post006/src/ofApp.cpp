#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofSetFrameRate(30);
  ofSetBackgroundColor(255);
  ofSetColor(0);
  ofSetLineWidth(1.5);

  curve_ = soo::DragonCurve(kRotationAngle_);
  curve_.GenerateRecursive(kIterations_);
}
//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() { curve_.draw(); }

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
