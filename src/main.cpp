#include "C:\Users\jackc\OneDrive\Desktop\Homework\Robotics\Vex\Over Under 23-24\COde\19390W\include\main.h"
class Triball {


    public:
        Triball() {
            flywheelMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        }

        void shoot() {
            if (master.get_digital(DIGITAL_R1)) {
                flywheelMotor = -127;
            } else {if (master.get_digital(DIGITAL_R2)) {
                flywheelMotor = 127;
            } else {
                flywheelMotor = 0;
            }}
        }

        

        void intake() {
            if (partner.get_digital(DIGITAL_R1)) {
                Intake = -127; //intake
            } else {if (partner.get_digital(DIGITAL_R2)) {
                Intake = 127; //outake
            } else {
                Intake = 0;
            }}
        }

        void plow() {
            wings.button_toggle(master.get_digital(DIGITAL_L2));
        };


};
// Chassis constructor
ez::Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  {-15, -20, 18}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is used as the sensor
  ,{16, 19, -17}

  // IMU Port
  ,IMU_port

  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
  ,3.25

  // Cartridge RPM
  ,600

  // External Gear Ratio (MUST BE DECIMAL) This is WHEEL GEAR / MOTOR GEAR
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 84/36 which is 2.333
  // eg. if your drive is 60:36 where the 36t is powered, your RATIO would be 60/36 which is 0.6
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 36/60 which is 0.6
  ,.6
);
class DT {
  public:
    void TurnPID (double target, double max, double swing){ //target is the angle to turn to. Max is the maximum power up to 127. swing is a way to change the turn radius. Negative moves the wheel on that point
      double kP = .1;
      double kI = 0;
      double kD = 0;
     double Pi = imu_sensor.get_yaw(); //defines initital position
     double P = target - Pi; // sets initialy error
     double I = 0;
     double D = 0;
     if (fabs(P)>180){
      target = (180-fabs(target))*target/fabs(target); // TODO check order of operations
      P = target - Pi;} //redefines target to give shortest path. if 
     while(fabs(P)>.1 && fabs(D)>0){
      double P0 = P; //copies our old p value before changing it
      P = target - imu_sensor.get_yaw();//iterates error, change pitch roll or yaw based on IMU mounting
      I += P; //defines integral
      D = (P-P0)/10.0; //derivative as degrees/ms
      double power = (kP*P + kI*I + kD*D); //puts all our statements together
      if (fabs(power) > max) { // limits the maximum power, keeps the sign of the power
        power = max*(power/fabs(power));
      }
      chassis.drive_set(-power, power);
      pros::delay(10);
    };
    };
      public:
    void DrivePID (double target, double max){ //target is the positio to drive to in inches. Max is the maximum power up to 127. 
      double kP = .1;
      double kI = 0;
      double kD = 0;
      chassis.drive_sensor_reset(); //zeroes the encoders
      double P = target;// sets initial error
      double I = 0;
      double D = 0; // sets inital derivative
     while(fabs(P)>.1 && fabs(D)>0){
      double P0 = P; //copies our old p value before changing it
      P = target - (3.25*6.28318530718 * 36/60/300 * (chassis.drive_sensor_right()+chassis.drive_sensor_left())/2);//iterates error, inches = wheelsize [in] * 2pi [1/revW] * pinionteeth [revM]/driventeeth[revW] / encoderclicks/revM [1/revM] * encoderclicks [UL]
      I += P; //defines integral
      D = (P-P0)/10.0; //derivative as inches/ms
      double power = (kP*P + kI*I + kD*D); //puts all our statements together
      if (fabs(power) > max) { // limits the maximum power, keeps the sign of the power
        power = max*(power/fabs(power));
      }
      chassis.drive_set(power, power);
      pros::delay(10);
    };
    };
};

Triball triball = Triball();
DT PDrive = DT();

/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////






/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(false); // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(.1); // Sets the active brake kP. We recommend 0.1.
  chassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  //default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("skills",skills),
    Auton("Close", close),
    Auton("Far", far)
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset(); // Resets PID targets to 0
  chassis.drive_imu_reset(); // Reset gyro position to 0
  chassis.drive_sensor_reset(); // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call(); // Calls selected auton from autonomous selector
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
  
  while (true) {
    if (!pros::competition::is_connected()) { 
      if (master.get_digital_new_press(DIGITAL_B)) 
        autonomous();

      // chassis.pid_tuner_iterate(); // Allow PID Tuner to iterate
    } 

    //chassis.opcontrol_tank(); // Tank control
    chassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    triball.intake();
    triball.plow();
    triball.shoot();   
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME

    };
  
  }


/////
// For installation, upgrading, documentations and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
// const int DRIVE_SPEED = 127;  
// const int TURN_SPEED = 90;
// const int SWING_SPEED = 90;

// ///
// // Constants
// ///
// void default_constants() {
//   chassis.pid_heading_constants_set(3, 0, 20);
//   chassis.pid_drive_constants_set(0.45, 0, 5);
//   chassis.pid_turn_constants_set(3, 0, 20);
//   chassis.pid_swing_constants_set(5, 0, 30);

//   chassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
//   chassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
//   chassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

//   chassis.slew_drive_constants_set(7_in, 80);
// }


void close(){
  Intake = -127; //outtakes a preloaded alliance triball into a staged triball to give 4 points to the alliance
  chassis.drive_set(-60,-60); //back up to avoid touching triball on accident
  pros::delay(300); 
};


void closeWP(){};
void far(
){
  chassis.drive_set(-80,-80); //slams an alliance triball into the goal
  pros::delay(1200);
  chassis.drive_set(60,60);
  pros::delay(800); //drives forward to void touching triball
};
void farWP(){};



void skills() {

  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);
  flywheelMotor = 30;
  chassis.drive_set(-60,-60);
pros::delay(1000);
chassis.drive_set(-60,0);
pros::delay(300);
wings.set(true);
  flywheelMotor = 127;
  pros::delay(30000); //runs the flywheel for the time we want
  wings.set(false);
  flywheelMotor=0;
  pros::delay(300);
  chassis.drive_set(-60,60);
  pros::delay(900); //turns to face the goal
  chassis.drive_set(-60,-60);
  pros::delay(1100); //drives to by the wall
  chassis.drive_set(-60,60);
  pros::delay(150); //turns to be "down the tunnel"
  chassis.drive_set(-80,-80);
  pros::delay(1800); //kachow
  chassis.drive_set(60,-60);
  pros::delay(600);
  chassis.drive_set(-60,-60);
  wings.set(true);
  pros::delay(700);
    chassis.drive_set(60,60);
  pros::delay(500);
    chassis.drive_set(-60,-60);
  pros::delay(500);
  chassis.drive_set(60,60);
  pros::delay(5000);


};
void nothing();


// . . .
// Make your own autonomous functions here!
// . . .