#include "Player.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"

#include <string>

Player::Player(int x, int y)
{
    xPos = x;
    yPos = y;
    velocity = PLAYER_SPEED;
    state = 2;

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
    // listen even => move and shoot



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

void Player::setState(int _state)
{
    state = _state;
}
