#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void run_unit_tests();
  void setup() {
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofSetColor(0);
  }
  void draw();

 private:
  void test_Particle_Constructor_position();
  void test_Particle_Constructor_position_direction();
  void test_Particle_SetRandomDirection();

  void test_DeformedLayeredCircle_Constructor();
  void draw_DeformedLayeredCircle(bool run);

  void test_TriangleVertices_Generate_from_vertices();
  void test_TriangleVertices_Generate_from_edge_lengths();
  void test_Triangle_Constructor();
  void draw_Triangle(bool run);
};
