#include "subsystems/pneumatics.h"
#include "robot_config.h"

PneumaticControl::PneumaticControl()
    : descoreState(false), unloaderState(false),
      A_lastState(false), L2_lastState(false) {}

void PneumaticControl::update() {
    // Descore (Button A)
    bool A_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);
    if (A_current && !A_lastState) {
        descoreState = !descoreState;
        Descore.set_value(descoreState);
    }
    A_lastState = A_current;

    // Unloader (Button L2)
    bool L2_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    if (L2_current && !L2_lastState) {
        unloaderState = !unloaderState;
        Unloader.set_value(unloaderState);
    }
    L2_lastState = L2_current;
}

bool PneumaticControl::getDescoreState() {
    return descoreState;
}

bool PneumaticControl::getUnloaderState() {
    return unloaderState;
}