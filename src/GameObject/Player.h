#pragma once

#include <SDL.h>
#include "../Animation/Animation.h"
#include "Bullet.h"
class Player
{
private:
    int state; // 0 : straight, 1: left, 2: right
    int xPos, yPos;
    int velocity;
    float shootDelay, shootTimmer;
    int currentShootType;
    SDL_Rect src[3];
    SDL_Rect boosterDest;
    Animation *boosterAnimation;

public:
    int hp;
    SDL_Rect shipDest;
    Player(int x, int y);
    ~Player();
    void update();
    void render();
    void shoot(int type);
    bool moveOutOfScreen(int direction);
};