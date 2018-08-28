#include <Servo.h>

#include <SoftwareSerial.h>


int incomingByte = 0;  // for incoming serial data
int armingTime;
int pin = 9;
int counter = 0;
int pulseTime = 1100; //microseconds
boolean highSpeed = true;
Servo myservo;

void setup(){
  
  Serial.begin(9600);
 
  myservo.attach(9);
  
 
  Serial.println("Enter 0-9 to adjust motor speed.");
  Serial.println("Enter h or l to change the speed range.");
}

void loop(){
  
 
  digitalWrite(pin, HIGH); 
  delayMicroseconds(pulseTime); 
  digitalWrite(pin, LOW); 
  delay(10-(pulseTime/1000)); 
  
  
  if(Serial.available() > 0){
    incomingByte = Serial.read();
    }
  



//void incomingByte(){
//void readSerialVal(){
  
  switch (incomingByte) {
      case '0':
        setTimingParams(1100);
        incomingByte='*';
        Serial.print("Throttle: ");
      Serial.print((pulseTime-1100)/8);
      Serial.println("%");     
        break;
    
      case '6':    
        setTimingParams(1600);
        incomingByte='*';
        Serial.print("Throttle: ");
      Serial.print((pulseTime-1100)/8);
      Serial.println("%");
        break;
  
      case '9':    
        setTimingParams(1900);
        incomingByte='*';
        Serial.print("Throttle: ");
      Serial.print((pulseTime-1100)/8);
      Serial.println("%");
        break;
 
    } 
}

void setTimingParams(int newPulseTimeVal){
 if(highSpeed){
    pulseTime = newPulseTimeVal;
  } else {
    pulseTime = 1025 + (newPulseTimeVal/10);
  }
}

