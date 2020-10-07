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

    // Define the dandelion pattern
    auto w = (ofGetWidth() - kExternalMargin) / kNCellsPerAxe;
    auto h = (ofGetHeight() - kExternalMargin) / kNCellsPerAxe;
    for(int i = 0; i < w * kNCellsPerAxe; i += w)
    {
        for(int j = 0; j < h * kNCellsPerAxe; j += h)
        {
            auto dandelion = std::make_shared<soo::Dandelion>();
            dandelion->generate(ofVec2f(i, j), w - kExternalMargin);
            dandelion_list_.push_back(dandelion);
        }
    }

    // Treat a dandelion differently
    dandelion_list_[kDifferentDandelionIdx]->hideBoundingBox();
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
    ofBackground(255, 200, 0);

    ofPushMatrix();
    {
        ofTranslate(kExternalMargin, kExternalMargin);

        int count = 0;
        for(auto& dandelion : dandelion_list_)
        {
            ofSetLineWidth(5);

            ofFill();
            ofSetColor(255);
            dandelion->drawBoundingBox();

            ofNoFill();
            ofSetColor(0);
            if(count == kDifferentDandelionIdx)
                ofSetColor(255);
            dandelion->drawBoundingBox();

            ofSetLineWidth(2);
            dandelion->drawLines();

            ofSetLineWidth(3);
            dandelion->drawCircle();
            ofFill();
            dandelion->drawEllipse();

            count++;
        }
    }
    ofPopMatrix();
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
