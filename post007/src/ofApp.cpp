#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    ofSetBackgroundAuto(false); // Do not refresh canvas
    ofEnableAlphaBlending();
    ofSetFrameRate(60);
    ofBackground(204, 75, 20);

    // Define the seven as a hairy shape
    font.load(fontName, 500, true, true, true);
    charPoly = font.getCharacterAsPoints(character, true, false).getOutline()[0];

    auto bbox = charPoly.getBoundingBox();
    float x = ofGetWidth() / 2 - (bbox.x + bbox.width / 2);
    float y = ofGetHeight() / 2 - (bbox.y + bbox.height / 2);
    charPoly.translate({x, y});
    charPoly = charPoly.getResampledBySpacing(1);

    seven.contour = charPoly;
    seven.color1 = ofColor::white;
    seven.color2 = ofColor(ofColor::cadetBlue + 20);
    seven.v1 = ofVec2f(0, 15.0);
    seven.v2 = ofVec2f(50, 0);
    seven.v3 = ofVec2f(0, -15.0);
    seven.numTriangles = 50;
    seven.minOffset = 10;
    seven.maxOffset = 20;
    seven.alpha = 50;

    // Add some hairy shapes
    initRandomShapes();
}

//--------------------------------------------------------------
void
ofApp::update()
{}

//--------------------------------------------------------------
void
ofApp::draw()
{
    // Render seven and extended bounding box
    //    ofNoFill();
    //    ofRectangle bbbox = seven.contour.getBoundingBox();
    //    bbbox.translate(-bbbox.width / 4, -bbbox.height / 4);
    //    bbbox.scaleWidth(1.5);
    //    bbbox.scaleHeight(1.5);
    //    ofDrawRectangle(bbbox);
    //    seven.contour.draw();

    // Drawing when the mouse is pressed
    if(ofGetMousePressed(OF_MOUSE_BUTTON_LEFT))
    {
        seven.drawStar();

        for(auto& shape : shapes)
            shape.drawStar();
    }

    if(ofGetMousePressed(OF_MOUSE_BUTTON_RIGHT))
    {
        ofBackground(204, 75, 20);
        initRandomShapes();
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
ofApp::initRandomShapes()
{
    shapes.clear();
    for(int i = 0; i < 7; i++)
    {
        ofPolyline circlePoly;

        // Circles places outside the seven
        ofRectangle boundary = seven.contour.getBoundingBox();
        boundary.translate(-boundary.width / 4, -boundary.height / 4);
        boundary.scaleWidth(1.5);
        boundary.scaleHeight(1.5);

        float x, y;
        float dist;
        do
        {
            x = ofRandomWidth();
            y = ofRandomHeight();

            ofVec2f closest = seven.contour.getClosestPoint({x, y, 0});
            dist = closest.distance({x, y});

        } while(!(boundary.inside(x, y) && dist > 50));
        // outside: while(boundary.inside(x, y) && dist < 50);
        // borderline: while(!(boundary.inside(x, y) && dist > 50))

        float radius = ofRandom(20, 40);
        circlePoly.arc({x, y, 0}, radius, radius, 0, 360);

        soo::HairyShape circle;
        circle.contour = circlePoly;
        circle.color1 = ofColor(0); // black
        circle.color2 = ofColor(ofRandom(5, 40)); // slightly lighter
        circle.v1 = ofVec2f(0, 0.15 * radius);
        circle.v2 = ofVec2f(radius, 0);
        circle.v3 = ofVec2f(0, -0.15 * radius);
        circle.numTriangles = 5;
        circle.minOffset = 0;
        circle.maxOffset = 15;
        circle.alpha = 50;
        shapes.push_back(circle);
    }
}
