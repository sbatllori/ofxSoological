#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(900);
    framesExporter.setActive(false);

    // Canvas settings
    ofSetFrameRate(30);
    ofSetCircleResolution(72);
    ofSetBackgroundAuto(false);

    // Define the dandelion grid
    auto w = (ofGetWidth() - kExternalMargin) / kNCellsPerAxe;
    auto h = (ofGetHeight() - kExternalMargin) / kNCellsPerAxe;
    for(int i = 0; i < w * kNCellsPerAxe; i += w)
        for(int j = 0; j < h * kNCellsPerAxe; j += h)
        {
            soo::Dandelion dandelion;
            dandelion.generate(ofVec2f(i, j), w - kExternalMargin);
            dandelion_list_.push_back(dandelion);
        }

    // Define noise particles
    int n = ofGetWidth() * ofGetHeight();

    black_noise_.resize(kBlackNoiseAmount * n);
    for(int i = 0; i < kBlackNoiseAmount * n; i++)
    {
        NoiseParticle particle;
        particle.position.x = ofRandomWidth();
        particle.position.y = ofRandomHeight();
        particle.properties.radius = ofRandom(.01f, .5f);
        particle.properties.alpha = ofRandom(10, 60);

        black_noise_[i] = particle;
    }

    white_noise_.resize(kWhiteNoiseAmount * n);
    for(int i = 0; i < kWhiteNoiseAmount * n; i++)
    {
        NoiseParticle particle;
        particle.position.x = ofRandomWidth();
        particle.position.y = ofRandomHeight();
        particle.properties.radius = ofRandom(.01f, .5f);
        particle.properties.alpha = ofRandom(10, 200);

        white_noise_[i] = particle;
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    if(ofGetFrameNum() == 10) // Optimization: draw the scene only once since it is static
    {
        ofBackground(255);

        // Draw the dandelion grid, centered on the canvas
        ofPushMatrix();
        {
            ofTranslate(kExternalMargin, kExternalMargin);

            // Draw all the dandelions equal, but one
            int count = 0;
            for(auto& dandelion : dandelion_list_)
            {
                if(count != kDifferentDandelionIdx)
                {
                    ofSetColor(0);

                    ofNoFill();
                    ofSetLineWidth(3);
                    dandelion.drawBoundingBox();

                    ofSetLineWidth(2);
                    dandelion.drawLines();

                    ofFill();
                    ofSetLineWidth(2);
                    dandelion.drawEllipse();

                    ofNoFill();
                    ofSetLineWidth(4);
                    dandelion.drawCircle();

                    ofSetLineWidth(4);
                    dandelion.drawTrunk();
                }
                count++;
            }

            // Draw the different dandelion
            auto& dandelion = dandelion_list_[kDifferentDandelionIdx];

            ofPushMatrix();
            {
                ofVec2f pivot;
                pivot.x = dandelion.getCenter().x + 0.5f * kExternalMargin - 2;
                pivot.y = dandelion.getCenter().y - 0.5f * kExternalMargin + 2;

                ofTranslate(pivot);
                ofRotateZDeg(270);

                ofSetColor(0);

                ofSetLineWidth(2);
                dandelion.drawLines(-pivot.x, -pivot.y);

                ofFill();
                ofSetLineWidth(2);
                dandelion.drawEllipse(-pivot.x, -pivot.y);

                ofNoFill();
                ofSetLineWidth(4);
                dandelion.drawCircle(-pivot.x, -pivot.y);

                ofSetLineWidth(4);
                dandelion.drawTrunk(-pivot.x, -pivot.y);

                //                ofSetColor(255, 200, 0);

                ofNoFill();
                ofSetLineWidth(3);
                dandelion.drawBoundingBox(-pivot.x, -pivot.y);
            }
            ofPopMatrix();
        }
        ofPopMatrix();

        // Draw the noise as the last layer on the canvas
        for(auto& particle : white_noise_)
        {
            ofFill();
            ofSetColor(255, 255, 255, particle.properties.alpha);
            ofDrawCircle(particle.position, particle.properties.radius);
        }

        for(auto& particle : black_noise_)
        {
            ofFill();
            ofSetColor(0, 0, 0, particle.properties.alpha);
            ofDrawCircle(particle.position, particle.properties.radius);
        }
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
