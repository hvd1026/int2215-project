#include "Manager/GameManager.h"

int main(int argc, char *argv[])
{
    GameManager* game = new GameManager();
    game->run();
    delete game;
    game = NULL;
    return 0;
}