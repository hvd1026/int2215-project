#include <SDL.h>
#include <string>
#include <iostream>
#include "../Manager/AssetManager.h"
#include "../Manager/TimeManager.h"
#include "../constants.h"
#include "Background.h"

Background::Background(){
    tail = 8;
    src = {0, 0, 512, 512};
    float base_y = 0;
    for (int i = 1; i<=8; i++){
        yPos[i] = base_y;
        dest[i] = {0, (int)yPos[i], SCREEN_WIDTH, SCREEN_HEIGHT};
        base_y -= SCREEN_HEIGHT;
    }

}
Background::~Background(){}


void Background::render(){  
    for (int i = 1; i<=8; i++){
        std::string bg = "bg" + std::to_string(i);
        AssetManager::getInstance()->draw(bg, src, dest[i]);
    }
}
void Background::update(){
    for (int i = 1; i<=8; i++){
        yPos[i] += scroll * TimeManager::getInstance()->getDeltaTime();
        dest[i].y = (int)yPos[i];
        if (dest[i].y >= SCREEN_HEIGHT){
            yPos[i] = yPos[tail] - SCREEN_HEIGHT + scroll * TimeManager::getInstance()->getDeltaTime();
            dest[i].y = (int)yPos[i];
            tail = i;
        }
    }
}