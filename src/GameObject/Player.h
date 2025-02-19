#pragma once

#include <SDL.h>
#include "../Animation/Animation.h"

class Player
{
private:
    int state; // 0 : straight, 1: left, 2: right
    int xPos, yPos;
    int velocity;
    SDL_Rect src[3];
    SDL_Rect shipDest;
    SDL_Rect boosterDest;
    Animation* boosterAnimation;
public:
    Player(int x, int y);
    ~Player();
    void update();
    void render();
    void setState(int _state);
};