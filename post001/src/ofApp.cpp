#include "ofApp.h"

void
ofApp::setup()
{
    // Setup frames exporter
    framesExporter.setStartAndEnd(0.1f, 25);
    framesExporter.setActive(false);

    // Setup constant canvas parameters
    ofSetFrameRate(30);
    ofBackground(0);
    ofSetCircleResolution(72);

    // Define main circle
    circle.properties.radius = 400;
    circle.position = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    // Define particles
    unsigned long numParticles = 1000;
    particles.resize(numParticles);

    for(unsigned long i = 0; i < numParticles; i++)
    {
        // Define new particle
        auto particle = soo::Particle<soo::Properties>();

        // Set random center inside the circle
        float inBoundary = 0.5f * circle.properties.radius;
        auto x = circle.position.x + ofRandom(-inBoundary, inBoundary);
        auto y = circle.position.y + ofRandom(-inBoundary, inBoundary);
        particle.position = ofVec2f(x, y);

        // Set random direction
        particle.setRandomDirection(particle.properties.speed);

        // Set random color from the color palette
        ofColor particleColor;
        particleColor.setHex(colorPalette[static_cast<unsigned long>(ofRandom(colorPalette.size()))]);
        particle.properties.color = particleColor;

        // Add particle
        particles[i] = particle;
    }
}

void
ofApp::update()
{
    framesExporter.updateByTime(ofGetElapsedTimeMillis());

    for(auto& particle : particles)
    {
        // Constraint the particle to be inside the circle
        float nextStepDistToCenter = circle.position.distance(particle.position + particle.direction);
        bool out = nextStepDistToCenter >= circle.properties.radius - particle.properties.radius;

        if(out)
        {
            // Change the direction if the particle is about to cross the border
            particle.direction.rotate(ofRandom(160, 200));
        }

        // Move forward
        particle.position += particle.direction;
    }
}

void
ofApp::draw()
{
    // Draw main circle
    ofNoFill();
    ofSetColor(200);
    ofSetLineWidth(2);
    ofDrawCircle(circle.position, circle.properties.radius);

    // Draw particles
    for(auto& particle : particles)
    {
        // Draw colors
        ofFill();
        ofSetColor(particle.properties.color);
        ofDrawCircle(particle.position, particle.properties.radius);

        //        // Draw geometry
        //        //        ofFill();
        //        //        ofSetLineWidth(0.5);
        //        //        ofSetColor(0, 0, 0, 150);
        //        //        ofDrawCircle(particle.position, particle.properties.radius);

        //        ofNoFill();
        //        ofSetColor(255, 0, 0);
        //        ofDrawCircle(particle.position, particle.properties.radius);

        //        glm::vec3 start(particle.position.x, particle.position.y, 0);
        //        glm::vec3 d(particle.direction.x, particle.direction.y, 0);
        //        ofDrawArrow(start, start + 0.5 * particle.properties.radius * d);
    }
}
