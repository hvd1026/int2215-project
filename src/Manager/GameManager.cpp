#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "GameManager.h"
#include "../constants.h"

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
}

void GameManager::init(){
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        // Create window and renderer
        window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
        if (window){
            renderer = SDL_CreateRenderer(window, -1, 0);
            if (renderer){
                running = 1;
            }
        }
        // init sdl_image
        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            running = false;
        }
    }

    if (!running) {
        std::cerr << "[ERROR]: " << SDL_GetError() << std::endl;
    }
}

void GameManager::event(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            running = 0;
            break;
        default:
            break;
    }
}

void GameManager::update(){
}
void GameManager::render(){
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    


    SDL_RenderPresent(renderer);
}

void GameManager::clean(){
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
    IMG_Quit();
}