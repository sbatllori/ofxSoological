#include "ofApp.h"
#include "soo_export.h"

//--------------------------------------------------------------
void ofApp::setup() {
  // Setup the background
  // - Load the background image
  // - Define a plane where to project the background image
  // - Resize the canvas to the fit the background image dimensions
  bg_image_.load(bg_image_path_);
  bg_plane_.set(bg_image_.getWidth(), bg_image_.getHeight(), 10, 10);
  bg_plane_.mapTexCoords(0, 0, bg_image_.getWidth(), bg_image_.getHeight());
  ofSetWindowShape(static_cast<int>(bg_image_.getWidth()),
                   static_cast<int>(bg_image_.getHeight()));
  // Setup the 3D scene
  // - Load the same mesh twice
  // - Initialize the mesh rotation
  // - Setup the camera pointing to the meshes
  left_mesh_.load(mesh_path_);
  right_mesh_.load(mesh_path_);
  rotate_mesh_ = true;
  camera_.setTarget({0, 0, 0});
  camera_.setDistance(8.35f);

  // Load the shaders
  bg_shader_.load("shaders/background_image");
  plastic_shader_.load("shaders/pierrextardif_plastic");
}

//--------------------------------------------------------------
void ofApp::update() { rotation_speed_ = rotate_mesh_ ? 0.03f : 0.f; }

//--------------------------------------------------------------
void ofApp::draw() {
  // Background shader
  //
  // Description:
  // The shader decreases the brightness of the background image in the cases
  // where the pixel color is too bright.
  //
  // Steps:
  // - Bind the background image as a texture
  // - Transform the plane vertices so that it is centered on the screen
  bg_image_.getTexture().bind();
  bg_shader_.begin();
  {
    bg_shader_.setUniform1f("height", ofGetHeight());
    ofPushMatrix();
    {
      ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
      bg_plane_.draw();
    }
    ofPopMatrix();
  }
  bg_shader_.end();
  bg_image_.getTexture().unbind();

  // Plastinc shader
  //
  // Description:
  // The shader projects a colored plastic texture on top of the
  // mesh surfaces. This shader is originally defined by Pierre Tardif.
  //
  // Steps:
  // - Transform the meshes so that they are side by side and with opposite
  // rotation directions
  // - Send the mesh geometry to the shaders
  ofEnableDepthTest();
  plastic_shader_.begin();
  {
    plastic_shader_.setUniform2f("u_resImg", ofGetWidth(), ofGetHeight());
    plastic_shader_.setUniform1f("u_time", 5 * ofGetElapsedTimef());
    plastic_shader_.setUniform2f("u_offset", glm::vec2(0, 0));

    camera_.begin();
    {
      ofPushMatrix();
      {
        ofTranslate({-2, 0});
        ofRotateYDeg(-rotation_speed_ * ofGetElapsedTimeMillis());
        ofScale(1.f, 1.3f);
        left_mesh_.draw();
      }
      ofPopMatrix();
      ofPushMatrix();
      {
        ofTranslate({2, 0});
        ofRotateYDeg(rotation_speed_ * ofGetElapsedTimeMillis());
        ofScale(1.f, 1.3f);
        right_mesh_.draw();
      }
      ofPopMatrix();
    }
    camera_.end();
  }
  plastic_shader_.end();
  ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
  if (key == 's') {
    soo::SaveFrame();
  }
  if (key == 'r') {
    rotate_mesh_ = !rotate_mesh_;
  }
}
