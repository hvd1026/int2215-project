#pragma once
#include <SDL.h>
#include <string>
#include "../Animation/Animation.h"
class Enemy
{
private:
    std::string m_Name;
    Animation *m_Animation;
    float velocity;
    float xpos;
    float ypos;
    float timeCounter;

public:
    int hp;
    SDL_Rect m_Rect;
    bool isActive;
    Enemy(std::string name, int x, int y, int _hp);
    ~Enemy();
    void update();
    void render();
    void shoot();
};

class EnemyManager
{
public:
    static EnemyManager *getInstance();
    void addEnemy(Enemy *enemy);
    std::vector<Enemy *> getEnemies();
    void update();
    void render();
    void clean();

private:
    EnemyManager() {};
    static EnemyManager *instance;
    static std::vector<Enemy *> enemies;
};
