#include "Player.h"
#include "Bullet.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"
#include "../Manager/EventManager.h"

#include <string>
#include <iostream>
#include <vector>

std::vector<Bullet *> bullets;

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
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        (*it)->update();
        if (!(*it)->isActive)
        {
            std::cout << "delete bullet" << std::endl;
            delete *it;
            it = bullets.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Player::update()
{
    boosterAnimation->update();
    shootTimeCounter += TimeManager::getInstance()->getDeltaTime();
    // listen even => move and shoot
    state = 0;
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_LEFT) && !moveOutOfScreen(MOVE_LEFT))
    {
        // left
        xPos -= velocity * TimeManager::getInstance()->getDeltaTime();
        state = 1;
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_RIGHT) && !moveOutOfScreen(MOVE_RIGHT))
    {
        // right
        xPos += velocity * TimeManager::getInstance()->getDeltaTime();
        state = 2;
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_UP) && !moveOutOfScreen(MOVE_UP))
    {
        // up
        yPos -= velocity * TimeManager::getInstance()->getDeltaTime();
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_DOWN) && !moveOutOfScreen(MOVE_DOWN))
    {
        // down
        yPos += velocity * TimeManager::getInstance()->getDeltaTime();
    }
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_X))
    {
        if (shootTimeCounter >= delayTime)
        {
            shoot();
            shootTimeCounter = 0.0f;
        }
    }

    // bullets
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        (*it)->update();
        if (!(*it)->isActive)
        {
            delete *it;
            it = bullets.erase(it);
        }
        else
        {
            ++it;
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

    // bullets
    for (auto it = bullets.begin(); it != bullets.end();it++)
    {
        (*it)->render();
    }

    // Render ship and booster
    AssetManager::getInstance()->draw("player", src[state], shipDest);
    AssetManager::getInstance()->draw(booster, boosterAnimation->getSrcRect(), boosterDest);
}

void Player::shoot()
{
    bullets.push_back(new Bullet(xPos + PLAYER_SIZE / 2 - BULLET_SIZE / 2, yPos));
}

bool Player::moveOutOfScreen(int direction)
{

    switch (direction)
    {
    case MOVE_RIGHT:
        // right:
        if (xPos + velocity * TimeManager::getInstance()->getDeltaTime() + PLAYER_SIZE >= SCREEN_WIDTH)
        {
            return true;
        }
        break;
    case MOVE_LEFT:
        // left:
        if (xPos - velocity * TimeManager::getInstance()->getDeltaTime() <= 0)
        {
            return true;
        }
        break;
    case MOVE_UP:
        // up:
        if (yPos - velocity * TimeManager::getInstance()->getDeltaTime() <= 0)
        {
            return true;
        }
        break;
    case MOVE_DOWN:
        // down:
        if (yPos + velocity * TimeManager::getInstance()->getDeltaTime() + PLAYER_SIZE >= SCREEN_HEIGHT)
        {
            return true;
        }
        break;
    }

    return false;
}