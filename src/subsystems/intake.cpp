#include "subsystems/intake.h"
#include "robot_config.h"

IntakeControl::IntakeControl() 
    : toggleForward(false), toggleReverse(false),
      R1_lastState(false), A_lastState(false) {}

void IntakeControl::update(bool isBlocked) {
    // Only allow R1/R2 control when NOT in mid-scoring mode
    // We check this via the isBlocked flag passed from Outtake
    
    bool R1_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    bool A_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_A);

    if (R1_current && !R1_lastState) {
        toggleReverse = !toggleReverse;
        if (toggleReverse) toggleForward = false;
    }
    if (A_current && !A_lastState) {
        toggleForward = !toggleForward;
        if (toggleForward) toggleReverse = false;
    }
    
    R1_lastState = R1_current;
    A_lastState = A_current;

    // Only move intake here if NOTblocked by outtake (mid-scoring)
    if (!isBlocked) {
        Intake.move_velocity(getVelocity());
    }
}

int IntakeControl::getVelocity() {
    if (toggleForward) return 600;   // Blue cartridge max RPM
    if (toggleReverse) return -600;
    return 0;
}