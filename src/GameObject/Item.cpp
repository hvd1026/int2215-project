#include "Item.h"
#include <cstdlib>
#include <SDL.h>
#include <iostream>
#include "../constants.h"
#include "../Manager/TimeManager.h"
#include "../Manager/AssetManager.h"
#include "Bullet.h"
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
    // update pos here
}

void Item::render()
{
    AssetManager::getInstance()->draw("bubble", {0,0,16,16}, bubbleDest);
    if (type < 5){
        AssetManager::getInstance()->draw((BulletManager::getInstance()->bulletProperties[type]).id, {0,0,16,16}, itemRect);
    }else{
        AssetManager::getInstance()->draw("playerHealth", {0,0,16,16}, itemRect);
    }
}

int Item::randomType()
{
    srand(time(0)); // Seed the random number generator
    int randNum = rand() % 5 + 1;
    if (randNum == 4) { // 4 is ENEMY_BULLET
        randNum = 0;
    }
    return randNum;
}