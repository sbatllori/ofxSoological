#include "ofApp.h"
#include "ofMain.h"

//========================================================================
int
main()
{
    int dim = 1080;
    ofSetupOpenGL(dim, dim, OF_WINDOW); // <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp(new ofApp());
}
