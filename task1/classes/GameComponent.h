#pragma once
#include <ctime>

class GameComponent {
private:
    static int instances;
    int id;
public:
    GameComponent();
    // Defined with virtual so the compiler knows to create a V table
    // in the event that a subclass overrides this function's implementation
    virtual void Update(const tm* eventTime);
};
