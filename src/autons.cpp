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
  
 BScore.extend();    // go back to holding position
 AScore.extend();
 LittleW.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(39, 50,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1500);  // clear loader
 chassis.pid_drive_set(-15, 127,false, true); // drive out of loader
 chassis.pid_wait_quick();
  chassis.pid_turn_set(315, 127); //turn to drive to the other side of the field
 chassis.pid_wait_quick();
chassis.pid_drive_set(-20, 127,false, true); // drive to position for cross field movement
 chassis.pid_wait_quick();
  chassis.pid_turn_set(360, 127); //turn to drive to the other side of the field
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-72, 127,false,true); // drive to other side of field
chassis.pid_wait();
  chassis.pid_turn_set(45, 127); //turn to between loader and long goal
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-60, 127,false,true); // drive to between long goal and loader
chassis.pid_wait();
chassis.pid_turn_set(180, 100); //turn to long long goal
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-23, 127,false, true); // drive to long goal
chassis.pid_wait();
  botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(1500); // wait for scoring
 BScore.extend();    // go back to holding position
 AScore.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(35, 50,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1500);  // clear loader
 chassis.pid_drive_set(-35, 55,false, true); // drive out of loader
 chassis.pid_wait_quick();
 botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-100);
 topIn.move(100);
 pros::delay(1500); // wait for scoring
pros::delay(10000);

}

void Auton_Functions::AWP2(){   

}

void Auton_Functions::Skills(){
  chassis.pid_targets_reset();
 chassis.drive_imu_reset();
 BScore.extend();
 AScore.extend();        // set intake to storing position
 descore.extend();       // set littleW to scoring position
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(11.5, 105, false, true); // drive to balls
 chassis.pid_wait();
 chassis.pid_turn_set(28, 105); //turn between long goal and loader
 chassis.pid_wait();
 chassis.pid_drive_set(18.5, 60,false, true); // drive to balls
 chassis.pid_wait();
 chassis.pid_turn_set(122, 105); //turn between long goal and loader
 chassis.pid_wait();
chassis.pid_drive_set(29, 105,false, true); // go to area between loader and long goal
 chassis.pid_wait();
 chassis.pid_turn_set(180, 105); //turn to long goal
 chassis.pid_wait();
chassis.pid_drive_set(-13, 105,false, true); // drive into long goal
 chassis.pid_wait();
 botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
  AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(900); // wait for scoring
 LittleW.extend();  // extend little will
 BScore.extend();    // go back to holding position
 AScore.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(30, 55,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1250);  // clear loader
 chassis.pid_drive_set(-15, 105); // back up from loader
 chassis.pid_wait_quick();
  LittleW.retract();  //retract little will
  botIn.move(-90);
 topIn.move(90);


 chassis.pid_turn_set(120, 105); //turn to go to other side of field
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-19, 105,false, true); // drive to right side of long goal
 chassis.pid_wait_quick();
 chassis.pid_turn_set(180, 105); //turn to drive to the other side of the field
 chassis.pid_wait_quick();
 pros::delay(100); 
  chassis.pid_drive_set(-70, 100,false,true); // drive to other side of field 
 chassis.pid_wait_quick();
 pros::delay(275);
 chassis.pid_turn_set(50, 105); //turn to between loader and long goal
 chassis.pid_wait_quick();
  pros::delay(205);
chassis.pid_drive_set(16.5, 105,false, true); // drive to in between loader and long goal
 chassis.pid_wait_quick();
 chassis.pid_turn_set(0, 105); //turn to long long goal
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-23, 100,false, true); // drive to long goal
 chassis.pid_wait_quick();
 LittleW.extend();  // extend little will
  botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(1700); // wait for scoring
 BScore.extend();    // go back to holding position
 AScore.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(35, 55 ,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1400);  // clear loader
 chassis.pid_drive_set(-35, 55,false, true); // back up from loader
 chassis.pid_wait_quick();


 AScore.retract();
 BScore.extend();   // score in long goal
 LittleW.retract();  // extend little will
 botIn.move(-100);
 topIn.move(100);
 pros::delay(1900); // wait for scoring
  chassis.pid_targets_reset();
 chassis.drive_imu_reset();
 /* chassis.pid_drive_set(5, 55,false, true); // back up from long goal
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-5, 65,false, true); // back up from ram long goal
 chassis.pid_wait_quick();*/
   chassis.pid_drive_set(7, 55,false, true); // back up from long goal
 chassis.pid_wait_quick();
