#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  gui_.setup();
  gui_.add(frame_rate_.setup("fps", 2000, 0, 2000));
  gui_.add(radius_1_.setup("radius 1", 200, 0, 500));
  gui_.add(radius_2_.setup("radius 2", 200, 0, 500));
  gui_.add(angle_0_.setup("angle 0", 1, 1, 360));
  gui_.add(angle_1_.setup("angle 1", 252.3, 1, 360));
  gui_.add(width_.setup("width", 2, 1, 8));
  gui_.add(transparency_.setup("transparency", 10, 0, 255));

  ofSetBackgroundAuto(false);
  ofBackground(255);

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
  gui_.draw();

  ofPushMatrix();
  ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
  {
    ofSetColor(0, transparency_);
    ofSetLineWidth(width_);
    ofDrawLine(previous_brush_position_, spirograph_.brush_position());
  }
  ofPopMatrix();

  if (ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT)) {
    ofBackground(255);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
