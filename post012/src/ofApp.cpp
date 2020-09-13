#include "ofApp.h"

void
ofApp::addParticle()
{
    auto particle = soo::Particle<soo::Properties>();

    // Set the initial position. The initial position is a point inside the mask.
    float x, y;
    bool in_mask;
    do
    {
        // Get random points from the interior of the mask bounding box
        x = ofRandom(maskBbox.x, maskBbox.x + maskBbox.width);
        y = ofRandom(maskBbox.y, maskBbox.y + maskBbox.height);

        // Check if the point is in the mask (white part)
        in_mask = mask.getColor(x, y) == ofColor::white;

    } while(!in_mask);
    particle.position = ofVec2f(x, y);

    // Set the particle color. The color is the pixel color of the background image in the initial particle's position
    particle.properties.color = background.getColor(x, y);

    // Set the particle direction. The direction points up with a bit of horizontal noise.
    particle.direction = ofVec2f(ofRandom(-0.1f, 0.1f), 1.).getNormalized();
    //    particle.direction.normalize();

    // Set the other particle properties
    particle.properties.radius = 10.f;
    particle.properties.speed = ofRandom(0.05f, 0.5f);

    // Add the particle to the list
    particles.push_back(particle);
}

void
ofApp::updateParticle(Particle& particle)
{
    // Move up with a bit of noise
    ofVec2f noise;
    noise.x = ofRandom(-1, 1) * ofNoise(particle.position);
    noise.y = ofRandom(-1, 1) * ofNoise(particle.position);

    particle.position -= particle.properties.speed * (particle.direction + noise);
}

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(2000);
    framesExporter.setActive(false);

    // Canvas settings
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);

    // Load images and define the bounding box for the mask
    background.load(imagePath);
    mask.load(maskPath);
    maskBbox.set(100, 600, ofGetWidth() - 200, 380);

    // Add particles
    numParticles = 500;
    particles.resize(numParticles);
    for(unsigned long i = 0; i < numParticles; i++)
        addParticle();
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    for(auto& particle : particles)
        updateParticle(particle);
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    if(ofGetFrameNum() < 10)
    {
        ofSetColor(255);
        background.draw(0, 0);
    }

    for(auto& particle : particles)
    {
        ofNoFill();
        ofSetColor(particle.properties.color, 10);
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
