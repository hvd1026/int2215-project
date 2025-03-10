#include <iostream>
#include <string>
#include <SDL.h>
#include <vector>
#include <cstdlib>
#include "Enemy.h"
#include "Bullet.h"
#include "../Animation/Animation.h"
#include "../constants.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"

std::vector<Enemy *> EnemyManager::enemies;
EnemyManager *EnemyManager::instance = nullptr;

Enemy::Enemy(std::string name, int x, int y, int _hp)
{
    m_Name = name;
    xpos = x;
    ypos = y;
    hp = _hp;
    timeCounter = -ENEMY_BULLET_DELAY;
    isActive = true;
    if (hp ==  1)
    {
        m_Rect = {(int)xpos, (int)ypos, 32, 32};
        velocity = ENEMY_SPEED_FAST;
    }
    else
    {
        velocity = ENEMY_SPEED_SLOW;
        m_Rect = {(int)xpos, (int)ypos, 64, 64};
    }

    if (name == "alan")
    {
        m_Animation = new Animation(0, 0, 16, 16, 6, ENEMY_ANIMATION_DURATION, true);
    }
    else if (name == "bonbon")
    {
        m_Animation = new Animation(0, 0, 16, 16, 4, ENEMY_ANIMATION_DURATION, true);
    }
    else
    {
        // name = lips
        m_Animation = new Animation(0, 0, 16, 16, 5, ENEMY_ANIMATION_DURATION, true);
    }
}

Enemy::~Enemy()
{
    delete m_Animation;
    m_Animation = nullptr;
}

void Enemy::update()
{
    timeCounter += TimeManager::getInstance()->getDeltaTime();
    if (timeCounter >= ENEMY_BULLET_DELAY)
    {
        int randomValue = rand() % 100 + 1;
        if (randomValue <= ENEMY_SHOOTING_PERCENTRATE)
        {
            shoot();
        }
        timeCounter = 0.0f;
    }

    if (isActive)
    {
        ypos += velocity * TimeManager::getInstance()->getDeltaTime();

        m_Animation->update();
    }
    m_Rect.x = (int)xpos;
    m_Rect.y = (int)ypos;
}

void Enemy::render()
{
    if (isActive)
    {
        AssetManager::getInstance()->draw(m_Name, m_Animation->getSrcRect(), m_Rect);
    }
}

void Enemy::shoot()
{
    BulletManager::getInstance()->addBullet(new Bullet(
        m_Rect.x, m_Rect.y + m_Rect.h, ENEMY_BULLET));
}
