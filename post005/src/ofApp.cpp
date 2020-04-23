#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Canvas settings
    ofBackground(0);
    ofSetFrameRate(30);
    w = ofGetWidth();
    h = ofGetHeight();

    // Load the character and initialize the character path
    font.load(fontName, 800, true, true, true);
    characterPath = font.getCharacterAsPoints(character, true, false);
    characterPath.setFilled(false);
    characterPath.setStrokeColor(ofColor::red);
    characterPath.setStrokeWidth(1);
    // Center the path in the window
    ofRectangle bbox = characterPath.getOutline()[0].getBoundingBox();
    float x = (w - bbox.width) / 2;
    float y = (h + bbox.height) / 2 - 25;
    characterPath.translate(ofVec2f(x, y));

    // Lines
    numLines = 80;
    lines.resize(numLines);

    float hMargin = 50, vMargin = 150;
    float dy = (h - 2 * vMargin) / (numLines - 1);

    for(size_t i = 0; i < numLines; i++)
    {
        // Define line
        soo::Line line;

        // Define path
        line.path.setFilled(false);
        line.path.setStrokeColor(255);
        line.path.setStrokeWidth(1);

        float x0 = hMargin;
        float y0 = vMargin + i * dy;

        float xf = w - hMargin;
        float yf = y0;

        line.path.moveTo(x0, y0);
        line.path.lineTo(xf, yf);

        // Define intersection points
        ofPolyline polyLine = line.path.getOutline()[0].getResampledBySpacing(1);
        for(int j = 0; j < polyLine.size() - 1; j++)
        {
            auto& p = polyLine[j];
            auto& pNext = polyLine[j + 1];

            bool bIn = characterPath.getOutline()[0].inside(p);
            bool bNextIn = characterPath.getOutline()[0].inside(pNext);

            if(bIn ^ bNextIn)
                line.intersectionPoints.push_back(p);
        }

        // Add line
        lines[i] = line;
    }

    // Bezier lines
    bezierLines.resize(numLines);
    for(auto& line : lines)
    {
        ofPath bezierLine;
        bezierLine.setFilled(false);
        bezierLine.setStrokeColor(255);
        bezierLine.setStrokeWidth(1);

        auto vertices = line.path.getOutline()[0].getVertices();
        auto v0 = vertices[0];
        auto vf = vertices[vertices.size() - 1];

        // Start bezier line
        bezierLine.moveTo(v0);

        if(line.intersectionPoints.size() > 0)
        {
            for(int i = 0; i < line.intersectionPoints.size() - 1; i = i + 2)
            {
                auto& p = line.intersectionPoints[i];
                auto& pNext = line.intersectionPoints[i + 1];

                float cp1x = p.x - 20;
                float cp1y = p.y - 30;
                float cp2x = pNext.x + 20;
                float cp2y = cp1y;

                // bezier line to firs intersection point, and bezier to the next one
                bezierLine.lineTo(p);
                bezierLine.bezierTo(cp1x, cp1y, cp2x, cp2y, pNext.x, pNext.y);
            }
        }

        // Finish bezier line
        bezierLine.lineTo(vf);
        bezierLines.push_back(bezierLine);
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    //    // Bezier lines
    //    bezierLines.clear();
    //    bezierLines.resize(numLines);
    //    for(auto& line : lines)
    //    {
    //        ofPath bezierLine;
    //        bezierLine.setFilled(false);
    //        bezierLine.setStrokeColor(255);
    //        bezierLine.setStrokeWidth(1);

    //        auto vertices = line.path.getOutline()[0].getVertices();
    //        auto v0 = vertices[0];
    //        auto vf = vertices[vertices.size() - 1];

    //        // Start bezier line
    //        bezierLine.moveTo(v0);

    //        if(line.intersectionPoints.size() > 0)
    //        {
    //            for(int i = 0; i < line.intersectionPoints.size() - 1; i = i + 2)
    //            {
    //                auto& p = line.intersectionPoints[i];
    //                auto& pNext = line.intersectionPoints[i + 1];

    //                float cp1x = p.x - 20 + ofRandom(-15, 15);
    //                float cp1y = p.y - 30 + ofRandom(-15, 15);
    //                float cp2x = pNext.x + 20 + ofRandom(-15, 15);
    //                float cp2y = pNext.y + 20 + ofRandom(-15, 15);

    //                // bezier line to firs intersection point, and bezier to the next one
    //                bezierLine.lineTo(p);
    //                bezierLine.bezierTo(cp1x, cp1y, cp2x, cp2y, pNext.x, pNext.y);
    //            }
    //        }

    //        // Finish bezier line
    //        bezierLine.lineTo(vf);
    //        bezierLines.push_back(bezierLine);
    //}
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofNoFill();
    ofSetColor(ofColor::yellow);

    //    characterPath.draw();

    //    for(auto& line : lines)
    //    {
    //        //        line.path.draw();

    //        for(auto& point : line.intersectionPoints)
    //            ofDrawCircle(point, 5);
    //    }

    for(auto& bezier : bezierLines)
        bezier.draw();
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
