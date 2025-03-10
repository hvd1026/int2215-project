#include "HomePage.h"
#include "../constants.h"
#include "../Manager/AssetManager.h"
#include "../Manager/EventManager.h"
#include "../Manager/TimeManager.h"
#include <iostream>
#include <string>
HomePage::HomePage()
{
    startedGame = false;
}

HomePage::~HomePage()
{
}

void HomePage::init(int _highScore, bool _firstTime, int _recentScore)
{
    highScore = _highScore;
    firstTime = _firstTime;
    recentScore = _recentScore;
    timer = 0.0f;
    startedGame = false;
}
void HomePage::clean()
{
}
void HomePage::update()
{
    timer += TimeManager::getInstance()->getDeltaTime();
    if (firstTime)
    {
        if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_SPACE))
        {
            startedGame = true;
        }
    }
    else{
        // when game over, player still press space => need delay
        if (EventManager::getInstance()->isKeyDown(SDL_SCANCODE_SPACE) && timer > 1.0f)
        {
            startedGame = true;
        }
    }

    if (timer > 100.0f) // prevent overflow
    {
        timer = 0.0f;
    }

}
void HomePage::render()
{
    AssetManager::getInstance()->draw("bg1", {0, 0, 512, 512}, {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT});
    AssetManager::getInstance()->draw("player", {16, 0, 16, 16}, {(SCREEN_WIDTH - PLAYER_SIZE) / 2, SCREEN_HEIGHT - 100, PLAYER_SIZE, PLAYER_SIZE});
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
    // game title or game over
    if (firstTime)
    {
        AssetManager::getInstance()->draw("title", {0, 0, 644, 78}, {SCREEN_WIDTH/2 - 384/2, 250, 384, 48});
    }
    else
    {
        AssetManager::getInstance()->draw("gameover", {0, 0, 72, 8}, {SCREEN_WIDTH/2 - 288/2, 50, 288, 32});
        // show recent score
        SDL_Rect tmpDest = {0, 0, 48, 48};
        std::string tmp = std::to_string(recentScore);
        int digitsCount = tmp.size();
        tmpDest.y = SCREEN_HEIGHT - 500;
        tmpDest.x = SCREEN_WIDTH / 2 - (digitsCount * 48) / 2 - (digitsCount - 1) * 12; // center the number
        for (int i = 0; i < digitsCount; i++)
        {
            int digit = tmp[i] - '0';
            AssetManager::getInstance()->draw("number", numberSrc[digit], tmpDest);
            tmpDest.x += 48 + 12;
        }
    }

    // show high score
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

    // press to play
    AssetManager::getInstance()->draw("press",{0, 0, 586, 61}, {SCREEN_WIDTH / 2 - 308/2, SCREEN_HEIGHT - 50, 308, 32});
}