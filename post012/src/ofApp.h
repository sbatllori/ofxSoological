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
};
} // namespace soo

using Particle = soo::Particle<soo::Properties>;

class ofApp : public ofBaseApp
{
public:
    // Images
    string imagePath = "012_background.jpg", maskPath = "012_mask.jpg";
    ofImage background, mask;

    // Particles
    ofRectangle maskBbox;
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
    /**
     * @brief Initializes a new particle and adds it to the list of particles.
     *
     * The particles are initialized inside the loaded mask, with the pixel color of the loaded background image in
     * that initial position, and with a vertical up direction with a bit of noise so that they move to the top of
     * the screen.
     */
    void addParticle();

    /**
     * @brief Updates the position of a given particle.
     * @param particle Particle& particle to update
     */
    void updateParticle(Particle& particle);
};
