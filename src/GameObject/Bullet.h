#pragma once
#include "../Animation/Animation.h"
#include <vector>
class Bullet
{
private:
    int xPos, yPos;
    int velocity;
    Animation *animate;

public:
    SDL_Rect dest;
    int bulletType;
    Bullet(int x, int y, int type);
    ~Bullet();
    void update();
    void render();

    int damage;
    bool isActive;
};

class BulletManager
{
public:
    static BulletManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new BulletManager();
        }
        return instance;
    };
    void addBullet(Bullet *bullet)
    {
        bullets.push_back(bullet);
    };
    std::vector<Bullet *> getBullets()
    {
        return bullets;
    };
    void update()
    {
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            (*it)->update();
            if (!(*it)->isActive)
            {
                delete (*it);
                bullets.erase(it);
                it--;
            }
        }
    }
    void render()
    {
        for (auto it = bullets.begin(); it != bullets.end(); it++)
        {
            (*it)->render();
        }
    }
    void clean()
    {
        for (auto bullet : bullets)
        {
            delete bullet;
        }
        bullets.clear();
        delete instance;
        instance = nullptr;
    };

private:
    BulletManager() {}
    static BulletManager *instance;
    static std::vector<Bullet *> bullets;
};