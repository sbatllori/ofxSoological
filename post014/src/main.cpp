#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  constexpr int kDim = 1080;
  ofSetupOpenGL(kDim, kDim, OF_WINDOW);
  ofRunApp(new ofApp());
}
