#include "Manager/GameManager.h"
#include "Manager/TimeManager.h"
#include "constants.h"
#include <iostream>
int main(int argc, char *argv[])
{
    GameManager* game = new GameManager();
    TimeManager* timer = TimeManager::getInstance();
    while (game->isRunning()){
        timer->update();
        game->event();
        game->update();
        if (timer->getDeltaTime() >= (1.0f / FPS)){
            game->render();
            timer->reset();
        }
    }
    delete game;
    game = NULL;
    timer->clean();
    timer = NULL;
    return 0;
}