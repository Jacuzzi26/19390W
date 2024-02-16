
// Declarations for systems motors

pros::Motor flywheelMotor (4, pros::E_MOTOR_GEARSET_06);
pros::Motor Intake (7);
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
int IMU_port = 6;
pros::Imu imu_sensor(IMU_port);