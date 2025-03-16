#pragma once

#include <SDL.h>
#include <vector>
#include "../GameObject/Item.h"
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../GameObject/Bullet.h"
#include "../Animation/Animation.h"
#include <utility>

class Collision
{
public:
    int score;
    Collision(Player *player);
    ~Collision();
    void update();
    void render();
    void boom(int x, int y);

    bool isCollide(SDL_Rect obj1, SDL_Rect obj2);
    void playerVsEnemy(Player *player, Enemy *enemy);
    void bulletVsEnemy(Bullet *bullet, Enemy *enemy);
    void bulletVsPlayer(Bullet *bullet, Player *player);
    void enemyOutOfScreen(Enemy *enemy);
    void bulletVsBullet(Bullet *bullet1, Bullet *bullet2);
    void playerVsItem(Item *item);

private:
    Player *m_player;
    std::vector<std::pair<Animation*, SDL_Rect> > m_animations;
};