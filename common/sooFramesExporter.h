#pragma once

#include "ofMain.h"

namespace soo
{
class FramesExporter;
using FramesExporterPtr = std::unique_ptr<FramesExporter>;

class FramesExporter
{
private:
    int duration;
    int epsilon = 100;
    int saveImageCounter = 0;
    bool showDoneInfo = true;
    bool active = false;

public:
    FramesExporter(int _duration)
        : duration(_duration)
    {}

    void
    setActive(bool _active)
    {
        active = _active;
    }

    void
    update(int elapsedTimeMillis)
    {
        if(active)
        {
            if(elapsedTimeMillis > epsilon && elapsedTimeMillis < 1000 * duration + epsilon)
            {
                if(saveImageCounter == 0)
                    std::cout << "[SOO INFO]\tStarting with frame exporting [" << duration << "s]\n";

                ofSaveFrame();
            }
            else
            {
                if(showDoneInfo)
                    std::cout << "[SOO INFO]\tDone with frame exporting.\n";
                showDoneInfo = false;
            }
        }
    }

private:
    void
    ofSaveFrame()
    {
        string zeroes = "00000000";
        zeroes = zeroes.substr(0, zeroes.length() - (ofToString(saveImageCounter).length()));
        string fileName = "./frames/f" + zeroes + ofToString(saveImageCounter) + ".png";
        ofSaveViewport(fileName);
        saveImageCounter++;
    }
};
} // namespace soo
