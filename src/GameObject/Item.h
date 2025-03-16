#pragma once
#include <SDL.h>
#include <vector>

class Item
{
public:
    Item(int x, int y);
    int type;
    bool isPickedUp;
    SDL_Rect bubbleDest, itemRect;
    void update();
    void render();

private:
    float xpos, ypos;
    float velocity;
    int randomType();
};

class ItemManager
{
private:
    ItemManager();
    static ItemManager *instance;
    static std::vector<Item *> items;

public:
    static ItemManager *getInstance();
    void update();
    void render();
    void clean();
    void addItem(Item *item);
    std::vector<Item *> getItems();
};