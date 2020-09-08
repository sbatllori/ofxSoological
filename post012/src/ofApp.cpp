#include "ofApp.h"

void
ofApp::addParticle()
{
    // TODO
}

void
ofApp::updateParticle(Particle& particle)
{
    // TODO
}

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(700);
    framesExporter.setActive(false);

    // Load images
    background.load(imagePath);
    mask.load(maskPath);

    // Define the bounding box for the loaded mask (white part)
    bbox.set(100, 600, ofGetWidth() - 200, 380);

    // Initialize the particles
    numParticles = 50;
    particles.resize(numParticles);

    for(unsigned long i = 0; i < numParticles; i++)
    {
        auto particle = soo::Particle<soo::Properties>();

        // The initial position needs to be a point in the mask (white part)
        float x, y;
        bool in_mask;
        do
        {
            // Get random points from the interior of the mask bounding box
            x = ofRandom(bbox.x, bbox.x + bbox.width);
            y = ofRandom(bbox.y, bbox.y + bbox.height);

            // Check if the point is in the mask (white part)
            in_mask = mask.getColor(x, y) == ofColor::white;

        } while(!in_mask);
        particle.properties.origin = ofVec2f(x, y);
        particle.position = ofVec2f(x, y);

        // Set the directionto be up with a bit of noise
        particle.direction = ofVec2f(ofRandom(-0.1f, 0.1f), 1.);
        particle.direction.normalize();

        // Set the particle properties
        particle.properties.color = background.getColor(x, y);
        particle.properties.radius = 10.f;
        particle.properties.speed = ofRandom(0.05f, 0.4f);

        // Add particle
        particles[i] = particle;
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    for(auto& particle : particles)
    {
        particle.position -=
            particle.properties.speed * (particle.direction + ofRandom(-1, 1) * ofNoise(particle.position));

        if(particle.position.y <= 0.f)
        {
            particle.position = particle.properties.origin;
            particle.properties.speed = ofRandom(0.05f, 0.4f);
        }
    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofSetColor(255);
    background.draw(0, 0);

    //    ofNoFill();
    //    ofSetLineWidth(5);
    //    ofDrawRectangle(bbox);

    for(auto& particle : particles)
    {
        // Draw colors
        ofNoFill();
        ofSetColor(particle.properties.color);
        ofDrawCircle(particle.position, particle.properties.radius);
    }
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
