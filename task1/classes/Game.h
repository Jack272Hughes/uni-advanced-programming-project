#pragma once
#include "GameComponent.h"

class Game {
private:
    const int TICKS_1000MS = 1000;
    int maxComponents;
    int componentCount;
    GameComponent** components;
    void (*initialise)();
    void (*terminate)();
public:
    Game(int maxComponents);
    void Add(GameComponent* component);
    void Run();
    void SetInitialise();
    void SetTerminate();
};
