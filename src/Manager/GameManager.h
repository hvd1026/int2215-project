#pragma once

#include <SDL.h>
#include "TimeManager.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    void run();

private:
    void init();
    void event();
    void update();
    void render();
    void clean();
    TimeManager *timer;
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *favicon;
};