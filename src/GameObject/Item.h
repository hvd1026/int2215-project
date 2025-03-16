#pragma once
#include <SDL.h>

class Item
{
public:
    Item(int x, int y);
    int type;
    float xpos, ypos;
    float velocity;
    bool isPickedUp;
    SDL_Rect bubbleDest, itemRect;
    void update();
    void render();

private:
    int randomType();
};

