#pragma once
#include <SDL.h>
#include <string>
#include "../Animation/Animation.h"
class Enemy
{
private:
    std::string m_Name;
    Animation *m_Animation;
    float velocity;
    float xpos;
    float ypos;

public:
    int hp;
    SDL_Rect m_Rect;
    bool isActive;
    Enemy(std::string name, int x, int y, int _hp);
    ~Enemy();
    void update();
    void render();
};