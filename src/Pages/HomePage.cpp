#include "HomePage.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/EventManager.h"
#include <iostream>
#include <string>
HomePage::HomePage()
{
    startedGame = false;
}

HomePage::~HomePage()
{
}

void HomePage::init(int _highScore)
{
    highScore = _highScore;
}
void HomePage::clean()
{
}
void HomePage::update()
{
    if (
        EventManager::getInstance()->isKeyDown(SDL_SCANCODE_SPACE))
    {
        startedGame = true;
    }
}
void HomePage::render()
{
    AssetManager::getInstance()->draw("bg1", {0, 0, 512, 512}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    AssetManager::getInstance()->draw("player", {16, 0, 16, 16}, {(SCREEN_WIDTH - PLAYER_SIZE) / 2, SCREEN_HEIGHT - 100, PLAYER_SIZE, PLAYER_SIZE});

    // show high score
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
    SDL_Rect dest = {0, 0, 48, 48};
    std::string tmp = std::to_string(highScore);
    int digitsCount = tmp.size();
    dest.y = SCREEN_HEIGHT - 200;
    dest.x = SCREEN_WIDTH / 2 - (digitsCount * 48) / 2 - (digitsCount - 1) * 12; // center the number
    for (int i = 0; i < digitsCount; i++)
    {
        int digit = tmp[i] - '0';
        AssetManager::getInstance()->draw("number", numberSrc[digit], dest);
        dest.x += 48 + 12;
    }
    AssetManager::getInstance()->draw("highscore", {0, 0, 450, 88}, {64, SCREEN_HEIGHT - 250, 160, 32});
}