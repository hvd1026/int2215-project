#include "Bullet.h"
#include "../Animation/Animation.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include "../constants.h"
#include <SDL.h>
#include <iostream>
#include <vector>
BulletManager *BulletManager::instance = nullptr;
std::vector<Bullet *> BulletManager::bullets;

Bullet::Bullet(int x, int y, int type)
{
    xPos = (float)x;
    yPos = (float)y;
    bulletType = type;
    properties = BulletManager::getInstance()->bulletProperties[type];
    animate = new Animation(0, 0, 16, 16, properties.animationFrames, properties.animationTime, (bulletType == SQUARE_BULLET)); // loop if square bullet
    dest = {(int)xPos, (int)yPos, BULLET_SIZE, BULLET_SIZE};
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
    yPos -= properties.velocity * TimeManager::getInstance()->getDeltaTime();
    dest.y = yPos;

    // if bullet out of screen
    if (yPos < 0 || yPos > SCREEN_HEIGHT)
    {
        isActive = false;
    }
}

void Bullet::render()
{
    AssetManager::getInstance()->draw(properties.id, animate->getSrcRect(), dest);
}

// BulletManager

BulletManager::BulletManager()
{
    bulletProperties.resize(BULLET_TYPES_COUNT);
    // id, damage, velocity, shootDelay, maxTime, animationTime, animationFrames
    bulletProperties[DEFAULT_BULLET] = {"default_bullet", 1, 500.0f, 0.2f, 0.0f, 0.5f, 1};
    bulletProperties[CHARGED_BULLET] = {"charged_bullet", 10, 200.0f, 0.8f, 20.0f, 2.0f, 2};
    bulletProperties[CIRCLE_BULLET]  = {"circle_bullet", 1, 600.0f, 0.1f, 20.0f, 1.5f, 4};
    bulletProperties[SQUARE_BULLET]  = {"square_bullet", 3, 250.0f, 0.4f, 20.0f, 1.5f, 4};
    bulletProperties[ENEMY_BULLET]   = {"enemy_bullet", 1, -100.0f, 5.0f, 0.0f, 4.0f, 4};
}
BulletManager *BulletManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new BulletManager();
    }
    return instance;
}

void BulletManager::addBullet(Bullet *bullet)
{
    bullets.push_back(bullet);
}

std::vector<Bullet *> BulletManager::getBullets()
{
    return bullets;
}
void BulletManager::update()
{
    for (auto it = bullets.begin(); it != bullets.end(); it++)
    {
        (*it)->update();
        if (!(*it)->isActive)
        {
            delete (*it);
            bullets.erase(it);
            it--;
        }
    }
}
void BulletManager::render()
{
    for (auto it = bullets.begin(); it != bullets.end(); it++)
    {
        (*it)->render();
    }
}
void BulletManager::clean()
{
    for (auto bullet : bullets)
    {
        delete bullet;
    }
    bullets.clear();
    delete instance;
    instance = nullptr;
}