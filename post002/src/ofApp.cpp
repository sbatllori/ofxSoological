#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    // Setup frames exporter
    framesExporter = soo::FramesExporterPtr(new soo::FramesExporter(50));
    framesExporter->setActive(false);

    // Canvas settings
    ofBackground(255);
    ofSetFrameRate(30);

    // Load the character and create a shape
    font.load(fontName, 800, true, true, true);
    auto path = font.getCharacterAsPoints(character, true, false);
    shape = std::make_unique<soo::Shape>(path);
    shape->toCenter();

    if(!renderKidLine)
    {
        // Save the the bottom of the shape separately
        auto vertices = shape->getVertices();
        ofPath pathBottom; // 2 - 125
        pathBottom.moveTo(vertices[2]);
        for(auto i = 2; i <= 125; i++)
            pathBottom.lineTo(vertices[i]);
        shapeBottom = pathBottom.getOutline()[0].getResampledBySpacing(1);

        // Save the end of the shape separately
        ofPath pathEnd; // 1-2
        pathEnd.moveTo(vertices[1]);
        pathEnd.lineTo(vertices[2]);
        shapeEnd = pathEnd.getOutline()[0].getResampledBySpacing(1);

        // Initilize the lines
        auto v1 = shape->getVertices()[124];
        auto v2 = shape->getVertices()[125];

        int numLines = 200;
        lines.resize(numLines);
        for(int i = 0; i < numLines; i++)
        {
            soo::Line line;
            line.stepLen = 10;
            line.angle = ofRandom(50, 140);
            ofVec2f originPosition;
            originPosition.x = ofRandom(v2.x, v1.x);
            originPosition.y = v1.y;
            line.origin.centre = originPosition; // TODO refactor in Particle
            line.origin.speed = 1; // TODO refactor in Particle
            line.origin.setRandomDirection();

            line.path.moveTo(line.origin.centre);
            line.path.setStrokeColor(ofColor(0, 0, 0, 50));
            line.path.setStrokeWidth(2);
            line.path.setFilled(false);

            lines.push_back(line);
        }
    }
    else
    {
        kidLine.stepLen = 5;
        kidLine.origin.centre = shape->getVertices()[124];
        kidLine.origin.speed = 1;
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
    framesExporter->update(ofGetElapsedTimeMillis());

    if(!renderKidLine)
    {
        for(auto& line : lines)
        {

            // Check if the line reached the end of the shape
            for(auto& endVertex : shapeEnd)
            {
                if(line.origin.centre.distance(endVertex) < line.stepLen)
                    line.done = true;
            }

            // Grow the line
            if(!line.done)
            {

                ofVec2f nextPosition = line.origin.centre + line.stepLen * line.origin.direction;

                // If the next step is inside the shape, move forward
                if(shape->inside(nextPosition.x, nextPosition.y))
                {
                    line.origin.centre = nextPosition;
                    line.path.lineTo(line.origin.centre.x, line.origin.centre.y);
                }
                // Otherwise, change direction
                else
                {
                    line.sign = 1;
                    // Check if we are close to the bottom of the shape to change angle sign
                    auto numSteps = line.path.getOutline()[0].getVertices().size();
                    if(numSteps > 1)
                    {
                        for(auto& bottomVertex : shapeBottom)
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
        ofVec2f next = kidLine.origin.centre;
        do
        {
            kidLine.origin.centre = next;
            next += kidLine.stepLen * kidLine.origin.direction;

        } while(shape->inside(next.x, next.y));

        kidLine.path.lineTo(kidLine.origin.centre.x, kidLine.origin.centre.y);
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
