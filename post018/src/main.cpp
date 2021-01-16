#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int main() {
  constexpr int kDim = 1080;

  ofGLWindowSettings settings;
  settings.setSize(kDim, kDim);
  settings.setGLVersion(3, 2);
  ofCreateWindow(settings);
  ofRunApp(new ofApp());
}
