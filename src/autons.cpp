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



void Auton_Functions::AWP1(){
 frontIn.move(70); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(34.7_in, 80);//Drive into balls
 chassis.pid_wait();
 chassis.pid_drive_set(-6_in, 127);
 chassis.pid_wait();
 chassis.pid_turn_set(65_deg, 127);//Turn to mid goal
 chassis.pid_wait();
 chassis.pid_drive_set(16.5_in, 127);//Drive into mid goal
 chassis.pid_wait();
 frontIn.move(70); //Outake balls
 backIn.move(70); //Outake balls
 topIn.move(-70); //Outake balls
 pros::delay(800); 
 frontIn.move(70); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(-12.5_in, 127);//Drive out of low goal
 chassis.pid_wait();
 chassis.pid_turn_set(106_deg, 127);//Turn to low goal balls
 chassis.pid_wait();
 chassis.pid_drive_set(37.1_in, 127);//Drive most of distance to low goal balls
 chassis.pid_wait();
 chassis.pid_drive_set(10_in, 75);//Drive rest of distance to low goal balls
 chassis.pid_wait();
 chassis.pid_turn_set(335_deg, 127);//Turn to low goal
 chassis.pid_wait();
 chassis.pid_drive_set(17.8_in, 127);//Drive into low goal
 chassis.pid_wait();
 frontIn.move(-70); //Outake balls
 backIn.move(70); //Outake Balls
 pros::delay(1500); //CHANGE TO CORRECT TIME
 frontIn.move(70); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(-57.2_in, 127);//Back up to infront of match load
 chassis.pid_wait();
 chassis.pid_turn_set(195_deg, 127);//Turn to match load
 LittleW.extend(); //Extend Little Will
 chassis.pid_wait();
 chassis.pid_drive_set(13.1_in, 127);//Drive into match load
 chassis.pid_wait();
 pros::delay(400); //Wait to load balls
 chassis.pid_drive_set(-22.1_in, 127);//Back away from match load
 LittleW.retract(); //Retract Little Will
 chassis.pid_wait();
 chassis.pid_turn_set(15_deg, 127);//Turn to long goal
 chassis.pid_wait();
 chassis.pid_drive_set(6_in, 127);//Drive into long goal
 chassis.pid_wait();
 frontIn.move(70);
 backIn.move(70);
 topIn.move(70);
 pros::delay(2000);
}

//Test AWP 2
void Auton_Functions::AWP2(){

}


void Auton_Functions::Skills(){
 chassis.pid_drive_set(47.3_in, 90);//Drive off park zone and toward match load
 chassis.pid_wait();
 chassis.pid_turn_set(270_deg, 80); //Turn to match load
 chassis.pid_wait();
 LittleW.extend(); //Extend Little Will
 frontIn.move(100); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(16.2, 70); //Drive into match load
 chassis.pid_wait();
 chassis.pid_drive_set(-7_in, 100); //Back away from match load
 chassis.pid_wait();
 chassis.pid_drive_set(7_in, 50); //Drive forward a bit
 chassis.pid_wait();
 pros::delay(1500);
 chassis.pid_drive_set(-21_in, 90); //Drive out of match load
 chassis.pid_wait();
 chassis.pid_turn_set(90_deg, 90); //Turn to high goal
 chassis.pid_wait();
 Aligner.toggle(); //Put aligner down
 LittleW.retract(); //Retract Little Will
 chassis.pid_drive_set(10_in, 80); //Drive into high goal
 chassis.pid_wait();
 chassis.pid_drive_set(-4_in, 127); //Back away from high goal
 chassis.pid_wait();
 chassis.pid_drive_set(4_in, 127); //Drive into high goal
 chassis.pid_wait();
 frontIn.move(70); // Outake balls
 backIn.move(70); // Outake balls
 topIn.move(70); // Outake balls
 pros::delay(5000);
 frontIn.move(0);
 backIn.move(0);
 topIn.move(0);
 chassis.pid_drive_set(-8_in, 90); //Back away from high goal
 chassis.pid_wait();
 chassis.pid_turn_set(180_deg, 90); //Turn to other side of field 
 chassis.pid_wait();
 frontIn.move(-100);
 backIn.move(100);
 chassis.pid_drive_set(25_in, 90); //Drive to other side of field
 chassis.pid_wait();
 chassis.pid_turn_set(270_deg, 80); //Turn to match load
 chassis.pid_wait();
 chassis.pid_drive_set(18, 80); //Drive into match load
 chassis.pid_wait();
 chassis.pid_swing_set(ez::RIGHT_SWING, 180_deg, 90); //Swing to face the wall
 chassis.pid_wait();
 chassis.pid_drive_set(-10_in, 90); //Back up to wall
 chassis.pid_wait();
 chassis.pid_drive_set(55_in, 127); //Back up to wall
 chassis.pid_wait();

}

