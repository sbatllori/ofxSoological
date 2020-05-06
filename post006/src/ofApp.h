#pragma once

#include "ofMain.h"

namespace soo
{
using Node = std::shared_ptr<ofNode>;
using Nodes = std::vector<Node>;

class DragonCurve
{
public:
    ofPolyline line;
    Nodes nodes;
    float length = 10;
    float deg = 90;

public:
    void
    generate(unsigned int iterations)
    {
        for(int it = 0; it < iterations; it++)
            computeNextIteration();
    }

private:
    void
    computeNextIteration()
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

            root->rotateDeg(deg, {0, 0, 1});

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

    //    ofPolyline line;
    unsigned long iterations;
    soo::DragonCurve dragonCurve;
};
