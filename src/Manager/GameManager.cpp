#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "../constants.h"

#include "../GameObject/Background.h"
// Background
Background *background = new Background();

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
    default:
        break;
    }
}

void GameManager::update()
{
    background->update();
}
void GameManager::render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    background->render();
    SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
    timer->clean();
    timer = NULL;

    AssetManager::getInstance()->clean();
    delete background;

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