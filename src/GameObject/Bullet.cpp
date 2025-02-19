#include "Bullet.h"
#include "../Animation/Animation.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include "../constants.h"
#include <SDL.h>
#include <iostream>

Bullet::Bullet(int x, int y)
{
    xPos = x;
    yPos = y;
    velocity = BULLET_SPEED;
    animate = new Animation(0, 0, 16, 16, 2, BULLET_ANIMATION_TIME, false);
    dest = {xPos, yPos, BULLET_SIZE, BULLET_SIZE};
    isActive = true;
}

Bullet::~Bullet()
{
    delete animate;
    animate = NULL;
}

void Bullet::update()
{
    animate->update();
    yPos -= velocity * TimeManager::getInstance()->getDeltaTime();
    dest.y = yPos;

    // if bullet out of screen
    if (yPos < 0)
    {
        isActive = false;
    }
}

void Bullet::render()
{
    AssetManager::getInstance()->draw("playerBullet", animate->getSrcRect(), dest);
}