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
  chassis.pid_turn_exit_condition_set(50_ms, 3_deg, 100_ms, 7_deg, 100_ms, 100_ms);
  chassis.pid_swing_exit_condition_set(50_ms, 3_deg, 100_ms, 7_deg, 100_ms, 100_ms);
  chassis.pid_drive_exit_condition_set(50_ms, 1_in, 100_ms, 3_in, 100_ms, 100_ms);
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
  chassis.pid_drive_set(48, 127, false, true); // drive to loader
  chassis.pid_wait_quick();
  chassis.pid_turn_set(-90, 127); //turn to loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(48, 127, false, true); // drive to loader
  chassis.pid_wait_quick();
  chassis.pid_turn_set(-180, 127); //turn to loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(48, 127, false, true); // drive to loader
  chassis.pid_wait_quick();
  chassis.pid_turn_set(-270, 127); //turn to loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(48, 127, false, true); // drive to loader
  chassis.pid_wait_quick();
  chassis.pid_turn_set(0, 127); //turn to loader
  chassis.pid_wait_quick();
  pros::delay(500);
}

void Auton_Functions::AWP2(){   
 chassis.pid_swing_set(LEFT_SWING, 180, 127);
  chassis.pid_wait();
  pros::delay(500);
}

void Auton_Functions::Skills(){

  botIn.move(-127); // Start intake
  chassis.pid_drive_set(34, 80); // drive to loader
  chassis.pid_wait();
  chassis.pid_turn_set(90, 80); //turn to loader
  chassis.pid_wait();
  chassis.pid_drive_set(-10, 80); // back up
  chassis.pid_wait();
  LittleW.extend();   // extend pneumatics
  chassis.pid_drive_set(21, 60); // drive into loader
  pros::delay(2200);
  chassis.pid_drive_set(-34, 70); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(-80); // outtake
  pros::delay(2200);
  topIn.brake(); // stop scoring
  chassis.pid_drive_set(15, 80); // drive out long goal
  chassis.pid_wait_quick();
  LittleW.retract();   // retract pneumatics
  chassis.pid_turn_set(218, 80); //turn to mid balls
  chassis.pid_wait();
  chassis.pid_drive_set(28, 60); // drive into mid balls
  chassis.pid_wait();
   chassis.pid_drive_set(-28, 60); // drive back to line up with long goal
  chassis.pid_wait();
  chassis.pid_turn_set(90, 80); //turn to long goal
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 80); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(-80); // outtake
  pros::delay(1200);
   chassis.pid_drive_set(15, 80); // drive out right long goal
  chassis.pid_wait_quick();
  topIn.brake(); // stop scoring
  chassis.pid_turn_set(195, 80); //turn to left side mid balls
  chassis.pid_wait();
   chassis.pid_drive_set(80, 80); // drive out right long goal
  chassis.pid_wait_quick();
  chassis.pid_turn_set(130, 80); //turn to long goal
  chassis.pid_wait();
  chassis.pid_drive_set(28, 80); // drive out right long goal
  chassis.pid_wait_quick();
   chassis.pid_turn_set(90, 80); //turn to loader
  chassis.pid_wait();
  chassis.pid_drive_set(-10, 80); // back up
  chassis.pid_wait();
  LittleW.extend();   // extend pneumatics
  chassis.pid_drive_set(21, 60); // drive into loader
  pros::delay(2200);
  chassis.pid_drive_set(-34, 70); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(-80); // outtake
  pros::delay(2200);
  chassis.pid_drive_set(10, 70); // drive into long goal
  chassis.pid_wait_quick();
  chassis.pid_turn_set(70, 80); //turn to long goal
  chassis.pid_wait();
   chassis.pid_drive_set(35, 70); // drive into long goal
  chassis.pid_wait_quick();
   chassis.pid_turn_set(0, 80); //turn to long goal
  chassis.pid_wait();
  chassis.pid_drive_set(30, 70); // drive into long goal
  chassis.pid_wait_quick();
}

//! RED FUNCTS

// 7 left
void Auton_Functions::RED_Auton::r1(){
  chassis.pid_drive_set(14, 80); // Drive off park zone
 chassis.pid_wait_quick();
  chassis.pid_turn_set(340, 100); // Turn to balls
  chassis.pid_wait_quick();
   botIn.move(-127); // Start intake
  topIn.move(20); // outtake
  chassis.pid_drive_set(16, 80); // Drive into balls
  chassis.pid_wait();  //* 4 balls held
  chassis.pid_turn_set(225, 80); //turn to loader
  chassis.pid_wait_quick();

  chassis.pid_drive_set(37, 100); // drive to loader
  chassis.pid_wait();

  chassis.pid_turn_set(-180, 80); //turn to loader
  chassis.pid_wait_quick();
  LittleW.extend();   // extend pneumatics
  pros::delay(100);
  chassis.pid_drive_set(-5, 80); // drive into loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(15, 80); // drive into loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-32, 100); // drive into loader
  chassis.pid_wait_quick();
  topIn.move(-127); // outtake
  botIn.move(-127); // Start intake
  pros::delay(10000);
  
} 

