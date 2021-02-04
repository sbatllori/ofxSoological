#include "ofApp.h"
#include "soo_color_palettes.h"
#include "soo_export.h"

void ofApp::GenerateRandomBoxeSizes() {
  box_sizes_.clear();

  top_outline_29_ = top_outline_29_.getResampledBySpacing(10);
  const auto num_boxes = top_outline_29_.getVertices().size();
  box_sizes_.reserve(num_boxes);
  std::generate_n(std::back_inserter(box_sizes_), num_boxes, []() {
    return ofVec3f{ofRandom(20, 50), ofRandom(20, 100), ofRandom(20, 50)};
  });
}

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup canvas
  ofSetFrameRate(30);
  ofSetCircleResolution(72);
  //  ofBackground(237);
  ofBackground(255);

  // Define the top outline of the 29
  // - Load the font and the number outlines
  // - Translate the number positions so that they draw a 29
  // - Get only the vertices that define the top part of the outline
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

  // Random box sizes
  GenerateRandomBoxeSizes();

  // Lights
  {
    ofLight light;
    light.setPosition({500, -100, -100});
    light.setDiffuseColor(ofColor::blanchedAlmond);
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setPosition({-500, ofGetHeight() / 2, -150});
    light.setDiffuseColor(ofColor::blanchedAlmond);
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setPosition({ofGetWidth(), -200, -100});
    light.setDiffuseColor(ofColor::blanchedAlmond);
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setPosition({0.6f * ofGetWidth(), ofGetHeight(), -150});
    light.setDiffuseColor(ofColor::blanchedAlmond);
    lights_.push_back(light);
  }
  {
    ofLight light;
    light.setPosition({ofGetWidth() + 500, ofGetHeight() / 2, -100});
    light.setDiffuseColor(ofColor::blanchedAlmond);
    lights_.push_back(light);
  }
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  if (ofGetMousePressed(OF_MOUSE_BUTTON_LEFT)) {
    GenerateRandomBoxeSizes();
  }

  for (auto& light : lights_) light.enable();

  const ofRectangle bbox = top_outline_29_.getBoundingBox();
  const float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2) - 10;
  const float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2) - 50;

  ofPushMatrix();
  ofTranslate(x, y);
  {
    soo::colors::Palette palette{soo::colors::procreate_flourish};
    ofColor color;

    for (int i{0}; i < box_sizes_.size(); i++) {
      auto v = top_outline_29_.getVertices()[i];
      const float w = box_sizes_[i].x;
      const float h = box_sizes_[i].y;
      const float d = box_sizes_[i].z;

      color.setHex(palette[static_cast<int>(h) % palette.size()]);
      ofSetColor(color);
      v.y += .5f * h;
      ofDrawBox(v, w, h, d);
    }
  }
  ofPopMatrix();

  for (auto& light : lights_) light.disable();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
