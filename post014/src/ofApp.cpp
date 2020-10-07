#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(900);
    framesExporter.setActive(false);

    // Canvas settings
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);

    //    dandelion.generate(ofVec2f(300), 400);

    int n_cells_per_axe = 4;
    auto w = (ofGetWidth() - external_margin_) / n_cells_per_axe;
    auto h = (ofGetHeight() - external_margin_) / n_cells_per_axe;
    for(int i = 0; i < w * n_cells_per_axe; i += w)
    {
        for(int j = 0; j < h * n_cells_per_axe; j += h)
        {
            auto dandelion = std::make_shared<soo::Dandelion>();
            dandelion->generate(ofVec2f(i, j), w - external_margin_);
            dandelion_list_.push_back(dandelion);
        }
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
    ofSetColor(0);

    ofPushMatrix();
    ofTranslate(external_margin_, external_margin_);
    for(auto& dandelion : dandelion_list_)
    {

        ofSetLineWidth(5);
        dandelion->drawBoundingBox();

        ofSetLineWidth(2);
        dandelion->drawLines();

        ofSetLineWidth(3);
        dandelion->drawCircle();
        dandelion->drawEllipse();
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
