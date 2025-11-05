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
 //! intake and move to get the 3 balls in the center, gets 2-1 of them most of the time
 //! with the rare triple grab
 frontIn.move(100);
  backIn.move(-100);
  chassis.pid_drive_set(29_in, 40);
 pros::delay(1000);
  chassis.pid_wait();

  //! moves back and turns to line up with the mid goal
  chassis.pid_drive_set(-5_in, 50);
  chassis.pid_wait();
  chassis.pid_turn_set(257_deg, 90);
  chassis.pid_wait();
  chassis.pid_drive_set(-15.5_in, 50);
  chassis.pid_drive_set(-15_in, 50);
  chassis.pid_wait();
  //! outakes balls
  frontIn.move(100);
  backIn.move(-100);
  topIn.move(-100);
  pros::delay(1500);
  //! goes to line up with the loader
  chassis.pid_drive_set(52_in, 80);
  chassis.pid_wait();
  chassis.pid_turn_set(215_deg, 90);
  chassis.pid_wait(); 
  Wings.set_value(true);
  pros::delay(500);
  frontIn.move(100);
  backIn.move(-100);
   chassis.pid_drive_set(15_in, 100);
   chassis.pid_wait(); 
   pros::delay(500);
    Aligner.set_value(true);
   chassis.pid_drive_set(-27_in, 60);
   chassis.pid_wait();
    frontIn.move(-100);
     backIn.move(100);
    topIn.move(100);
       pros:delay(1000);
   frontIn.move(100);
      backIn.move(-100);
      topIn.move(100);
}

void Auton_Functions::AWP2(){
  chassis.pid_turn_set(180_deg, 80); //Turn to match load
chassis.pid_wait();
chassis.pid_turn_set(90_deg, 80); //Turn to match load
chassis.pid_wait();
chassis.pid_turn_set(270_deg, 80); //Turn to match load
pros::delay(1000);
}

void Auton_Functions::Skills(){
 
}

//! RED FUNCTS

//* 8 Ball Long Left
void Auton_Functions::RED_Auton::r1(){
  //todo make swing movements work
  //todo tune speed on movements
  frontIn.move(100); //Intake
  backIn.move(-100); //Intake
  //todo add correct degree 
  //todo find timing for little will to grab balls
  chassis.pid_swing_set(RIGHT_SWING, 300, 100);
  chassis.pid_wait_quick();
  
  //todo add correct degree
  frontIn.move(0); //Stop Intake
  backIn.move(0); //Stop Intake
  chassis.pid_swing_set(RIGHT_SWING, 180, 100);
  chassis.pid_wait_quick();
  LittleW.extend();
  frontIn.move(100); //Intake
  backIn.move(-100); //Intake

  chassis.pid_drive_set(11, 100); //Drive into match load
  chassis.pid_wait_quick();
  pros::delay(500); //Wait to intake balls

  frontIn.move(0); //Stop Intake
  backIn.move(0); //Stop Intake
  chassis.pid_drive_set(-41.806, 100); //Drive into long goal
  chassis.pid_wait_quick();
  Wings.extend(); //Open Wings
  frontIn.move(100);
  backIn.move(-100);
  topIn.move(100);
  //todo check time
  pros::delay(4000); //Wait to outtake completly

  //todo tune to get balls into control zone
  chassis.pid_drive_set(5, 127); //Back up to ram
  chassis.pid_wait_quick();

  chassis.pid_drive_set(-5, 127); //Ram into long goal
  chassis.pid_wait_quick();
}

//* 5 Mid 3 Long Left
void Auton_Functions::RED_Auton::r2(){
  //todo make swing movements work
  //todo tune speed on movements
  frontIn.move(100); //Intake
  backIn.move(-100); //Intake
  //todo add correct degree 
  //todo find timing for little will to grab balls
  chassis.pid_swing_set(RIGHT_SWING, 300, 100);
  chassis.pid_wait_quick();

  frontIn.move(0); //Stop Intake
  backIn.move(0); //Stop Intake
  chassis.pid_drive_set(32.45, 100);//Drive back to mid goal
  chassis.pid_wait_quick();

  chassis.pid_turn_set(220, 100);//Turn to mid goal
  chassis.pid_wait_quick();

  chassis.pid_drive_set(-11.27,100); //Drive into mid goa;
  chassis.pid_wait_quick();
  //Outake to mid goal
  frontIn.move(100); 
  backIn.move(-100);
  topIn.move(-100);
  //todo tune time
  pros::delay(1000);
  //Stop Intake
  frontIn.move(0);
  backIn.move(0);
  topIn.move(0);

  chassis.pid_drive_set(55.14,100);//Drive to match load 
  chassis.pid_wait_quick();

  chassis.pid_turn_set(180 ,100); //Turn to match load
  chassis.pid_wait();
  LittleW.extend();//Put little will out

  chassis.pid_drive_set(18.82, 100);
  chassis.pid_wait_quick();
  frontIn.move(100); //Intake
  backIn.move(-100); //Intake

  frontIn.move(0); //Stop Intake
  backIn.move(0); //Stop Intake
  chassis.pid_drive_set(-41.806, 100); //Drive into long goal
  chassis.pid_wait_quick();
  Wings.extend(); //Open Wings
  frontIn.move(100);
  backIn.move(-100);
  topIn.move(100);
  //todo check time
  pros::delay(4000); //Wait to outtake completly

  //todo tune to get balls into control zone
  chassis.pid_drive_set(5, 127); //Back up to ram
  chassis.pid_wait_quick();

  chassis.pid_drive_set(-5, 127); //Ram into long goal
  chassis.pid_wait_quick();
}

void Auton_Functions::RED_Auton::r3(){
 
}

//? BLUE FUNCTS

//* 8 Ball Long Right
void Auton_Functions::BLUE_Auton::b1(){
 //todo add ram as last movement
 
}

//* 5 Mid 3 Long Right
void Auton_Functions::BLUE_Auton::b2(){

}

void Auton_Functions::BLUE_Auton::b3(){
  
}