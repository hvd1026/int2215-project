#include "Bullet.h"
#include "../Animation/Animation.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include "../constants.h"
#include <SDL.h>
#include <iostream>
#include <vector>
BulletManager* BulletManager::instance = nullptr;
std::vector<Bullet*> BulletManager::bullets;

Bullet::Bullet(int x, int y, int type)
{
    xPos = x;
    yPos = y;
    bulletType = type;
    if (type == SLOW_BULLET)
    {
        velocity = SLOW_BULLET_SPEED;
        damage = SLOW_BULLET_DAMAGE;
        animate = new Animation(0, 0, 16, 16, 2, SLOW_BULLET_ANIMATION_TIME, false);
    }   
    else if (type == FAST_BULLET)
    {
        animate = new Animation(0, 0, 16, 16, 1, SLOW_BULLET_ANIMATION_TIME, false);
        damage = FAST_BULLET_DAMAGE;
        velocity = FAST_BULLET_SPEED;
    }
    dest = {xPos, yPos, BULLET_SIZE, BULLET_SIZE};
    isActive = true;
}

Bullet::~Bullet()
{
    // std::cout << "[INFO]: Bullet removed" << std::endl;
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
    if (bulletType == SLOW_BULLET)
        AssetManager::getInstance()->draw("slowBullet", animate->getSrcRect(), dest);
    else {
        AssetManager::getInstance()->draw("fastBullet", {0,0,16,16}, dest);
    }
}