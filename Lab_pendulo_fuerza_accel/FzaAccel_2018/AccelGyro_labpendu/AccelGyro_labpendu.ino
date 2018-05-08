// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

#include "HX711.h"

#define DOUT  A1
#define CLK  A0


HX711 balanza(DOUT, CLK);

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
const int MPU_addr=0x68;  // I2C address of the MPU-6050

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 accelgyro;
//MPU6050 accelgyro(0x69); // <-- use for AD0 high

int16_t ax, ay, az;
int16_t gx, gy, gz;
// se generan valores float------------------------------------------------
float axf, ayf, azf;
float gxf, gyf, gzf;

long val=0 ;
long offsetval=0;
float t;
// uncomment "OUTPUT_READABLE_ACCELGYRO" if you want to see a tab-separated
// list of the accel X/Y/Z and then gyro X/Y/Z values in decimal. Easy to read,
// not so easy to parse, and slow(er) over UART.
#define OUTPUT_READABLE_ACCELGYRO
// Alternative names for the combined definitions
// The name uses the full scale range for the accelerometer.
//#define MPU6050_AFS_SEL_2G  MPU6050_AFS_SEL_0
//#define MPU6050_D3 3
//setFullScaleAccelRange(MPU6050_ACCEL_FS_8)
//#define MPU6050_AFS_SEL_4G  MPU6050_AFS_SEL_1
//#define MPU6050_AFS_SEL_8G  MPU6050_AFS_SEL_2
//#define MPU6050_AFS_SEL_16G MPU6050_AFS_SEL_3
// uncomment "OUTPUT_BINARY_ACCELGYRO" to send all 6 axes of data as 16-bit
// binary, one right after the other. This is very fast (as fast as possible
// without compression or data loss), and easy to parse, but impossible to read
// for a human.
//#define OUTPUT_BINARY_ACCELGYRO


#define LED_PIN 13
bool blinkState = false;

void setup() {
  for (int i=0;i<100;i++){
    offsetval=offsetval+balanza.read();
   }
  offsetval=offsetval/100.;
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        //setFullScaleAccelRange(2);

    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
    // it's really up to you depending on your project)
//    Serial.begin(38400);
    Serial.begin(115200);
    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();
    
     //set sensitivity @ address 1C
      Wire.beginTransmission(MPU_addr);
      Wire.write(0x1C);
      Wire.write(B00010000);   //here is the byte for sensitivity (8g here) check datasheet for the one u want
//      Wire.write(B00000000);   //here is the byte for sensitivity (8g here) check datasheet for the one u want
      Wire.endTransmission(true);

//    // initialize device
//    Serial.println("Initializing I2C devices...");
//    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values
    /*
    Serial.println("Updating internal sensor offsets...");
    // -76  -2359 1688  0 0 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print("\n");
*/ 
    accelgyro.setXGyroOffset(92);
    accelgyro.setYGyroOffset(-13);
    accelgyro.setZGyroOffset(28);
   
   
    accelgyro.setXAccelOffset(-1234);
    accelgyro.setYAccelOffset(702);
    accelgyro.setZAccelOffset(1873);
//    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
//    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
//    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
//    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
//    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
//    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
//    Serial.print("\n");
//    */
delay(1000);
    // configure Arduino LED for
    pinMode(LED_PIN, OUTPUT);
}
//long cero = 188190;
//long cal = 4784600;
//float sens = 7390.0/(cal-cero);
//float peso;
long tiempo =millis();
void loop() {
   t = millis();
  
//  peso=sens*(val-cero);
  val = balanza.read();
    // read raw accel/gyro measurements from device
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
//    //----------------- convierte a FLOAT ------------------
      axf=ax*1.f/16384*9.81*4;//*4;
      ayf=ay*1.f/16384*9.81*4;//*4;
      azf=az*1.f/16384*9.81*4;//*4;
//      gxf=gx*1.f;
//      gyf=gy*1.f;
//      gzf=gz*1.f;
    int16_t g0=sqrt(axf*axf+ayf*ayf+azf*azf);

   //--------------------------------------------------------   
    #ifdef OUTPUT_READABLE_ACCELGYRO
        // display tab-separated accel/gyro x/y/z values
//        Serial.print("a/g:\t");
        Serial.print((t-tiempo)/1000.,3); Serial.print("\t");
        Serial.print((val-offsetval)*1.f/4614410*73900); Serial.print("\t");//558600*25.762); Serial.print("\t");
        Serial.print(axf); Serial.print("\t");
        Serial.print(ayf); Serial.print("\t");
        Serial.print(azf); Serial.println("\t");
        //  Serial.print(g0); Serial.print("\t");
//        Serial.print(gx); Serial.print("\t");
//        Serial.print(gy); Serial.print("\t");
//        Serial.println(gz);  
////---------------------------------------------------------      
//        Serial.print(axf); Serial.print("\t");
//        Serial.print(ayf); Serial.print("\t");
//        Serial.print(azf);  Serial.print("\t");
//        Serial.print(gxf); Serial.print("\t");
//        Serial.print(gyf); Serial.print("\t");
//        Serial.print(gzf);Serial.print("\t");        
//        Serial.print(ax); Serial.print("\t");
//        Serial.print(ay); Serial.print("\t");
//        Serial.print(az);  Serial.print("\t");
//        Serial.print(gx); Serial.print("\t");
//        Serial.print(gy); Serial.print("\t");
//        Serial.println(gz);        
////---------------------------------------------------------
    #endif

    #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif

//    // blink LED to indicate activity--- no led-----------
//    blinkState = !blinkState;
//    digitalWrite(LED_PIN, blinkState);
}
