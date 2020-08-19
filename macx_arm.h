#ifndef MACX_ARM_H
#define MACX_ARM_H

#include <Arduino.h>
#include <Servo.h>

Servo servos[10];

/* ------------------------
* Servo Arm Joint Control *
-------------------------*/

// attach joining
void attachJoint(int pin_);
void attachJoints(int pins_[]);

// joint moves
void moveJoint(int pin_, int degrees_, int delay_);

// read joint position
int readJoint(int pin_);

// reset joins
void resetJoint(int pin_);
void resetJoints(int pins_[]);


/* ------------------------
*    Conveyor Control     *
-------------------------*/

#endif