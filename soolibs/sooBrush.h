#pragma once

#include "ofMain.h"

namespace soo {
class Brush
{
public:
    Brush() = default;
    virtual ~Brush() = default;

    virtual void draw(const ofVec2f& p) = 0;
};
}
