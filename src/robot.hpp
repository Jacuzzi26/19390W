//#include "constants.h"
#include "main.h"

class Triball {
    private:
        bool isPlowing;

    public:
        Triball() {
            //Flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
            Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

            this->isPlowing = false;
        }

        void shoot() {
            double flywheelSpeed = flywheelMotor.get_actual_velocity()*5;
            if (master.get_digital(DIGITAL_R1)) {
                flywheelPID.target_set(flywheelTarget);
            }
            else if (master.get_digital(DIGITAL_R2)){
                flywheelPID.target_set(-flywheelTarget);
            }
            else{
                flywheelPID.target_set(0);
            }
            flywheelMotor = flywheelPID.compute(flywheelSpeed);

            // if (master.get_digital(DIGITAL_R1)) {
            //     Flywheel = 127;
            // }
            // else {
            // if (master.get_digital(DIGITAL_R2)) {
            //     Flywheel = -127;
            // }  
            // else {
            //     Flywheel = 0;
            // }}
        }

        void intake() {
            if (partner.get_digital(DIGITAL_R1)) {
                Intake = 127;
            } else {if (partner.get_digital(DIGITAL_R2)) {
                Intake = -127;
            } else {
                Intake = 0;
            }}
        }

        void plow() {
            wings.button_toggle(master.get_digital(DIGITAL_L2));
            // if (!isPlowing && master.get_digital(DIGITAL_L2)) {
            //     // TODO push out wings
            //     piston1.set_value(false);
            //     isPlowing = !isPlowing;
            // } else if (isPlowing && master.get_digital(DIGITAL_L2)) {
            //     // TODO bring in wings
            //     piston1.set_value(true);//for the dual acting, true is port A
            //     isPlowing = !isPlowing;
            // }
        }

};

// class Autonomous{
//     private:
//         int drivePower = 50; //default drive power
//         int turnPower = 50; //default turning power
//         int pipePower = 75; //default power to clear the pipe
//         Drivetrain drivetrain;
//     public:
//         Autonomous() {
//             drivetrain = Drivetrain(Drivetype::ARCADE);
//         }
        
//         void driverBase(){
//             Flywheel = 10;
//             pros::delay(200);
//             Flywheel = 0;
//             drivetrain.turnTo(45,turnPower);
//             drivetrain.driveTo(15,drivePower);
//             drivetrain.turnTo(-45,turnPower);
//             Intake = -127;
//             drivetrain.driveTo(4,drivePower);
//             Intake = 0;
//             drivetrain.driveTo(-8,drivePower);
//             drivetrain.turnTo(-180,turnPower);
//             Intake= 127;
//             drivetrain.driveTo(18,drivePower);
//             drivetrain.driveTo(6,pipePower);//more power to get over the loading hump
//             drivetrain.driveTo(-12,pipePower)
//             ;
//         }
//         void driver(){
//             driverBase();
//             drivetrain.turnTo(90,turnPower);
//             Flywheel = 127
//             ;
//         }
//         void driverPark(){
//             driverBase();
//             drivetrain.turnTo(45,turnPower);
//             drivetrain.driveTo(24,drivePower);
//             drivetrain.turnTo(45,turnPower);
//             drivetrain.driveTo(36,drivePower)
//             ;
//         }
//         void skills(){
//             drivetrain.driveTo(15,drivePower);
//             drivetrain.turnTo(-90,turnPower);
//             drivetrain.driveTo(-30,drivePower);
//             Flywheel = 127
//             ;
//         }
//         void scoreBase(){
//             Flywheel = 10;
//             pros::delay(200);
//             Flywheel = 0;
//             drivetrain.driveTo(60,drivePower);
//             drivetrain.turnTo(-90,turnPower);
//             Intake = -127;
//             drivetrain.driveTo(4, drivePower);
//             drivetrain.driveTo(-4, drivePower);
//             Intake = 0
//             ;
//         }
//         void score(){
//             scoreBase();
//             drivetrain.turnTo(180, turnPower);
//             Intake = 127;
//             drivetrain.driveTo(4,drivePower);
//             drivetrain.turnTo(180,turnPower);
//             Intake = -127;
//             drivetrain.driveTo(24, drivePower)
//             ;
//         }
//         void scorePark(){
//             scoreBase();
//             drivetrain.turnTo(90,turnPower);
//             drivetrain.driveTo(-55,drivePower);
//             drivetrain.turnTo(90,turnPower);
//             drivetrain.driveTo(36, drivePower)
//             ;
//         }
// };