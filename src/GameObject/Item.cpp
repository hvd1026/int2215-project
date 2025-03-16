#include "Item.h"
#include <cstdlib>
#include <SDL.h>
#include <iostream>
#include <vector>
#include "../constants.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include "Bullet.h"

ItemManager *ItemManager::instance = nullptr;
std::vector<Item *> ItemManager::items;

Item::Item(int x, int y)
{
    xpos = x;
    ypos = y;
    velocity = ITEM_VELOCITY;
    type = randomType();
    isPickedUp = false;
    bubbleDest = {x, y, BUBBLE_SIZE, BUBBLE_SIZE};
    itemRect = {x + 4, y + 4, ITEM_SIZE, ITEM_SIZE};
}

void Item::update()
{
    ypos += velocity * TimeManager::getInstance()->getDeltaTime();
    bubbleDest.y = (int)ypos;
    itemRect.y = bubbleDest.y + 4;
    if (ypos > SCREEN_HEIGHT)
    {
        isPickedUp = true;
    }
}

void Item::render()
{
    AssetManager::getInstance()->draw("bubble", {0, 0, 16, 16}, bubbleDest);
    if (type < 5)
    {
        AssetManager::getInstance()->draw((BulletManager::getInstance()->bulletProperties[type]).id, {0, 0, 16, 16}, itemRect);
    }
    else
    {
        AssetManager::getInstance()->draw("playerHealth", {0, 0, 16, 16}, itemRect);
    }
}

int Item::randomType()
{
    int randNum;
    int randomValue = rand() % 100 + 1; // Random value between 1 and 100

    if (randomValue <= 10)
    { // 10% health item
        randNum = 5;
    }
    else
    {                         // 90% chance bullet
        randNum = rand() % 3 + 1; // 1->3
    }
    return randNum;
}

ItemManager::ItemManager()
{
}

ItemManager *ItemManager::getInstance()
{
    if (instance == nullptr)
    {
        instance = new ItemManager();
    }
    return instance;
}
void ItemManager::update()
{
    for (auto it = items.begin(); it != items.end(); it++)
    {
        (*it)->update();
        if ((*it)->isPickedUp)
        {
            delete (*it);
            items.erase(it);
            it--;
        }
    }
}

void ItemManager::render()
{
    for (auto it = items.begin(); it != items.end(); it++)
    {
        (*it)->render();
    }
}

void ItemManager::clean()
{
    for (auto item : items)
    {
        delete item;
    }
    items.clear();
    delete instance;
    instance = nullptr;
}

void ItemManager::addItem(Item *item)
{
    items.push_back(item);
}

std::vector<Item *> ItemManager::getItems()
{
    return items;
}