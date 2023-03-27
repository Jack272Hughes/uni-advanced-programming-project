#include <algorithm>
#include <iostream>
#include "DrawableGameComponent.h"

using namespace std;

const char* DrawableGameComponent::directionString[] = { "Left", "Right", "Up", "Down" };

DrawableGameComponent::DrawableGameComponent(int x, int y): GameComponent() {
    this->x = x;
    this->y = y;
    this->direction = Right;
}

void DrawableGameComponent::ChangeDirection() {
    Direction newDirection;
    // The do..while loop will ensure a new direction is chosen randomly at least
    // once and will rechoose if the chosen direction matches the previous one
    do {
        newDirection = Direction(rand() % 4);
    } while (newDirection == direction);
    direction = newDirection;
}

void DrawableGameComponent::Draw() {
    printf("Direction: %s, X: %d, Y: %d\n", directionString[direction], x, y);
}

// The eventTime uses "const" to indicate to the user that
// this member function will not mutate the variable
void DrawableGameComponent::Update(const tm* eventTime) {
    GameComponent::Update(eventTime);
    // A switch statement is used because "direction" can be one of four values and is more
    // effective than an if statement, since it doesn't need to check each direction one by one
    // and will instead go directly to the matching case
    switch(direction) {
        case Left:
            // The max method is used to stop the value of x/y from subceeding zero
            x = max(0, x - 1);
            break;
        case Right:
            // The min method is used to stop the value of x/y from exceeding the screen's dimensions
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
