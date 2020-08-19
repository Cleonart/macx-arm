#include "macx_arm.h"

// for one dof at a time
void attachJoint(int pin_){
	servos.attach(pin_);
}

// multiple dof at a time
void attachJoints(int pins_[]){
	for(int i = 0; i < sizeof(pins_); i++){
		servos[i].attach(pins_[i]);
	}
}

// move joint
void moveJoint(int pin_, int degrees_, int delay_){
	
	int degreesOfServo = readJoint(pin_);

  	// if servo degrees now is less than degrees to go
  	if(readJoint(pin_) < degrees_){
    	while(degreesOfServo <= degrees_){
      		degreesOfServo++;
      		servos[pin_].write(degreesOfServo);
      		Serial.println("+");
      		delay(delay_);
    	}
    }

  	// if servo degress more then degrees to go
  	else if(degrees_ < readJoint(pin_)){
    	while(degreesOfServo >= degrees_){
      		servos[pin_].write(degreesOfServo);
      		Serial.println("-");
      		degreesOfServo--;
      		delay(delay_);
    	}
  	}

  	else{
    	Serial.println("*");
  	}

}

// read servo degrees now
int readJoint(int pin_){
  	return servos[pin_].read();
}

// reset joint to 0 degrees
void resetJoint(int pin_){
	moveJoint(pin_, 0, 50);
}

// reset all joints to 0 degrees
void resetJoints(int pins_[]){
	for(int i = 0; i < sizeof(pins_); i++){
		moveJoint(pins_[i], 0, 50);
	}
}