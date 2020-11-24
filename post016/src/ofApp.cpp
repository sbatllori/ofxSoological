#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  hide_gui_ = false;
  gui_.setup();
  gui_.add(frame_rate_.setup("fps", 60, 30, 2000));
  gui_.add(radius_1_.setup("radius 1", 200, 10, 500));
  gui_.add(radius_2_.setup("radius 2", 150, 10, 500));
  gui_.add(angle_0_.setup("angle 0", 1, 0, 1));
  gui_.add(angle_1_.setup("angle 1", 5, 0, 180));
  gui_.add(stroke_width_.setup("stroke", 2, 1, 8));
  gui_.add(color_.setup("color", ofColor(0), ofColor(0, 0), ofColor(255, 255)));

  ofSetBackgroundAuto(false);
  ofBackground(255);

  spirograph_.nodes_mutable().clear();
  spirograph_.AddNode({0, 0, 0}, angle_0_);
  spirograph_.AddNode({radius_1_, 0, 0}, angle_1_, true);
  spirograph_.AddNode({radius_2_, 0, 0}, 0, true);
}

//--------------------------------------------------------------
void ofApp::update() {
  previous_brush_position_ = spirograph_.brush_position();
  spirograph_.nodes_mutable()[0]->RotateZ();
  spirograph_.nodes_mutable()[1]->RotateZ();

  spirograph_.nodes_mutable()[0]->set_rotate_deg(angle_0_);
  spirograph_.nodes_mutable()[1]->set_rotate_deg(angle_1_);

  spirograph_.nodes_mutable()[1]->set_position({radius_1_, 0, 0});
  spirograph_.nodes_mutable()[2]->set_position({radius_2_, 0, 0});

  ofSetFrameRate(frame_rate_);
}

//--------------------------------------------------------------
void ofApp::draw() {
  if (!hide_gui_) {
    gui_.draw();
  }

  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    ofSetColor(color_);
    ofSetLineWidth(stroke_width_);
    ofDrawLine(previous_brush_position_, spirograph_.brush_position());
  }
  ofPopMatrix();

  if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
    ofBackground(255);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 'h') {
    hide_gui_ = !hide_gui_;
  }

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
