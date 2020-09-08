#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

namespace soo
{
struct Properties
{
    ofColor color;
    float radius;
    float speed;
    ofVec2f origin;
};
} // namespace soo

using Particle = soo::Particle<soo::Properties>;

class ofApp : public ofBaseApp
{
public:
    // Images
    int w, h;
    string imagePath = "012_background.jpg", maskPath = "012_mask.jpg";
    ofImage background, mask;

    // Particles
    ofRectangle bbox;
    unsigned long numParticles;
    std::vector<Particle> particles;

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

private:
    void addParticle();
    void updateParticle(Particle& particle);
};
