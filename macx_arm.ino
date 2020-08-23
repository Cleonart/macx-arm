#include <Servo.h>

/*
 * Servo 1 PIN 2  : Swinger
 * Servo 2 PIN 4  : Arm
 * Servo 3 PIN 5  : Roll
 * Servo 4 PIN 19 : Claw
 * 
 * 
 * 1 : 0 - 179
 * 2 : 0 - 60 
 * 
 * Robot Control
 * 
 */

bool canSwing = true;
bool conveyorMove = false;
bool claw     = false;

// servos setter
static const int servosPins[4] = {2, 4, 5, 6};
Servo servos[4];

// attaching servo
void setServos(){
  for(int i = 0; i < 4; i++){
     servos[i].attach(servosPins[i]);
  }
}

// move servo
int servosSet(int pin_, int degrees_, int delay_){
  
  int degreesOfServo = readServo(pin_);
  Serial.println("------------------------------");
  Serial.print("Moving Servo.");

  // if servo degrees now is less than degrees to go
  if(readServo(pin_) < degrees_){
    while(degreesOfServo <= degrees_){
      degreesOfServo++;
      servos[pin_].write(degreesOfServo);
      Serial.print(degreesOfServo);
      Serial.print(" : ");
      digitalWrite(13, HIGH);
      delay(delay_);
      digitalWrite(13, LOW);
    }
    Serial.println("------------------------------");
  }

  // if servo degress now more than degrees to go
  else if(degrees_ < readServo(pin_)){
    while(degreesOfServo >= degrees_){
      degreesOfServo--;
      servos[pin_].write(degreesOfServo);
      Serial.print(degreesOfServo);
      Serial.print(" : ");
      digitalWrite(13, HIGH);
      delay(delay_);
      digitalWrite(13, LOW);
    }
    Serial.println("------------------------------");
  }

  // if servo degrees is the same with degrees to go
  else{
    Serial.println("****************");
    Serial.println("* SERVO LOCKED *");
    Serial.println("****************");
  }

  Serial.println("");
}

// read servo data
int readServo(int i){
  return servos[i].read();
}

void setup() {
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  setServos();
  servos[1].write(0);
  servos[2].write(140);
  servos[3].write(0);
  digitalWrite(8, HIGH);
  delay(50);   
}

void loop() {
  if(Serial.available() > 0){
    int data = Serial.read();
    servoScenario(data);
  }
}

// servo 1 | swinger
void servo_Swinger(int data){
  if(canSwing){
    if(data == 49){
      servosSet(0, 110, 20);
    }  
    else if(data == 50){
      servosSet(0, 170, 20);
    }
  }
}

// servo 2 | arm
void servo_Arm(int data){
  if(data == 97){
    canSwing = true;
    servosSet(1, 0, 20);
  }
  else if(data == 98){
    canSwing = false;
    servosSet(1, 20, 20);
  } 
}

// servo 3 | roll
void servo_Roll(int data){
  if(data == 56){
    canSwing = true;
    servosSet(2, 120, 20);
   }
   else if(data == 57){
    canSwing = false;
    servosSet(2, 170, 20);
   } 
}

// servo 4 | claw
void servo_Claw(int data){
  if(data == 99){
    if(claw == true){
        servosSet(3, 0, 10);
        claw = false;
        Serial.println("Open Claw");
     }
     else{
        servosSet(3, 100, 10);
        claw = true;
        Serial.println("Close Claw");
     }
   }
}  

// conveyor control
void conveyor_StartStop(int data){
  if(data == 115){
    if(conveyorMove){
      digitalWrite(8, HIGH);
      conveyorMove = false;
    }
    else{
      digitalWrite(8, LOW);
      conveyorMove = true;
    }
  }
}

// servo scenario
void servoScenario(int data){
  
  Serial.println(data);
  servo_Swinger(data);
  servo_Arm(data);
  servo_Roll(data);
  servo_Claw(data);
  conveyor_StartStop(data);
 
  // special command
  
  // drop things
  // key : d
  if(data == 100){
    servosSet(1, 0, 20);    // pull arm to top
    delay(1000);
    servosSet(2, 170, 20);  // pull roll to top
    delay(1000);
    servosSet(0, 160, 10);  // swing to drop point
    delay(1000);
    servosSet(1, 40, 10);   // lower the arm
    delay(1000);
    servosSet(2, 115, 20);  // pull roll to down
    delay(1000);
    servosSet(3, 0, 20);   // open the claw
    delay(1000);
    canSwing = false;
    claw = false;
   }
   
   // go to catch point
   // key : g
   if(data == 103){
    servosSet(3, 0, 20);    // open the claw
    delay(1000);
    servosSet(1, 0, 20);    // pull arm to top
    delay(1000);
    servosSet(2, 170, 20);  // pull roll to top
    delay(1000);
    canSwing = true;
    servo_Swinger(49);      // swing to pick up point
    delay(1000);
    servo_Roll(56);         
    delay(1000);
    servo_Arm(98);          
    delay(1000);
   }
   
   // reset all servo to normal
   // key : r
   if(data == 114){
    servosSet(1, 0, 20);    // pull arm to top
    delay(1000);
    servosSet(0, 0, 20);    // pull arm to top
    delay(1000);
    servosSet(2, 90, 20);   // pull arm to top
    delay(1000);
    servosSet(3, 0, 20);    // pull arm to top
    delay(1000);
   }
    
   if(data == 122){
    recording();
    }
}

void recording(){
  servoScenario(114);
  digitalWrite(8, HIGH);
  delay(1000);
  digitalWrite(8, LOW);
  delay(1200);
  digitalWrite(8, HIGH);
  delay(2000);
  servoScenario(103);
  delay(1000);
  servo_Claw(99);
  delay(1000);
  servoScenario(100);  
  delay(1000);
  digitalWrite(8, LOW);
  delay(2255);
  digitalWrite(8, HIGH);
}
