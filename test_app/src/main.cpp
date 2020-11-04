#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  ofApp* app = new ofApp();
  app->run_unit_tests();

  constexpr int kDim = 1080;
  ofSetupOpenGL(kDim, kDim, OF_WINDOW);
  ofRunApp(new ofApp());
}
