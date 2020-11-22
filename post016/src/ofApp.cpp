#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetBackgroundAuto(false);
  ofSetFrameRate(600);
  ofBackground(255);
  ofSetLineWidth(2);

  Spirograph sg01;
  sg01.nodes_.push_back(new SpirographNode({0, 0, 0}));
  sg01.nodes_.push_back(new SpirographNode({200, 0, 0}, sg01.nodes_[0]));
  sg01.nodes_.push_back(new SpirographNode({150, 0, 0}, sg01.nodes_[1]));
  sg01.nodes_[0]->set_rotate_deg(1.1f);
  sg01.nodes_[1]->set_rotate_deg(5);
  sg01.color_ = ofColor(50);
  spirographs_.push_back(sg01);
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto& spirograph : spirographs_) {
    spirograph.previous_brush_position_ = spirograph.brush_position();
    std::for_each(spirograph.nodes_.begin(), --spirograph.nodes_.end(),
                  [](auto& node) { node->RotateZ(); });
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    for (auto& spirograph : spirographs_) {
      ofSetColor(spirograph.color_);
      ofDrawLine(spirograph.previous_brush_position_,
                 spirograph.brush_position());
    }
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
