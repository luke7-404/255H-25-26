#include "menu.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-11, -12, 15},     // Left Chassis Ports (negative port will reverse it!)
    {-13, 18, 20},  // Right Chassis Ports (negative port will reverse it!)

    //! |---------!!!!!!! CHANGE ME !!!!!!!---------|
    1,      // IMU Port      
    3.25,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    450);   // Wheel RPM = cartridge * (motor gear / wheel gear)

Auton_Functions autonFunc; // Auton function object

LCD_Menu menu; // LCD Menu object

// Variable to store the autonomous routine ID
char autonID;

// void function that handles screen interactions
void printMenu(){
    // while the menu object is able to function
    while(!menu.isDeconstructed){
        autonID = menu.getAutonID();
        master.print(0, 0, "ID: %c: %s", autonID, menu.getAutonName());
        master.clear_line(0);
        pros::delay(250); // save computer resources
    }
}


/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  //! |---------!!!!!!! CHANGE ME !!!!!!!---------|
  chassis.opcontrol_curve_buttons_toggle(true);   // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0.25);   // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(1.043, 1.043);  // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();


  // Initialize chassis and auton selector
  chassis.initialize();
  master.rumble(chassis.drive_imu_calibrated() ? "." : "---");
  

  // start tasks 
  menu.init();
  pros::Task printGUI(printMenu);
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.odom_xyt_set(0_in, 0_in, 0_deg);    // Set the current position, you can start at a specific position with this
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  
  chassis.pid_drive_set(10_in, 127);
  chassis.pid_wait();
  chassis.pid_drive_set(-10_in, 127);
  chassis.pid_wait();

  // Make Blue and Red autonomous objects
  Auton_Functions::BLUE_Auton Blue(autonFunc);
  Auton_Functions::RED_Auton Red(autonFunc);
  

  // Switch conditional statement to choose from any of the 9 scenarios
  switch (autonID){
    
    // SKILLS
    case '1': // Flow through design because regardless if it is blue or red, the process is the same
    case 'A':
        autonFunc.Skills();
        Blue.~BLUE_Auton(); // Since it is a general function destroy objects
        Red.~RED_Auton();
      break;

      case '2': // General Function for AWP1
      autonFunc.AWP1();
      Blue.~BLUE_Auton(); // Since it is a general function destroy objects
      Red.~RED_Auton();
      break;
      
      case 'B': // General Function for AWP1 
      autonFunc.AWP1();
      Blue.~BLUE_Auton(); // Since it is a general function destroy objects
      Red.~RED_Auton();
      break;
      
      // AWP 2
      case '3': // General Function for AWP2
      autonFunc.AWP2();
      Blue.~BLUE_Auton(); // Since it is a general function destroy objects
      Red.~RED_Auton();
      break;
      
      case 'C': // General Function for AWP2
      autonFunc.AWP2();
      Blue.~BLUE_Auton(); // Since it is a general function destroy objects
      Red.~RED_Auton();
      break;

      case '4': //! R1
        Blue.~BLUE_Auton(); // Since it is a general function destroy objects
        Red.r1();
      break;

    case 'D': //? B1
        Red.~RED_Auton();
        Blue.b1(); 
      break;
      
    case '5': //! R2    
        Blue.~BLUE_Auton(); // Destroy object since we aren't using it
        Red.r2();
      break;

    case 'E': //? B2    
        Red.~RED_Auton(); // Destroy object since we aren't using it
        Blue.b2();
      break;

    case '6': //! R3    
        Blue.~BLUE_Auton(); // Destroy object since we aren't using it
        Red.r3();
      break;

    case 'F': //? B3    
        Red.~RED_Auton(); // Destroy object since we aren't using it
        Blue.b3();
      break;
      
    default: // If nothing ran, destroy objects
        Blue.~BLUE_Auton();
        Red.~RED_Auton();
      break;
  }

}

/**
 * Gives you some extras to run in your opcontrol:
 * - run your autonomous routine in opcontrol by pressing DOWN and B
 *   - to prevent this from accidentally happening at a competition, this
 *     is only enabled when you're not connected to competition control.
 * - gives you a GUI to change your PID values live by pressing X
 */
void ez_template_extras() {
  // Only run this when not connected to a competition switch
  if (!pros::competition::is_connected()) {
    // PID Tuner
    // - after you find values that you're happy with, you'll have to set them in auton.cpp

    // Enable / Disable PID Tuner
    //  When enabled:
    //  * use A and Y to increment / decrement the constants
    //  * use the arrow keys to navigate the constants
    if (master.get_digital_new_press(DIGITAL_X))
      chassis.pid_tuner_toggle();

    // Trigger the selected autonomous routine
    if (master.get_digital(DIGITAL_B) && master.get_digital(DIGITAL_DOWN)) {
      pros::motor_brake_mode_e_t preference = chassis.drive_brake_get();
      autonomous();
      chassis.drive_brake_set(preference);
    }

    // Allow PID Tuner to iterate
    chassis.pid_tuner_iterate();
  }

  // Disable PID Tuner when connected to a comp switch
  else {
    if (chassis.pid_tuner_enabled())
      chassis.pid_tuner_disable();
  }
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on
  chassis.drive_brake_set(MOTOR_BRAKE_COAST);

  while (true) {
    // Gives you some extras to make EZ-Template ezier
    ez_template_extras();

    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade

    // . . .
    // Put more user control code here!
    // . . .

    if (master.get_digital(DIGITAL_L1)){   // in-take through 
      frontIn.move(70);
      backIn.move(-70);
    } else if (master.get_digital(DIGITAL_L2)){  // out-take through
      frontIn.move(-70);
      backIn.move(70);
    } else if (master.get_digital(DIGITAL_R1)){  // mid tier
      frontIn.move(70);
      backIn.move(70);
      topIn.move(-70);
    } else if (master.get_digital(DIGITAL_R2)){  // top tier
      frontIn.move(70);
      backIn.move(70);
      topIn.move(70);
    } else {   // if all else, stop
      frontIn.brake();
      backIn.brake();
      topIn.brake();
    }

    if(master.get_digital_new_press(DIGITAL_Y)) { // PNEUMATICS
      LittleW.toggle();
    } 

   //! CALL BACKS
    // if(master.get_digital_new_press(DIGITAL_R2)) { } // 
    // if(master.get_digital_new_press(DIGITAL_R1)) { } // 


    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
