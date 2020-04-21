#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Frames exporter
    framesExporter.setEnd(300);
    framesExporter.setActive(false);

    // Canvas settings
    ofSetFrameRate(30);
    ofSetCurveResolution(72);

    // Text
    font.load(fontName, 30, true, true, true);
    font.setLineHeight(34.f);

    // Sky
    auto w = ofGetWidth();
    auto h = ofGetHeight();
    sky.ellipse(w / 2, h / 2, 2 * w / 3, 3 * h / 4);

    // Stars
    size_t numStars = 40;
    stars.resize(numStars);
    for(size_t i = 0; i < numStars; i++)
    {
        Star star;

        // Star position "inside" the sky
        float x, y;
        do
        {
            x = ofRandomWidth();
            y = ofRandomHeight();
        } while(!sky.getOutline()[0].inside(x, y));
        star.position = ofVec2f(x, y);
        star.properties.radius = ofRandom(1, 2.5);
        stars[i] = star;
    }

    // Ground
    size_t numRocks = 700;
    ground.resize(numRocks);
    for(size_t i = 0; i < numRocks; i++)
    {
        Rock rock;

        // Rock position "outside" the sky
        float x, y;
        do
        {
            x = ofRandomWidth();
            y = ofRandomHeight();
        } while(sky.getOutline()[0].inside(x, y));
        rock.position = ofVec2f(x, y);
        rock.resolution = (int)ofRandom(6, 12);
        rock.minRadius = ofRandom(52, 60);
        rock.maxRadius = rock.minRadius + 10;
        rock.generateRandom(9, 7.f);
        rock.setDefaultDrawingSettings();
        ground[i] = rock;
    }

    // Flying rock
    flyingRock.position = ofVec2f(0, 65);
    flyingRock.resolution = 10;
    flyingRock.minRadius = 20;
    flyingRock.maxRadius = 25;
    flyingRock.generateRandom(5, 4.5);
    flyingRock.setDefaultDrawingSettings();

    // Fire
    fire.position = ofVec2f(0, -45);
    fire.resolution = 8;
    fire.minRadius = 15;
    fire.maxRadius = 18;
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByFrames(ofGetFrameNum());

    // Update fire radii so that it moves
    fire.generateRandom(3, 5.f);
    fire.setDefaultDrawingSettings();
    fire.paths[0].setColor(ofColor::yellow);
    fire.paths[1].setColor(ofColor::orange);
    fire.paths[2].setColor(ofColor::red);
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    // Draw background gradient
    ofColor in(0, 30, 160), out(0, 0, 0);
    ofBackgroundGradient(in, out, OF_GRADIENT_CIRCULAR);

    // Draw stars
    ofSetColor(ofColor::white);
    for(auto& star : stars)
        ofDrawCircle(star.position, star.properties.radius + ofRandom(-0.5, 0.5));

    // Draw sky scene
    ofPushMatrix();
    {
        // Transform the space to define the sky scene relatively: person, fire and flying rock
        ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2 + 20);
        ofScale(1.4f);

        // Drawing settings
        ofFill();
        ofSetLineWidth(2);
        ofSetColor(ofColor::black);

        // Draw person
        ofDrawEllipse(0, 0, 10, 12); // Head
        ofDrawTriangle(0, -5, -8, 30, 8, 30); // Body
        ofPath leftArm;
        leftArm.setFilled(false);
        leftArm.setStrokeColor(ofColor::black);
        leftArm.setStrokeWidth(2);
        leftArm.arc(0, -5, 10, 15, 90, 200);
        leftArm.draw();
        ofPushMatrix();
        {
            ofRotateYDeg(180);
            leftArm.draw(); // Right arm
        }
        ofPopMatrix();
        ofDrawLine(-3, 25, -3, 45); // Left leg
        ofDrawLine(3, 25, 3, 45); // Right leg

        // Draw fire
        fire.draw();

        // Draw flying rock
        flyingRock.draw();
    }
    ofPopMatrix();

    // Draw ground
    for(auto& rock : ground)
        rock.draw();

    // Draw Text
    ofSetColor(ofColor::white);
    ofRectangle bbox = font.getStringBoundingBox(text, 0, 0);
    float x = (ofGetWidth() - bbox.width) / 2;
    float y = ofGetHeight() / 3;
    font.drawString(text, x, y);
}
