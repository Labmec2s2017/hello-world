/*
Sensor de proximidad 
  HC-SR04 conexiones:
  VCC al arduino 5v 
  GND al arduino GND
  Echo al Arduino pin 6 
  Trig al Arduino pin 7
  
 */
 
#define Pecho 6
#define Ptrig 7
int linha = 0;
int LABEL = 1;
long duracion, distancia;   
 
void setup() {                
  Serial.begin (9600);       // inicializa el puerto seria a 9600 baudios
  //Serial.println("CLEARDATA");            // Reset da comunicação serial
  //Serial.println("LABEL,Hora,duracion,distancia,linha");   // Nombre de las columnas
  pinMode(Pecho, INPUT);     // define el pin 6 como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin 7 como salida  (triger)
  
  }
  
void loop() {
  
  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // se genera el pulso de triger por 10 microsegundos segun datasheet del sensor
  delayMicroseconds(10);       // 
  digitalWrite(Ptrig, LOW);    //pasado los 10 microsegundos se detiene el pulso
  linha++; // incrementa a linha de excel para que a lectura aumente en uno cada vez

  
  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  
  if (distancia >= 500 || distancia <= 0){  // si la distancia es mayor a 500cm o menor a 0cm 
    Serial.println("---");                  // no mide nada
  }
  else {
    //Serial.print("DATA,TIME,"); //inicia a impresion de datos en excel 
    Serial.print(duracion);    //imprimo la duracion de la señal en microsegundos
    Serial.print(",");
    Serial.println(distancia);           // envia el valor de la distancia por el puerto serial
    //Serial.println("us");
    Serial.println(linha);
    
    
   // le coloca a la distancia los centimetros "cm"
    if (linha > 100) //laço para limitar a quantidade de dados
{
       linha = 0;
      //Serial.println("ROW,SET,2"); // alimentação das linhas com os dados sempre iniciando
}
  }
  
   if (distancia <= 10 && distancia >= 1){
    
    //Serial.println("Alarma.......");         // envia la palabra Alarma por el puerto serial
  }
  delay(5);                                // espera 400ms para que se logre ver la distancia en la consola
}
