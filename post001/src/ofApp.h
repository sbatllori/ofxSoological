#pragma once

#include "ofMain.h"
#include <iostream>
#include <memory>

namespace soo
{
class FramesExporter;
using FramesExporterPtr = std::unique_ptr<FramesExporter>;

//struct Particle;
//using ParticlePtr = std::shared_ptr<Particle>;

class FramesExporter
{
private:
    int duration;
    int epsilon = 100;
    int saveImageCounter = 0;
    bool showDoneInfo = true;
    bool active = false;

public:
    FramesExporter(int _duration)
        : duration(_duration)
    {}

    void
    setActive(bool _active)
    {
        active = _active;
    }

    void
    update(int elapsedTimeMillis)
    {
        if(active)
        {
            if(elapsedTimeMillis > epsilon && elapsedTimeMillis < 1000 * duration + epsilon)
            {
                if(saveImageCounter == 0)
                    std::cout << "[SOO INFO]\tStarting with frame exporting [" << duration << "s]\n";

                ofSaveFrame();
            }
            else
            {
                if(showDoneInfo)
                    std::cout << "[SOO INFO]\tDone with frame exporting.\n";
                showDoneInfo = false;
            }
        }
    }

private:
    void
    ofSaveFrame()
    {
        string zeroes = "00000000";
        zeroes = zeroes.substr(0, zeroes.length() - (ofToString(saveImageCounter).length()));
        string fileName = "./frames/f" + zeroes + ofToString(saveImageCounter) + ".png";
        ofSaveViewport(fileName);
        saveImageCounter++;
    }
};

struct Particle
{
    float radius;
    float speed;
    ofVec2f centre;
    ofVec2f direction;
    ofColor color;

    Particle() = default;

    void
    setRandomDirection()
    {
        float x = ofRandom(-1, 1);
        float y = ofRandom(-1, 1);
        direction = speed * (ofVec2f(x, y)).normalize();
    }
};
} // namespace soo

class ofApp : public ofBaseApp
{
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

    soo::FramesExporterPtr framesExporter;

    // Main circle
    soo::Particle circle;

    // Particles
    std::vector<soo::Particle> particles;
};
