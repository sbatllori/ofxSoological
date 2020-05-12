#pragma once

#include "ofMain.h"
#include "sooTrianglesOutBrush.h"

namespace soo
{
struct HairyShape
{
    ofPolyline contour;
    TrianglesOutBrush brush;

    void drawRandom()
    {
        ofVec2f p = contour[ofRandom(contour.size())];
        brush.draw(p);
    }
};
} // namespace soo

class ofApp : public ofBaseApp
{
private:
    // Character
    const uint32_t character = '7';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;
    ofPolyline charPoly;

    // Hairy shapes
    soo::HairyShape seven;
    std::vector<soo::HairyShape> shapes;

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

private:
    void initRandomShapes();
};
