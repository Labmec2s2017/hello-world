#include <SoftwareSerial.h> //libreria para el bluetooth hc05

#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

SoftwareSerial BTserial(0,1);//RX,TX
const int mpuAddress = 0x68;  // Puede ser 0x68 o 0x69
MPU6050 mpu(mpuAddress);

      //int ax, ay, az;
        int gx, gy, gz;

       //este codigo permite calibrar  
     //me calcula la fuerza  en unidades de decanewton 
    // Factores de conversion
      //const float accScale = 2.0 * 9.81 / 32768.0;
         const float gyroScale = 131 ;//250.0 / 32768.0;
         
#include "HX711.h"

#define DOUT  A1
#define CLK  A0

HX711 balanza(DOUT, CLK);


void setup() {
  Serial.begin(115200);// tasa por defecto
  BTserial.begin(115200);
  Wire.begin();
   mpu.initialize();
}

long val;
long count=0;
float tiempo_muestreo=0;
long cero=-384700;
long cal = 531000;
float sens = 590.0/(cal-cero);
int muestra=0;
float peso ;

void loop() {

   mpu.getRotation(&gx, &gy, &gz);  
  long tiempo=millis();
  
  count=count+1; 
 
 while(millis()-tiempo < 1 )//realizamos mediciones durante 1 ms por cada bucle
  { 
     peso = sens*(val-cero);
                         
    
     val=balanza.read();                        // Proceso de Lectura del ADC
     
     //Serial.print(millis());//*gyroScale); 
     //Serial.print("\t"); 
     //Serial.println((gz/gyroScale)/6);//resultado en grados sobre segundo*gyroScale);
     //Serial.print("\t");
     //Serial.print(count);
     Serial.print((gz/gyroScale)/6);
     Serial.print(",");
     Serial.print(peso);
     Serial.print(",");
     Serial.println(val);
     
     //Serial.print("\t");
//     Serial.print(sens,7);
//     Serial.print("\t");
     delay(20);

     
  }

}
