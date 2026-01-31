#pragma once
#include <cstdint>  // For uint32_t

class OuttakeControl {
private:
    bool toggleForward;
    bool comboMode;      // L2 combo mode: runs both intake and outtake
    bool L1_lastState;
    bool L2_lastState;
    bool midScoringMode;
    bool X_lastState;
    
    uint32_t unjamStartTime;
    bool isUnjamming;

public:
    OuttakeControl();
    void update();
    int getVelocity();
    bool isMidScoring();
    bool isComboModeActive();
};