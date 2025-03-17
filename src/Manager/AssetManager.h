#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string>
#include <map>

class AssetManager
{
    private:
        AssetManager();
        static AssetManager* sInstance;
        SDL_Renderer* mRenderer = nullptr;
        std::map<std::string, SDL_Texture*> mTextures;
        std::map<std::string, Mix_Chunk*> mSounds;
    public:
        static AssetManager* getInstance();
        void setRenderer(SDL_Renderer* renderer);
        void loadTexture(std::string id, std::string path);
        void loadAllTextures();
        void loadAllSounds();
        void draw(std::string id, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int playSound(std::string id, int loop); // return channel
        void stopSound(int channel);
        void clean();
};
