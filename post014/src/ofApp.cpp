#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofSetFrameRate(30);
  ofSetCircleResolution(72);
  ofSetBackgroundAuto(false);

  // Define the grid
  //
  // The grid is defined by the number of cells per axis, an external margin
  // and an internal margin. It is symmetric, meaning that it has the same
  // amount of rows than of columns. The external margin is defined as the
  // distance between the grid and the screen borders. The internal margin is
  // defined as the horizontal and vertical spacing between the cells.
  // Therefore, in order to compute the size of the cells, we need to substract
  // the external marging twice, and the internal margin once per each cell but
  // the last one.
  const float total_space = ofGetWidth();  // width = height
  const float external_space = 2.f * grid_.kExternalMargin_;
  const float internal_space =
      (grid_.kNCellsPerAxe_ - 1) * grid_.kInternalMargin_;
  const float bbox_edge_length =
      (total_space - external_space - internal_space) / grid_.kNCellsPerAxe_;

  for (int i{0}; i < grid_.kNCellsPerAxe_; i++) {
    for (int j{0}; j < grid_.kNCellsPerAxe_; j++) {
      ofVec2f bbox_top_left_corner{
          i * (bbox_edge_length + grid_.kInternalMargin_),
          j * (bbox_edge_length + grid_.kInternalMargin_)};

      soo::Dandelion dandelion(bbox_top_left_corner, bbox_edge_length);
      grid_.dandelions_.push_back(dandelion);
    }
  }

  // Define black and white noise covering the whole screen
  const ofRectangle noise_bbox = ofRectangle(0, 0, ofGetWidth(), ofGetHeight());

  soo::GenerateNoiseParams noise_params;
  noise_params.min_radius(.01f).max_radius(.5f).min_alpha(10);  // common params

  black_noise_ = soo::noise::Rectangle(
      noise_bbox,
      noise_params.amount(kBlackNoisePercent_ * ofGetWidth() * ofGetHeight())
          .max_alpha(50)
          .color(ofColor::black));

  white_noise_ = soo::noise::Rectangle(
      noise_bbox,
      noise_params.amount(kWhiteNoisePercent_ * ofGetWidth() * ofGetHeight())
          .max_alpha(100)
          .color(ofColor::white));
}

//--------------------------------------------------------------
void ofApp::update() {}

//--------------------------------------------------------------
void ofApp::draw() {
  // Optimization: draw the scene only once since it is static
  if (ofGetFrameNum() == 10) {
    ofBackground(ofColor::white);

    // Draw the dandelion grid centered on the canvas
    ofPushMatrix();
    {
      ofTranslate(ofVec2f(grid_.kExternalMargin_));
      grid_.draw();
    }
    ofPopMatrix();

    // Draw the noise on top
    ofFill();
    white_noise_.draw();
    black_noise_.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
}
