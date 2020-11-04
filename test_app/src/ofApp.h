#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void run_unit_tests() {
    test_DeformedLayeredCircle_Constructor();
    test_TriangleVertices_Constructor_vertices();
    test_TriangleVertices_Constructor_edge_lengths();
    test_Triangle_Constructor();
    test_Motion_UniformLinear();
    test_Inside_InCircle();
  }
  void setup() {
    ofSetBackgroundAuto(false);
    ofSetCircleResolution(72);
    ofSetLineWidth(1);
    ofBackground(255);
    ofSetColor(0);
  }
  void draw() {
    if (ofGetFrameNum() == 10) {
      draw_DeformedLayeredCircle(false);
      draw_Triangle(false);
      draw_TrianglesOutBrush(true);
      draw_Dandelion(false);
      draw_Intersection_Horizontal_PolylineClosed(false);
      draw_noise_Rectagle(true);
    }

    if (kRunDrawFractals_) {
      ofSetBackgroundAuto(true);
      draw_DragonCurve(false);
      draw_LevyCCurve(false);
    }
  }

  //  void keyPressed(int key) {}

 private:
  const bool kRunDrawFractals_ = false;

  void test_DeformedLayeredCircle_Constructor();
  void test_TriangleVertices_Constructor_vertices();
  void test_TriangleVertices_Constructor_edge_lengths();
  void test_Triangle_Constructor();
  void test_Motion_UniformLinear();
  void test_Inside_InCircle();

  void draw_DeformedLayeredCircle(bool run);
  void draw_Triangle(bool run);
  void draw_TrianglesOutBrush(bool run);
  void draw_Dandelion(bool run);
  void draw_Intersection_Horizontal_PolylineClosed(bool run);
  void draw_DragonCurve(bool run);
  void draw_LevyCCurve(bool run);
  void draw_noise_Rectagle(bool run);
};
