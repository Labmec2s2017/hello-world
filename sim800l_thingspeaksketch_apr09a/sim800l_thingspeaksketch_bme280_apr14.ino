#include <SoftwareSerial.h>         
#include <String.h>     
SoftwareSerial Sim900Serial(7, 8);  //Configarión de los pines serial por software
//sensor bme280
//temperatura ambiental ,humedad relativa,presion atmosferica

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BME_SCK 13   //scl
#define BME_MISO 12   //sdo
#define BME_MOSI 11   //sda
#define BME_CS 10     //csb

#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK); // software SPI

//float sensorValue;
//float temperatura=0.00;
float tempc=1.1;
void setup()
{
Sim900Serial.begin(19200);       //Arduino se comunica con el SIM900 a una velocidad de 19200bps   
Serial.begin(19200);             //Velocidad del puerto serial de arduino
//--------------------------------------bme280-----------------------
bool status;
    
    // default settings
    // (you can also pass in a Wire library object like &Wire2)
    status = bme.begin();  
    if (!status) {
        //Serial.println("Could not find a valid BME280 sensor, check wiring!");
        while (1);
    } 
//-----------------------------------fin bme280-------------------------           
//Encendido del módulo por sofware
digitalWrite(9, HIGH);
delay(1000);
digitalWrite(9, LOW);
delay(20000);                    //Tiempo prudencial para el escudo inicie sesión de red con tu operador
}
void loop(){  
           float tempc = analogRead(A0);
           comandosAT();                    //Llama a la función comandosAT  
              if(Sim900Serial.available())     //Verificamos si hay datos disponibles desde el SIM900
                 Serial.write(Sim900Serial.read());//Escribir datos
            delay(1800000);
}
void comandosAT(){

         Sim900Serial.println("AT+CIPSTATUS");        //Consultar el estado actual de la conexión
         delay(2000);

         Sim900Serial.println("AT+CIPMUX=0");         //comando configura el dispositivo para una conexión IP única o múltiple 0=única
         delay(3000);
         mostrarDatosSeriales();
                        //Sim900Serial.println("AT+CSTT=\"gprs.movistar.com.ar\",\"wap\",\"wap\"");//comando configura el APN, nombre de usuario y contraseña."gprs.movistar.com.ar","wap","wap"->Movistar Arg.
         
         Sim900Serial.println("AT+CSTT=\"bam.entelpcs.cl\",\"entelpcs\",\"entelpcs\"");//comando configura el APN, nombre de usuario y contraseña."gprs.movistar.com.ar","wap","wap"->Movistar Arg.
         delay(1000);
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIICR");            //REALIZAR UNA CONEXIÓN INALÁMBRICA CON GPRS O CSD
         delay(3000);
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIFSR");            // Obtenemos nuestra IP local
         delay(2000);
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIPSPRT=0");        //Establece un indicador '>' al enviar datos
         grados();
         delay(3000);
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\""); //Indicamos el tipo de conexión, url o dirección IP y puerto al que realizamos la conexión
         delay(6000);
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIPSEND");          //ENVÍA DATOS A TRAVÉS DE una CONEXIÓN TCP O UDP
         delay(4000);
         grados();
         mostrarDatosSeriales();          //String datos="GET https://api.thingspeak.com/update?api_key=ORCX992TAK09EZQD&field1=%f "+ String(tempc);
         String datos = "GET https://api.thingspeak.com/update?api_key=ORCX992TAK09EZQD&field1=0"+String(analogRead(A0))+"&field2="+String(analogRead(A1))+"&field3="+String(bme.readTemperature())+"&field4="+String(bme.readPressure() / 100.0F)+"&field5="+String(bme.readHumidity());
         //String datos = "GET https://api.thingspeak.com/update?api_key=";
         //datos += "ORCX992TAK09EZQD";
         //datos  += "&field1=";
         //datos  += String(sensorValue);
         Sim900Serial.println(datos);        //Envía datos al servidor remoto
         Serial.println(datos);
         delay(8000);
         mostrarDatosSeriales();

         Sim900Serial.println((char)26);
         delay(8000);//Ahora esperaremos una respuesta pero esto va a depender de las condiones de la red y este valor quizá debamos modificarlo dependiendo de las condiciones de la red
         Sim900Serial.println();
         mostrarDatosSeriales();

         Sim900Serial.println("AT+CIPSHUT");//Cierra la conexión(Desactiva el contexto GPRS PDP)
         delay(5000);
         mostrarDatosSeriales();
} 

void mostrarDatosSeriales()   //Muestra los datos que va entregando el sim900
{
     while(Sim900Serial.available()!=0)
     Serial.write(Sim900Serial.read());
}
void grados(){//Función para la lectura del sensor de temepratura
  //sensors.requestTemperatures(); // Envía el comando para obtener temperaturas
//  tempc=sensors.getTempCByIndex(0);/// getTempCByIndex(0) se refiere al primer 
  //sensor si es que tubieramos más de uno conectado en el cable
  float tempc = analogRead(A0);
  Serial.print("La humedad es: ");
  Serial.print(tempc);
  //Serial.print(temperatura);//Imprime la temperatura
  Serial.println(" porcentaje ");
}
