#include "Manager/GameManager.h"

int main(int argc, char *argv[])
{
    GameManager* game = new GameManager();
    while (game->isRunning()){
        game->event();
        game->update();
        game->render();
    }
    delete game;
    return 0;
}