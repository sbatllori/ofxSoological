#include "sooFramesExporter.h"

namespace soo
{

FramesExporter::FramesExporter(int _duration)
    : duration(_duration)
{}

void
FramesExporter::setActive(bool _active)
{
    active = _active;
}

void
FramesExporter::update(int elapsedTimeMillis)
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

void
FramesExporter::ofSaveFrame()
{
    string zeroes = "00000000";
    zeroes = zeroes.substr(0, zeroes.length() - (ofToString(saveImageCounter).length()));
    string fileName = "./frames/f" + zeroes + ofToString(saveImageCounter) + ".png";
    ofSaveViewport(fileName);
    saveImageCounter++;
}

} // namespace soo
