#pragma once

#include "EZ-Template/api.hpp"
#include "api.h"

extern Drive chassis;

// Your motors, sensors, etc. should go here.  Below are examples

// intake motor group
inline std::vector<pros::Motor> intakeMotors = {pros::Motor(11), pros::Motor(16)};
#define topIn intakeMotors[0]
#define botIn intakeMotors[1]


// PNEUMATICS
inline pros::adi::Pneumatics LittleW('H', false);
inline pros::adi::Pneumatics descore('D', false);
inline pros::adi::Pneumatics BScore('C', false); // when Both A and B are both not extended it is in long goal scoring mode // 
inline pros::adi::Pneumatics AScore('B', false); // when only B is extended it is in holding mode //
                                                 // When Both A and B are both extended it is in Mid goal scoring mode //

// The color sensor
// inline pros::Optical name(6);

// The rotation sensor
// inline pros::Rotation name(7);