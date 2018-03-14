
int valorADC = 0;        // Variable para almacenar valor del ADC.
float temperatura;
float luz;
void setup() {
  
  Serial.begin(115200); // Inicializa el puerto serie a 115200 bps.
}

void loop() {
  
  valorADC = analogRead(A0); //Leemos entrada del ADC.

  temperatura = ( (valorADC/1023.0 * 5.0)/0.01);


  valorADC = analogRead(A1); //Leemos entrada del ADC.

  luz = (valorADC/1023.0 * 5.0);
  
  Serial.print(temperatura); //Enviamos el dato en formato string.
  Serial.print(","); //Enviamos una coma para separar los datos
  Serial.println(luz); //Enviamos el dato en formato string.

 
  

  delay(1);
}
