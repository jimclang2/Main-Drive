#pragma once

class PneumaticControl {
private:
    bool descoreState;
    bool unloaderState;
    bool A_lastState;
    bool L2_lastState;

public:
    PneumaticControl();
    void update();
    bool getDescoreState();
    bool getUnloaderState();
};