//! RED FUNCTS

void Auton_Functions::RED_Auton::r1(){
  chassis.pid_swing_set(ez::LEFT_SWING, 90_deg, 90); //Swing to face the wall
  chassis.pid_wait();
}


void Auton_Functions::RED_Auton::r2(){
  frontIn.move(100); //Spin to intake balls
  backIn.move(-70); //Spin to intake balls
  chassis.pid_drive_set(34.7_in, 70); //Drive into balls
  chassis.pid_wait();
  chassis.pid_drive_set(-9_in, 90); //Back to line up
  chassis.pid_wait();
  frontIn.move(0);
  backIn.move(0);
  chassis.pid_turn_set(300_deg, 90); //Turn to mid goal
  chassis.pid_wait();
  chassis.pid_drive_set(18_in, 90); //Drive into mid goal
  chassis.pid_wait();
  frontIn.move(-50); //Outake balls
  backIn.move(65); //Outake balls
  pros::delay(2300);
  frontIn.move(0); 
  backIn.move(0);
  topIn.move(0);
  chassis.pid_drive_set(-49_in, 90); //Drive out of middle goal to match load
  chassis.pid_wait();
  chassis.pid_turn_set(170_deg, 90); //Turn to match load
  chassis.pid_wait();
  pros::delay(200);
  LittleW.extend(); //Extend Little Will
  frontIn.move(100); //Spin to intake balls
  backIn.move(-70); //Spin to intake balls
  pros::delay(100);
  chassis.pid_drive_set(23.93_in, 70);  //Drive into match load
  chassis.pid_wait();
  chassis.pid_drive_set(-20.1_in, 100); //Back away from match load
  chassis.pid_wait(); 
  Aligner.toggle(); //Put aligner down
  LittleW.retract(); //Retract Little Will
  chassis.pid_turn_set(355_deg, 90); //Turn to long goal
  chassis.pid_wait();
  chassis.pid_drive_set(10_in, 90); //Drive into long goal
  chassis.pid_wait();
  frontIn.move(70); // Outake balls
  backIn.move(70); // Outake balls
  topIn.move(70); // Outake balls
  pros::delay(15000); 
}


void Auton_Functions::RED_Auton::r3(){
 frontIn.move(100); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 chassis.pid_drive_set(34.7_in, 70);//Drive into balls
 chassis.pid_wait();
 chassis.pid_drive_set(-6_in, 90);// Back to line up
 chassis.pid_wait();
 frontIn.move(0);
 backIn.move(0);
 chassis.pid_turn_set(65_deg, 90);//Turn to mid goal
 chassis.pid_wait();
 chassis.pid_drive_set(15.5_in, 90);//Drive into mid goal
 chassis.pid_wait();
 frontIn.move(70); //Outake balls
 backIn.move(70); //Outake balls
 topIn.move(-70); //Outake balls
 pros::delay(2300); 
 frontIn.move(0);
 backIn.move(0);
 topIn.move(0);
 chassis.pid_drive_set(-44_in, 90); //Drive out of middle goal to match load
 chassis.pid_wait();
 chassis.pid_turn_set(190_deg, 90);// Turn to match load
 chassis.pid_wait();
 pros::delay(200); //Wait to get lined up
 LittleW.extend(); //Extend Little Will
 frontIn.move(75); //Spin to intake balls
 backIn.move(-70); //Spin to intake balls
 pros::delay(100); //Wait for Little Will to extend and stuff
 LittleW.extend(); //Extend Little Will
 chassis.pid_drive_set(23.93_in, 70);//Drive into match load
 chassis.pid_wait(); 
 chassis.pid_drive_set(-20.1_in, 90);//Back away from match load
 chassis.pid_wait();
 Aligner.toggle(); //Put aligner down
 LittleW.retract(); //Retract Little Will 
 chassis.pid_turn_set(5_deg, 90);// Turn to long goal
 chassis.pid_wait();
 chassis.pid_drive_set(10.55_in, 90);//Drive into long goal 
 chassis.pid_wait();
 frontIn.move(70); // Outake balls
 backIn.move(90); // Outake balls
 topIn.move(80); // Outake balls
 pros::delay(15000); // Wait so it can run and stuff
}

//? BLUE FUNCTS

void Auton_Functions::BLUE_Auton::b1(){
 
}

void Auton_Functions::BLUE_Auton::b2(){

}

void Auton_Functions::BLUE_Auton::b3(){
  
}