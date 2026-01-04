#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// intake motor group
inline std::vector<pros::Motor> intakeMotors = {pros::Motor(7), pros::Motor(6)};
#define topIn intakeMotors[0]
#define botIn intakeMotors[1]


// PNEUMATICS
inline pros::adi::Pneumatics LittleW('H', false);
inline pros::adi::Pneumatics descore('B', false);

// The color sensor
// inline pros::Optical name(6);

// The rotation sensor
// inline pros::Rotation name(7);