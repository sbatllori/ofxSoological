#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  ofApp* app = new ofApp();
  app->run_unit_tests();

  int dim = 1080;
  ofSetupOpenGL(dim, dim, OF_WINDOW);
  ofRunApp(new ofApp());
}
