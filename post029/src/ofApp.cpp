#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);
  ofBackground(255);

  // Load the numbers
  font_.load("Lato-Light.ttf", 800, true, true, true);

  auto outline_2 = font_.getCharacterAsPoints('2', true, false).getOutline()[0];
  auto outline_9 = font_.getCharacterAsPoints('9', true, false).getOutline()[0];
  outline_2.translate({0, 80});
  outline_9.translate({550, 0});

  // Vertices definining the top outline of the number 2: 74 - 0
  std::for_each(
      outline_2.getVertices().begin() + 74, outline_2.getVertices().end(),
      [this](const auto& vertex) { top_outline_29_.addVertex(vertex); });
  std::for_each(
      outline_2.getVertices().begin(), outline_2.getVertices().begin() + 1,
      [this](const auto& vertex) { top_outline_29_.addVertex(vertex); });

  // Vertices definining the top outline of the number 9: 33 - ~end
  std::for_each(
      outline_9.getVertices().begin() + 33, outline_9.getVertices().end(),
      [this](const auto& vertex) { top_outline_29_.addVertex(vertex); });

  top_outline_29_ = top_outline_29_.getResampledBySpacing(10);
}

//--------------------------------------------------------------
void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());
}

//--------------------------------------------------------------
void ofApp::draw() {
  const ofRectangle bbox = top_outline_29_.getBoundingBox();
  const float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2);
  const float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2);

  ofPushMatrix();
  ofTranslate(x, y);
  {
    ofSetColor(0);

    for (const auto& v : top_outline_29_.getVertices()) {
      ofDrawRectangle(v.x, v.y, 2, 15);
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
