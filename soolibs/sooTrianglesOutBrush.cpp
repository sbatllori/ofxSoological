#include "sooTrianglesOutBrush.h"

namespace soo
{
void TrianglesOutBrush::draw(const ofVec2f& p)
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

        p1 += p + triangleOffset;
        p2 += p + triangleOffset;
        p3 += p + triangleOffset;

        ofColor col1(color1);
        ofColor col2(color2);
        ofColor col = col1.lerp(col2, ofRandom(1.0));
        ofSetColor(col, alpha);
        ofFill();
        ofDrawTriangle(p1, p2, p3);
    }
}
}
