#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(700);
    framesExporter.setActive(false);

    // Setup background
    // - Load the background image
    backgroundImage.load("background.jpg");

    // - Get the image dimensions
    w = backgroundImage.getWidth();
    h = backgroundImage.getHeight();

    // - Define a plane where to project the background image
    backgroundPlane.set(w, h, 10, 10);
    backgroundPlane.mapTexCoords(0, 0, w, h);

    // - Set the window dimensions to the background image dimensions
    ofSetWindowShape(w, h);

    // Setup 3D scene
    // - Load the meshes '1'
    meshL.load("one.ply");
    meshR.load("one.ply");

    // - Initialize the rotation parameter
    meshRotation = 0;

    // - Setup the camera pointing to the meshes
    cam.setTarget({0, 0, 0});
    cam.setDistance(8.35);

    // Load shaders
    backgroundShader.load("shaders/background_image");
    plasticShader.load("shaders/pierrextardif_plastic");
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    // Update the rotation parameter to rotate the meshes
    meshRotation += 0.01;
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    // Background shader
    // - Bind the background image as a texture
    backgroundImage.getTexture().bind();
    backgroundShader.begin();

    // - Send uniform data to the shader
    backgroundShader.setUniform1f("height", h);

    // - Draw the plane
    ofPushMatrix();
    {
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
        backgroundPlane.draw();
    }
    ofPopMatrix();

    backgroundShader.end();
    backgroundImage.getTexture().unbind();

    // Plastinc shader
    ofEnableDepthTest();
    plasticShader.begin();

    // - Send uniform data to the shader
    plasticShader.setUniform2f("u_resImg", ofGetWidth(), ofGetHeight());
    plasticShader.setUniform1f("u_time", 5 * ofGetElapsedTimef());
    plasticShader.setUniform2f("u_offset", glm::vec2(0, 0));

    // - Draw the meshes
    cam.begin();
    ofPushMatrix();
    {
        ofTranslate({-2, 0});
        ofRotateYDeg(meshRotation);
        meshL.draw();
    }
    ofPopMatrix();
    ofPushMatrix();
    {
        ofTranslate({2, 0});
        ofRotateYDeg(-meshRotation);
        meshR.draw();
    }
    ofPopMatrix();
    cam.end();

    plasticShader.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{
    if(key == 's')
    {
        glReadBuffer(GL_FRONT); // HACK: only needed on windows, when using ofSetAutoBackground(false)
        ofSaveScreen("savedScreenshot_" + ofGetTimestampString() + ".png");
    }
}

//--------------------------------------------------------------
void
ofApp::keyReleased(int key)
{}

//--------------------------------------------------------------
void
ofApp::mouseMoved(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::mouseDragged(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mousePressed(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void
ofApp::mouseEntered(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::mouseExited(int x, int y)
{}

//--------------------------------------------------------------
void
ofApp::windowResized(int w, int h)
{}

//--------------------------------------------------------------
void
ofApp::gotMessage(ofMessage msg)
{}

//--------------------------------------------------------------
void
ofApp::dragEvent(ofDragInfo dragInfo)
{}
