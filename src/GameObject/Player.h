#pragma once

#include <SDL.h>
#include "../Animation/Animation.h"
#include "Bullet.h"
#include <vector>
class Player
{
private:
    int state; // 0 : straight, 1: left, 2: right
    int xPos, yPos;
    int velocity;
    float slowShootDelay, slowShootCounter;
    float fastShootDelay, fastShootCounter;
    int hp;
    SDL_Rect src[3];
    SDL_Rect shipDest;
    SDL_Rect boosterDest;
    Animation *boosterAnimation;

public:
    static std::vector<Bullet* > bullets;
    Player(int x, int y);
    ~Player();
    void update();
    void render();
    void shoot(int type);
    bool moveOutOfScreen(int direction);
};