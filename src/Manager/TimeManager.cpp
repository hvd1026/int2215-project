#include "TimeManager.h"
#include <SDL.h>
#include <iostream>
TimeManager *TimeManager::instance = NULL;
TimeManager::TimeManager()
{
    reset();
    elapsedTime = 0;
    deltaTime = 0;
}

TimeManager::~TimeManager()
{
}

TimeManager *TimeManager::getInstance()
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
}

void TimeManager::update()
{
    elapsedTime = SDL_GetTicks() - startTime; // ms
    deltaTime = elapsedTime / 1000.0f;        // convert ms to s
}

float TimeManager::getDeltaTime()
{
    return deltaTime;
}
void TimeManager::clean()
{
    std::cout << "[INFO]: TimeManager destroyed" << std::endl;
    delete instance;
    instance = NULL;
}