#include "autonomous.h"
#include "pros/rtos.hpp"
#include "robot_config.h"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include <ctime>


void skills_autona() { // default
chassis.setPose(0, 0, 270);
chassis.moveToPoint(-31.75, 2,1750);
chassis.turnToHeading(180, 1000,{},false);
Unloader.set_value(true);
Intake.move(-127);
pros::delay(300);
chassis.moveToPoint(-31.75, -15, 2000, {.maxSpeed = 100} ); // unload
pros::delay(1500);
chassis.moveToPoint( -32, 5, 1750, {.forwards = false, .maxSpeed = 80},false);
Unloader.set_value(false);
Intake.move(0);
chassis.turnToHeading(90, 1000);
chassis.moveToPoint( -55, 5, 1000, {.forwards = false, .minSpeed = 70}); // allign
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(-47, 90, 2000,{.maxSpeed=80});

chassis.turnToHeading(90, 1000);
chassis.moveToPoint(-60, 90, 1000, {.forwards = false, .minSpeed = 60}); // allign
chassis.moveToPoint(-33, 90, 1750);
chassis.turnToHeading(0, 1000);
chassis.moveToPoint(-33, 70, 2000,{.forwards = false, .maxSpeed = 50},false); // go to goal and score
Unloader.set_value(true);
Outtake.move(127);
Intake.move(-127);
pros::delay(2500); // Reduce to minimum needed CLAUDE
left_motors.move(40); // Slightly faster
right_motors.move(40);
pros::delay(150); // Reduce
left_motors.brake();
right_motors.brake();
Outtake.move(0);
chassis.turnToHeading(0, 500,{},false); // allign with unloader
chassis.moveToPoint(-31, 110, 2000, {.maxSpeed = 70, .minSpeed = 60},false);
pros::delay(1500); // unload
chassis.moveToPoint(-32, 70, 1500,{.forwards = false, .maxSpeed = 75}, false); // back to goal and score
Outtake.move(127);
Unloader.set_value(false);
pros::delay(2500);
Outtake.move(0);
Intake.move(0);
chassis.moveToPoint(-32, 90, 1000);
chassis.turnToHeading(270, 1000);
chassis.moveToPoint(130, 90, 4000, {.forwards = false, .maxSpeed = 70},false);
chassis.setPose(130, 90, 270);


chassis.moveToPoint(112,80,2000,{});
chassis.turnToHeading(0, 1000,{},false); // turn to unloader
Unloader.set_value(true);
Intake.move(-127);
pros::delay(500);
chassis.moveToPoint(111,110,2000,{.maxSpeed=100},false); //unload
pros::delay(1500);
chassis.moveToPoint(111, 85, 2000,{.forwards=false},false); // back up
Unloader.set_value(false);
pros::delay(300);
chassis.turnToHeading(270,1000);
chassis.moveToPoint(150,90,1500,{.forwards=false,.maxSpeed=80}, false); // allign
chassis.setPose(130,90,270);
chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 1000); // turn
chassis.moveToPoint(142, 0, 2000,{.forwards = false, .maxSpeed=80});
chassis.turnToHeading(270,0);
chassis.moveToPoint(170, 0, 2000,{.forwards=false,.maxSpeed=60}); // allign
chassis.moveToPoint(124, 0, 1000,{.maxSpeed=60});
chassis.turnToHeading(180,1000);
chassis.moveToPoint(124,30,2000,{.forwards=false,.maxSpeed=60},false); // score
Outtake.move(127);
Intake.move(-127);
chassis.setPose(0,0,0); //remove this if we wanna do next goal
pros::delay(2500);
left_motors.move(30); // forwards a bit
right_motors.move(30);
/*Outtake.move(0);
chassis.moveToPoint(124, -60, 2500, {.maxSpeed = 50},false); //unload
chassis.moveToPoint(124, 40, 2000,{.forwards = false, .maxSpeed = 80}, false); // score
pros::delay(300);
Outtake.move(127);
Unloader.set_value(false);

pros::delay(1500);
left_motors.move(30); // forwards a bit
right_motors.move(30);
*/
chassis.moveToPose(17, 26, 70, 2000);
chassis.moveToPose(46.16, 33.53, 89.42, 2000, {.minSpeed=100}); // park

}

