#pragma once
#include "../Animation/Animation.h"
#include <vector>
#include <string>

struct BulletProperties
{
    std::string id;
    int damage;
    float velocity;
    float shootDelay;
    float maxTime;
    float animationTime;
    int animationFrames;
};
class Bullet
{
private:
    float xPos, yPos;
    Animation *animate;

public:
    Bullet(int x, int y, int type);
    ~Bullet();
    void update();
    void render();

    SDL_Rect dest;
    int bulletType;
    bool isActive;
    BulletProperties properties;
};

class BulletManager
{
public:
    static BulletManager *getInstance();
    void addBullet(Bullet *bullet);
    std::vector<Bullet *> getBullets();
    std::vector<BulletProperties> bulletProperties;
    void update();
    void render();
    void clean();

private:
    BulletManager();
    static BulletManager *instance;
    static std::vector<Bullet *> bullets;
};
