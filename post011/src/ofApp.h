#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"

class ofApp : public ofBaseApp
{
public:
    // Background
    float w, h;
    ofImage backgroundImage;
    ofPlanePrimitive backgroundPlane;
    ofShader backgroundShader;

    // 3D scene
    ofEasyCam cam;
    bool rotateMesh;
    float meshRotationSpeed;
    ofMesh meshL, meshR;
    ofShader plasticShader;

    // Frames Exporter
    soo::FramesExporter framesExporter;

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
};