void skills_auton() { // risky
/*chassis.setPose(0, 0, 270);
chassis.moveToPoint(-31.75, 2, 1550);
chassis.turnToHeading(180, 800, {}, false);
Unloader.set_value(true);
Intake.move(-127);
pros::delay(300);
chassis.moveToPoint(-31.75, -15, 1800, {.maxSpeed = 100}); // unload
pros::delay(1300);
chassis.moveToPoint(-32, 5, 1550, {.forwards = false, .maxSpeed = 80}, false);
Unloader.set_value(false);
Intake.move(0);
chassis.turnToHeading(90, 800);
chassis.moveToPoint(-55, 5, 800, {.forwards = false, .minSpeed = 70}); // allign
chassis.turnToHeading(0, 800);
chassis.moveToPoint(-47, 90, 1800, {.maxSpeed = 80});

chassis.turnToHeading(90, 800);
chassis.moveToPoint(-60, 90, 800, {.forwards = false, .minSpeed = 60}); // allign
chassis.moveToPoint(-33, 90, 1550);
chassis.turnToHeading(0, 800);
chassis.moveToPoint(-33, 70, 1800, {.forwards = false, .maxSpeed = 50}, false); // go to goal and score
Unloader.set_value(true);
Outtake.move(127);
Intake.move(-127);
pros::delay(2000); // Reduce to minimum needed CLAUDE
left_motors.move(40); // Slightly faster
right_motors.move(40);
pros::delay(0); // Reduce (removed delay as 150-200 would be negative)
left_motors.brake();
right_motors.brake();
Outtake.move(0);
chassis.turnToHeading(0, 300, {}, false); // allign with unloader
chassis.moveToPoint(-31, 110, 1800, {.maxSpeed = 70, .minSpeed = 60}, false);
pros::delay(1300); // unload
chassis.moveToPoint(-32, 70, 1300, {.forwards = false, .maxSpeed = 75}, false); // back to goal and score
Outtake.move(127);
Unloader.set_value(false);
pros::delay(2300);
Outtake.move(0);
Intake.move(0);
chassis.moveToPoint(-32, 90, 800);
chassis.turnToHeading(270, 800);
chassis.moveToPoint(130, 90, 3800, {.forwards = false, .maxSpeed = 70}, false);
chassis.setPose(130, 90, 270);

chassis.moveToPoint(112, 80, 1800, {});
chassis.turnToHeading(0, 800, {}, false); // turn to unloader
Unloader.set_value(true);
Intake.move(-127);
pros::delay(300);
chassis.moveToPoint(111, 110, 1800, {.maxSpeed = 80}, false); //unload
pros::delay(1300);
chassis.moveToPoint(111, 85, 1800, {.forwards = false}, false); // back up
Unloader.set_value(false);
pros::delay(100);
chassis.turnToHeading(270, 800);
chassis.moveToPoint(150, 90, 1300, {.forwards = false, .maxSpeed = 80}, false); // allign
chassis.setPose(130, 90, 270);
chassis.swingToHeading(0, lemlib::DriveSide::RIGHT, 800); // turn
chassis.moveToPoint(142, 0, 1800, {.forwards = false, .maxSpeed = 80});
chassis.turnToHeading(270, 0);
chassis.moveToPoint(170, 0, 1800, {.forwards = false, .maxSpeed = 60}); // allign
chassis.moveToPoint(122, 0, 800, {.maxSpeed = 60});
chassis.turnToHeading(180, 800);
chassis.moveToPoint(122, 30, 1800, {.forwards = false, .maxSpeed = 60}, false); // score
Outtake.move(127);
Intake.move(-127);
Unloader.set_value(true);
pros::delay(2300);
left_motors.move(30); // forwards a bit
right_motors.move(30);
Outtake.move(0);
chassis.moveToPoint(122, -70, 2300, {.maxSpeed = 50}, false); //unload
pros::delay(2000);
chassis.moveToPoint(122, 40, 1800, {.forwards = false, .maxSpeed = 80}, false); // score
pros::delay(100);*/
Outtake.move(127);
Intake.move(-127); //remove
chassis.setPose(0, 0, 0);
Unloader.set_value(false);
pros::delay(1500);
chassis.moveToPoint(0, 15, 1000);
chassis.moveToPoint(22, 26, 1800);
chassis.moveToPoint(40, 36.32, 1800, {.minSpeed = 120}); // park
Unloader.set_value(true);
}

