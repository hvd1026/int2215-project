#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <fstream>

#include "../constants.h"

#include "GameManager.h"
#include "TimeManager.h"
#include "AssetManager.h"
#include "EventManager.h"

#include "../Pages/GamePage.h"
#include "../Pages/HomePage.h"
GamePage *gamePage;
HomePage *homePage;

GameManager::GameManager()
{
    init();
}

GameManager::~GameManager()
{
    clean();
    std::cout << "[INFO]: GameManager destroyed" << std::endl;
}

void GameManager::init()
{
    window = NULL;
    renderer = NULL;
    running = 0;
    currentPage = HOME_PAGE; // default is homepage
    hadBeenInited = false;
    firstTime = true;
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
        return;
    }
    std::cout << "[INFO]: Game started successfully" << std::endl;
    // Create instances of managers
    TimeManager::getInstance();
    EventManager::getInstance();
    AssetManager::getInstance()->setRenderer(renderer);
    AssetManager::getInstance()->loadAllTextures();

    // Load high score from file
    std::ifstream file("highscore.txt");
    if (file.is_open())
    {
        file >> m_highScore;
        file.close();
    }
    else
    {
        updateHighScore(0);
    }

    // random
    srand(time(0));
}

void GameManager::event()
{
    SDL_Event ev;
    SDL_PollEvent(&ev);
    switch (ev.type)
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
            homePage->init(m_highScore, firstTime, recentScore);
        }

        hadBeenInited = true;
    }
    // update pages
    if (currentPage == HOME_PAGE)
        homePage->update();
    if (currentPage == GAME_PAGE)
    {
        firstTime = false;
        gamePage->update();
    }
    // change page
    if (currentPage == HOME_PAGE && hadBeenInited && homePage->startedGame)
    {
        changePage(GAME_PAGE);
    }
    if (currentPage == GAME_PAGE && hadBeenInited && gamePage->gameOver)
    {
        if (gamePage->score > m_highScore)
        {
            updateHighScore(gamePage->score);
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

    TimeManager::getInstance()->clean();
    EventManager::getInstance()->clean();
    AssetManager::getInstance()->clean();
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
    SDL_Quit();
    IMG_Quit();
}


void GameManager::changePage(int newPage)
{
    // clean old page
    if (currentPage == GAME_PAGE)
    {
        recentScore = gamePage->score;
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

void GameManager::run()
{
    while (running)
    {
        TimeManager::getInstance()->update(); // update delta time
        event();
        if (TimeManager::getInstance()->getDeltaTime() >= (1.0f / FPS)) // limit game's fps
        {
            update();                            // update game
            render();                            // render everything
            TimeManager::getInstance()->reset(); // reset delta time
        }
    }
}