chassis.pid_turn_set(262, 105); //turn to long long goal
  chassis.pid_wait_quick(); 
  BScore.extend();    // go back to holding position
 AScore.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(70, 85,false,true); // drive to other side of field 
 chassis.pid_wait_quick();
 chassis.pid_turn_set(125, 105); //turn to between long goal and loader left side
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-34, 105,false, true); // drive to between long goal and loader
chassis.pid_wait();
 chassis.pid_turn_set(0, 105); //turn to long long goal
 chassis.pid_wait_quick();
 pros::delay(100); // wait for scoring
   chassis.pid_drive_set(-27, 100,false, true); // drive to long goal
chassis.pid_wait();
  botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(900); // wait for scoring
 chassis.pid_targets_reset();
 chassis.drive_imu_reset();
 BScore.extend();    // go back to holding position
 AScore.extend();
 LittleW.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(41, 55,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1250);  // clear loader
 chassis.pid_drive_set(-15, 105,false, true); // drive out of loader
 chassis.pid_wait_quick();


 BScore.extend();    // go back to holding position
 AScore.extend();
 LittleW.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_turn_set(315, 105); //turn to drive to the other side of the field
 chassis.pid_wait_quick();
chassis.pid_drive_set(-22, 105,false, true); // drive to position for cross field movement
 chassis.pid_wait_quick();
  chassis.pid_turn_set(360, 105); //turn to drive to the other side of the field
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-72, 100,false,true); // drive to other side of field
chassis.pid_wait();
  chassis.pid_turn_set(65, 105); //turn to between loader and long goal
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-15, 105,false,true); // drive to between long goal and loader
chassis.pid_wait();
chassis.pid_turn_set(180, 105); //turn to long long goal
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-23, 105,false, true); // drive to long goal
chassis.pid_wait();
  botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(1500); // wait for scoring
 BScore.extend();    // go back to holding position
 AScore.extend();
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(35, 55,false, true); // drive to loader
 chassis.pid_wait_quick();
 pros::delay(1500);  // clear loader
 chassis.pid_drive_set(-35, 55,false, true); // drive out of loader
 chassis.pid_wait_quick();
 botIn.move(127);
   topIn.move(-127);
   pros::delay(.250); // outtake
 AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-100);
 topIn.move(100);
 pros::delay(1500); // wait for scoring
   /*chassis.pid_drive_set(10, 55,false, true); // back up from loader
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-10, 60,false, true); // back up from loader
 chassis.pid_wait_quick();*/
 LittleW.retract();  // retract little will
    chassis.pid_drive_set(22, 55,false, true); // back up from loader
 chassis.pid_wait_quick();
 chassis.pid_turn_set(292, 105); //turn to long long goal
 chassis.pid_wait_quick();
  botIn.move(127);
  topIn.move(-127);
  chassis.pid_drive_set(-60, 127,false, true); // back up from loader
 chassis.pid_wait_quick();
pros::delay(10000);
}

//! RED FUNCTS

