#include "HX711.h"

#define DOUT  A1
#define CLK  A0


HX711 balanza(DOUT, CLK);
HX711 balanza2( 10 , 11 );

void setup() {
  Serial.begin(115200);
}
long val = 0;
long val2 = 0;
float count = 0;
float tiempo_muestreo = 0;
//long tiempo_muestreo=0;
//long tiempo_muestreo1=0;
int muestra = 0;
float t;
void loop() {
  long tiempo = millis();
  count = count + 1;
  while (millis() - tiempo < 1000 ) //realizamos mediciones durante 1000 ms por cada bucle
  {
    //tiempo_muestreo= tiempo_muestreo+0.0125f;   // si tenemos 80 [Hz]= 12,5 ms
    tiempo_muestreo = tiempo_muestreo + 0.1f; // si tenemos 10 [Hz] = 100 ms
    muestra = muestra + 1;   
    val = balanza.read();
    val2 = balanza2.read();
    t=millis();
    //     Serial.println((val-(-872800)) /(- 7002.74f));//cero en -.8728e6 73 kg en -1.384e6
    //    Serial.println((val*1.f+64500)/257200*3.95);//escribe el valor del adc
    //     Serial.println((val*1.f-12500)/229000*3.57);//escribe el valor del adc
    Serial.print((val - 37500) * 1.750f / 110000.);
    Serial.print("\t");
    Serial.print((val2-8000) * 1.750f/110000.);
    Serial.print("\t");
    Serial.println(t);
    
  }
  }
