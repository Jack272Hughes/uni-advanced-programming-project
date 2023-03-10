#include <algorithm>
#include <iostream>
#include <numeric>
#include "DrawableGameComponent.h"

using namespace std;

DrawableGameComponent::DrawableGameComponent(int x, int y): GameComponent() {
    this->x = x;
    this->y = y;
    this->direction = Right;
}

void DrawableGameComponent::ChangeDirection() {
    Direction newDirection;
    do {
        newDirection = Direction(rand() % 4);
    } while (newDirection != direction);
    direction = newDirection;
}

void DrawableGameComponent::Draw() {
    printf("Direction: %u, X: %d, Y: %d\n", direction, x, y);
}



void DrawableGameComponent::Update(const tm* eventTime) {
    GameComponent::Update(eventTime);
    switch(direction) {
        case Left:
            x = max(0, x - 1);
            break;
        case Right:
            x = min(SCREEN_WIDTH, x + 1);
            break;
        case Up:
            y = min(SCREEN_HEIGHT, y + 1);
            break;
        case Down:
            y = max(0, y - 1);
            break;
    }

    Draw();
    ChangeDirection();
}
