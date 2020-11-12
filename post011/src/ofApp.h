#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

 public:
  // Background
  const std::string bg_image_path_ = "background.jpg";
  ofImage bg_image_;
  ofPlanePrimitive bg_plane_;
  ofShader bg_shader_;

  // 3D scene
  const std::string mesh_path_ = "one.ply";
  ofMesh left_mesh_;
  ofMesh right_mesh_;
  bool rotate_mesh_;
  float rotation_speed_;
  ofEasyCam camera_;
  ofShader plastic_shader_;
};
