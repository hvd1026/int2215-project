#include <SDL.h>
#include <vector>
#include <math.h>
#include <iostream>
#include <algorithm>
#include "Collision.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Item.h"
#include "../Manager/AssetManager.h"
#include "../constants.h"

Collision::Collision(Player *player)
{
    m_player = player;
}

Collision::~Collision()
{
    for (auto animation : m_animations)
    {
        delete animation.first;
    }
    m_animations.clear();
}

void Collision::update()
{
    score = 0;
    for (auto it = m_animations.begin(); it != m_animations.end();)
    {
        it->first->update();
        if (it->first->isFinished)
        {
            delete it->first;
            it = m_animations.erase(it);
        }
        else
        {
            it++;
        }
    }

    for (auto enemy : EnemyManager::getInstance()->getEnemies())
    {
        playerVsEnemy(m_player, enemy);
        enemyOutOfScreen(enemy);
        for (auto bullet : BulletManager::getInstance()->getBullets())
        {
            bulletVsEnemy(bullet, enemy);
        }
    }
    for (auto bullet : BulletManager::getInstance()->getBullets())
    {
        bulletVsPlayer(bullet, m_player);
    }

    for (auto bullet1 : BulletManager::getInstance()->getBullets())
    {
        for (auto bullet2 : BulletManager::getInstance()->getBullets())
        {
            bulletVsBullet(bullet1, bullet2);
        }
    }

    for (auto item : ItemManager::getInstance()->getItems())
    {
        playerVsItem(item);
    }
}

void Collision::render()
{

    for (auto it = m_animations.begin(); it != m_animations.end(); it++)
    {
        AssetManager::getInstance()->draw("boom", it->first->getSrcRect(), it->second);
    }
}

void Collision::boom(int x, int y)
{
    m_animations.push_back({new Animation(0, 0, 16, 16, 6, BOOM_ANIMATION_TIME, false), {x, y, 32, 32}});
}

bool Collision::isCollide(SDL_Rect obj1, SDL_Rect obj2)
{
    // change pos
    obj1.x += obj1.w / 2;
    obj1.y += obj1.h / 2;
    obj2.x += obj2.w / 2;
    obj2.y += obj2.h / 2;
    // aabb algorithm
    float dx = fabs(obj1.x - obj2.x) - (obj1.w + obj2.w) / 2.0f;
    float dy = fabs(obj1.y - obj2.y) - (obj1.h + obj2.h) / 2.0f;
    if (dx <= 0.0f && dy <= 0.0f)
    {
        return true;
    }

    return false;
}

void Collision::playerVsEnemy(Player *player, Enemy *enemy)
{
    if (isCollide(player->shipDest, enemy->m_Rect))
    {
        enemy->isActive = false;
        player->hp -= 1;
        boom(enemy->m_Rect.x, enemy->m_Rect.y);
        boom(player->shipDest.x, player->shipDest.y);
    }
}

void Collision::bulletVsEnemy(Bullet *bullet, Enemy *enemy)
{
    SDL_Rect temp = enemy->m_Rect;
    temp.y -= temp.h / 4; // because enemy is smaller than box
    if (bullet->bulletType != ENEMY_BULLET)
        if (isCollide(bullet->dest, temp))
        {
            score += std::min(enemy->hp, (bullet->properties).damage);
            bullet->isActive = false;
            enemy->hp -= (bullet->properties).damage;
            if (enemy->hp <= 0)
            {
                boom(enemy->m_Rect.x, enemy->m_Rect.y);
                enemy->isActive = false;
            }
        }
}

void Collision::bulletVsPlayer(Bullet *bullet, Player *player)
{
    if (bullet->bulletType == ENEMY_BULLET)
        if (isCollide(bullet->dest, player->shipDest))
        {
            bullet->isActive = false;
            player->hp -= (bullet->properties).damage;
            boom(player->shipDest.x, player->shipDest.y);
        }
}

void Collision::enemyOutOfScreen(Enemy *enemy)
{
    if (enemy->m_Rect.y + enemy->m_Rect.h / 2 > SCREEN_HEIGHT)
    {
        m_player->hp -= 1;
        enemy->isActive = false;
    }
}

void Collision::bulletVsBullet(Bullet *bullet1, Bullet *bullet2)
{
    if (isCollide(bullet1->dest, bullet2->dest) && bullet1->bulletType == ENEMY_BULLET && (bullet2->bulletType != ENEMY_BULLET))
    {
        bullet1->isActive = false;
        bullet2->isActive = false;
        boom(bullet1->dest.x, bullet1->dest.y);
        score += (bullet1->properties).damage;
    }
}

void Collision::playerVsItem(Item *item)
{
    if (isCollide(m_player->shipDest, item->bubbleDest))
    {
        item->isPickedUp = true;
        if (item->type == HEART_ITEM){
            if (m_player->hp < 3) {
                m_player->hp += 1;
            }
        }
        else {
            m_player->currentShootType = item->type;
            m_player->bulletTimer = 0.0f; // reset on change bullet type
        }
    }
}