#include "AssetManager.h"
#include "../constants.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

AssetManager *AssetManager::sInstance = nullptr;

void AssetManager::loadAllTextures()
{
    // Backgrounds
    loadTexture("bg1", "assets/BG/1.png");
    loadTexture("bg2", "assets/BG/2.png");
    loadTexture("bg3", "assets/BG/3.png");
    loadTexture("bg4", "assets/BG/4.png");
    loadTexture("bg5", "assets/BG/5.png");
    loadTexture("bg6", "assets/BG/6.png");
    loadTexture("bg7", "assets/BG/7.png");
    loadTexture("bg8", "assets/BG/8.png");
    // Player
    loadTexture("player", "assets/Ship/Player_ship.png");
    loadTexture("booster0", "assets/Ship/Boosters.png");
    loadTexture("booster1", "assets/Ship/Boosters_left.png");
    loadTexture("booster2", "assets/Ship/Boosters_right.png");
    loadTexture("playerHealth", "assets/UI/heart.png");
    // Enemies
    loadTexture("alan", "assets/Enemies/Alan.png");
    loadTexture("bonbon", "assets/Enemies/Bon_Bon.png");
    loadTexture("lips", "assets/Enemies/Lips.png");
    // Bullets
    loadTexture("default_bullet", "assets/Bullets/default_bullet.png");
    loadTexture("charged_bullet", "assets/Bullets/charged_bullet.png");
    loadTexture("circle_bullet", "assets/Bullets/circle_bullet.png");
    loadTexture("square_bullet", "assets/Bullets/square_bullet.png");
    loadTexture("enemy_bullet", "assets/Bullets/enemy_bullet.png");
    // Effect
    loadTexture("boom", "assets/Effects/Explosion.png");
    // ui
    loadTexture("number", "assets/UI/Number.png");
    loadTexture("highscore", "assets/UI/Highscore.png");
    loadTexture("press", "assets/UI/press_to_play.png");
    loadTexture("gameover", "assets/UI/GAME_OVER.png");
    loadTexture("title", "assets/UI/game_title.png");
    loadTexture("frame", "assets/UI/frame.png");
    loadTexture("bubble", "assets/UI/bubble.png"); 
}

void AssetManager::loadAllSounds()
{
    mSounds["bgm"] = Mix_LoadWAV("assets/sound/bgm.wav");
    mSounds["shoot"] = Mix_LoadWAV("assets/sound/shoot.wav");
    mSounds["enemy_shoot"] = Mix_LoadWAV("assets/sound/enemy_shoot.wav");
    mSounds["explosion"] = Mix_LoadWAV("assets/sound/explosion.wav");
    mSounds["hit"] = Mix_LoadWAV("assets/sound/hit.wav");
    mSounds["item"] = Mix_LoadWAV("assets/sound/item.wav");
}

AssetManager::AssetManager()
{
    mRenderer = nullptr;
}

AssetManager *AssetManager::getInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new AssetManager();
    }

    return sInstance;
}

void AssetManager::setRenderer(SDL_Renderer *renderer)
{
    mRenderer = renderer;
}

void AssetManager::loadTexture(std::string id, std::string path)
{
    mTextures[id] = IMG_LoadTexture(mRenderer, path.c_str());
}

void AssetManager::draw(std::string id, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    if (mTextures[id] == nullptr)
    {
        std::cerr << "[ERROR]: Texture " << id << " not found" << std::endl;
        return;
    }
    SDL_RenderCopyEx(mRenderer, mTextures[id], &src, &dest, 0, NULL, flip = SDL_FLIP_NONE);
}

int AssetManager::playSound(std::string id, int loop)
{
    if (mSounds[id] == nullptr)
    {
        std::cerr << "[ERROR]: Sound " << id << " not found" << std::endl;
        return 0;
    }
    int channel = Mix_PlayChannel(-1, mSounds[id], loop);
    Mix_Volume(channel, DEFAULT_VOLUME);
    return channel;
}

void AssetManager::stopSound(int channel)
{
    Mix_HaltChannel(channel);
}

void AssetManager::clean()
{
    std::cout << "[INFO]: AssetManager destroyed" << std::endl;
    for (auto const &i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }

    for (auto const &i : mSounds)
    {
        Mix_FreeChunk(i.second);
    }

    mSounds.clear();
    mTextures.clear();
    delete sInstance;
    sInstance = nullptr;
}
