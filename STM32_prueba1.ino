#include <Wire.h>

int16_t Gyro_x,Gyro_y,Gyro_z;
float t0;
void setup() {
  t0=millis();
  Serial.begin(115200);
 // Wire.setClock(400000);
  Wire.begin();
  delay(250);

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  

}

void loop() {

 Wire.beginTransmission(0x68);
 Wire.write(0x3B);
 Wire.endTransmission();
 Wire.requestFrom(0x68,6);
 Gyro_x = Wire.read()<<8 | Wire.read();
 Gyro_y = Wire.read()<<8 | Wire.read();
 Gyro_z = Wire.read()<<8 | Wire.read();
  //Serial.print(millis()-t0);
// Serial.print("\t");
 Serial.print(Gyro_x);
 Serial.print("\t");
 Serial.print(Gyro_y);
 Serial.print("\t");
 Serial.println(Gyro_z);
 //delay(250);
 
}
