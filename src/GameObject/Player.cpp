#include "Player.h"
#include "Bullet.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"
#include "../Manager/EventManager.h"

#include <string>
#include <iostream>
#include <vector>

Player::Player(int x, int y)
{
    currentShootType = DEFAULT_BULLET;
    // player properties
    hp = PLAYER_HP;
    shootTimer = 0.0f;
    bulletTimer = 0.0f;
    xPos = (float)x;
    yPos = (float)y;
    velocity = PLAYER_SPEED;
    state = 0;

    // Src rect
    boosterAnimation = new Animation(0, 0, 16, 16, 2, PLAYER_BOOSTER_TIME, true); // booster
    src[1] = {0, 0, 16, 16};                                                      // ship move left
    src[0] = {16, 0, 16, 16};                                                     // ship move straight
    src[2] = {32, 0, 16, 16};                                                     // ship move right

    // Dest rect
    shipDest = {x, y, PLAYER_SIZE, PLAYER_SIZE};
    boosterDest = {x, y + PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE};
}

Player::~Player()
{
    delete boosterAnimation;
    boosterAnimation = NULL;
}

void Player::update()
{
    boosterAnimation->update();
    shootTimer += TimeManager::getInstance()->getDeltaTime();
    if (currentShootType != DEFAULT_BULLET) {
        bulletTimer += TimeManager::getInstance()->getDeltaTime();
        if (bulletTimer >= (BulletManager::getInstance()->bulletProperties[currentShootType]).maxTime) {
            currentShootType = DEFAULT_BULLET;
            bulletTimer = 0.0f;
        }
    }
    // listen even => move and shoot
    state = 0; // move direction state
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
    if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_SPACE) && shootTimer >= BulletManager::getInstance()->bulletProperties[currentShootType].shootDelay)
    {
        shoot(currentShootType);
        shootTimer = 0.0f;
    }
    // update dest rect
    boosterDest.x = (int)xPos;
    boosterDest.y = (int)yPos + PLAYER_SIZE;
    shipDest.x = (int)xPos;
    shipDest.y = (int)yPos;
}

void Player::render()
{
    std::string booster = "booster" + std::to_string(state);
    // Render ship and booster
    AssetManager::getInstance()->draw("player", src[state], shipDest);
    AssetManager::getInstance()->draw(booster, boosterAnimation->getSrcRect(), boosterDest);
}

void Player::shoot(int type)
{
    AssetManager::getInstance()->playSound("shoot", 0);
    BulletManager::getInstance()->addBullet(new Bullet(xPos + PLAYER_SIZE / 2 - BULLET_SIZE / 2, yPos, type));
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