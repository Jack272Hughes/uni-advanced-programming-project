#pragma once
#include <ctime>
#include "GameComponent.h"

class DrawableGameComponent : public GameComponent {
private:
    // Using an enum for the direction will stop the user from being
    // able to use potentially nonsense strings for the "direction" variable
    enum Direction { Left, Right, Up, Down };
    static const char* directionString[];
    int x;
    int y;
    void ChangeDirection();
    void Draw();
public:
    const int SCREEN_HEIGHT = 20;
    const int SCREEN_WIDTH = 80;
    Direction direction;
    DrawableGameComponent(int x, int y);
    void Update(const tm* eventTime);
};
