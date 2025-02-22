#pragma once

class HomePage{
private:
    int highScore;
public:
    bool startedGame;
    HomePage();
    ~HomePage();
    void init(int _highScore);
    void clean();
    void update();
    void render();
};