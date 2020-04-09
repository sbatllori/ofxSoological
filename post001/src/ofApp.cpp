#include "ofApp.h"

void
ofApp::setup()
{
    // Setup fragment exporter
    framesExporter = soo::FramesExporterPtr(new soo::FramesExporter(25));
    framesExporter->setActive(false);

    // Setup constant canvas parameters
    ofSetFrameRate(30);
    ofBackground(0);
    ofSetCircleResolution(72);

    // Define main circle
    circle.radius = 400;
    circle.centre = ofVec2f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2);

    // Define particles
    auto numParticles = 1000;
    particles.resize(numParticles);

    auto particleRadius = 10;
    auto particleSpeed = 3;
    std::vector<int> colorPalette{0x8DF4A4, 0x67E4AA, 0x72D6BF, 0x7EC6CC, 0x86B3D3, 0x849DD6, 0x7D87D9, 0x7C74DA,
                                  0x8067D8, 0x6D4FD8, 0xA1F798, 0xA0E792, 0xC3D59F, 0xDAC0A7, 0xE2A9AF, 0xE090B9,
                                  0xD976C2, 0xCE5FC8, 0xC34FCE, 0xC139CE, 0xCEF9AD, 0xC8E17B, 0xE0CB6D, 0xEDB066,
                                  0xF5926E, 0xF4727D, 0xEC5589, 0xE14192, 0xD5379C, 0xC3268A};

    for(auto i = 0; i < numParticles; i++)
    {
        // Define new particle
        auto particle = soo::Particle();

        // Set constant data
        particle.speed = particleSpeed;
        particle.radius = particleRadius;

        // Set random center inside the circle
        float in = 0.5 * circle.radius;
        auto x = circle.centre.x + ofRandom(-in, in);
        auto y = circle.centre.y + ofRandom(-in, in);
        particle.centre = ofVec2f(x, y);

        // Set random direction
        particle.setRandomDirection();

        // Set random color from the color palette
        ofColor particleColor;
        particleColor.setHex(colorPalette[(int)ofRandom(colorPalette.size())]);
        particle.color = particleColor;

        // Add particle
        particles[i] = particle;
    }
}

void
ofApp::update()
{
    framesExporter->update(ofGetElapsedTimeMillis());

    for(auto& particle : particles)
    {
        // Constraint the particle to be inside the circle
        float nextStepDistToCenter = circle.centre.distance(particle.centre + particle.direction);
        bool out = nextStepDistToCenter >= circle.radius - particle.radius;

        if(out)
        {
            // Change the direction if the particle is about to cross the border
            particle.direction.rotate(ofRandom(160, 200));
        }

        // Move forward
        particle.centre += particle.direction;
    }
}

void
ofApp::draw()
{
    // Draw main circle
    ofNoFill();
    ofSetColor(200);
    ofSetLineWidth(2);
    ofDrawCircle(circle.centre, circle.radius);

    // Draw particles
    for(auto& particle : particles)
    {
        // Draw colors
        ofFill();
        ofSetColor(particle.color);
        ofDrawCircle(particle.centre, particle.radius);

        //        // Draw geometry
        //        //        ofFill();
        //        //        ofSetLineWidth(0.5);
        //        //        ofSetColor(0, 0, 0, 150);
        //        //        ofDrawCircle(particle.centre, particle.radius);

        //        ofNoFill();
        //        ofSetColor(255, 0, 0);
        //        ofDrawCircle(particle.centre, particle.radius);

        //        glm::vec3 start(particle.centre.x, particle.centre.y, 0);
        //        glm::vec3 d(particle.direction.x, particle.direction.y, 0);
        //        ofDrawArrow(start, start + 0.5 * particle.radius * d);
    }
}
