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
#include "../GameObject/Item.h"

GamePage::GamePage()
{
    // init();
}

GamePage::~GamePage()
{
}

void GamePage::init()
{
    background = new Background();
    player = new Player((SCREEN_WIDTH - PLAYER_SIZE) / 2, SCREEN_HEIGHT - 100);
    collision = new Collision(player);
    gameOver = false;
    score = 0;
    timer = 0.0f;

    enemySpawnTime = ENEMY_SPAWN_TIME;
    bossSpawnRate = BOSS_SPAWN_RATE;
    lastDecreaseSpawnTime = 0; // last score that decrease spawn time
    lastIncreaseSpawnRate = 0; // last score that increase spawn boss rate

    std::cout << "[INFO]: GamePage loaded" << std::endl;
}
void GamePage::update()
{
    if (player->hp <= 0)
    {
        gameOver = true;
        return;
    }
    background->update();
    player->update();
    BulletManager::getInstance()->update();
    EnemyManager::getInstance()->update();
    ItemManager::getInstance()->update();
    collision->update();
    spawnEnemy();
    score += collision->score;
}
void GamePage::render()
{
    background->render();
    BulletManager::getInstance()->render();
    EnemyManager::getInstance()->render();
    ItemManager::getInstance()->render();
    player->render();
    collision->render(); // only boom effect
    showPlayerHealth();
    showScore();
    showBulletType();
}
void GamePage::clean()
{
    EnemyManager::getInstance()->clean();
    BulletManager::getInstance()->clean();
    ItemManager::getInstance()->clean();
    delete background;
    delete player;
    delete collision;
    std::cout << "[INFO]: GamePage cleaned" << std::endl;
}

void GamePage::showPlayerHealth()
{
    SDL_Rect src, dest;
    src = {0, 0, 16, 16};
    dest = {10, 10, 24, 24};
    for (int i = 0; i < player->hp; i++)
    {
        AssetManager::getInstance()->draw("playerHealth", src, dest);
        dest.x += 30;
    }
}

void GamePage::showScore()
{
    int tmpScore = score;
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
    if (tmpScore == 0)
    {
        AssetManager::getInstance()->draw("number", numberSrc[0], dest);
    }
    else
        while (tmpScore > 0)
        {
            int digit = tmpScore % 10;
            tmpScore /= 10;
            AssetManager::getInstance()->draw("number", numberSrc[digit], dest);
            dest.x -= 20;
        }
}

void GamePage::showBulletType()
{
    // frame
    AssetManager::getInstance()->draw("frame", {0,0,512,512}, {SCREEN_WIDTH - 10 - 48+8, SCREEN_HEIGHT - 50-8, 48, 48});
    // bullet
    AssetManager::getInstance()->draw(BulletManager::getInstance()->bulletProperties[player->currentShootType].id, {0,0,16,16}, {SCREEN_WIDTH - 10 - 32, SCREEN_HEIGHT - 50, 32, 32});
}

void GamePage::spawnEnemy()
{
    timer += TimeManager::getInstance()->getDeltaTime();
    int tmpScore = (int)score;
    if (timer >= enemySpawnTime)
    {
        if (randomIsBoss())
        {
            EnemyManager::getInstance()->addEnemy(new Enemy(
                randomEnemyName(), randomXPos(), -64, randomHp()));
        }
        else
        {
            EnemyManager::getInstance()->addEnemy(new Enemy(
                randomEnemyName(), randomXPos(), -32, 1));
        }
        timer = 0.0f;
    }
    // make game harder
    if (bossSpawnRate < MAX_BOSS_SPAWN_RATE && tmpScore % 10 == 0 && tmpScore != lastIncreaseSpawnRate)
    {
        bossSpawnRate += BOSS_INCREASE_RATE;
        lastIncreaseSpawnRate = tmpScore;
    }
    if (enemySpawnTime > MAX_ENEMY_SPAWN_TIME && tmpScore % 100 == 0 && tmpScore != lastDecreaseSpawnTime)
    {
        enemySpawnTime -= ENEMY_SPAM_DECREASE;
        lastDecreaseSpawnTime = tmpScore;
    }
}

std::string GamePage::randomEnemyName()
{
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

bool GamePage::randomIsBoss()
{
    int random = rand() % 101;
    if (random <= BOSS_SPAWN_RATE)
    {
        return true;
    }
    return false;
}

int GamePage::randomHp()
{
    return 10 + (rand() % 11);
}

int GamePage::randomXPos()
{
    return rand() % (SCREEN_WIDTH - 64);
}
