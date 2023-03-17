#include "Game.h"
#include <unistd.h>

Game::Game(int maxComponents) {
    components = new GameComponent*[maxComponents];
    componentCount = 0;
}

Game::~Game() {
    for (int index = 0; index < componentCount; index++) {
        delete components[index];
    }
    delete[] components;
}

void Game::Add(GameComponent* component) {
    components[componentCount] = component;
    componentCount++;
}

void Game::Run() {
    if (initialise) initialise();

    for (int invocations = 1; invocations <= 5; invocations++) {
        time_t now = time(0);
        tm eventTime;
        gmtime_r(&now, &eventTime);

        for (int index = 0; index < componentCount; index++) {
            components[index]->Update(&eventTime);
        }
        
        sleep(TICKS_1000MS);
    }

    if (terminate) terminate();
}

void Game::SetInitialise(FP init) {
    this->initialise = init;
}

void Game::SetTerminate(FP term) {
    this->terminate = term;
}
