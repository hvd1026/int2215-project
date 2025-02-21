#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include "GamePage.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"
#include "../Collision/Collision.h"
#include "../GameObject/Player.h"
#include "../GameObject/Background.h"
#include "../GameObject/Bullet.h"
#include "../GameObject/Enemy.h"

GamePage::GamePage()
{
    init();
}

GamePage::~GamePage()
{
}

void GamePage::init()
{
    std::cout << "[INFO]: GamePage loaded" << std::endl;
    background = new Background();
    player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
    collision = new Collision(player);
    gameOver = false;
    score = 0.0f;

    timmer = 0.0f;
    enemySpawnTime = ENEMY_SPAWN_TIME;
    bossSpawnRate = BOSS_SPAWN_RATE;

    lastDecreaseSpawnTime = 0;
    lastIncreaseSpawnRate = 0;
}
void GamePage::update()
{
    if (player->hp <= 0)
    {
        gameOver = true;
        lastScore = (int)score;
        return;
    }
    background->update();
    player->update();
    collision->update();
    BulletManager::getInstance()->update();
    EnemyManager::getInstance()->update();
    spawnEnemy();
    score += TimeManager::getInstance()->getDeltaTime() * SCORE_PER_SECOND;
}
void GamePage::render()
{
    background->render();
    BulletManager::getInstance()->render();
    EnemyManager::getInstance()->render();
    player->render();
    collision->render();

    showPlayerHealth();
    showScore();
}
void GamePage::clean()
{
    std::cout << "[INFO]: GamePage cleaned" << std::endl;
    EnemyManager::getInstance()->clean();
    BulletManager::getInstance()->clean();
    delete background;
    delete player;
    delete collision;
}

void GamePage::showPlayerHealth()
{
    int cnt = player->hp;
    if (cnt <= 0)
    {
        return;
    }
    SDL_Rect src, dest;
    src = {0, 0, 16, 16};
    dest = {10, 10, 24, 24};
    for (int i = 0; i < cnt; i++)
    {
        AssetManager::getInstance()->draw("playerHealth", src, dest);
        dest.x += 30;
    }
}

void GamePage::showScore()
{
    int scoreInt = (int)score;
    SDL_Rect dest;

    SDL_Rect numberSrc[10];
    numberSrc[0] = {32, 8, 8, 8};
    numberSrc[1] = {0, 0, 8, 8};
    numberSrc[2] = {8, 0, 8, 8};
    numberSrc[3] = {16, 0, 8, 8};
    numberSrc[4] = {24, 0, 8, 8};
    numberSrc[5] = {32, 0, 8, 8};
    numberSrc[6] = {0, 8, 8, 8};
    numberSrc[7] = {8, 8, 8, 8};
    numberSrc[8] = {16, 8, 8, 8};
    numberSrc[9] = {24, 8, 8, 8};

    dest = {SCREEN_WIDTH - 32, 10, 24, 24};
    while (scoreInt > 0)
    {
        int digit = scoreInt % 10;
        scoreInt /= 10;
        AssetManager::getInstance()->draw("number", numberSrc[digit], dest);
        dest.x -= 20;
    }
}

void GamePage::spawnEnemy()
{
    timmer += TimeManager::getInstance()->getDeltaTime();
    int scoreInt = (int)score; 
    if (timmer >= enemySpawnTime)
    {
        if (randomIsBoss()){
            EnemyManager::getInstance()->addEnemy(new Enemy(
                randomEnemyName(), randomXPos(), -64, randomHp(true)
            ));
        }else{
            EnemyManager::getInstance()->addEnemy(new Enemy(
                randomEnemyName(), randomXPos(), -32, randomHp(false)
            ));
        }
        timmer = 0.0f;   
    }
    // make game harder
    if (bossSpawnRate < MAX_BOSS_SPAWN_RATE && scoreInt % 10 == 0 && scoreInt != lastIncreaseSpawnRate)
    {
        bossSpawnRate += BOSS_INCREASE_RATE;
        lastIncreaseSpawnRate = scoreInt;
    }
    if (enemySpawnTime > MAX_ENEMY_SPAWN_TIME && scoreInt % 100 == 0 && scoreInt != lastDecreaseSpawnTime)
    {
        enemySpawnTime -= ENEMY_SPAM_DECREASE;
        lastDecreaseSpawnTime = scoreInt;
    }
}

std::string GamePage::randomEnemyName(){
    int random = rand() % 3;
    switch (random)
    {
    case 0:
        return "alan";
    case 1:
        return "bonbon";
    case 2:
        return "lips";
    default:
        return "alan";
    }
}

bool GamePage::randomIsBoss(){
    int random = rand() % 101;
    if (random <= BOSS_SPAWN_RATE)
    {
        return true;
    }
    return false;
}

int GamePage::randomHp(bool isBoos){
    if (isBoos)
    {
        return 10 + (rand() % 11); // from 10 to 20
    }
    return 1 + rand() % 3; // from 1 to 3
}

int GamePage::randomXPos(){
    return rand() % (SCREEN_WIDTH - 64);
}
