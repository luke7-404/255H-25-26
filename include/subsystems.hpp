#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// intake motor group
inline std::vector<pros::Motor> intakeMotors = {pros::Motor(9), pros::Motor(8), pros::Motor(10)};
#define frontIn intakeMotors[0]
#define backIn intakeMotors[1]
#define topIn intakeMotors[2]

//* PNEUMATICS
//inline pros::adi::Pneumatics name('port letter', false);

// The distance sensor 
// inline pros::Distance name(15);

// The color sensor
// inline pros::Optical name(6);

// The rotation sensor
// inline pros::Rotation name(7);