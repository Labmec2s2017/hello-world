#include <SoftwareSerial.h>

SoftwareSerial BT1(10, 11); // RX | TX

void setup(){
  Serial.begin(38400);
  Serial.println("Levantando el modulo HC-06");
  Serial.println("Esperando comandos AT:");
  BT1.begin(38400);
}

void loop(){
  if (BT1.available())
    Serial.write(BT1.read());
  if (Serial.available())
    BT1.write(Serial.read());
}
