// Include dependencies
#include "main.h"
#include "liblvgl/lvgl.h"

// Add definition guards
#pragma once
#ifndef PRINTING_HPP_ // If the header file has not been defined
#define PRINTING_HPP_ // Define the header file

// Define class constants
#define BLUE lv_color_hex(0x004aad) // Abbreviates the hex code for our background color to BLUE
#define BLACK lv_color_hex(0x000000) // Abbreviates the hex code for black to BLACK
#define WHITE lv_color_hex(0xFFFFFF) // Abbreviates the hex code for white to WHITE
#define AUTON_RED lv_color_hex(0xFF0000) // Abbreviates the hex code for red to AUTON_RED
#define AUTON_BLUE lv_color_hex(0x00FF) // Abbreviates the hex code for blue to AUTON_BLUE
#define SKILLS_GREEN lv_color_hex(0x008000) // Abbreviates the hex code for green to SKILLS_GREEN
#define NONE_ORANGE lv_color_hex(0xFF8C00) // Abbreviates the hex code for orange to NONE_ORANGE

/**
 * @brief Use the LCD_Menu class to create a GUI on the VEX V5 Brain
*/
class LCD_Menu{
    public:
        /**
         * @brief Creates a new LCD_Menu object
        */
        LCD_Menu();

        /**
         * @brief Destroys a LCD_Menu object
        */
        ~LCD_Menu();

        /**
         * @brief Gets the selected autonomous ID
         * 
         * @return char 
        */
        char getAutonID();

        /**
         * @brief Gets the name of the selected autonomous program
         * 
         * @return string 
        */
        std::string getAutonName();

        /**
         * @brief Starts the screen
        */
        void init();

        static bool isBlue; // A logic variable for when viewing the blue auton screen
        
        // When the class is destructed, the value will terminate the object's ability to print
        static bool isDeconstructed;

    private:

// ------------------------------ STATIC VARIABLES ------------------------------ //

        static uint8_t viewing;                                                 // The index of the currently viewed screen
        static lv_obj_t* tabBar;                                                // The tab bar object for the GUI
        static lv_obj_t* redAuton;                                              // The red autonomous selection screen object
        static lv_obj_t* blueAuton;                                             // The blue autonomous selection screen object
        static lv_obj_t* systemScreen;                                          // The system information screen object
        static lv_obj_t* selectedAutonLabel;                                    // Label object to display the selected autonomous routine
        static lv_obj_t* telemetryLabel;                                        // Label object for printing diagnostics
        static lv_timer_t* screenTimer;                                         // Timer for updating labels on the screen
        static std::vector<lv_obj_t*> autonButton;                              // A vector to store autonomous selection button objects

// -------------------------------- SCREEN UTIL -------------------------------- //

        /**
         * @brief Prints the tabs at the top of the screen
        */
        static void makeButtons();

        /**
         * @brief Clears the screen and redraws the tabs 
        */ 
        static void screenClear();

        /**
         * @brief Handles the tab button clicks
         */
        static void tabHandler_STATIC(lv_event_t* e);

        /**
         * @brief 
         * 
         */
        static void timerHandler_STATIC(lv_timer_t* timer);

// -------------------------------- AUTON FUNC -------------------------------- //

        /**
         * @brief Prints out buttons for auton selection
        */
        static void printAuton(lv_color_t color);
        
        /**
         * @brief Handles the redAuton autonomous button clicks
         */
        static void redAuton_eventHandler_STATIC(lv_event_t* e);
        
        /**
         * @brief Handles the blueAuton autonomous button clicks
         */
        static void blueAuton_eventHandler_STATIC(lv_event_t* e);

        /**
         * @brief Handles the auton selector buttons' clicks
        */
        static void auton_eventHandler_STATIC(lv_event_t* e);

        /**
         * @brief Prints out the position of the drivetrain's position for odometry debugging
        */
        static void printPose();

// -------------------------------- SYSTEM FUNC -------------------------------- //

        /**
         * @brief Lists a few diagnostics for the motors in the motor array provided and prints them to the screen.
         * 
         * @return A string containing the diagnostics information for the motors.
         */
        static void listMotors();

        /**
         * @brief Prints out system information like motor diagnostics and battery %
        */
        static void printSystem();

        /**
         * @brief Handles the system information button clicks
         */
        static void system_eventHandler_STATIC(lv_event_t* e);
};
#endif // End of header