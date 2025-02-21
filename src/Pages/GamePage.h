#pragma once

#include <SDL.h>
#include <iostream>
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
    void update();
    void render();
    void clean();
    
    void showPlayerHealth();
    void showScore();
    void spawnEnemy();

private:
    float score;
    float timmer;

    int bossSpawnRate;
    int lastIncreaseSpawnRate;
    float enemySpawnTime;
    int lastDecreaseSpawnTime;
    Background *background;
    Player *player;
    Collision *collision;

    std::string randomEnemyName();
    bool randomIsBoss();
    int randomHp(bool isBoos);
    int randomXPos();
};

