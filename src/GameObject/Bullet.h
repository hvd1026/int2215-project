#pragma once
#include "Bullet.h"
#include "../Animation/Animation.h"
#include <SDL.h>

class Bullet{
private:
    int xPos, yPos;
    int velocity;
    SDL_Rect dest;
    Animation* animate;
public:
    Bullet(int x, int y);
    ~Bullet();
    void update();
    void render();

    bool isActive;
};