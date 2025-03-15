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
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool running;
    
    int m_highScore;
    int recentScore;

    int currentPage; // current page of game
    bool hadBeenInited; // if page had been initialized
    bool firstTime; // first time render home page
};