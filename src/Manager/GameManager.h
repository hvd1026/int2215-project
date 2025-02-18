#pragma once

#include <SDL.h>
#include "TimeManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void init();
    void event();
    void update();
    void render();
    void clean();

    void run();

private:
    TimeManager *timer;
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
};