#pragma once

#include "sooBrush.h"

namespace soo {
class TrianglesOutBrush : Brush
{
public:
    ofColor color1, color2;
    ofVec2f v1, v2, v3;
    int numTriangles;
    int minOffset;
    int maxOffset;
    int alpha;

public:
    void draw(const ofVec2f& p);
};
}
