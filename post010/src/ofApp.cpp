#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Load and resize the background image
  image_.load(image_path_);
  const int image_width = static_cast<int>(image_.getWidth()) / 6;
  const int image_height = static_cast<int>(image_.getHeight()) / 6;
  image_.resize(image_width, image_height);

  // Resize the canvas to be a square fitting the shortest side of the image
  const int window_size =
      image_width > image_height ? image_height : image_width;
  ofSetWindowShape(window_size, window_size);

  // Load the shaders
  shader_.load("shaders/shader");
}

//--------------------------------------------------------------
void ofApp::update() {
  // soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(255);

  shader_.begin();
  {
    shader_.setUniform1f("time", ofGetElapsedTimef());
    shader_.setUniform1f("width", ofGetWidth());
    shader_.setUniform1f("height", ofGetHeight());
    image_.draw(0, 0);
  }
  shader_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
