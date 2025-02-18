#pragma once

#include <SDL.h>

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
    bool isRunning(){ return running; };

private:
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;   
};