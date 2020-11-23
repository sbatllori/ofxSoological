#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetBackgroundAuto(false);
  ofSetFrameRate(600);
  ofBackground(255);
  ofSetLineWidth(2);

  spirograph_.AddNode({0, 0, 0}, 1.1f);
  spirograph_.AddNode({200, 0, 0}, 5, true);
  spirograph_.AddNode({150, 0, 0}, 0, true);
}

//--------------------------------------------------------------
void ofApp::update() {
  previous_brush_position_ = spirograph_.brush_position();

  std::for_each(spirograph_.nodes_mutable().begin(),
                --spirograph_.nodes_mutable().end(),
                [](auto& node) { node->RotateZ(); });
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    ofSetColor(0);
    ofDrawLine(previous_brush_position_, spirograph_.brush_position());
  }
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
