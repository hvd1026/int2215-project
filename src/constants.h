#pragma once

// Game setting
#define GAME_TITLE "Huan making the game"
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 800
#define FPS 60
#define BG_SCROLL_SPEED 120.0f
#define BOOM_ANIMATION_TIME 0.8f
#define SCORE_PER_SECOND 6
#define BOSS_SPAWN_RATE 10 
#define BOSS_INCREASE_RATE 1 // per 10 score
#define MAX_BOSS_SPAWN_RATE 60
#define ENEMY_SPAWN_TIME 0.6f
#define ENEMY_SPAM_DECREASE 0.005f // per 100 score
#define MAX_ENEMY_SPAWN_TIME 0.3f

// Player setting
#define PLAYER_SPEED 300
#define PLAYER_SIZE 32
#define PLAYER_BOOSTER_TIME 0.3f
#define PLAYER_HP 3

// Direction define
#define MOVE_LEFT 1
#define MOVE_RIGHT 2
#define MOVE_UP 3
#define MOVE_DOWN 4

// Bullet setting
#define BULLET_SIZE 32
#define SLOW_BULLET 0
#define SLOW_BULLET_DELAY 0.8f
#define SLOW_BULLET_ANIMATION_TIME 0.8f
#define SLOW_BULLET_SPEED 300
#define SLOW_BULLET_DAMAGE 10
#define FAST_BULLET 1    
#define FAST_BULLET_DELAY 0.2f
#define FAST_BULLET_DAMAGE 1
#define FAST_BULLET_SPEED 600
#define ENEMY_BULLET 2
#define ENEMY_BULLET_SPEED -100
#define ENEMY_BULLET_DAMAGE 1
#define ENEMY_BULLET_DELAY 5.0f

// Enemy setting
#define ENEMY_SPEED_SLOW 10.0f
#define ENEMY_SPEED_FAST 25.0f
#define ENEMY_ANIMATION_DURATION 0.8f
#define ENEMY_SHOOTING_PERCENTRATE 10

// Pages
#define HOME_PAGE 0
#define GAME_PAGE 1
#define GAME_OVER_PAGE 2