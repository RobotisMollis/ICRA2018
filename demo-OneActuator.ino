// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!

#include <AFMotor.h>

AF_DCMotor motor(1, MOTOR12_64KHZ);
AF_DCMotor valve(2, MOTOR12_64KHZ);

int incomingByte=0;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Soft robotics demo");

  // turn on motor
  motor.setSpeed(200);
  motor.run(RELEASE);
  
  valve.setSpeed(255);
}

void loop() {
     if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                Serial.print("I received: ");
                Serial.println(incomingByte, DEC);
        
   switch (incomingByte)
    {
    case 49: //'1' sent in serial monitor
   behav1();
   behav1();
   behav1();
    break;
    case 50: //'2' sent
   behav2();
      break;
    default:
      break;
    }
  
}
}


void behav2(){
  int inflateTime=800;
  int deflateTime=80;
  int maxThres=255;

//INITIAL INFLATION
Serial.println("initial inflate start");
motor.run(FORWARD);
motor.setSpeed(maxThres);  
delay(1200);

//INFLATION CYCLE #1
for (int k=1; k<6;k++){
//INFLATION
Serial.println("inflate start");
motor.run(FORWARD);
motor.setSpeed(maxThres);  
delay(inflateTime);

//WAIT 
motor.run(RELEASE);
//delay(2000);

//DEFLATION
valve.run(FORWARD);
valve.setSpeed(225); 
delay(deflateTime);
valve.run(RELEASE);

} 

//INITIAL INFLATION
Serial.println("inflate morestart");
motor.run(FORWARD);
motor.setSpeed(maxThres);  
delay(1200);


//INFLATION CYCLE #2
for (int k=1; k<9;k++){
//INFLATION
Serial.println("inflate start");
motor.run(FORWARD);
motor.setSpeed(maxThres);  
delay(inflateTime/3);

//WAIT 
motor.run(RELEASE);
//delay(2000);

//DEFLATION
valve.run(FORWARD);
valve.setSpeed(225); 
delay(deflateTime/2);
valve.run(RELEASE);

} 

}

void behav1(){
  int minThres=120;
  int maxThres=255;
  int delayUp=12;
  int fullInflateDelay=1000;
  int delayDown=26;

  //INFLATION
    Serial.println("inflate start");
    motor.run(FORWARD);

  //
  for (int i=minThres; i<maxThres; i++) {
    motor.setSpeed(i);  
    delay(delayUp);
    }
  //
  delay(fullInflateDelay);
  //
  for (int i=maxThres; i!=minThres; i--) {
    motor.setSpeed(i);  
    delay(delayDown);
    }
  motor.run(RELEASE);


//DEFLATION
Serial.println("deflate start");
valve.setSpeed(255); 
for (int j=0; j<35; j++) {
 valve.run(FORWARD);
 delay(5);
 valve.run(RELEASE);
 delay(50);
}

Serial.println("-deflate done");
 
} 

