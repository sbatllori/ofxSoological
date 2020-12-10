#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetWindowShape(kWidth_, kHeight_);

  // Setup the camera
  camera_.setVerbose(false);  // TODO: check what does this mean
  camera_.setDeviceID(1);
  camera_.setup(kWidth_, kHeight_);

  // Load the shaders
  shader_.load("shaders/shader");
}

//--------------------------------------------------------------
void ofApp::update() {
  // soo::SaveFrame(ofGetFrameNum());
  camera_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  shader_.begin();
  shader_.setUniformTexture("tex0", camera_.getTexture(), 1);
  camera_.draw(0, 0);
  shader_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
