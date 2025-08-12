#pragma once

void default_constants();


/**
 * @class Auton_Functions
 * 
 * @brief This class provides autonomous functions for a robot, including control over
 *        various pneumatic components and motor groups. It supports different autonomous
 *        routines for both red and blue sides of the field, as well as skills.
 * 
 * @details The class manages the state of the robot's claw using an enum `clawState` and
 *          provides methods to set the claw state and perform automatic clamping. It also
 *          includes nested structures for red and blue autonomous routines, each with
 *          specific strategies like goal rush and ring rush.
 * 
 */
class Auton_Functions {

  public:
    // Constructor for the Auton_Functions class
    Auton_Functions(){}

      
    void AWP1(); // Left Side of field
    void AWP2(); // Right Side of field
    void Skills(); // Skills is skills

    /**
     * @brief Represents the autonomous routine for the RED alliance.
     *
     * This structure is used to define and manage the actions and
     * strategies specific to the RED alliance
     * during the autonomous phase.
     */
    struct RED_Auton {
            // Assign parameter value to member variable
            RED_Auton(Auton_Functions& parent) : parent(parent){}
            ~RED_Auton(){} // Destructor so that C++ can delete object

            /**
             * @brief Executes the autonomous routine for _ on Red side
             */
            void r1();

            /**
             * @brief Executes the autonomous routine for _ on Red side
             */
            void r2();

            /**
             * @brief Executes the autonomous routine for _ on Red side
             */
            void r3();
        private:
            /**
             * @brief A reference to the parent Auton_Functions object.
             * 
             * This member variable is used to access the functionalities
             * provided by the parent Auton_Functions instance.
             */
            Auton_Functions& parent;
    };

    /**
     * @brief Represents the autonomous routine for the BLUE alliance.
     *
     * This structure is used to define and manage the actions and
     * strategies specific to the BLUE alliance during the 
     * autonomous phase
     */
    struct BLUE_Auton : private RED_Auton {
            // Assign parameter value to member variable
            BLUE_Auton(Auton_Functions& parent) : RED_Auton(parent){}
            ~BLUE_Auton(){} // Destructor so that C++ can delete object

            /**
             * @brief Executes the autonomous routine for _ on Blue side
             */
            void b1();

            /**
             * @brief Executes the autonomous routine for _ on Blue side
             */
            void b2();

            /**
             * @brief Executes the autonomous routine for _ on Blue side
             */
            void b3();
    };
  /**
   * @brief Private member variables for controlling various robot components.
   */
  private:
};