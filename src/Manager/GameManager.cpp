#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "EventManager.h"
#include "../constants.h"

// Background
#include "../GameObject/Background.h"
Background *background = new Background();
// Player
#include "../GameObject/Player.h"
Player *player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100);
#include <vector>

GameManager::GameManager()
{
    window = NULL;
    renderer = NULL;
    running = 0;
    init();
}

GameManager::~GameManager()
{
    clean();
    std::cout << "[INFO]: GameManager destroyed" << std::endl;
}

void GameManager::init()
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        // Create window and renderer
        window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (window)
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer)
            {
                running = 1;
            }
        }
        // init sdl_image
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        {
            running = false;
        }
    }

    if (!running)
    {
        std::cerr << "[ERROR]: " << SDL_GetError() << std::endl;
    }
    std::cout << "[INFO]: Game started successfully" << std::endl;
    // favicon
    favicon = IMG_Load("assets/UI/Player_life_icon.png");
    SDL_SetWindowIcon(window, favicon);
    // timer
    timer = TimeManager::getInstance();

    // asset manager
    AssetManager::getInstance()->setRenderer(renderer);
    AssetManager::getInstance()->loadAllTextures();
}

void GameManager::event()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        running = 0;
        break;
    case SDL_KEYDOWN:
        EventManager::getInstance()->onKeyDown();
        break;
    case SDL_KEYUP:
        EventManager::getInstance()->onKeyUp();
        break;
    default:
        break;
    }
}

void GameManager::update()
{
    background->update();
    player->update();
    std::cout << player->bullets.size() << std::endl;
}
void GameManager::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    background->render();
    player->render();
    SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
    SDL_FreeSurface(favicon);
    favicon = NULL;

    timer->clean();
    timer = NULL;

    AssetManager::getInstance()->clean();

    EventManager::getInstance()->clean();
    
    delete background;
    delete player;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
    IMG_Quit();
}

void GameManager::run()
{
    while (running)
    {
        timer->update(); // update delta time
        event();
        if (timer->getDeltaTime() >= (1.0f / FPS)) // limit game's fps
        {
            update();       // update game
            render();       // render everything
            timer->reset(); // reset delta time
        }
    }
}