#pragma once
#include <ctime>

class GameComponent {
private:
    static int instances;
    int id;
public:
    GameComponent();
    virtual void Update(const tm* eventTime);
};
