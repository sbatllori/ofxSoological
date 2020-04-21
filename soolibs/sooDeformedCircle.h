#pragma once

#include "ofMain.h"

namespace soo
{

using Paths = std::vector<ofPath>;
using Radii = std::vector<float>;

class DeformedCircle
{
public:
    Paths paths;
    ofVec2f position;
    size_t resolution;
    float minRadius;
    float maxRadius;

public:
    DeformedCircle() = default;

    void generateRandom(const size_t numLayers, const float layerSpacing = 10.f);
    void setDefaultDrawingSettings();
    void draw();

private:
    Radii generateRandomRadii();
    ofPath generatePath(const Radii& radii);
    void addPolarPoint(ofPath& path, const float r, const float theta);
    ofVec2f polarToCartesian(const float r, const float theta);
};

} // namespace soo
