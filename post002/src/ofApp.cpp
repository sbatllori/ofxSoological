#include "ofApp.h"

//--------------------------------------------------------------
void
ofApp::setup()
{
    ofBackground(ofColor::white);
    ofSetFrameRate(30);
    ofSetCircleResolution(72);

    font.load(fontName, 800, true, true, true);
    auto path = font.getCharacterAsPoints(character, true, false);

    shape = std::make_unique<soo::Shape>(path);
    shape->toCenter();

    // Save the the bottom of the shape separately
    auto vertices = shape->getVertices();
    ofPath pathBottom; // 2 - 125
    pathBottom.moveTo(vertices[2]);
    for(auto i = 2; i <= 125; i++)
    {
        pathBottom.lineTo(vertices[i]);
    }
    shapeBottom = pathBottom.getOutline()[0].getResampledBySpacing(1);

    // Save the end of the shape separately
    ofPath pathEnd; // 1-2
    pathEnd.moveTo(vertices[1]);
    pathEnd.lineTo(vertices[2]);
    shapeEnd = pathEnd.getOutline()[0].getResampledBySpacing(1);

    // Init line
    origin.centre = shape->getVertices()[124]; // TODO refactor .center for .position
    origin.speed = 1; // TODO speed needs to be required by the setRandomDirection function
    //    originTop.setRandomDirection();
    origin.direction = ofVec2f(-1, -1);
    line.moveTo(origin.centre);

    // Drawing settings
    // (200, 100, 100, 100);
    ofColor lineTopColor(0);
    line.setStrokeColor(lineTopColor);
    line.setStrokeWidth(2);
    line.setFilled(false);

    // TODO vector of lines

    //    ofFill();
    //    ofSetLineWidth(2);
    //    ofSetColor(lineColor.r, lineColor.g, lineColor.b);

    //    float stepLen = 50;
    //    int maxSteps = 100;
    //    for(int i = 0; i < 1000; i++)
    //    {
    //        ofVec2f next = origin.centre;
    //        int numSteps = 0;
    //        do
    //        {
    //            origin.centre = next;
    //            next += stepLen * origin.direction;
    //            numSteps++;

    //        } while(shape->inside(next.x, next.y) && numSteps < maxSteps);

    //        line.curveTo(origin.centre.x, origin.centre.y);
    //        origin.setRandomDirection();
    //    }
}

//--------------------------------------------------------------
void
ofApp::update()
{
    bool done = false;
    float stepLen = 5;

    for(auto& v : shapeEnd)
    {
        if(origin.centre.distance(v) < stepLen)
            done = true;
    }
    if(!done)
    {

        ofVec2f next = origin.centre + stepLen * origin.direction;
        //    std::cout << "origin: " << originTop.centre << std::endl;
        //    std::cout << "next: " << next << std::endl;

        if(shape->inside(next.x, next.y))
        {
            //        std::cout << "MES" << std::endl;

            origin.centre = next;
            line.lineTo(origin.centre.x, origin.centre.y);
        }
        else
        {
            if(line.getOutline()[0].getVertices().size() > 1)
            {
                for(auto& v : shapeBottom)
                {
                    if(next.distance(v) < stepLen)
                    {
                        std::cout << "CHAAAAANGIN SIGN\n";
                        sign = -1;
                        break;
                    }
                }
            }
            origin.direction.rotate(sign * angle);
            sign = 1;
        }
    }

    //        std::cout << "AFTER:" << originTop.direction << std::endl;

    //    stepLen = 20;
    //    next = originBottom.centre + stepLen * originBottom.direction;

    //    if(shape->inside(next.x, next.y))
    //    {
    //        originBottom.centre = next;
    //        lineBottom.lineTo(originBottom.centre.x, originBottom.centre.y);
    //    }
    //    else
    //    {
    //        originBottom.setRandomDirection();
    //    }
}

//--------------------------------------------------------------
void
ofApp::draw()
{

    ofSetColor(ofColor::black);
    //    ofFill();
    ofSetLineWidth(1);

    shape->path.draw();
    //    line.draw();

    //    shapeBottom->path.setColor(ofColor::orange);
    //    shapeBottom->path.setStrokeWidth(8);
    //    shapeBottom->path.setFilled(false);
    //    shapeBottom->path.draw();

    //    auto resampled = shapeBottom->path.getOutline()[0].getResampledBySpacing(10);
    //    for(auto& v : shapeBottom->getVertices())
    //    {
    //        ofNoFill();
    //        ofSetColor(ofColor::orange);
    //        ofDrawCircle(v, 20);
    //    }
    //    for(auto& v : resampled)
    //    {
    //        ofNoFill();
    //        ofSetColor(ofColor::red);
    //        ofDrawCircle(v, 20);
    //    }
    glm::vec3 start(origin.centre.x, origin.centre.y, 0), end(0);
    end = start + 30 * glm::vec3(origin.direction.x, origin.direction.y, 0);
    ofSetColor(ofColor::red);
    ofSetLineWidth(2);
    ofDrawArrow(start, end, 5);
    line.draw();

    //    lineBottom.draw();

    //    ofFill();
    //    ofSetColor(ofColor::red);
    //    ofDrawCircle(shape->getVertices()[245], 20);
    //    shape->path.draw();

    //    for(auto& v : shape->getVertices())

    //    {
    //        ofNoFill();
    //        ofSetColor(ofColor::black);
    //        ofDrawCircle(v, 20);
    //    }

    //    auto vertices = lineTop.getOutline()[0].getVertices();
    //    //    if(vertices.size() >= 2)
    //    //    {
    //    //        auto v1 = vertices[vertices.size() - 1];
    //    //        auto v2 = vertices[vertices.size() - 2];
    //    //        ofDrawArrow(glm::vec3(v2.x, v2.y, 0), glm::vec3(v1.x, v1.y, 0), 5.0);
    //    //    }
    //    for(auto& v : vertices)
    //    {
    //        ofSetColor(ofColor::black);
    //        ofDrawCircle(v, 2);
    //        glm::vec3 start(v.x, v.y, 0), end(0);
    //        end = start + 30 * glm::vec3(-1, -1, 0);
    //        ofSetColor(ofColor::red);
    //        ofDrawArrow(start, end, 5);
    //    }
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
