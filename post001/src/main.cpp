#include "ofApp.h"
#include "ofMain.h"

int
main()
{
    unsigned int instaSquareDim = 1080; // 600 or 1080
    ofSetupOpenGL(instaSquareDim, instaSquareDim, OF_WINDOW);
    ofRunApp(new ofApp());
}
