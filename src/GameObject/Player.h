#pragma once

#include <SDL.h>
#include "../Animation/Animation.h"
#include "Bullet.h"
class Player
{
private:
    int state; // 0 : straight, 1: left, 2: right
    float xPos, yPos;
    float velocity;
    float shootTimer; // time from last shoot
    SDL_Rect src[3]; // ship move left, straight, right
    SDL_Rect boosterDest;
    Animation *boosterAnimation;

public:
    int currentShootType;
    float bulletTimer; // time from last bullet change
    int hp;
    SDL_Rect shipDest;
    Player(int x, int y);
    ~Player();
    void update();
    void render();
    void shoot(int type);
    bool moveOutOfScreen(int direction);
};