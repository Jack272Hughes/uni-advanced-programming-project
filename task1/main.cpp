#include <ctime>
#include <iostream>

#include "classes/Game.h"
#include "classes/GameComponent.h"
#include "classes/DrawableGameComponent.h"

void initialise() {
    std::cout << "Initialising game" << std::endl;
}

void terminate() {
    std::cout << "Terminating game" << std::endl;
}

int main() {
    // This only needs to be called once at the beginning of the program
    // and seeds the random function (rand) using the current time
    srand(time(0));

    Game* game = new Game(2);
    game->SetInitialise(initialise);
    game->SetTerminate(terminate);

    game->Add(new GameComponent());
    game->Add(new DrawableGameComponent(0, 0));

    game->Run();

    delete game;
}
