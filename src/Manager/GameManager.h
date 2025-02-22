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
    void changePage(int newPage);
    void updateHighScore(int newHighScore);
    TimeManager *timer;
    bool running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *favicon;
    int currentPage;
    bool hadBeenInited;
    int m_highScore;
};