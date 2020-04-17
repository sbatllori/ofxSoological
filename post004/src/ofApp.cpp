#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(500);
    framesExporter.setActive(false);

    // Define canvas settings
    ofSetFrameRate(30);
    ofSetCurveResolution(72);

    // Define text
    font.load(fontName, 24, true, true, true);
    font.setLineHeight(30.f);

    // Define shapes
    ofPath ellipse;
    ellipse.ellipse(ofGetWidth() / 2, ofGetHeight() / 2, 2 * ofGetWidth() / 3, 3 * ofGetHeight() / 4);

    size_t numShapes = 700;
    shapes.resize(numShapes);
    for(size_t shapeIdx = 0; shapeIdx < numShapes; shapeIdx++)
    {
        // Define layer parameters
        size_t numLayers = 9;
        int numCorners = (int)ofRandom(6, 12);
        float minRadiusOuterLayer = ofRandom(72, 80) - 20;
        float maxRadiusIncrease = 10;
        float layersSpacing = 7;

        // Define shape
        Shape shape;
        shape.resize(numLayers);
        //        float x = ofRandomWidth();
        //        float y = ofRandom(ofGetHeight() / 2 + 150 + ofRandom(-50, 0), ofGetHeight());

        float x, y;
        do
        {
            x = ofRandomWidth();
            y = ofRandomHeight();
        } while(ellipse.getOutline()[0].inside(x, y));

        ofVec2f position(x, y);
        std::vector<float> radii(numCorners);

        // Define outer layer
        for(size_t i = 0; i < radii.size(); i++)
            radii[i] = ofRandom(minRadiusOuterLayer, minRadiusOuterLayer + maxRadiusIncrease);

        for(size_t layerIdx = 0; layerIdx < numLayers; layerIdx++)
        {
            // Add layer to shape
            DeformedCirclePtr layer = std::make_shared<soo::DeformedCircle>(position, numCorners, radii, 0);
            shape[layerIdx] = layer;

            // Define inner layers
            for(size_t i = 0; i < radii.size(); i++)
                radii[i] = radii[i] - layersSpacing;
        }

        // Add shape to shapes
        shapes[shapeIdx] = shape;
    }

    // Define stone
    size_t numLayers = 4;
    int numCorners = 10;
    float minRadiusOuterLayer = 20;
    float maxRadiusIncrease = 5;
    float layersSpacing = 5;
    ofVec2f position(0, 65);

    stone.resize(numLayers);
    std::vector<float> radii(numCorners);
    for(size_t i = 0; i < radii.size(); i++)
        radii[i] = ofRandom(minRadiusOuterLayer, minRadiusOuterLayer + maxRadiusIncrease);
    for(size_t layerIdx = 0; layerIdx < numLayers; layerIdx++)
    {
        DeformedCirclePtr layer = std::make_shared<soo::DeformedCircle>(position, numCorners, radii, 0);
        stone[layerIdx] = layer;
        for(size_t i = 0; i < radii.size(); i++)
            radii[i] = radii[i] - layersSpacing;
    }

    // Define stars
    size_t numStars = 40;
    stars.resize(numStars);
    for(size_t i = 0; i < numStars; i++)
    {
        soo::Particle<Properties> star;
        star.properties.radius = ofRandom(1, 2.5);

        float x, y;
        do
        {
            x = ofRandomWidth();
            y = ofRandomHeight();
        } while(!ellipse.getOutline()[0].inside(x, y));

        star.position.x = x;
        star.position.y = y;

        stars[i] = star;
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
    ofColor in(0, 30, 160), out(0, 0, 0);
    ofBackgroundGradient(in, out, OF_GRADIENT_CIRCULAR);

    // Draw stars
    ofSetColor(ofColor::white);
    for(auto& star : stars)
    {
        float r = star.properties.radius;
        ofDrawCircle(star.position, r + ofRandom(-0.5, 0.5));
    }

    // Draw person
    ofFill();
    ofSetLineWidth(2);
    ofSetColor(ofColor::black);
    ofPushMatrix();
    {
        ofVec2f centre(ofGetWidth() / 2, ofGetHeight() / 2 + 20);
        ofTranslate(centre);
        ofScale(1.2);

        // Head
        ofDrawEllipse(0, 0, 10, 12);

        // Body
        ofDrawTriangle(0, -5, -8, 30, 8, 30);

        // Left arm
        ofPath leftArm;
        leftArm.setFilled(false);
        leftArm.setStrokeColor(ofColor::black);
        leftArm.setStrokeWidth(2);
        leftArm.arc(0, -5, 10, 15, 90, 200);
        leftArm.draw();

        // Right arm
        ofPushMatrix();
        {
            ofRotateYDeg(180);
            leftArm.draw();
        }
        ofPopMatrix();

        // Legs
        ofDrawLine(-3, 25, -3, 45);
        ofDrawLine(3, 25, 3, 45);

        // Fire
        Shape fire;
        size_t numLayers = 3;
        int numCorners = 8;
        float minRadiusOuterLayer = 15;
        float maxRadiusIncrease = 3;
        float layersSpacing = 5;
        ofVec2f position(0, -45);

        fire.resize(numLayers);
        std::vector<float> radii(numCorners);
        for(size_t i = 0; i < radii.size(); i++)
            radii[i] = ofRandom(minRadiusOuterLayer, minRadiusOuterLayer + maxRadiusIncrease);
        for(size_t layerIdx = 0; layerIdx < numLayers; layerIdx++)
        {
            DeformedCirclePtr layer = std::make_shared<soo::DeformedCircle>(position, numCorners, radii, 0);
            layer->path.setFilled(true);
            ofColor color;

            switch(layerIdx)
            {
            case 2:
                color = ofColor::red;
                break;
            case 1:
                color = ofColor::orange;
                break;
            default:
                color = ofColor::yellow;
                break;
            }
            layer->path.setColor(color);

            fire[layerIdx] = layer;

            for(size_t i = 0; i < radii.size(); i++)
                radii[i] = radii[i] - layersSpacing;
        }
        for(auto& layer : fire)
            layer->path.draw();

        // Stone
        for(auto& layer : stone)
            layer->path.draw();
    }
    ofPopMatrix();

    // Draw shapes
    for(auto& shape : shapes)
        for(auto& layer : shape)
            layer->path.draw();

    // Draw Text
    float x = ofGetWidth() / 2 - 140;
    float y = ofGetHeight() / 2 - 140;
    //    ofFill();
    //    ofSetColor(ofColor::white);
    //    ofDrawRectRounded(x - 12, y - 32, 312, 62, 15);
    //    ofNoFill();
    //    ofSetLineWidth(4);
    //    ofSetColor(ofColor::black);
    //    ofDrawRectRounded(x - 12, y - 32, 312, 62, 15);
    ofSetColor(ofColor::white);
    font.drawString(text, x, y);
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
