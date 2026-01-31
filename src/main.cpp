#include "lemlib/api.hpp"
#include "pros/rtos.hpp"
#include "main.h"
#include "robot_config.h"
#include "autonomous.h"
#include "subsystems/intake.h"
#include "subsystems/outtake.h"
#include "subsystems/pneumatics.h"

void initialize() {
    initializeRobot();
    drawAutonSelector(); // Just draw it, don't block
}

void disabled() {}

void competition_initialize() {
    // If connected to field: wait for enable (timeout = 0)
    // If not connected (testing): 15 second timeout
    if (pros::competition::is_connected()) {
        runAutonSelector(0); // Competition mode - waits for field enable
    } else {
        runAutonSelector(15000); // Practice mode - 15 seconds
    }
}

void autonomous() {
    switch(autonSelection) {
        case 0:
            skills_auton();
            break;
        case 1:
            leftAuton();
            break;
        case 2:
            rightAuton();
            break;
        case 3:
            rightAutonDescore();
            break;
    }
}

void opcontrol() {
    IntakeControl intake;
    OuttakeControl outtake;
    PneumaticControl pneumatics;
    
    // Reset lock timer when driver control starts
    lockTimer = pros::millis();

    while (true) {
        // Check and lock selector after 5 seconds
        checkAndLockSelector(5000);

        // Tank Drive (ALWAYS WORKS)
        int left = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int right = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        left_motors.move(left);
        right_motors.move(right);

        // Update subsystems (ALWAYS WORKS)
        outtake.update();
        intake.update(outtake.isMidScoring());
        pneumatics.update();

        pros::delay(20);
    }
}