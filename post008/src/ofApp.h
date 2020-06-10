#pragma once

#include "ofMain.h"
#include "sooParticle.h"

struct BrushProperties
{
    int size;
    int alpha;
    float speed;
    bool active;
};

class ofApp : public ofBaseApp
{
public:
    int w, h;
    string imagePath = "MaddalenaDoni.jpg";
    ofImage image;
    std::vector<soo::Particle<BrushProperties>> brushes;

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
