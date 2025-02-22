#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>

#include "GameManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "EventManager.h"
#include "../constants.h"

#include "../Pages/GamePage.h"
#include "../Pages/HomePage.h"
GamePage *gamePage;
HomePage *homePage;

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
    currentPage = HOME_PAGE;
    hadBeenInited = false;
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

    // high score
    // m_highScore = 0;
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> m_highScore;
        file.close();
    }
    else{
        updateHighScore(0);
    }
    
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
    // init pages
    if (!hadBeenInited)
    {
        if (currentPage == GAME_PAGE)
        {
            gamePage = new GamePage();
            gamePage->init();
        }
        if (currentPage == HOME_PAGE)
        {
            homePage = new HomePage();
            homePage->init(m_highScore);
        }

        hadBeenInited = true;
    }
    // update pages
    if (currentPage == GAME_PAGE)
        gamePage->update();
    if (currentPage == HOME_PAGE)
        homePage->update();
    // change page
    if (currentPage == HOME_PAGE && hadBeenInited && homePage->startedGame)
    {
        changePage(GAME_PAGE);
    }
    if (currentPage == GAME_PAGE && hadBeenInited &&  gamePage->gameOver)
    {
        if (gamePage->lastScore > m_highScore)
        {
            updateHighScore(gamePage->lastScore);
        }
        changePage(HOME_PAGE);
    }

}
void GameManager::render()
{
    SDL_RenderClear(renderer);
    if (currentPage == GAME_PAGE && hadBeenInited)
        gamePage->render();
    if (currentPage == HOME_PAGE && hadBeenInited)
        homePage->render();
    SDL_RenderPresent(renderer);
}

void GameManager::clean()
{
    SDL_FreeSurface(favicon);
    favicon = NULL;

    if (currentPage == GAME_PAGE && hadBeenInited)
    {
        gamePage->clean();
        delete gamePage;
        gamePage = nullptr;
    }
    if (currentPage == HOME_PAGE && hadBeenInited)
    {
        homePage->clean();
        delete homePage;
        homePage = nullptr;
    }

    timer->clean();
    timer = NULL;
    AssetManager::getInstance()->clean();
    EventManager::getInstance()->clean();
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

void GameManager::changePage(int newPage)
{
    // clean old page
    if (currentPage == GAME_PAGE)
    {
        gamePage->clean();
        delete gamePage;
        gamePage = nullptr;
    }
    if (currentPage == HOME_PAGE)
    {
        homePage->clean();
        delete homePage;
        homePage = nullptr;
    }

    // switch to new page
    currentPage = newPage;
    hadBeenInited = false;
}

void GameManager::updateHighScore(int newHighScore)
{
    m_highScore = newHighScore;
    std::ofstream outFile("highscore.txt");
    if (outFile.is_open())
    {
        outFile << m_highScore;
        outFile.close();
    }
}