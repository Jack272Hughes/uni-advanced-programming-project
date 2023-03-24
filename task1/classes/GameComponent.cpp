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
    // The format identifier "%X" will format the 24 hour time in the form of HH:MM:SS
    // As "formattedTime" is sent by reference, strftime will mutate it to include the formatted time string
    strftime(formattedTime, sizeof(formattedTime), "%X", eventTime);
    printf("ID: %d updated at %s\n", this->id, formattedTime);
}
