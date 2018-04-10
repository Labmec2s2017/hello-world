#include <SoftwareSerial.h> //libreria para el bluetooth hc05

#include <Wire.h>    //libreria necesaria para comunicacion I2C
//#include "HX711.h"
SoftwareSerial BTserial(0,1);//RX,TX   linea del bluetooth

const int MPU2 = 0x69, MPU1=0x68;  //nombres de cada mpu6050
//#define DOUT  A1
//#define CLK  A0
//HX711 balanza(DOUT, CLK);
//long accelX, accelY, accelZ;               // creacion de variables de aceleracion para el primer MPU6050
//float gForceX, gForceY, gForceZ, gyroX, gyroY, gyroZ,rotX, rotY, rotZ; // // creacion de variables de aceleracion para el primer MPU6050
float rotX, rotY, rotZ;      //valor en grados/segundo segun datasheet 
float  gyroX, gyroY, gyroZ;    //valor ADC del giro
//long accelX2, accelY2, accelZ2;            // creacion de variables de aceleracion para el segundo MPU6050
//float gForceX2, gForceY2, gForceZ2;       // creacion de variables de aceleracion para el segundo MPU6050

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU1);
  Wire.write(0x6B);
  Wire.write(0b00000000);
  Wire.endTransmission();  
  Wire.beginTransmission(MPU1);
  Wire.write(0x1B);   //registro de configuracion giroscopio para primer MPU pag 14 del register map rev 4.2
  Wire.write(0x00001000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU1);
  Wire.write(0x1C);   //registro de configuracion del acelerometro para primer MPU pag 15 del register map rev 4.2
  Wire.write(0b00000000);
  Wire.endTransmission(); 
  
  Wire.begin();
  Wire.beginTransmission(MPU2);
  Wire.write(0x6B);    
  Wire.write(0b00000000); 
  Wire.endTransmission();  
  Wire.beginTransmission(MPU2); 
  Wire.write(0x1B);  //registro de configuracion giroscopio para segundo MPU pag 14 del register map rev 4.2
  Wire.write(0x00000000);
  Wire.endTransmission(); 
  Wire.beginTransmission(MPU2);
  Wire.write(0x1C);  //registro de configuracion del acelerometro del segundo MPU  pag 15 del register map rev 4.2
  Wire.write(0b00000000);
  Wire.endTransmission(); 
  Serial.begin(115200);    //tasa de bit per second
  BTserial.begin(115200);
}
long val;
long count=0;
float tiempo_muestreo=0;
long cero=-384700;
long cal = 531000;
float sens = 590.0/(cal-cero);
int muestra=0;
float peso ;

void loop(){
  long tiempo=millis();
  count=count+1; 

  while(millis()-tiempo < 1 )//realizamos mediciones durante 1 ms por cada bucle
  { 
     GetMpuValue(MPU1);
    Serial.print(",");
  //Serial.print("\t ||| \t");

     GetMpuValue(MPU2);
    Serial.println("");
  //   peso = sens*(val-cero);
                         
    
  //   val=balanza.read();                        // Proceso de Lectura del ADC
     
     //Serial.print(millis());//*gyroScale); 
     //Serial.print("\t"); 
     //Serial.println((gz/gyroScale)/6);//resultado en grados sobre segundo*gyroScale);
     //Serial.print("\t");
     //Serial.print(count);
   //  Serial.print((gz/gyroScale)/6);
     Serial.print(",");
     Serial.print(peso);
     Serial.print(",");
     Serial.println(val);
     
     //Serial.print("\t");
    //Serial.print(sens,7);
    //Serial.print("\t");
   // delay(20);

     
  }
  
//  GetMpuValue(MPU1);
//    Serial.print(",");
//  //Serial.print("\t ||| \t");
//
//  GetMpuValue(MPU2);
//  Serial.println("");
}

void GetMpuValue(const int MPU){
//  Wire.beginTransmission(MPU); 
//  Wire.write(0x3B);  // el registro 3B es el primero acce_xout_H segun register map revision 4.2 pag 7 y pag 29
//  Wire.endTransmission();
//  Wire.requestFrom(MPU,6);  //los 6 registros totales de aceleracion dos por cada eje el valor HIGH y el LOW
//  while(Wire.available() < 6);
//  accelX = Wire.read()<<8|Wire.read(); 
//  accelY = Wire.read()<<8|Wire.read(); 
//  accelZ = Wire.read()<<8|Wire.read();
  
  Wire.beginTransmission(MPU);
  Wire.write(0x43);    //el registro 43 es el primer gyro_xout_h segun register map revision 4.2 pag 7 y pag 31
  Wire.endTransmission();
  Wire.requestFrom(MPU,6); //los 6 registros totales de velocidad angular dos por cada eje el valor high y el low
  while(Wire.available() < 6);
  gyroX = Wire.read()<<8|Wire.read();
  gyroY = Wire.read()<<8|Wire.read();
  gyroZ = Wire.read()<<8|Wire.read(); 


//gForceX = accelX / 16384.0;
//gForceY = accelY / 16384.0; 
//gForceZ = accelZ / 16384.0;
  rotX = gyroX /65.5; //131.0;
//rotY = gyroY / 131.0; 
  rotZ = gyroZ / 131.0;
//Serial.print("gyro\t");
  Serial.print(rotX/6);
//Serial.print("\t");
//Serial.print(rotY);
  Serial.print(",");
  Serial.print(rotZ/6);
//Serial.print("\tAcc\t");
//Serial.print(gForceX);
//Serial.print("\t");
//Serial.print(gForceY);
//Serial.print("\t");
//Serial.print(gForceZ);
  delay(20);
  
}
