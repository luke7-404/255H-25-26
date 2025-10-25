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



void Auton_Functions::AWP1(){
 
}

//Test AWP 2
void Auton_Functions::AWP2(){
  chassis.pid_turn_set(180_deg, 80); //Turn to match load
chassis.pid_wait();
chassis.pid_turn_set(90_deg, 80); //Turn to match load
chassis.pid_wait();
chassis.pid_turn_set(270_deg, 80); //Turn to match load
pros::delay(1000);
}


void Auton_Functions::Skills(){
 
 //test
}

//! RED FUNCTS

void Auton_Functions::RED_Auton::r1(){
 //! intake and move to get the 3 balls in the center, gets 2-1 of them most of the time
 //! with the rare triple grab
 frontIn.move(100);
  backIn.move(-100);
  chassis.pid_drive_set(32_in, 40);
 chassis.pid_wait_until(24_in);
 pros::delay(1000);
  chassis.pid_wait();

  //! moves back and turns to line up with the mid goal
  chassis.pid_drive_set(-5_in, 50);
  chassis.pid_wait();
  chassis.pid_turn_set(257_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-13.75_in, 50);
  chassis.pid_wait();
  //! outakes balls
  frontIn.move(100);
  backIn.move(-100);
  topIn.move(-100);
  pros::delay(1500);
  //! goes to line up with the loader
  chassis.pid_drive_set(48_in, 80);
  chassis.pid_wait();
  chassis.pid_turn_set(210_deg, 90);
  chassis.pid_wait(); 
  LittleW.set_value(true);
  frontIn.move(100);
  backIn.move(-100);
   chassis.pid_drive_set(15_in, 40);
   chassis.pid_wait(); 
   pros::delay(2000);
     Aligner.set_value(true);
   chassis.pid_drive_set(-25_in, 60);
   chassis.pid_wait();
   frontIn.move(100);
      backIn.move(-100);
      topIn.move(100);

/*
 //! Drive 6 of the 24 inches at 30 speed then go to 110 speed
  chassis.pid_drive_set(24_in, 30);
 chassis.pid_wait_until(6_in);
  chassis.pid_wait();

 chassis.slew_drive_set(true); //! Set the drive movements to slew movements
 chassis.slew_drive_constants_set(3_in, 50); //! Start at 50 percent speed for 3 inches
 //! Left Side
 //! ADD PISTON AND INTAKE COMMANDS
 chassis.pid_drive_set(47.53_in, 100, true); //! Drive off park bar
 chassis.pid_wait_quick();
 //! Little will
 chassis.pid_turn_set(270_deg, 100, false); //! Turn to match load
 chassis.pid_wait_quick();
 //! Intake
 chassis.pid_drive_set(16.53_in, 100, true); //! Drive into match load
 chassis.pid_wait_quick();
 pros::delay(100); //! CHANGE TO CORRECT TIME
 chassis.pid_drive_set(39.27_in, 100, true); //! Drive into long goal
 chassis.pid_wait_quick();
 //! Open wings
 //! Stop Intake
 chassis.pid_drive_set(-15.51_in, 100, false); //! Drive out of long goal
 chassis.pid_wait_quick();
 chassis.pid_turn_set(140_deg, 100, false); //! Turn to middle 3 balls
 chassis.pid_wait_quick();
 //! Close wings
 chassis.pid_drive_set(31.69_in, 100, false);//! Drive to middle balls
 chassis.pid_wait_until(28_in); //! Wait until it gets to 28
 chassis.pid_speed_max_set(60); //! Set speed to 60 when it reaches 28
 chassis.pid_wait_quick();
 chassis.pid_drive_set(17.24_in, 100, true); //! Drive rest of distance to middle goal
 chassis.pid_wait_quick();
 //! Intake*/
}


void Auton_Functions::RED_Auton::r2(){
  
}


void Auton_Functions::RED_Auton::r3(){
 
}

//? BLUE FUNCTS

void Auton_Functions::BLUE_Auton::b1(){
 
}

void Auton_Functions::BLUE_Auton::b2(){

}

void Auton_Functions::BLUE_Auton::b3(){
  
}