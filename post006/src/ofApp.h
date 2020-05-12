#pragma once

#include "ofMain.h"
#include "sooFramesExporter.h"

namespace soo
{
using Node = std::shared_ptr<ofNode>;
using Nodes = std::vector<Node>;

class DragonCurve
{
private:
    Nodes nodes;
    float length, angle;

public:
    ofPolyline line;

public:
    DragonCurve(const float _length = 10, const float _angle = 90)
        : length(_length)
        , angle(_angle)
    {}

    void generateRecursive(unsigned int it)
    {
        computeNextIteration();
        if(it == 0)
            return;
        generateRecursive(it - 1);
    }

    void drawStatic()
    {
        ofPushMatrix();
        {
            ofRectangle bbox = line.getBoundingBox();

            // Define scaling parameters
            float margin = 50;
            float W = ofGetWidth() - 2 * margin;
            float H = ofGetHeight() - 2 * margin;
            float scaleFactor;
            if(bbox.width > bbox.height)
                scaleFactor = W / bbox.width;
            else
                scaleFactor = H / bbox.height;

            // Define translation parameters
            float x = ofGetWidth() / 2 - scaleFactor * (bbox.x + bbox.width / 2);
            float y = ofGetHeight() / 2 - scaleFactor * (bbox.y + bbox.height / 2);

            ofTranslate(x, y);
            ofScale(scaleFactor);

            line.draw();
        }
        ofPopMatrix();
    }

private:
    void computeNextIteration()
    {
        if(nodes.empty())
        {
            Node root = std::make_shared<ofNode>();
            root->setPosition({0, 0, 0});
            nodes.push_back(root);
            line.addVertex(root->getGlobalPosition());

            Node node = std::make_shared<ofNode>();
            node->setParent(*root);
            node->setGlobalPosition({length, 0, 0});
            nodes.push_back(node);
            line.addVertex(node->getGlobalPosition());
        }
        else
        {
            Nodes copyNodes;
            Node root = std::make_shared<ofNode>();
            root->setPosition(nodes[nodes.size() - 1]->getGlobalPosition());
            root->setOrientation(nodes[nodes.size() - 1]->getGlobalOrientation());
            copyNodes.push_back(root);

            for(int i = nodes.size() - 2; i >= 0; i--)
            {
                Node node = std::make_shared<ofNode>();
                node->setParent(*root);
                node->setGlobalPosition(nodes[i]->getGlobalPosition());
                node->setGlobalOrientation(nodes[i]->getGlobalOrientation());
                copyNodes.push_back(node);
            }

            root->rotateDeg(angle, {0, 0, 1});

            for(size_t i = 0; i < copyNodes.size(); i++)
            {
                nodes.push_back(copyNodes[i]);
                line.addVertex(copyNodes[i]->getGlobalPosition());
            }
        }
    }
};
} // namespace soo

class ofApp : public ofBaseApp
{
private:
    soo::FramesExporter framesExporter;
    std::shared_ptr<soo::DragonCurve> dragonCurve;

public:
    void setup();
    void update();
    void draw();
};
