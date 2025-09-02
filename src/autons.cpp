#include "main.h"

using namespace pros;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

///
// Constants
///
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(19.9, 0.01, 200.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(0.8, 0.0, 3.75, 14.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}

// . . .
// Make your own autonomous functions here!
// . . .


/**
 * @brief Base function for win point auton (used for the left side of the field)
 */
void Auton_Functions::AWP1(){
 chassis.pid_drive_set(18_in, 110); //Drive forward 24in
 chassis.pid_wait();
 chassis.pid_turn_set(25_deg, 110); //Turn to face win point
 chassis.pid_wait();
 frontIn.move(70); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(20_in, 75); //Drive into win point
 chassis.pid_wait();
 chassis.pid_turn_set(45_deg, 110); //Turn to face next balls
 chassis.pid_wait();
 chassis.pid_drive_set(10_in, 100); //Drive into win point
 chassis.pid_wait();
 frontIn.move(70);
 backIn.move(70);
 topIn.move(-70);
 pros::delay(700);
 frontIn.brake();
 backIn.brake();
 topIn.brake();
 chassis.pid_drive_set(-14_in, 110); //Back away from win point
 chassis.pid_wait();
 chassis.pid_turn_set(95_deg, 110); //Turn to face next balls
 chassis.pid_wait();
 frontIn.move(70); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(35_in, 110); //Drive into next balls
 chassis.pid_wait();
 chassis.pid_drive_set(15_in, 75); //Back away from balls
 chassis.pid_wait();
 chassis.pid_turn_set(-44_deg, 110); //Turn to face goal
 chassis.pid_wait();
 chassis.pid_drive_set(21_in, 110); //Drive into goal
 chassis.pid_wait();
 frontIn.move(-70);
 backIn.move(70);
 pros::delay(1500);
}

/**
 * @brief mirrored function for win point auton (used for the right side of the field)
 */
void Auton_Functions::AWP2(){
  // Drive forward 24in
}

/**
 * @brief function for Skills auton
 */
void Auton_Functions::Skills(){

}

//! RED FUNCTS
/**
 * @brief base function for goal rush (we didn't complete it)
 * 
 */
void Auton_Functions::RED_Auton::r1(){
 
}

/**
 * @brief base function for ring rush (best auton we've had)
 * 
 */
void Auton_Functions::RED_Auton::r2(){
  
}

/**
 * @brief These are functions that we never got to develop/ mirror 
 */
void Auton_Functions::RED_Auton::r3(){

}

//? BLUE FUNCTS
/**
 * @brief These are functions that are mirrored so develop red functs 
 */
void Auton_Functions::BLUE_Auton::b1(){
  chassis.odom_theta_flip();
  
  RED_Auton::r1();
}

void Auton_Functions::BLUE_Auton::b2(){
  chassis.odom_theta_flip();
  
  RED_Auton::r2();
}

void Auton_Functions::BLUE_Auton::b3(){
  chassis.odom_theta_flip();
  
  RED_Auton::r3();
}