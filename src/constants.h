#pragma once

// Game setting
#define GAME_TITLE "Space Shooter"
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
#define PLAYER_SPEED 250.0f
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
#define BULLET_TYPES_COUNT 5
#define DEFAULT_BULLET 0
#define CHARGED_BULLET 1
#define CIRCLE_BULLET 2
#define SQUARE_BULLET 3
#define ENEMY_BULLET 4

// Item
#define BUBBLE_SIZE 32
#define ITEM_SIZE 24
#define HEART_ITEM 5
#define ITEM_VELOCITY 100.0f
#define ITEM_SPAWN_RATE 5

// Enemy setting
#define ENEMY_SPEED_SLOW 10.0f
#define ENEMY_SPEED_FAST 25.0f
#define ENEMY_ANIMATION_DURATION 0.8f
#define ENEMY_SHOOTING_PERCENTRATE 10

// Pages
#define HOME_PAGE 0
#define GAME_PAGE 1
#define GAME_OVER_PAGE 2