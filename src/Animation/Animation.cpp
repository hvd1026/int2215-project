#include "Animation.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include <SDL.h>

Animation::Animation(int x, int y, int w, int h, int _frameCount, float _animationDuration, bool _loop)
{
    startX = x;
    startY = y;
    frameCount = _frameCount;
    animationDuration = _animationDuration;
    loop = _loop;
    isFinished = false;

    timePerFrame = animationDuration / frameCount;
    animationTimer = 0.0f;

    timer = TimeManager::getInstance();

    srcRect = {x, y, w, h};
}
Animation::~Animation()
{
}

void Animation::update()
{
    if (!isFinished)
    {
        animationTimer += timer->getDeltaTime();

        if (animationTimer >= animationDuration)
        {
            if (loop)
            {
                animationTimer -= animationDuration;
            }
            else
            {
                isFinished = true;
                animationTimer = animationDuration - timePerFrame; // keep stop at the last frame
            }
        }
        srcRect.x = startX + (int)(animationTimer / timePerFrame) * srcRect.w;
    }
}

SDL_Rect Animation::getSrcRect()
{
    return srcRect;
}