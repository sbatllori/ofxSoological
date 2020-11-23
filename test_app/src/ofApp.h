#pragma once

#include "ofMain.h"
#include "shapes/Spirograph.h"
#include "soo_export.h"

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

    setup_Spirograph();
  }
  void draw() {
    if (ofGetFrameNum() == 10) {
      draw_DeformedLayeredCircle(false);
      draw_Triangle(false);
      draw_TrianglesOutBrush(false);
      draw_Dandelion(false);
      draw_Intersection_Horizontal_ClosedPolyline(false);
      draw_Noise_Rectagle(false);
    }
    draw_Spirograph(true);

    if (run_draw_fractals) {
      ofSetBackgroundAuto(true);
      draw_DragonCurve(false);
      draw_LevyCCurve(true);
    }
  }

  void keyPressed(int key) {
    if (key == 's') {
      soo::SaveFrame();
    }
  }

 private:
  const bool run_draw_fractals = false;

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
  void draw_Intersection_Horizontal_ClosedPolyline(bool run);
  void draw_DragonCurve(bool run);
  void draw_LevyCCurve(bool run);
  void draw_Noise_Rectagle(bool run);

  soo::Spirograph spirograph;
  void setup_Spirograph();
  void draw_Spirograph(bool run);
};
