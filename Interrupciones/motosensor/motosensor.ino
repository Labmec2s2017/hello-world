//codigo que permite calcular rpm
//tutorial explica el codigo  
//https://www.youtube.com/watch?v=lVfWT9viTwg&t=64s

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//#include <Servo.h>

#define tacoPin 2
#define servoPin 6
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
//Servo motor;
volatile int rpm = 0;
//nota : volatile es una palabra clave conocidad como qualifier (cualificadora), se usa usualmente antes del tipo de datos de una variable, para 
//modificar la manera en que el compilador y el programa deben tratar a esta variable.
//La declaración de una variable volatile es una directiva del compilador. El compilador es un software que traduce el código C/C ++ en el código de máquina, que son 
//las instrucciones reales para el chip Atmel en el Arduino.
//Específicamente, el compilador carga la variable de RAM y no de un registro de almacenamiento, que es una ubicación 
//de memoria temporal donde se almacenan y manipulan las variables del programa. Bajo ciertas condiciones, el valor 
//de una variable almacenada en los registros puede ser inexacto.
//Una variable debe ser declarada volatile cada vez que su valor pueda ser cambiado por algo más allá del 
//control de la sección de código en la que aparece, como otro código que se ejecuta simultáneamente. 
//En el Arduino, el único lugar que es probable que esto ocurra es en secciones de código asociadas a las interrupciones, que llaman a una rutina de servicio de interrupción.
volatile unsigned long dt = 0;
int ciclo = 0;

void setup(){
 motor.attach(servoPin);
 pinMode(tacoPin, INPUT);
 attachInterrupt(digitalPinToInterrupt(tacoPin), contar, FALLING);
 lcd.init(); // inicializa el lcd 
 lcd.backlight();
 lcd.print("Rev:");
 lcd.setCursor(10, 0);
 lcd.print("RPM");
 lcd.setCursor(0, 1);
 lcd.print("Temp:");
 lcd.setCursor(10, 1);
 lcd.print((char)223); //simbolo ascii de grado
 lcd.print("C");
}

void contar(){
  unsigned long t_act = micros(); // para filtrar rebotes
  if((t_act - dt) >= 2500){ // a 2500 us de espera y 1 s de muestreo las RPM max son 12000
    rpm += 30; // 60/(2 *deltaT)         2 es por 2 pulsos x revolucion de la helice,delta T = 1 second
    dt = t_act;
  }  // nota: el rebote hara que se active la interrupcion tanto en bajadas como subidas
}

void loop(){
  int val = analogRead(A0); //lextura potenciometro
  motor.write(map(val, 0, 1023, 50, 115));
  ciclo++;
  if(ciclo == 10){
    val = analogRead(A1); // termocupla
    int temp = map(val, 0, 1023, 37, 290); //basado en pruebas anteriores
    lcd.setCursor(5,0);
    lcd.print("     ");
    lcd.setCursor(5,0);
    lcd.print(rpm);
    rpm = 0;
    lcd.setCursor(5,1);
    lcd.print("   ");
    lcd.setCursor(5,1);
    lcd.print(temp);
    ciclo = 0;
  }
  delay(100);
}

