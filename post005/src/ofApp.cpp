#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(400);
    framesExporter.setActive(false);

    // Canvas settings
    ofBackground(0);
    ofSetFrameRate(30);
    w = ofGetWidth();
    h = ofGetHeight();

    // Load the character and initialize the character path
    font.load(fontName, 800, true, true, true);
    ofPath characterPath = font.getCharacterAsPoints(character, true, false);

    // Center the path in the window
    ofRectangle bbox = characterPath.getOutline()[0].getBoundingBox();
    float x = (w - bbox.width) / 2 - 25;
    float y = (h + bbox.height) / 2 - 25;
    characterPath.translate(ofVec2f(-1.2 * bbox.width, y));

    // Get the polyline
    characterPoly = characterPath.getOutline()[0];

    // Define lines
    numLines = 39;
    wMargin = 0;
    hMargin = 0;

    float x0 = wMargin;
    float xf = w - wMargin;
    float dy = (h - 2 * hMargin) / (numLines - 1);

    lines.resize(numLines);
    for(int i = 0; i < numLines; i++)
    {
        float y = hMargin + i * dy;
        auto line = std::make_shared<soo::BezierLine>(x0, xf, y, characterPoly);
        lines[i] = line;
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    for(auto& line : lines)
        line->moveY(-2.f, hMargin, h - hMargin, characterPoly);

    characterPoly.translate(ofVec2f(5, 0));
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    for(auto& line : lines)
        line->path.draw();
}
