#include "EventManager.h"
#include <iostream>
EventManager *EventManager::instance = NULL;

EventManager::EventManager()
{
    keyState = SDL_GetKeyboardState(NULL);
}

EventManager *EventManager::getInstance()
{
    if (instance == NULL)
    {
        instance = new EventManager();
    }
    return instance;
}
bool EventManager::isKeyDown(SDL_Scancode key)
{
    return keyState[key];
}

void EventManager::onKeyDown()
{
    keyState = SDL_GetKeyboardState(NULL);
}

void EventManager::onKeyUp()
{
    keyState = SDL_GetKeyboardState(NULL);
}

void EventManager::clean()
{
    std::cout << "[INFO]: EventManager cleaned" << std::endl;
    delete instance;
    instance = NULL;
}