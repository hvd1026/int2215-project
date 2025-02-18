#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

void AssetManager::loadAllTextures()
{
    loadTexture("background", "assets/BG.png");
}


AssetManager::AssetManager()
{
    mRenderer = nullptr;
}

AssetManager* AssetManager::getInstance()
{
    if (sInstance == nullptr)
    {
        sInstance = new AssetManager();
    }

    return sInstance;
}

void AssetManager::setRenderer(SDL_Renderer* renderer)
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
    SDL_RenderCopyEx(mRenderer, mTextures[id], &src, &dest, 0, NULL, flip);
}

void AssetManager::dropTexture(std::string id)
{
    SDL_DestroyTexture(mTextures[id]);
    mTextures.erase(id);
}

void AssetManager::clean()
{
    std::cout << "[INFO]: AssetManager destroyed" << std::endl;
    for (auto const& i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }

    mTextures.clear();
    delete sInstance;
    sInstance = nullptr;
}
