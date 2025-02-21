#pragma once
#include <SDL.h>
#include <string>
#include "../Manager/TimeManager.h"

class Animation
{
private:
    int startX;
    int startY;
    int frameCount;

    float animationTimer;
    float animationDuration;
    float timePerFrame;

    bool loop;

    TimeManager *timer;

    SDL_Rect srcRect;

public:
    bool isFinished;
    Animation(int x, int y, int w, int h, int _frameCount, float _animationDuration, bool _loop);
    ~Animation();
    void update();
    SDL_Rect getSrcRect();
};