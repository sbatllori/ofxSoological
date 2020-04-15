#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Setup frames exporter
    framesExporter.setStartAndEnd(10, 100);
    framesExporter.setActive(false);

    ofSetFrameRate(30);
    ofSetBackgroundColor(255);
    ofSetLineWidth(4);

    // TODO gradient?
    //    randomColors.push_back(ofColor::red);
    //    randomColors.push_back(ofColor::green);
    //    randomColors.push_back(ofColor::blue);
    //    randomColors.push_back(ofColor::yellow);

    int bright = 255, dark = 50;
    randomColors.push_back(ofColor(bright, dark, dark));
    randomColors.push_back(ofColor(dark, bright, dark));
    randomColors.push_back(ofColor(dark, dark, bright));
    randomColors.push_back(ofColor(bright, bright, dark));

    std::vector<int> indices(nRows * nColumns);
    std::iota(indices.begin(), indices.end(), 0);
    std::random_shuffle(indices.begin(), indices.end());
    for(auto idx : indices)
        unsetIndices.push(idx);

    // Initialize cells
    auto w = ofGetWindowWidth() / nRows;
    auto h = ofGetWindowHeight() / nColumns;

    for(int i = 0; i < nRows; i++)
    {
        for(int j = 0; j < nColumns; j++)
        {
            soo::Cell cell;
            cell.w = w;
            cell.h = h;
            cell.origin = ofVec2f(i * w, j * h);
            cell.color = randomColors[(int)ofRandom(0, randomColors.size())];

            if(std::count(shapeIndices.begin(), shapeIndices.end(), std::make_pair(j, i)))
            {
                cell.finalColor = randomColors[0];
            }

            cells.push_back(cell);
        }
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    // Update cell colors
    for(auto& cell : cells)
    {
        if(ofGetFrameNum() % 3 == 0)
        {
            if(cell.isFinalColorSet)
            {
                cell.color = cell.finalColor;
            }
            else
            {
                cell.color = randomColors[(int)ofRandom(0, randomColors.size())];
            }
        }
    }

    // Set cells to draw the final color
    if(!unsetIndices.empty() && ofGetFrameNum() > 60 && ofGetFrameNum() % 3 == 0)
    {
        auto idx = unsetIndices.top();
        cells[idx].isFinalColorSet = true;
        unsetIndices.pop();
    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    for(auto& cell : cells)
    {
        ofFill();
        ofSetColor(cell.color);
        ofDrawRectangle(cell.origin, cell.w, cell.h);

        ofNoFill();
        ofSetColor(ofColor::white);
        ofDrawRectangle(cell.origin, cell.w, cell.h);
    }
}

//--------------------------------------------------------------
void
ofApp::keyPressed(int key)
{}

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
