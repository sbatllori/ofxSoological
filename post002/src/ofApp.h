#pragma once

#include "ofMain.h"
#include "sooParticle.h"

namespace soo
{

struct Shape
{
    ofPath path;

    Shape() = default;

    Shape(ofPath& _path)
    {
        path = _path;
    }

    ofRectangle
    getBoundingBox()
    {
        // TODO careful. with the 0-element
        return path.getOutline()[0].getBoundingBox();
    }

    std::vector<ofVec2f>
    getVertices()
    {
        std::vector<ofVec2f> vertices;

        // TODO careful. with the 0-element
        for(auto& v : path.getOutline()[0].getVertices())
        {
            vertices.push_back(ofVec2f(v.x, v.y));
        }
        return vertices;
    }

    bool
    inside(const float x, const float y)
    {
        return path.getOutline()[0].inside(x, y);
    }

    void
    toCenter()
    {
        auto bbox = getBoundingBox();
        float x = ofGetWindowWidth() / 2 - bbox.width / 2;
        float y = ofGetWindowHeight() / 2 + bbox.height / 2;
        path.translate(ofVec2f(x, y));
    }
};

} // namespace soo

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    const uint32_t character = '2';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;

    std::unique_ptr<soo::Shape> shape;
    ofPolyline shapeBottom, shapeEnd;
    soo::Particle origin;
    ofPath line;
    int sign = 1;
    float angle = 60;
    ofVec2f lastUsedDir;
};
