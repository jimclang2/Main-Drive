#include "subsystems/outtake.h"
#include "robot_config.h"

OuttakeControl::OuttakeControl()
    : toggleForward(false),
      L1_lastState(false),
      midScoringMode(false), X_lastState(false),
      unjamStartTime(0), isUnjamming(false) {}

void OuttakeControl::update() {
    // Handle unjam sequence
    if (isUnjamming) {
        if (pros::millis() - unjamStartTime >= 100) {  // Time of delay
            isUnjamming = false;
            // Don't set intake here - let it fall through to mid-scoring mode logic below
        } else {
            Intake.move_velocity(600);   // Unjam (reverse) - velocity control
            Outtake.move_velocity(-600); // Make sure outtake also runs during unjam
            return; // Exit early during unjam
        }
    }

    // Mid Scoring Toggle (Button X)
    bool X_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    if (X_current && !X_lastState) {
        midScoringMode = !midScoringMode;
        
        if (midScoringMode) {
            // ENTERING mid-scoring mode - turn off combo mode
            toggleForward = false;
            MidScoring.set_value(true); // Retract piston
            isUnjamming = true;
            unjamStartTime = pros::millis();
        } else {
            // EXITING mid-scoring mode
            MidScoring.set_value(false); // Extend piston
            isUnjamming = false;
            Intake.move_velocity(0); // Stop intake
            Outtake.move_velocity(0); // Stop outtake
            // Reset toggles so they start fresh
            toggleForward = false;
            X_lastState = X_current; // Update state BEFORE returning
            return; // Exit function immediately after turning off mid-scoring
        }
    }
    X_lastState = X_current;

    int velocity = 0;

    if (midScoringMode && !isUnjamming) {
        // Mid-scoring mode AFTER unjam: run intake forward and outtake reverse
        Intake.move_velocity(-600);  // This will run continuously during mid-scoring
        velocity = -450;
        // Update last states to prevent "stored" button presses
        L1_lastState = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    } else if (!midScoringMode) {
        // Normal mode: L1 = outtake forward
        bool L1_current = master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);

        // L1: Toggle outtake forward only
        if (L1_current && !L1_lastState) {
            toggleForward = !toggleForward;
        }
        
        L1_lastState = L1_current;

        // Set motor velocities based on current mode
        if (toggleForward) {
            velocity = 600;
        }
        // If neither is active, velocity stays 0
    }

    Outtake.move_velocity(velocity);
}

int OuttakeControl::getVelocity() {
    if (midScoringMode) return -450;
    if (toggleForward) return 600;
    return 0;
}

bool OuttakeControl::isMidScoring() {
    return midScoringMode;
}