// 4 Push Right
void Auton_Functions::RED_Auton::r1(){
  BScore.extend();
 AScore.extend();        // set intake to storing position
 descore.extend();       // set littleW to scoring position
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(10.5, 100); // drive to balls
 chassis.pid_wait_quick();
 chassis.pid_turn_set(33, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
 chassis.pid_drive_set(18.5, 60); // drive to balls
 chassis.pid_wait();
 chassis.pid_turn_set(122, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
chassis.pid_drive_set(29, 100); // go to area between loader and long goal
 chassis.pid_wait();
 chassis.pid_turn_set(180, 100); //turn to long goal
 chassis.pid_wait_quick();
chassis.pid_drive_set(-13, 100); // drive into long goal
 chassis.pid_wait_quick();
  AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(900);
 chassis.pid_swing_set(LEFT_SWING, 270, 100); // swing to position for push
  chassis.pid_wait_quick();
  chassis.pid_drive_set(6, 100); // drive out for push position
 chassis.pid_wait();
 descore.retract();  
 chassis.pid_turn_set(180, 100); //turn final push position
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-30, 80); // drive into long goal for push with descore down
 chassis.pid_wait();
} 

// 4 pushe left
void Auton_Functions::RED_Auton::r2(){
   BScore.extend();
 AScore.extend();        // set intake to storing position
 descore.extend();       // set littleW to scoring position
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(10.5, 100); // drive to balls
 chassis.pid_wait_quick();
 chassis.pid_turn_set(330, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
 chassis.pid_drive_set(18.5, 60); // drive to balls
 chassis.pid_wait();
 chassis.pid_turn_set(238, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
chassis.pid_drive_set(28, 100); // go to area between loader and long goal
 chassis.pid_wait();
 chassis.pid_turn_set(180, 100); //turn to long goal
 chassis.pid_wait_quick();
chassis.pid_drive_set(-13, 100); // drive into long goal
 chassis.pid_wait_quick();
  AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(1000);
 chassis.pid_swing_set(RIGHT_SWING, 90, 100); // swing to position for push
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-18, 100); // drive out for push position
 chassis.pid_wait();
 descore.retract();  
 chassis.pid_turn_set(180, 100); //turn final push position
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-29.5, 70); // drive into long goal for push with descore down
 chassis.pid_wait();
}

void Auton_Functions::RED_Auton::r3(){
  chassis.pid_turn_set(180, 127); //turn to between long goal and loader left side
 chassis.pid_wait_quick();
 pros::delay(100);
 chassis.pid_targets_reset();
 chassis.drive_imu_reset();
 pros::delay(100);
}

//? BLUE FUNCTS

// 4/3 split
void Auton_Functions::BLUE_Auton::b1(){
 BScore.extend();
 AScore.extend();        // set intake to storing position
 descore.extend();       // set littleW to scoring position
 botIn.move(-127);
 topIn.move(127);
 chassis.pid_drive_set(10.5, 100); // drive to balls
 chassis.pid_wait_quick();
 chassis.pid_turn_set(330, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
 chassis.pid_drive_set(18.5, 60); // drive to balls
 chassis.pid_wait();
  chassis.pid_turn_set(-132, 100); //turn between long goal and loader
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-20, 100); // drive to balls
 chassis.pid_wait();
  AScore.extend();
  BScore.retract();
  botIn.move(-100);
  topIn.move(100);
  pros::delay(1100); // outtake
  botIn.move(0);
  topIn.move(0);
   chassis.pid_drive_set(53, 100); // drive to balls
 chassis.pid_wait();
  chassis.pid_turn_set(180, 100); //turn between long goal and loader
 chassis.pid_wait();
 LittleW.extend();  // extend little will
 pros::delay(250);
   BScore.extend();
  AScore.extend();
 botIn.move(-127);
 topIn.move(127);
  chassis.pid_drive_set(13, 80); // drive to balls
 chassis.pid_wait();
 pros::delay(250);
  chassis.pid_drive_set(-29, 100); // drive to balls
 chassis.pid_wait();
 LittleW.retract();  // retract little will
  AScore.retract();
 BScore.extend();   // score in long goal
 botIn.move(-127);
 topIn.move(127);
 pros::delay(1000);
 chassis.pid_swing_set(RIGHT_SWING, 90, 100); // swing to position for push
  chassis.pid_wait_quick();
  chassis.pid_drive_set(-18, 100); // drive out for push position
 chassis.pid_wait();
 descore.retract();  
 chassis.pid_turn_set(180, 100); //turn final push position
 chassis.pid_wait_quick();
  chassis.pid_drive_set(-29.5, 50); // drive into long goal for push with descore down
 chassis.pid_wait();
 
}

// 3/4 left 
void Auton_Functions::BLUE_Auton::b2(){
    topIn.move(-85); // outtake
  botIn.move(-127); // Start intake
   pros::delay(1000);
}

void Auton_Functions::BLUE_Auton::b3(){
   chassis.pid_drive_set(22, 55,false, true); // back up from loader
 chassis.pid_wait_quick();
 chassis.pid_turn_set(120, 100); //turn final push position
 chassis.pid_wait_quick();
 chassis.pid_drive_set(-24, 55,false, true); // back up from loader
 chassis.pid_wait_quick();
 chassis.pid_swing_set(ez::RIGHT_SWING, 90_deg, 90); //Swing to face the wall
 chassis.pid_wait_quick();

chassis.pid_drive_set(-80, 90);
chassis.pid_wait_until(80);
pros::delay(1000);
}