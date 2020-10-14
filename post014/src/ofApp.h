#pragma once

#include "ofMain.h"
#include "sooDandelion.h"
#include "sooFramesExporter.h"
#include "sooParticle.h"

namespace soo
{
struct NoiseProperties
{
    float radius;
    float alpha;
};
} // namespace soo

using NoiseParticle = soo::Particle<soo::NoiseProperties>;

class ofApp : public ofBaseApp
{
private:
    // Frames Exporter
    soo::FramesExporter framesExporter;

    // Dandelion Grid
    const int kExternalMargin = 25;
    const int kNCellsPerAxe = 4;
    const int kDifferentDandelionIdx = 6;
    std::vector<soo::Dandelion> dandelion_list_;

    // General Noise
    const float kBlackNoiseAmount = 0.7f;
    const float kWhiteNoiseAmount = 0.3f;
    std::vector<NoiseParticle> black_noise_;
    std::vector<NoiseParticle> white_noise_;

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
