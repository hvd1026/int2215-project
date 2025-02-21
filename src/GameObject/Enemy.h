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
    static EnemyManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new EnemyManager();
        }
        return instance;
    };
    void addEnemy(Enemy *enemy)
    {
        enemies.push_back(enemy);
    };
    std::vector<Enemy *> getEnemies()
    {
        return enemies;
    };
    void update()
    {
        for (auto it = enemies.begin(); it != enemies.end(); it++)
        {
            (*it)->update();
            if (!(*it)->isActive)
            {
                delete (*it);
                enemies.erase(it);
                it--;
            }
        }
    };
    void render()
    {
        for (auto enemy : enemies)
        {
            enemy->render();
        }
    };
    void clean()
    {
        for (auto enemy : enemies)
        {
            delete enemy;
        }
        enemies.clear();
        delete instance;
        instance = nullptr;
    };

private:
    EnemyManager() {};
    static EnemyManager *instance;
    static std::vector<Enemy *> enemies;
};
