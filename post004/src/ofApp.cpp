#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Define shapes
    size_t numShapes = 250;
    shapes.resize(numShapes);
    for(size_t shapeIdx = 0; shapeIdx < numShapes; shapeIdx++)
    {
        // Define layer parameters
        size_t numLayers = 8;
        int numCorners = (int)ofRandom(6, 15);
        float minRadiusOuterLayer = ofRandom(72, 80);
        float maxRadiusIncrease = 20;
        float layersSpacing = 10;
        float x = ofRandomWidth();
        float y = ofRandom(ofGetHeight() / 2 + 150 + ofRandom(-50, 0), ofGetHeight());

        // Define shape
        Shape shape;
        shape.resize(numLayers);

        // Define outer layer
        ofVec2f position(x, y);
        std::vector<float> radiusPerCorner(numCorners);
        for(size_t i = 0; i < radiusPerCorner.size(); i++)
            radiusPerCorner[i] = ofRandom(minRadiusOuterLayer, minRadiusOuterLayer + maxRadiusIncrease);

        // Define inner layers
        for(size_t layerIdx = 0; layerIdx < numLayers; layerIdx++)
        {
            DeformedCirclePtr layer = std::make_shared<soo::DeformedCircle>(position, numCorners, radiusPerCorner, 0);
            shape[layerIdx] = layer;

            for(size_t i = 0; i < radiusPerCorner.size(); i++)
                radiusPerCorner[i] = radiusPerCorner[i] - layersSpacing;
        }
        shapes[shapeIdx] = shape;
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{}

//--------------------------------------------------------------
void
ofApp::draw()
{
    ofColor in(0, 0, 0), out(0, 30, 150);
    ofBackgroundGradient(in, out, OF_GRADIENT_LINEAR);

    for(auto& shape : shapes)
        for(auto& layer : shape)
            layer->path.draw();
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
