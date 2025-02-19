#include "Player.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"
#include "../Manager/EventManager.h"

#include <string>
#include <iostream>
#include <vector>

Player::Player(int x, int y)
{
    hp = PLAYER_HP;
    delayTime = PLAYER_SHOOT_DELAY;
    shootTimeCounter = PLAYER_SHOOT_DELAY;
    xPos = x;
    yPos = y;
    velocity = PLAYER_SPEED;
    state = 0;

    // Src rect
    boosterAnimation = new Animation(0, 0, 16, 16, 2, PLAYER_BOOSTER_TIME, true); // booster
    src[1] = {0, 0, 16, 16};                                                      // ship move left
    src[0] = {16, 0, 16, 16};                                                     // ship move straight
    src[2] = {32, 0, 16, 16};                                                     // ship move right

    // Dest rect
    shipDest = {xPos, yPos, PLAYER_SIZE, PLAYER_SIZE};
    boosterDest = {xPos, yPos + PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE};
}

Player::~Player()
{
    delete boosterAnimation;
    boosterAnimation = NULL;
}

void Player::update()
{
    boosterAnimation->update();
    shootTimeCounter += TimeManager::getInstance()->getDeltaTime();
    // listen even => move and shoot
    state = 0;
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_LEFT))
    {
        xPos -= velocity * TimeManager::getInstance()->getDeltaTime();
        state = 1;
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT))
    {
        xPos += velocity * TimeManager::getInstance()->getDeltaTime();
        state = 2;
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_UP))
    {
        yPos -= velocity * TimeManager::getInstance()->getDeltaTime();
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_DOWN))
    {
        yPos += velocity * TimeManager::getInstance()->getDeltaTime();
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        if (shootTimeCounter >= delayTime)
        {
            shoot();
            shootTimeCounter = 0.0f;
        }
    }

    // update dest rect
    boosterDest.x = xPos;
    boosterDest.y = yPos + PLAYER_SIZE;
    shipDest.x = xPos;
    shipDest.y = yPos;
}

void Player::render()
{
    std::string booster = "booster" + std::to_string(state);

    // Render ship and booster
    AssetManager::getInstance()->draw("player", src[state], shipDest);
    AssetManager::getInstance()->draw(booster, boosterAnimation->getSrcRect(), boosterDest);
}

void Player::shoot()
{
    std::cout << "Pew pew" << std::endl;
}
