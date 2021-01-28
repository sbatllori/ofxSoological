#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofBackground(255);
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Define random angles
  constexpr unsigned long kNumParticles = 1000;
  particles_.reserve(kNumParticles);
  std::generate_n(std::back_inserter(particles_), kNumParticles,
                  []() { return ofRandomWidth(); });
}

//--------------------------------------------------------------
void ofApp::update() {
  for (auto& p : particles_) {
    p++;
    p = p % ofGetWidth();
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofBackground(255);

  for (const auto& p : particles_) {
    float x = p;
    float y = ofMap(sin(ofDegToRad(p)), -1, 1, 300, ofGetHeight() - 300);

    ofSetColor(0);
    ofNoFill();
    ofDrawCircle(x, y, 5);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
