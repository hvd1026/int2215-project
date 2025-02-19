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
    int base_y = 0;
    for (int i = 1; i<=8; i++){
        dest[i] = {0, base_y, SCREEN_WIDTH, SCREEN_HEIGHT};
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
        dest[i].y += scroll;
        if (dest[i].y >= SCREEN_HEIGHT){
            dest[i].y = dest[tail].y - SCREEN_HEIGHT + scroll;
            tail = i;
        }
    }
}