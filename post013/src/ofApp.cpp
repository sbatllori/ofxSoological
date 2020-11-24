#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Canvas settings
  ofBackground(255);
  ofSetFrameRate(30);
  ofSetCircleResolution(72);

  // Background settings
  // - The vertical moving border starts in the left side of the canvas
  // - The initial color for the background is pink, i.e. blue will start
  // covering the left side while the vertical border moves forward
  bg_vertical_ = 0;
  bg_color_ = pink_;

  // Character settings
  // - Load the font
  // - Init the character rotation
  ofTrueTypeFont::setGlobalDpi(72);
  font_.load(font_name_, 650, true, true);
  rotate_character_ = true;
  rotation_angle_deg_ = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
  //  soo::SaveFrame(ofGetFrameNum());

  // Update the scene:
  // - The vertical border moves forward until it reaches the end of the canvas.
  // Then, it starts moving again from the left side of the canvas.
  // - Increase the rotation angle if the rotation is activated
  // - Switch the background color in the following situations:
  //    - Every time the moving border is resarted
  //    - Randomly up to 5% of the times
  const bool end_reached = bg_vertical_ >= ofGetWidth();
  const bool up_to_5_percent = ofRandom(100) < 5;

  bg_vertical_ = end_reached ? 0 : bg_vertical_ + 5;
  if (rotate_character_) rotation_angle_deg_++;
  if (end_reached || up_to_5_percent) SwitchBgColor();
}

//--------------------------------------------------------------
void ofApp::draw() {
  const int w = ofGetWidth();
  const int h = ofGetHeight();

  ofColor pico_color;
  ofColor tres_color;

  ofFill();
  ofSetColor(bg_color_);

  // Draw the background
  // - The background color is switched so that the canvas is divided in two
  // halfs, and the moving border defines what portion of each half belongs to
  // the background color
  // - The color of the characters also change according to the background color
  // changes
  if (bg_vertical_ < w / 2) {
    // ==> The moving border is on the first half of the canvas

    // Rectangle covering the first half of the screen
    SwitchBgColor();
    ofDrawRectangle(0, 0, w / 2, h);
    pico_color = GetFontColor();

    // Rectangle covering the second half of the screen
    SwitchBgColor();
    ofDrawRectangle(w / 2, 0, w / 2, h);
    tres_color = GetFontColor();

    // Moving rectangle on the first half of the screen
    ofDrawRectangle(0, 0, bg_vertical_, h);

  } else {
    // ==> The moving border is on the second half of the canvas

    // Rectangle covering the full screen
    ofDrawRectangle(0, 0, w, h);
    pico_color = GetFontColor();
    tres_color = GetFontColor();

    // Moving rectangle on the second half of the screen
    SwitchBgColor();
    ofDrawRectangle(w / 2, 0, bg_vertical_ - w / 2, h);
    SwitchBgColor();
  }

  // Draw the characters
  // - Each character is centered vertically in a different half of the screen
  // - The "pico" caracter rotates, while the "tres" character remains static
  const int distance_between_chars = 90;

  ofPushMatrix();
  {
    const ofRectangle bbox = font_.getStringBoundingBox("<", 0, 0);
    ofTranslate((w - bbox.width) / 2 - distance_between_chars, h / 2);
    ofRotateZDeg(rotation_angle_deg_);

    ofSetColor(pico_color);
    font_.drawString("<", -bbox.width / 2, bbox.height / 2);
  }
  ofPopMatrix();

  ofPushMatrix();
  {
    const ofRectangle bbox = font_.getStringBoundingBox("3", 0, 0);
    ofTranslate(w / 2 + distance_between_chars, (h + bbox.height) / 2);

    ofSetColor(tres_color);
    font_.drawString("3", 0, 0);
  }
  ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
  if (key == 'r') {
    rotate_character_ = !rotate_character_;
  }
}
