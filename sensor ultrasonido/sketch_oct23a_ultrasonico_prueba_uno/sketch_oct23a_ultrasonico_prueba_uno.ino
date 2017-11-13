//********SENSOR ultrasonico HC SR04********//
//*
//*el hc sr04 es un sensor ultrasonico que es capaz de medir la distancia

#define echo 13 //

#define trig 12 // El pin DIG 12 corresponde a una señal de salida para activar el sensor y tomar una lectura

//variables empleadas
int start,finish,time ;
float dist;

void setup() {
  Serial.begin(9600);  //se inicia comunicacion serial a 9600 baudios
  pinMode(echo, INPUT); //se declara como entrada el PIN que recibe la señal del sensor
  pinMode(trig, OUTPUT);//se declara como salida el PIN que activa al sensor
  

}

void loop() {

  digitalWrite(trig, HIGH); //se envia un pulso en alto que activa el sensor
  delayMicroseconds(15); //debe tener una duracion de al menos 10ms
  digitalWrite(trig, LOW);

  //esperamos a que el sensor envie una señal ultrasonica a 40 kHz y se comience el conteo del tiempo
  while(digitalRead(echo) == LOW);

  start = micros();//se inicia el conteo del tiempo en microsegundos.

  //por las caracteristicas del sensor oscilador de 16 MHz el conteo se hara en multiplos de 4
  while(digitalRead(echo)==HIGH);//esperamos a que el Rx reciba la señal del Tx
  finish = micros();//terminamos el conteo
  time = finish - start; //se calcula el tiempo transcurrido entre la transmision y la recepcion
  if (time>25000)//dadas las limitaciones del sensor si el tiempo es mayor de 25ms puede tratarse de una lectura
  time=0;//erronea.si el tiempo es de 38ms se da por hecho que el Rx no recibio ninguna señal

  dist = 0.01715*time; //se realiza el calculo de la distancia si d=v*t considerando que la velocidad del sonido en el aire es de 343m/s
  // d=34300cm/s *(tiempo*10e-6)s=0.0343*time cm
  //esta distancia es la recorrida por la señal del Rx al cuerpo y del cuerpo al Tx,por lo que es necesario dividirla entre 2,obteniendo d=0.01715*time cm
  Serial.print("Distancia:");//se imprime la distancia al objeto en cm
  Serial.print(dist);
  Serial.println("cm");//se imprime por pantalla la unidad centimetro
  Serial.print(time);//imprime tiempo
  delay(15);//retardo por estabilidad ,tiempo de espera para una nueva medicion

}
