// // #include "constants.h"
// //#include "main.h"

// class Triball {


//     public:
//         Triball() {
//             //Flywheel.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
//             Intake.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

//             this->isPlowing = false;
//         }

//         void shoot() {
//             double flywheelSpeed = flywheelMotor.get_actual_velocity()*5;
//             if (master.get_digital(DIGITAL_R1)) {
//                 flywheelPID.target_set(flywheelTarget);
//             }
//             else if (master.get_digital(DIGITAL_R2)){
//                 flywheelPID.target_set(-flywheelTarget);
//             }
//             else{
//                 flywheelPID.target_set(0);
//             }
//             flywheelMotor = flywheelPID.compute(flywheelSpeed);


//         }

//         void intake() {
//             if (partner.get_digital(DIGITAL_R1)) {
//                 Intake = 127;
//             } else {if (partner.get_digital(DIGITAL_R2)) {
//                 Intake = -127;
//             } else {
//                 Intake = 0;
//             }}
//         }

//         void plow() {
//             wings.button_toggle(master.get_digital(DIGITAL_L2));
//         };


// };

