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
    static BulletManager *getInstance();
    void addBullet(Bullet *bullet);
    std::vector<Bullet *> getBullets();
    void update();
    void render();
    void clean();

private:
    BulletManager();
    static BulletManager *instance;
    static std::vector<Bullet *> bullets;
};