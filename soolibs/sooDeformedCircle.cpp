#include "sooDeformedCircle.h"

namespace soo
{
void
DeformedCircle::generateRandom(const size_t numLayers, const float layerSpacing)
{
    paths.clear();
    paths.resize(numLayers);

    Radii radii = generateRandomRadii();

    for(size_t i = 0; i < numLayers; i++)
    {
        // Generate and add the path
        auto path = generatePath(radii);
        paths[i] = path;

        // Decrease the radii for the next layer
        for(size_t j = 0; j < radii.size(); j++)
            radii[j] -= layerSpacing;
    }
}

void
DeformedCircle::setDefaultDrawingSettings()
{
    for(auto& path : paths)
    {
        path.setFilled(true);
        path.setFillColor(ofColor::white);
        path.setStrokeColor(ofColor::black);
        path.setStrokeWidth(2);
        path.setCurveResolution(72);
    }
}

void
DeformedCircle::draw()
{
    for(auto& path : paths)
        path.draw();
}

Radii
DeformedCircle::generateRandomRadii()
{
    assert(resolution > 0);

    Radii radii;
    radii.resize(resolution);
    for(size_t i = 0; i < resolution; i++)
        radii[i] = ofRandom(minRadius, maxRadius);

    return radii;
}

ofPath
DeformedCircle::generatePath(const Radii& radii)
{
    assert(radii.size() == resolution);

    ofPath path;

    // Add the first point twice to avoid the straight line caused by OF when using path.moveTo
    float r = radii[0];
    addPolarPoint(path, r, 0);
    addPolarPoint(path, r, 0);

    // Add the points in between
    for(size_t i = 1; i < resolution; i++)
        addPolarPoint(path, radii[i], (1.f * i) / resolution);

    // Close the path the same way it was opened
    addPolarPoint(path, r, 0);
    addPolarPoint(path, r, 0);
    path.close();

    return path;
}

void
DeformedCircle::addPolarPoint(ofPath& path, const float r, const float theta)
{
    auto p = polarToCartesian(r, theta);
    path.curveTo(p);
}

ofVec2f
DeformedCircle::polarToCartesian(const float r, const float theta)
{
    auto x = position.x + r * cos(TWO_PI * theta);
    auto y = position.y + r * sin(TWO_PI * theta);
    return ofVec2f(x, y);
}
} // namespace soo