// 7 right
void Auton_Functions::RED_Auton::r2(){
  chassis.pid_drive_set(14, 80); // Drive off park zone
 chassis.pid_wait();
  chassis.pid_turn_set(20, 100); // Turn to balls
  chassis.pid_wait();
  botIn.move(-127); // Start intake
  topIn.move(20); // outtake
  chassis.pid_drive_set(16, 80); // Drive into balls
  chassis.pid_wait();  //* 4 balls held
  botIn.brake();
  topIn.brake();
  chassis.pid_turn_set(135, 80); //turn to loader
  chassis.pid_wait_quick();

  chassis.pid_drive_set(37, 100); // drive to loader
  chassis.pid_wait();

  chassis.pid_turn_set(180, 80); //turn to loader
  chassis.pid_wait();
  LittleW.extend();   // extend pneumatics
  pros::delay(100);
  botIn.move(-100); // Start intake
  topIn.move(20); // outtake
  chassis.pid_drive_set(-5, 80); // back up
  chassis.pid_wait_quick();
  chassis.pid_drive_set(15, 80); // drive into loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-32, 100); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(127); // outtake
  botIn.move(50); // Start intake
  pros::delay(50); 
  topIn.move(-127); // outtake
  botIn.move(-127); // Start intake
  pros::delay(2000);
}

void Auton_Functions::RED_Auton::r3(){
  chassis.pid_drive_set(3, 100);
chassis.pid_wait();
}

//? BLUE FUNCTS

// SAWP
void Auton_Functions::BLUE_Auton::b1(){
  LittleW.extend();
  chassis.pid_drive_set(35,110); // drive to loader
  chassis.pid_wait();
  chassis.pid_turn_set(90, 110); //turn to loader
  chassis.pid_wait();
  botIn.move(-127);
  chassis.pid_drive_set(11.2, 60); // drive into loader
  chassis.pid_wait_quick();
  pros::delay(75);
  chassis.pid_drive_set(-32, 127); // drive into long goal
    LittleW.retract();
  chassis.pid_wait_quick();
 topIn.move(127); // outtake
  botIn.move(80); // Start intake
  pros::delay(25); 
  topIn.move(-127); // outtake
  botIn.move(-127); // Start intake
  pros::delay(1000);
  chassis.pid_swing_set(LEFT_SWING, 180, 110, -110);
  chassis.pid_wait();
   topIn.brake();
  chassis.pid_drive_set(62, 80); // drive into long goal
  chassis.pid_wait_quick();
  chassis.pid_turn_set(130, 110); //turn to loader
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-20.5, 110); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(-60); // outtake
  botIn.move(-127); // Start intake
  pros::delay(280);
  topIn.brake(); // outtake
  botIn.brake(); // Start intake
  chassis.pid_drive_set(10, 110); // drive out the goal
  chassis.pid_wait_quick();
  chassis.pid_turn_set(140, 127); //turn to between loader and goal
  chassis.pid_wait_quick();
    chassis.pid_drive_set(39 , 100); // drive into long goal
  chassis.pid_wait_quick();
   chassis.pid_turn_set(90, 127); //turn to loader
  chassis.pid_wait();
  chassis.pid_drive_set(-15, 127); // drive into long goal
  chassis.pid_wait_quick();
  topIn.move(127); // outtake
  botIn.move(50); // Start intake
  pros::delay(50); 
  topIn.move(-127); // outtake
  botIn.move(-127); // Start intake
  pros::delay(1000);
  chassis.pid_drive_set(15, 127); // drive into long goal
  chassis.pid_wait_quick();
  pros::delay(1000);
}

// 3/4 left 
void Auton_Functions::BLUE_Auton::b2(){
    topIn.move(-85); // outtake
  botIn.move(-127); // Start intake
   pros::delay(1000);
}

void Auton_Functions::BLUE_Auton::b3(){
chassis.pid_drive_set(-35, 100);
chassis.pid_wait();
chassis.pid_turn_set(45, 80); //turn to loader
chassis.pid_wait_quick();
topIn.move(-90); // outtake
botIn.move(-127); // Start intake
pros::delay(1000);
botIn.move(-127);
topIn.move(25);
chassis.pid_turn_set(50, 80); //turn to loader
chassis.pid_wait_quick();
chassis.pid_drive_set(52, 100); // drive into loader
chassis.pid_wait_quick();
chassis.pid_turn_set(0, 80); //turn to loader
chassis.pid_wait_quick();
LittleW.extend();   // extend pneumatics
pros::delay(100);
chassis.pid_drive_set(-5, 80); // drive into loader
chassis.pid_wait_quick();
chassis.pid_drive_set(19, 60); // drive into loader
chassis.pid_wait_quick();
pros::delay(200);
chassis.pid_drive_set(-30, 100); // drive into loader
chassis.pid_wait_quick();
topIn.move(-127); // outtake
botIn.move(-127); // Start intake
pros::delay(2000);
}