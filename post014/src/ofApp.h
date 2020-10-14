#pragma once

#include "ofMain.h"
#include "sooDandelion.h"
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
    // Dandelion Grid
    constexpr static int kExternalMargin = 200;
    constexpr static int kInternalMargin = 50;
    constexpr static int kNCellsPerAxe = 1;
    constexpr static int kDifferentDandelionIdx = -1;
    bool light_mode_ = true;
    std::vector<soo::Dandelion> dandelion_list_;

    // General Noise
    constexpr static float kBlackNoiseAmount = 0.7f;
    constexpr static float kWhiteNoiseAmount = 0.3f;
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
