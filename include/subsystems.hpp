#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// intake motor group
inline std::vector<pros::Motor> intakeMotors = {pros::Motor(10), pros::Motor(9), pros::Motor(14)};
#define topIntake intakeMotors[0]
#define middleIntake intakeMotors[1]
#define bottomIntake intakeMotors[2]

// PNEUMATICS
inline pros::adi::Pneumatics Wings('A', false);
inline pros::adi::Pneumatics Aligner('D', false);

// The color sensor
// inline pros::Optical name(6);

// The rotation sensor
// inline pros::Rotation name(7);