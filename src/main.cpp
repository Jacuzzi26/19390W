#include "main.h"
class Triball {


    public:
        Triball() {
            flywheelMotor.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

        }

        void shoot() {
            if (master.get_digital(DIGITAL_UP)) {
                flywheelMotor = -127;
            } else {if (master.get_digital(DIGITAL_DOWN)) {
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
            Lwing.button_toggle(master.get_digital(DIGITAL_L2));
            Rwing.button_toggle(master.get_digital(DIGITAL_R2));
      
        };
        void hang() {
          Hang.button_toggle(partner.get_digital(DIGITAL_A));
          Balance.button_toggle(master.get_digital(DIGITAL_A))
        }

};
// Chassis constructor
ez::Drive EZchassis (
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


Triball triball = Triball();

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
  EZchassis.opcontrol_curve_buttons_toggle(false); // Enables modifying the controller curve with buttons on the joysticks
  EZchassis.opcontrol_drive_activebrake_set(.1); // Sets the active brake kP. We recommend 0.1.
  EZchassis.opcontrol_curve_default_set(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  //default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("skills",skills),
    Auton("Close", closeWP),
    Auton("Far", far)
  });

  // Initialize chassis and auton selector
  EZchassis.initialize();
  LLchassis.calibrate();
  LLchassis.setPose(0,0,0);
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
void autonomous() {  EZchassis.drive_brake_set(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency
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
  EZchassis.drive_brake_set(MOTOR_BRAKE_HOLD);
  
  while (true) {
    if (!pros::competition::is_connected()) { 
      if (master.get_digital(DIGITAL_B)){
      autonomous();}
      pros::lcd::print(3, "kP: %f", kP);
      pros::lcd::print(4, "kD: %f", kD);
    }

    //chassis.opcontrol_tank(); // Tank control
    EZchassis.opcontrol_arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE); // Flipped single arcade

    triball.intake();
    triball.plow();
    triball.shoot();
    triball.hang();
    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME

    };
  
  }


void close(){

};


void closeWP(){


};
void far(){
LLchassis.setPose(0,0,0);
LLchassis.moveTo(0, 0, 5000);
LLchassis.moveTo(0, 21.117, 5000);// driveforward
LLchassis.moveTo(-26.362, 52.172, 5000); // lineup with middle triball
LLchassis.turnTo(-50,52.172,5000); //turn away from goal
LLchassis.moveTo(-10.076, 52.172, 5000);
LLchassis.moveTo(1.242, 52.172, 5000);
LLchassis.moveTo(-10.628, 52.172, 5000);
LLchassis.moveTo(1.38, 52.31, 5000);
LLchassis.moveTo(-29.26, 62.248, 5000);
LLchassis.moveTo(-30.089, 39.06, 5000);



};



void skills() {

LLchassis.setPose(0,0,0);
LLchassis.turnTo(30,0,5000);
  
};
void nothing();


// . . .
// Make your own autonomous functions here!
// . . .