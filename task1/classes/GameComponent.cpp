#include "GameComponent.h"
#include <iostream>

// Static variables are shared across all instances of a class and
// needs to be instantiated outside a constructor to prevent it from
// being overwritten every time a new object for the class is created
int GameComponent::instances = 0;

GameComponent::GameComponent() {
    instances++;
    this->id = instances;
}

void GameComponent::Update(const tm* eventTime) {
    char formattedTime[9];
    // strftime will use a string pattern to create a formatted string of the time defined by a
    // "tm" object (eventTime), which is then assigned to the char array argument (formattedTime)
    // The format identifier "%X" will format the 24 hour time in the formation of HH:MM:SS
    strftime(formattedTime, sizeof(formattedTime), "%X", eventTime);
    printf("ID: %d updated at %s\n", this->id, formattedTime);
}
