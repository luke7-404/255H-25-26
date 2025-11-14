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
  chassis.pid_turn_constants_set(0.9, 0.15, 3.65, 14.0);     // Turn in place constants
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



//Solo AWP 
void Auton_Functions::AWP1(){
 //Drive to mid goal
 chassis.pid_drive_set(41, 100);
 chassis.pid_wait_quick();

 //Turn to mid goal
 chassis.pid_turn_set(230, 100);
 chassis.pid_wait_quick();
 topIn.move(-127);

 //Drive into mid goal and outtake match load
 chassis.pid_drive_set(-8, 50);
 chassis.pid_wait_quick();
 topIn.move(-127);

 //Turn to balls
 chassis.pid_swing_set(RIGHT_SWING, 90, 100);
 chassis.pid_wait_quick();

 //Drive to balls and intake
 chassis.pid_drive_set(25, 100);
 chassis.pid_wait_quick();
 frontIn.move(127);
 backIn.move(-127);

 //Turn to middle goal
 chassis.pid_turn_set(310, 100);
 chassis.pid_wait_quick();

 //Drive to mid goal
 chassis.pid_drive_set(-18.65, 100);
 chassis.pid_wait_quick();
 topIn.move(-127);//Outtake to mid goal

 //Drive to match load
 chassis.pid_drive_set(55.14, 100);
 chassis.pid_wait_quick();
}

void Auton_Functions::AWP2(){
 chassis.pid_drive_set(-30, 70);
 chassis.pid_wait();
}

void Auton_Functions::Skills(){
 
}

//! RED FUNCTS

//* 7  Ball Long Left
void Auton_Functions::RED_Auton::r1(){
  //todo tune speed on movements
  //todo fix distances on marked movements
  frontIn.move(40); //Intake
  backIn.move(-127); //Intake
  topIn.move(30); //Intake

  chassis.pid_drive_set(15, 100);
  chassis.pid_wait_quick();

  chassis.pid_turn_set(-35, 100);
  chassis.pid_wait();

  chassis.pid_drive_set(21, 50);
  chassis.pid_wait_quick();

  chassis.pid_turn_set(-146, 100);
  chassis.pid_wait_quick();

  chassis.pid_drive_set(37, 80);
  chassis.pid_wait();

  chassis.pid_turn_set(-180, 100);
  chassis.pid_wait_quick();
  LittleW.extend();

  chassis.pid_drive_set(15, 70);
  chassis.pid_wait_quick();
  pros::delay(50);

  chassis.pid_drive_set(-28, 80, false, true);
  chassis.pid_wait_quick();
  Wings.extend();
  frontIn.move(127); //Intake
  backIn.move(-127); //Intake
  topIn.move(127); //Intake

}

//* 4 Mid 3 Long Left
void Auton_Functions::RED_Auton::r2(){

  //* 1 ball held
  chassis.pid_drive_set(14.119, 100); // Drive off park zone
  chassis.pid_wait_quick();

  //-30
  chassis.pid_turn_set(330, 100); // Turn to balls
  chassis.pid_wait_quick();
  frontIn.move(127); //Intake
  backIn.move(-127); //Intake
  topIn.move(127); //Intake

  //todo tune to get all 3 every time
  chassis.pid_drive_set(20.977, 40); // Drive into balls
  chassis.pid_wait_quick();
  //* 4 balls held

  //-135
  chassis.pid_turn_set(225, 100); // Turn to balls
  chassis.pid_wait_quick();

  //* Score 4 on mid goal
  chassis.pid_drive_set(-19.297, 100); // Drive to mid goal
  chassis.pid_wait_quick();
  frontIn.move(127); //Intake
  backIn.move(-127); //Intake
  topIn.move(-127); //Intake
  //todo correct timing
  pros::delay(300); //Wait to outtake 4 balls

  chassis.pid_drive_set(53.724, 100); //Drive to long goal
  chassis.pid_wait_quick();

  //-180
  chassis.pid_turn_set(180, 100);
  chassis.pid_wait_quick();
  LittleW.extend();
  backIn.move(-50);
  topIn.move(0); //Intake

  //* 3 Balls held
  //todo fix distance so it doesn't do the stopping thing
  chassis.pid_drive_set(21.049, 100, true, true); //Drive into match load
  chassis.pid_wait_quick();

  //* Score 3 on long goal
  //todo fix distance so it doesn't do the stopping thing
  chassis.pid_drive_set(39.666, 100, false, true); //Drive into long goal
  chassis.pid_wait_quick();
  backIn.move(-127); //Intake
  topIn.move(127); //Intake
}

void Auton_Functions::RED_Auton::r3(){
  //todo tune speed on movements
  //todo fix distances on marked movements
  frontIn.move(40); //Intake
  backIn.move(-127); //Intake
  topIn.move(30); //Intake

  chassis.pid_drive_set(15, 100);
  chassis.pid_wait_quick();

  chassis.pid_turn_set(-35, 100);
  chassis.pid_wait();

  chassis.pid_drive_set(21, 50);
  chassis.pid_wait_quick();

  chassis.pid_turn_set(-146, 100);
  chassis.pid_wait_quick();

  chassis.pid_drive_set(37, 80);
  chassis.pid_wait();

  chassis.pid_turn_set(-180, 100);
  chassis.pid_wait_quick();
  LittleW.extend();

  chassis.pid_drive_set(15, 70);
  chassis.pid_wait_quick();
  pros::delay(50);

  chassis.pid_drive_set(-28, 80, false, true);
  chassis.pid_wait_quick();
  Wings.extend();
  frontIn.move(127); //Intake
  backIn.move(-127); //Intake
  topIn.move(127); //Intake
}

//? BLUE FUNCTS

//* 7 Ball Long Right
void Auton_Functions::BLUE_Auton::b1(){
}

//* 4 Mid 3 Long Right
void Auton_Functions::BLUE_Auton::b2(){

}

void Auton_Functions::BLUE_Auton::b3(){
  
}