#include "autonomous.h"
#include "robot_config.h"
#include "lemlib/api.hpp" // IWYU pragma: keep

void skills_auton() {
    chassis.setPose(0, 0, 270);
    chassis.moveToPoint(-31.75, 2,2000);
    chassis.turnToHeading(180, 1500,{},false);
    Unloader.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-31.75, -15, 2000, {.maxSpeed = 100} );
    Intake.move(-600);
    Outtake.move(-600);
    chassis.moveToPoint( -32,  5, 2000, {.forwards = false, .maxSpeed = 80},false);
    pros::delay(500);
    Unloader.set_value(false);
    Intake.move(0);
    Outtake.move(0);
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint( -51,  5, 2000, {.forwards = false, .maxSpeed = 70}); // allign
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(-44, 85, 2000);
//_____
    chassis.turnToHeading(90, 2000);
    chassis.moveToPoint(-50, 85, 1000, {.forwards = false, .minSpeed = 60}); // allign
    chassis.moveToPoint(-32, 90, 2000);
    chassis.turnToHeading(0, 2000);
    chassis.moveToPoint(-32, 70, 2000,{.forwards = false, .maxSpeed = 50},false); // go to goal and score
    Unloader.set_value(true);
    Outtake.move(600);
    Intake.move(-600);
    pros::delay(1500);
    Outtake.move(-600);
    pros::delay(1000);
    left_motors.move(30); // forwards a bit
    right_motors.move(30);
    pros::delay(300);
    left_motors.move(0);
    right_motors.move(0); 
    chassis.turnToHeading(0, 1000,{},false); // allign with unloader
    chassis.moveToPoint(-30, 110, 2000, {.maxSpeed = 70, .minSpeed = 60},false);
    pros::delay(2500); // unload
    chassis.moveToPoint(-30, 70, 2000,{.forwards = false, .maxSpeed = 75},false); // back to goal and score
    pros::delay(1700);
    Outtake.move(600);
    Intake.move(-600);
    pros::delay(1000);
    Unloader.set_value(false);
    pros::delay(1500);
    Outtake.move(0);
    Intake.move(0);

    chassis.moveToPoint(-32, 90, 1000);
    chassis.turnToHeading(90, 1000);
    chassis.moveToPoint(-50, 90, 1000,{.forwards=false}); // allign again but we might be able to remove, test later
    chassis.moveToPoint(-32, 90, 1000);
    chassis.turnToHeading(270, 1000);

    chassis.moveToPoint(130,90,5000,{.forwards=false,.maxSpeed=80},false);
    chassis.setPose(130,90,270);
    
    chassis.moveToPoint(110,90,2000,{});
    chassis.turnToHeading(0, 1000,{},false); // turn to unloader
    pros::delay(300);
    Unloader.set_value(true);
    Intake.move(-600);
    chassis.moveToPoint(110,100,2000,{.maxSpeed = 100});
    pros::delay(1000); // unload #3
    chassis.moveToPoint(100, 100, 2000,{.forwards=false},false); // back up
    Unloader.set_value(false);
    chassis.turnToHeading(270,1500,{},false); 
    chassis.moveToPoint(130, 100, 2000, {.forwards = false, .maxSpeed = 70}); // allign
    chassis.turnToHeading(180, 1500,{},false); 
    chassis.moveToPoint(130, 70, 2000, {.forwards = false, .maxSpeed = 80});
    chassis.turnToHeading(270, 1500);
    chassis.moveToPoint(135, 70, 2000, {.forwards = false, .maxSpeed = 80});

}

void leftAuton() {
    Descore.set_value(true);
    chassis.setPose(0, 0, 270);
    
    chassis.moveToPoint(-32, 10, 2000);
    Intake.move(-600);
    chassis.turnToPoint(-32, -10, 1500);
    pros::delay(1000);
    Descore.set_value(false);
    Unloader.set_value(true);
    chassis.moveToPoint(-32, -15, 3000);
    chassis.moveToPoint(-32, 30, 2000, {.forwards = false, .maxSpeed = 80}, false);
    
    Outtake.move(600);
}

void rightAuton() {
    Descore.set_value(true);
    chassis.setPose(0, 0, 90);
    
    chassis.moveToPoint(32, 10, 2000);
    Intake.move(-600);
    chassis.turnToPoint(32, -10, 1500);
    pros::delay(1000);
    Unloader.set_value(true);
    Descore.set_value(false);
    chassis.moveToPoint(32, -15, 3000, {.maxSpeed = 127}, false);
    chassis.moveToPoint(32, 30, 3000, {.forwards = false, .maxSpeed = 80}, false);
    
    Outtake.move(600);


}

