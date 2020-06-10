#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

struct BrushProperties
{
    int size;
    int alpha;
    float speed;
    bool active;
};

using Brush = soo::Particle<BrushProperties>;
using Brushes = std::vector<Brush>;

class ofApp : public ofBaseApp
{
public:
    int w, h;
    string imagePath = "MaddalenaDoni.jpg";
    ofImage image;
    Brushes brushes;

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
