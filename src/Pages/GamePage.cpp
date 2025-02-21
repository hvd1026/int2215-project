#include <SDL.h>
#include <iostream>
#include "GamePage.h"
#include "../constants.h"
#include "../GameObject/Player.h"
#include "../Collision/Collision.h"
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
}
void GamePage::update()
{
    background->update();
    BulletManager::getInstance()->update();
    EnemyManager::getInstance()->update();
    player->update();
    collision->update();
}
void GamePage::render()
{
    background->render();
    BulletManager::getInstance()->render();
    EnemyManager::getInstance()->render();
    player->render();
    collision->render();
}
void GamePage::clean()
{
    EnemyManager::getInstance()->clean();
    BulletManager::getInstance()->clean();
    delete background;
    delete player;
    delete collision;
}