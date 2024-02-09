#include "autons.hpp"
#include "main.h"

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;  
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///

void default_constants(){
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(10, 0, 100);
  chassis.pid_turn_constants_set(3, 0, 20);
  chassis.pid_swing_constants_set(5, 0, 30);

  chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  chassis.slew_drive_constants_set(7_in, 80);
}
void close();
void closeWP();
void far();
void farWP();
void skills();


void skills() {
  // pros::Motor flywheelMotor (4, pros::E_MOTOR_GEARSET_06);
  // double flywheelTarget = 2600;
  // ez::PID flywheelPID{1,.001, 4, 100, "Flywheel"};
  flywheelPID.target_set(flywheelTarget);
  double flywheelSpeed = flywheelMotor.get_actual_velocity()*5;
  flywheelMotor = flywheelPID.compute(flywheelSpeed);
  
  chassis.pid_turn_set(-75_deg, TURN_SPEED);
  chassis.pid_wait();
  chassis.drive_set(-12, DRIVE_SPEED);
  chassis.pid_wait();
}
void nothing();