void rightAutonDescore() {
    Descore.set_value(true);
    chassis.setPose(0, 0, 90);
    
    chassis.moveToPoint(32, 10, 2000);
    Intake.move(-600);
    chassis.turnToPoint(32, -10, 1500);
    pros::delay(1000);
    Unloader.set_value(true);
    Descore.set_value(false);
    chassis.moveToPoint(32, -15, 3000, {.maxSpeed = 127}, false);
    chassis.moveToPoint(32, 30, 2000, {.forwards = false, .maxSpeed = 80}, false);
    Outtake.move(600);
    pros::delay(2000);
    chassis.moveToPoint(32, 20, 2000);
    chassis.moveToPose(42, 27, 180, 3000, {.forwards = false, .maxSpeed = 80});

        /* test swing to heading
    after score:
    chassis.swingToHeading(90,1000);
    lemlib::Pose pose = chassis.getPose(false);
    chassis.moveToPoint((pose.x+10),pose.y,1000);
    chassis.turnToHeading(0,1000);
    chassis.moveToPoint((pose.x+10),(pose.y+10),2000);
    */


}

void leftAutonDescore() {
    Descore.set_value(true);
    chassis.setPose(0, 0, 90);
    
    chassis.moveToPoint(-32, 10, 2000);
    Intake.move(-600);
    chassis.turnToPoint(-32, -10, 1500);
    pros::delay(1000);
    Unloader.set_value(true);
    Descore.set_value(false);
    chassis.moveToPoint(-32, -15, 3000, {.maxSpeed = 127}, false);
    chassis.moveToPoint(-32, 30, 2000, {.forwards = false, .maxSpeed = 80}, false);
    Outtake.move(600);
    pros::delay(2000);
    chassis.swingToHeading(0,lemlib::DriveSide::RIGHT,1000);
    lemlib::Pose pose = chassis.getPose(false);
    chassis.moveToPoint((pose.x),(pose.y+10),2000);

}

void rightautowinpoint() {
    chassis.setPose(-46.766, -14.998, 90);
    chassis.swingToPoint(-19.254,-21.922,lemlib::DriveSide::LEFT,2000);
    Intake.move(-600);
    chassis.moveToPoint(-19.254,-21.922,2000,{},false);
    chassis.turnToPoint(-12.758,-14.052,1500);
    chassis.moveToPoint(-12.758,-14.052,2000,{},false);
    Intake.move(100);
    pros::delay(2000);
    chassis.moveToPoint(-41.118,-47.611,2000,{.forwards=false},false);
    chassis.turnToHeading(270,1500,{},false);
    Unloader.set_value(true);
    Intake.move(-600);
    Outtake.move(-600);
    pros::delay(300);
    chassis.moveToPoint(-60.795,-47.611,1500,{.maxSpeed=100});
    chassis.moveToPoint(-28.911,-47.611,2000,{.forwards=false,.maxSpeed=80},false);
    Outtake.move(600);
    Unloader.set_value(false);

}

void leftautowinpoint() {
    chassis.setPose(-46.766, 14.998, 90);
    chassis.swingToPoint(-19.254,21.922,lemlib::DriveSide::LEFT,2000);
    Intake.move(-600);
    Outtake.move(-600);
    chassis.moveToPoint(-19.254,21.922,2000,{},false);
    chassis.turnToPoint(-12.758,14.052,1500,{.forwards=false},false);
    chassis.moveToPoint(-12.758,14.052,2000,{.forwards=false},false);
    MidScoring.set_value(true);
    pros::delay(2000);
    Intake.move(0);
    Outtake.move(0);
    chassis.moveToPoint(-41.118,47.611,2000,{},false);
    chassis.turnToHeading(270,1500,{},false);
    Unloader.set_value(true);
    Intake.move(-600);
    Outtake.move(-600);
    pros::delay(300);
    chassis.moveToPoint(-60.795,47.611,1500,{.maxSpeed=100});
    chassis.moveToPoint(-28.911,47.611,2000,{.forwards=false,.maxSpeed=80},false);
    Outtake.move(600);
    Unloader.set_value(false);

}

void auton_coord_finder() {
    chassis.setPose(0, 0, 0); // reset pose to origin
    while (true) {
        lemlib::Pose pose = chassis.getPose(false);
        pros::lcd::set_text(0, ("X: " + std::to_string(pose.x)).c_str());
        pros::lcd::set_text(1, ("Y: " + std::to_string(pose.y)).c_str());
        pros::lcd::set_text(2, ("Theta: " + std::to_string(pose.theta)).c_str());
        pros::delay(50);
    }
}