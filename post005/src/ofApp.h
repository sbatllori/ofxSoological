#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"

// TODO move this to soolibs
namespace soo
{

class BezierLine
{
public:
    ofPath path;
    float x0, xf, y;
    std::vector<ofVec2f> intersectionPoints;

public:
    BezierLine(const float _x0, const float _xf, const float _y, const ofPolyline& other)
        : x0(_x0)
        , xf(_xf)
        , y(_y)
    {
        // Path drawing settings
        path.setFilled(false);
        path.setStrokeColor(255);
        path.setStrokeWidth(2);

        // Path geometry
        update(other);
    }

    void
    moveY(const float step, const float marginUp, const float marginDown, const ofPolyline& other)
    {
        // Handle extreme cases
        // a) moving down
        if(step > 0)
        {
            if(y >= marginDown)
                y = marginUp;
        }
        // b) moving up
        else
        {
            if(y <= marginUp)
                y = marginDown;
        }

        // Update y
        y += step;

        // Update line
        update(other);
        path.setStrokeColor(255 * y / ofGetHeight());
    }

private:
    void
    findIntersectionPoints(const ofPolyline& other)
    {
        // Consider the line segment inside the other's bounding box
        ofRectangle bbox = other.getBoundingBox();
        ofPolyline tmpLine;
        tmpLine.addVertex(bbox.x, y);
        tmpLine.addVertex(bbox.x + bbox.width, y);
        ofPolyline resampled = tmpLine.getResampledBySpacing(1);

        // Get the intersection points
        intersectionPoints.clear();
        for(int i = 0; i < resampled.size(); i++)
        {
            auto& p = resampled[i];
            auto& pNext = resampled[i + 1];

            bool bIn = other.inside(p);
            bool bNextIn = other.inside(pNext);

            if(bIn ^ bNextIn)
                intersectionPoints.push_back(p);
        }
    }

    void
    update(const ofPolyline& other)
    {
        path.clear();
        findIntersectionPoints(other);

        path.moveTo(x0, y);
        auto intersections = intersectionPoints.size();
        if(intersections > 0)
        {
            for(int i = 0; i < intersections - 1; i += 2)
            {
                auto& p = intersectionPoints[i];
                auto& pNext = intersectionPoints[i + 1];

                // Dynamic values depending on the distance between p and pNext
                float d = p.distance(pNext);
                float dx = 20;
                float dy = d / 10;

                // Line to first intersection point, and bezier line to the next one
                path.lineTo(p);
                path.bezierTo(p.x - dx, p.y - dy, pNext.x + dx, pNext.y - dy, pNext.x, pNext.y);
            }
        }
        path.lineTo(xf, y);
    }
};

} // namespace soo

class ofApp : public ofBaseApp
{

public:
    void setup();
    void update();
    void draw();

    // Frames Exporter
    soo::FramesExporter framesExporter;

    // Window dimensions
    float w, h;

    // Character
    const uint32_t character = '5';
    const string fontName = "FreeSans.ttf";
    ofTrueTypeFont font;
    ofPolyline characterPoly;

    // Lines
    size_t numLines;
    float wMargin, hMargin;
    std::vector<std::shared_ptr<soo::BezierLine>> lines;
};
