#include "GameComponent.h"
#include <iostream>

int GameComponent::instances = 0;

GameComponent::GameComponent() {
    instances++;
    this->id = instances;
}

void GameComponent::Update(const tm* eventTime) {
    char formattedTime[9];
    strftime(formattedTime, sizeof(formattedTime), "%X", eventTime);
    printf("ID: %d updated at %s\n", this->id, formattedTime);
}
