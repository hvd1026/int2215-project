#pragma once

#include <SDL.h>
#include <vector>
#include "../GameObject/Player.h"
#include "../GameObject/Enemy.h"
#include "../GameObject/Bullet.h"

class Collision
{
public:
    Collision(Player* player, std::vector<Enemy*> enemies);
    ~Collision();
    void update();

    bool isCollide(SDL_Rect a, SDL_Rect b);
    bool playerVsEnemy(Player *player, Enemy *enemy);
    bool bulletVsEnemy(Bullet *bullet, Enemy *enemy);
    bool bulletVsPlayer(Bullet *bullet, Player *player);
private:
    
};