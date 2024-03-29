#pragma once
#include "GameComponent.h"

// A type definition (FP) for a function that
// takes no parameters and returns void
typedef void (*FP)();

class Game {
private:
    const int TICKS_1000MS = 1;
    int componentCount;
    GameComponent** components;
    FP initialise;
    FP terminate;
public:
    Game(int maxComponents);
    ~Game();
    void Add(GameComponent* component);
    void Run();
    void SetInitialise(FP init);
    void SetTerminate(FP term);
};
