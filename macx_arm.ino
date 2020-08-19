#include <Servo.h>

// servos setter
static const int servosPins[3] = {2, 4, 5};
Servo servos[3];

void setServos(){
  for(int i = 0; i < 3; i++){
     servos[i].attach(servosPins[i]);
  }
}

int servosSet(int pin_, int degrees_, int delay_){
  
  int degreesOfServo = readServo(pin_);

  // if servo degrees now is less than degrees to go
  if(readServo(pin_) < degrees_){
    while(degreesOfServo <= degrees_){
      degreesOfServo++;
      servos[pin_].write(degreesOfServo);
      Serial.println("+");
      delay(delay_);
    }
  }

  // if servo degress more then degrees to go
  else if(degrees_ < readServo(pin_)){
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

// read servo data
int readServo(int i){
  return servos[i].read();
}

void setup() {
  Serial.begin(115200);
  setServos();
  servos[1].write(0);
  servos[2].write(0);
  servos[3].write(0);
  delay(50);   
}

void loop() {
  servosSet(0, 179, 20);
  servosSet(1, 0, 20);
  servosSet(2, 180, 20);
  delay(1000);
  servosSet(0, 1, 20);
  servosSet(1, 50, 20);
  servosSet(2, 0, 20);
  delay(1000);
}
