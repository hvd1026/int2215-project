#pragma once

#include <SDL.h>
#include "../GameObject/Background.h"
#include "../GameObject/Player.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Enemy.h"
#include "../Collision/Collision.h"

class GamePage
{
public:
    bool gameOver;
    GamePage();
    ~GamePage();

    void init();
    void spawnEnemy();
    void update();
    void render();
    void clean();

    void showPlayerHealth();

private:
    Background *background;
    Player *player;
    Collision *collision;
};