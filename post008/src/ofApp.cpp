#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(1500);
    framesExporter.setActive(false);

    // Load image
    image.load(imagePath);
    w = image.getWidth();
    h = image.getHeight();

    // Canvas settings
    ofSetWindowShape(w, h);
    ofSetBackgroundAuto(false);
    ofBackground(255);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);

    // Brushes definition
    int numBrushes = 250;
    brushes.resize(numBrushes);
    for(int i = 0; i < numBrushes; i++)
    {
        Brush brush;

        // Brush falling from the top of the canvas vertically
        brush.direction = {0.0, 1.0};
        brush.position.x = ofRandomWidth();
        brush.position.y = 0;
        brush.properties.active = true;

        // 10% of the brushes can be bigger than the rest
        if(ofRandom(100) < 10)
        {
            brush.properties.size = ofRandom(5, 30);
            brush.properties.speed = brush.properties.size / 5.f;
            brush.properties.alpha = 5;
        }
        else
        {
            brush.properties.size = ofRandom(5, 10);
            brush.properties.speed = ofRandom(0.1, 2);
            brush.properties.alpha = 10;
        }

        brushes[i] = brush;
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    for(auto& brush : brushes)
    {
        // Define the next position of the brush, according to its speed and adding a bit of noise to simulate the drops
        brush.position += brush.properties.speed * brush.direction + ofRandom(-1, 1) * ofNoise(brush.position);

        // Deactivate the brush if it reached the end of the canvas
        bool outside = brush.position.x < 0 || brush.position.x > w || brush.position.y < 0 || brush.position.y > h;
        if(outside)
            brush.properties.active = false;
    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    // Each brush draws a circle with the correspondent image pixel color
    for(auto& brush : brushes)
    {
        if(brush.properties.active)
        {
            ofColor color = image.getColor(brush.position.x, brush.position.y);
            color.a = brush.properties.alpha;
            ofSetColor(color);
            ofDrawCircle(brush.position, brush.properties.size);
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
