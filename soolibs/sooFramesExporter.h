#pragma once

#include "ofMain.h"

namespace soo
{

class FramesExporter
{
private:
    float start = 0; // time [s] or number of frames
    float end = 500; // time [s] or number of frames
    int saveImageCounter = 0;
    bool showDoneInfo = true;
    bool active = false;

public:
    FramesExporter() = default;

    void setStartAndEnd(const float _start, const float _end);
    void setEnd(const float _end);
    void setActive(const bool _active);

    void updateByTime(const float _elapsedTimeMillis);
    void updateByFrames(const float _currentFrameNum);

private:
    void update(const float _start,
                const float _end,
                const float _current,
                const std::string _units);
    void ofSaveFrame();
};

} // namespace soo
