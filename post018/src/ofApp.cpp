#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Load the shaders
  shader_.load("shaders/shader");
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  shader_.begin();
  shader_.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
  ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
  shader_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
