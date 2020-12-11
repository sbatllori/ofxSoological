#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetFrameRate(30);
  ofSetWindowShape(kWidth_, kHeight_);

  // Setup the video grabber
  video_grabber_.setDeviceID(1);
  video_grabber_.setup(kWidth_, kHeight_);

  // Load the shaders
  //  shader_.load("shaders/shader");
}

//--------------------------------------------------------------
void ofApp::update() {
  shader_.load("shaders/shader");

  // soo::SaveFrame(ofGetFrameNum());
  video_grabber_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
  shader_.begin();
  {
    shader_.setUniformTexture("webcam", video_grabber_.getTexture(), 0);
    shader_.setUniform2i("resolution", kWidth_, kHeight_);
    shader_.setUniform1f("time", ofGetElapsedTimef());
    video_grabber_.draw(0, 0);
  }
  shader_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
