#include "main.h"
#include "robot.h"
#include "autoSelect/selection.h"
//#include "auton.h"

// TODO set controller style here
Drivetrain drivetrain = Drivetrain(DriveType::ARCADE);
Triball triball = Triball();
// Autonomous autonomous = Autonomous();


/**
Screen setup and pre ran funtions
 */
void initialize () { 
	
	pros::lcd::initialize(); 
	pros::lcd::set_background_color(57, 255, 20);

	pros::lcd::print(0, "Calibrating...");

	// TODO need to test this.. potential risk of infinite loop if pros::delay stops calibration
	// feel free to comment out if doesn't work or is hanging up
	pros::delay(3000);
	// while (inertial.is_calibrating()) {
	// 	pros::delay(100)
	// }

	pros::lcd::print(1, "Dat Wascally Wabbit");
	selector::init();

	

}

/**
diabled screen output
 */
void disabled() {}

/**
Comp intialization
 */
void competition_initialize() {}

/**
Auto code runs here
 */
void autonomous() {
	pros::delay(2);
	if(selector::auton == 1){Intake = -127;
	pros::delay(1000);
	drivetrain.driveTo(-500, 20);
	Intake = 0;} //driver
	if(selector::auton == 2){} //driverpark
	if(selector::auton == 3){} //score
	if(selector::auton == 4){} //scorepark
	if(selector::auton == 5){} //nothing
	if(selector::auton == 0){
		Flywheel = -127;
		//pros::delay(45000);

	} //skills

}

/**
Driver control
 */
void opcontrol () {

	while (true) {
		drivetrain.kachow();
		triball.shoot();
		triball.intake();
		triball.plow();
		
		pros::delay(2);	
	}
}