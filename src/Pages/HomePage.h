#pragma once

class HomePage{
private:
    int highScore;
    bool firstTime;
    int recentScore;
public:
    bool startedGame;
    HomePage();
    ~HomePage();
    void init(int _highScore, bool _firstTime, int _recentScore);
    void clean();
    void update();
    void render();
};