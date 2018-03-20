// Arduino and scilab.
// Measuring the temperature of a room using usb port.
// Temperature sensor TMP36.

int Sensor_pin = 0; // Arduino sensors input pin.
char Out_string[7]; // String that will send via usb port.

void setup()
{
	Serial.begin(9600); // Start serial communication and set the baud rate.
}

void loop()
{
	float Sensor_reading = analogRead(Sensor_pin); // Sensor reading.

	float Sensor_voltage = Sensor_reading * 5.0; // Convert sensor reading to voltage.
	Sensor_voltage /= 1024.0; // Convert sensor reading to voltage.

	float temperature_celsius = (Sensor_voltage - 0.5) * 100 ; // Convert sensor voltage to celsius temperature degree

	dtostrf(temperature_celsius,7,3 , Out_string); // Convert float to string.

	Serial.write(13); // Write ascii character 13 to the usb buffer.
	Serial.write(Out_string);

	delay(100); // Stop the programm for 100 msec
}
