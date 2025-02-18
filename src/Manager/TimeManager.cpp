#include "TimeManager.h"
#include <SDL.h>

TimeManager* TimeManager::instance = NULL;
TimeManager::TimeManager()
{
    reset();
}

TimeManager::~TimeManager()
{
    delete instance;
    instance = NULL;
}

TimeManager* TimeManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new TimeManager();
    }
    return instance;
}

void TimeManager::reset()
{
    startTime = SDL_GetTicks();
    elapsedTime = 0;
    deltaTime = 0;
}

void TimeManager::update()
{
    elapsedTime = SDL_GetTicks() - startTime; // ms
    deltaTime = elapsedTime / 1000.0f; // convert ms to s
}

float TimeManager::getDeltaTime()
{
    return deltaTime;
}