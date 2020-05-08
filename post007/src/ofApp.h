#pragma once

#include "ofMain.h"

namespace soo
{
struct HairyShape
{
    ofColor color1, color2;
    ofPolyline contour;
    ofVec2f v1, v2, v3;
    int numTriangles;
    int minOffset;
    int maxOffset;
    int alpha;

    void
    drawStar()
    {
        ofVec2f pos = contour[ofRandom(contour.size())];
        drawStar(pos);
    }

    void
    drawStar(const ofVec2f& pos)
    {
        for(int t = 0; t < numTriangles; t++)
        {
            float offsetRadius = ofRandom(minOffset, maxOffset);

            // Define a triangle at the origin (0,0) that points to the right
            ofVec2f p1(v1);
            ofVec2f p2(v2);
            ofVec2f p3(v3);

            // Rotate the triangle points around the origin
            float rotation = ofRandom(360); // The rotate function uses degrees!
            p1.rotate(rotation);
            p2.rotate(rotation);
            p3.rotate(rotation);

            ofVec2f triangleOffset(offsetRadius, 0.0);
            triangleOffset.rotate(rotation);

            p1 += pos + triangleOffset;
            p2 += pos + triangleOffset;
            p3 += pos + triangleOffset;

            ofColor col1(color1);
            ofColor col2(color2);
            ofColor col = col1.lerp(col2, ofRandom(1.0));
            ofSetColor(col, alpha);
            ofFill();
            ofDrawTriangle(p1, p2, p3);
        }
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
    void initRandomShapes();

    // Character
    const uint32_t character = '7';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;
    ofPolyline charPoly;

    // Hairy shapes
    soo::HairyShape seven;
    std::vector<soo::HairyShape> shapes;
};
