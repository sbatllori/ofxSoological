#include "sooFramesExporter.h"

namespace soo
{

void
FramesExporter::setStartAndEnd(const float _start, const float _end)
{
    start = _start;
    end = _end;
}

void
FramesExporter::setEnd(const float _end)
{
    end = _end;
}

void
FramesExporter::setActive(bool _active)
{
    active = _active;
}

void
FramesExporter::updateByTime(const float _elapsedTimeMillis)
{
    update(1000 * start, 1000 * end, _elapsedTimeMillis, "s");
}

void
FramesExporter::updateByFrames(const float _currentFrameNum)
{
    update(start, end, _currentFrameNum, "frames");
}

void
FramesExporter::update(const float _start,
                       const float _end,
                       const float _current,
                       const std::string _units)
{
    if(active)
    {
        if(_current > _start && _current <= _end)
        {
            if(saveImageCounter == 0)
                std::cout << "[SOO INFO]\tStarting with frame exporting [" << _end - _start << " " << _units << "]\n";

            ofSaveFrame();
        }
        else if(_current >= _end)
        {
            if(showDoneInfo)
            {
                std::cout << "[SOO INFO]\tDone with frame exporting.\n";
                showDoneInfo = false;
            }
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
