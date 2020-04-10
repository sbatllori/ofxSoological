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
    FramesExporter(int _duration);
    void setActive(bool _active);

    void update(int elapsedTimeMillis);

private:
    void ofSaveFrame();
};

} // namespace soo
