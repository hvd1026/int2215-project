#pragma once
#include <SDL.h>

// unique, accessible
class TimeManager
{
private:
    static TimeManager* instance;
    Uint32 startTime;
    Uint32 elapsedTime;
    float deltaTime;
    TimeManager();
public:
    ~TimeManager();
    static TimeManager* getInstance();
    void reset();
    void update();
    void clean();
    float getDeltaTime();
};