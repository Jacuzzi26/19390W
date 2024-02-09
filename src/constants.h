// TODO update motor ports here

// Declarations for drivetrain motors
pros::Motor LeftFront (9);
pros::Motor RightFront (3);
pros::Motor LeftMiddle (10);
pros::Motor RightMiddle (2);
pros::Motor LeftRear (8);
pros::Motor RightRear (1);

pros::Motor Flywheel (4);
pros::Motor Intake (7);

// Controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);

// Handy Enums
enum DriveType { ARCADE, TANK };

// Gyro
pros::IMU inertial(6);

// Pneumatic controls here
pros::ADIDigitalOut piston1 (2);
