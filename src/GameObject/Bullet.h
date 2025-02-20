#pragma once
#include "Bullet.h"
#include "../Animation/Animation.h"

class Bullet{
private:
    int xPos, yPos;
    int velocity;
    int bulletType;
    SDL_Rect dest;
    Animation* animate;
    public:
    Bullet(int x, int y, int type);
    ~Bullet();
    void update();
    void render();
    
    int damage;
    bool isActive;
};