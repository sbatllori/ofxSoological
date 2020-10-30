#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  constexpr int dim = 1080;
  ofSetupOpenGL(dim, dim, OF_WINDOW);
  ofRunApp(new ofApp());
}
