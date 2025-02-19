#pragma once

#include <SDL.h>
#include "../constants.h"
class Background{
public:
    Background();
    ~Background();
    void render();
    void update();
private:
    SDL_Rect src;
    SDL_Rect dest[9];
    int scroll = BG_SCROLL;
    int tail;
};