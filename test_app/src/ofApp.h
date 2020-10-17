#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
 public:
  void run_unit_tests();

 private:
  void test_Particle_Constructor_position();
  void test_Particle_Constructor_position_direction();
  void test_Particle_SetRandomDirection();
};
