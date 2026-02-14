#pragma once

class IntakeControl {
private:
    bool toggleForward;
    bool toggleReverse;
    bool R1_lastState;
    bool A_lastState;

public:
    IntakeControl();
    void update(bool isBlocked = false);
    int getVelocity();
};