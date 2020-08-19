#include "macx_arm.h"

// servos setter
static const int servosPins[3] = {2, 4, 5};

void setup() {
  Serial.begin(115200);
  attachJoints(servosPins);
  resetJoins(servosPins);
}

void loop() { 
  recording1();
}

void recording1(){
  moveJoint(0, 179, 20);
  moveJoint(1, 0, 20);
  moveJoint(2, 180, 20);
  delay(1000);
  moveJoint(0, 1, 20);
  moveJoint(1, 50, 20);
  moveJoint(2, 0, 20);
  delay(1000);
}
