#include <SDL.h>

class EventManager
{
private:
    EventManager();
    static EventManager *instance;
    const Uint8 *keyState;

public:
    static EventManager *getInstance();

    bool isKeyDown(SDL_Scancode key);
    void onKeyDown();
    void onKeyUp();
    void clean();
};