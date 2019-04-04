//#include <DHT.h>

#include <ESP8266WiFi.h>
 
String apiKey = "82TX2R13ZCZO6DG2";//copiar apikey desde la pagina web thingspeak.com
const char* ssid = "ALCATEL ONE TOUCH T'Pop"; //nombre ssid wifi 
const char* password = "newtongaus2016"; // wifi password 
const char* server = "api.thingspeak.com";
float tempC;
int tempPin=A0; 
//#define DHTPIN  D6 
//#define DHTTYPE DHT11 
 
//DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
 
void setup()
{
Serial.begin(115200);
delay(10);
//dht.begin();
 
WiFi.begin(ssid, password);
 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
 
WiFi.begin(ssid, password);
 
while (WiFi.status() != WL_CONNECTED)
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
 
}
 
void loop()
{
tempC = analogRead(tempPin);  
//float h = dht.readHumidity();
//float t = dht.readTemperature();
//    if (isnan(h) || isnan(t))
//    {
//     Serial.println("Error obteniendo los datos del sensor DHT11");
//      return;
//    }
//tempC = (5.0 * tempC * 100.0)/1024.0;  
if (client.connect(server,80)) {
String postStr = apiKey;
postStr +="&field1=";
postStr += String(tempC);
//postStr +="&field2=";
//postStr += String(h);
postStr += "\r\n\r\n";
 
client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n");
client.print(postStr);

 Serial.print(tempC);
 Serial.print("\n");
//Serial.print("Temperatura: ");
//Serial.print(t);
//Serial.print("humedad: ");
//Serial.print(h);
//Serial.println("hola Data Thingspeak");
}
client.stop();
 
//Serial.println("espera un segundo");
delay(20);
}
