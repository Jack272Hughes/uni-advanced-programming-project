#pragma once
#include <ctime>

class GameComponent {
private:
    int id;
    int instances;
public:
    GameComponent();
    virtual void Update(const tm* eventTime);
};