void leftAuton_descore() { //7 ball
    chassis.setPose(0, 0, 0);
    Descore.set_value(true);
    Intake.move(-127);
    chassis.moveToPoint(-10, 20,  2500);
    chassis.moveToPoint(-30, 0, 2000,{},false);
    chassis.turnToPoint(-30, -10, 1000);
    Unloader.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-30, -15, 2300,{.minSpeed=50},false); // unload
    Intake.move(0);
    chassis.moveToPoint(-30, 30, 2000,{.forwards=false,.maxSpeed=80},false);
    Intake.move(-127);
    Outtake.move(127);
    Unloader.set_value(false);
    Descore.set_value(false);
    pros::delay(2500);
    Intake.move(0);
    Outtake.move(0);
    left_motors.move(40); // Slightly faster
    right_motors.move(40);
    pros::delay(200); // Reduce
    left_motors.brake();
    right_motors.brake();
    pros::delay(300);
    chassis.swingToHeading(330,lemlib::DriveSide::RIGHT,2000,{.minSpeed=50});
    chassis.swingToHeading(15,lemlib::DriveSide::RIGHT,1000,{},false);
    pros::delay(300);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,16.7,1000,{.minSpeed=50});
}

void leftAuton() { //mid
    chassis.setPose(0, 0, 0);
    Descore.set_value(true);
    Intake.move(-127);
    chassis.moveToPoint(-10, 20,  2500);
    chassis.turnToPoint(8, 38, 1000,{.forwards=false});
    chassis.moveToPoint(8, 38, 2000,{.forwards=false,.maxSpeed=80},false);
    Intake.move(127);
    pros::delay(200);
    Intake.move(-127);
    Outtake.move(-127);
    MidScoring.set_value(true); // score mid
    pros::delay(2000);
    Outtake.move(0);
    MidScoring.set_value(false);
    chassis.moveToPoint(-35, 10, 2000,{},false); // go to unload plane
    chassis.turnToHeading(183,1000,{},false);
    Unloader.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(-32, -15, 1800,{.minSpeed=50},false); // unload
    Intake.move(0);
    chassis.moveToPoint(-32, 30, 2000,{.forwards=false,.maxSpeed=80},false);
    Intake.move(-127);
    Outtake.move(127);
    Unloader.set_value(false);
    Descore.set_value(false);
    pros::delay(2500);
    Intake.move(0);
    Outtake.move(0);
    left_motors.move(40); // Slightly faster
    right_motors.move(40);
    pros::delay(200); // Reduce
    left_motors.brake();
    right_motors.brake();
    pros::delay(300);
    chassis.swingToHeading(330,lemlib::DriveSide::RIGHT,2000,{.minSpeed=50});
    chassis.swingToHeading(15,lemlib::DriveSide::RIGHT,1000,{},false);
    pros::delay(300);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,16.7,1000,{.minSpeed=50});
    
}

void rightAuton() {
    chassis.setPose(0, 0, 0);
    Descore.set_value(true);
    Intake.move(-127);
    chassis.moveToPoint(10, 20,  2500);
    chassis.moveToPoint(32, 0, 2000,{},false);
    chassis.turnToPoint(33, -10, 1000);
    Unloader.set_value(true);
    pros::delay(300);
    chassis.moveToPoint(32, -15, 2300,{.minSpeed=50},false); // unload
    Intake.move(0);
    chassis.moveToPoint(31, 30, 2000,{.forwards=false,.maxSpeed=80},false);
    Intake.move(-127);
    Outtake.move(127);
    Unloader.set_value(false);
    Descore.set_value(false);
    pros::delay(2500);
    Intake.move(0);
    Outtake.move(0);
    left_motors.move(40); // Slightly faster
    right_motors.move(40);
    pros::delay(300); // Reduce
    left_motors.brake();
    right_motors.brake();
    pros::delay(300);
    chassis.swingToHeading(330,lemlib::DriveSide::RIGHT,2000,{.minSpeed=50});
    chassis.swingToHeading(0,lemlib::DriveSide::RIGHT,1000,{},false);
    pros::delay(300);
    chassis.setPose(0,0,0);
    chassis.moveToPoint(0,20,1000,{.minSpeed=50});

}
void rightAutonDescore(){

}
void midAuton() { //mid auton
    chassis.setPose(0,0,0);
    Descore.set_value(true);
    Intake.move(-127);
    chassis.moveToPoint(-10, 20,  2500);
}