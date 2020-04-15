#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Setup frames exporter
    framesExporter.setStartAndEnd(0.1f, 50);
    framesExporter.setActive(false);

    // Canvas settings
    ofBackground(255);
    ofSetFrameRate(30);

    // Load the character and initialize the character path
    font.load(fontName, 800, true, true, true);
    path = std::make_shared<ofPath>(font.getCharacterAsPoints(character, true, false));

    // Center the path in the window
    ofRectangle bbox = path->getOutline()[0].getBoundingBox();
    float x = ofGetWindowWidth() / 2 - bbox.width / 2 - 50;
    float y = ofGetWindowHeight() / 2 + bbox.height / 2;
    path->translate(ofVec2f(x, y));

    // Get the vertices defining the path
    std::vector<ofVec2f> vertices;
    for(auto& v : path->getOutline()[0].getVertices())
    {
        vertices.push_back(ofVec2f(v.x, v.y));
    }

    if(!renderKidLine)
    {
        // Save the the bottom of the character path separately, to change the moving direction of the lines
        ofPath pathBottom; // 2 - 125
        pathBottom.moveTo(vertices[2]);
        for(auto i = 2; i <= 125; i++)
            pathBottom.lineTo(vertices[i]);
        bottom = pathBottom.getOutline()[0].getResampledBySpacing(1);

        // Save the end of the character path separately, to stop the lines once they reach it
        ofPath pathEnd; // 1 - 2
        pathEnd.moveTo(vertices[1]);
        pathEnd.lineTo(vertices[2]);
        end = pathEnd.getOutline()[0].getResampledBySpacing(1);

        // Initilize the lines
        auto v1 = vertices[124];
        auto v2 = vertices[125];

        unsigned long numLines = 300;
        lines.resize(numLines);
        for(unsigned long i = 0; i < numLines; i++)
        {
            soo::Line line;

            // Define line properties
            line.stepLen = 10;
            line.angle = ofRandom(50, 140);
            line.origin.position = ofVec2f(ofRandom(v2.x, v1.x), v1.y);
            line.origin.setRandomDirection();

            // Define path properties
            line.path.moveTo(line.origin.position);
            line.path.setStrokeColor(ofColor(0, 0, 0, 50));
            line.path.setStrokeWidth(2);
            line.path.setFilled(false);

            lines[i] = line;
        }
    }
    else
    {
        kidLine.stepLen = 5;
        kidLine.origin.position = vertices[124];
        kidLine.origin.setRandomDirection();
        kidLine.path.setStrokeColor(ofColor(200, 100, 100, 100));
        kidLine.path.setStrokeWidth(10);
        kidLine.path.setFilled(false);
    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    framesExporter.updateByTime(ofGetElapsedTimeMillis());

    if(!renderKidLine)
    {
        for(auto& line : lines)
        {

            // Check if the line reached the end of the shape
            for(auto& endVertex : end)
            {
                if(line.origin.position.distance(endVertex) < line.stepLen)
                    line.done = true;
            }

            // Grow the line
            if(!line.done)
            {

                ofVec2f nextPosition = line.origin.position + line.stepLen * line.origin.direction;

                // If the next step is inside the shape, move forward
                if(path->getOutline()[0].inside(nextPosition.x, nextPosition.y))
                {
                    line.origin.position = nextPosition;
                    line.path.lineTo(line.origin.position.x, line.origin.position.y);
                }
                // Otherwise, change direction
                else
                {
                    line.sign = 1;
                    // Check if we are close to the bottom of the shape to change angle sign
                    auto numSteps = line.path.getOutline()[0].getVertices().size();
                    if(numSteps > 1)
                    {
                        for(auto& bottomVertex : bottom)
                        {
                            if(nextPosition.distance(bottomVertex) < line.stepLen)
                            {
                                line.sign = -1;
                                break;
                            }
                        }
                    }

                    // Change direction
                    line.origin.direction.rotate(line.sign * line.angle);
                }
            }
        }
    }
    else
    {
        // Kidline
        ofVec2f next = kidLine.origin.position;
        do
        {
            kidLine.origin.position = next;
            next += kidLine.stepLen * kidLine.origin.direction;

        } while(path->getOutline()[0].inside(next.x, next.y));

        kidLine.path.lineTo(kidLine.origin.position.x, kidLine.origin.position.y);
        kidLine.origin.setRandomDirection();
    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{
    if(!renderKidLine)
        for(auto& line : lines)
            line.path.draw();
    else
    {
        kidLine.path.draw();
    }
}
