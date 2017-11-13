/*
  Este programa esta diseñado para el sensor hc sr04 ultrasonico
  
*/

#define echoPin 6 // defino echon en el pin 6
#define trigPin 7 // defino trig en el pin 7


void setup()
{

  Serial.begin(9600);//defino la tasa en puerto serial en baudios
 
  pinMode(echoPin, INPUT); // defino echo como entrada
  pinMode(trigPin, OUTPUT); // defino trig como salida
}


void loop()
{
  
  long duration, distance;// defino dos variables numericas tipo long
  digitalWrite(trigPin, LOW);  // inicialmente dejo trig en low
  delayMicroseconds(2); // se espera 2 microsegundos
  digitalWrite(trigPin, HIGH);//luego se genera un pulso que activa al sensor
  delayMicroseconds(10); // el tiempo minimo de activacion es de 10 microsegundos
  digitalWrite(trigPin, LOW);// desactivo el pulso trig
  duration = pulseIn(echoPin, HIGH); // pulseIn mide el tiempo de la señal ida y vuelta
  distance = (duration) / 58;  //calculo la distancia en centimetros

  //for this example we just use 1 byte so we have to keep the value limited to 0-255
  if(distance > 255)
    distance = 255;
    
  //Send the distance in 1 byte (actually sends for example 156, not '1' '5' and '6')
  Serial.write(distance);
  
  
  delay(50);// tiempo de espera para reiniciar el programa 50 milisegundos

}

