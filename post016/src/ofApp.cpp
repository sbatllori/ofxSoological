#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetBackgroundAuto(false);
  ofSetFrameRate(100);
  ofBackground(255);
  ofSetColor(0);
  ofSetLineWidth(2);

  position_ = SpirographNode({0, 0, 0});
  circle_ = SpirographNode({200, 0, 0}, position_);
  brush_ = SpirographNode({150, 0, 0}, circle_);
}

//--------------------------------------------------------------
void ofApp::update() {
  previous_brush_position_ = brush_.global_position();

  position_.RotateZ();
  circle_.RotateZ();

  if (position_.IsCicleStart()) {
    position_.set_rotate_deg(ofRandom(.1f, 1.f));
    circle_.set_rotate_deg(ofRandom(1, 5));
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  ofDrawLine(previous_brush_position_, brush_.global_position());
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
