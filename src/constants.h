// Declarations for systems motors
#include "lemlib/api.hpp"
pros::Motor flywheelMotor (11, pros::E_MOTOR_GEARSET_06);
pros::Motor Intake (14);
double flywheelTarget = 2600;

//Flywheel PID
ez::PID flywheelPID{1,.001, 4, 100, "Flywheel"};


// Controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Controller partner(pros::E_CONTROLLER_PARTNER);



// Pneumatic controls here
//pros::ADIDigitalOut piston1 (2);
ez:: Piston wings(2);

//IMU declaration
int IMU_port = 12;
pros::Imu imu_sensor(IMU_port);

//lemlib motors
pros::Motor FR(19, pros::E_MOTOR_GEARSET_06, false);
pros::Motor BR(16, pros::E_MOTOR_GEARSET_06, false);
pros::Motor TR(17, pros::E_MOTOR_GEARSET_06, true);
pros::Motor FL(20, pros::E_MOTOR_GEARSET_06, true);
pros::Motor BL(15, pros::E_MOTOR_GEARSET_06, true);
pros::Motor TL(18, pros::E_MOTOR_GEARSET_06, false); // state bot

pros::MotorGroup LDrive({FL,BL,TL});
pros::MotorGroup RDrive({FR,BR,TR});

lemlib::Drivetrain_t lemDrive {
    &LDrive, // left drivetrain motors
    &RDrive, // right drivetrain motors
    9.9, // track width (SET THIS)
    3.25, // wheel diameter
    360 // wheel rpm
};
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &imu_sensor// inertial sensor
};
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

lemlib::Chassis chassis(lemDrive, lateralController, angularController, sensors);