/*
  Controlling a servo position using a potentiometer (variable resistor)
  by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

  modified on 8 Nov 2013
  by Scott Fitzgerald
  http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
#include <Wire.h>
#include <ZX_Sensor.h>

// Constants
const int ZX_ADDR = 0x10;  // ZX Sensor I2C address

// Global Variables
ZX_Sensor zx_sensor = ZX_Sensor(ZX_ADDR);
uint8_t x_pos;
uint8_t z_pos;

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int potpin1 = 0;  // analog pin used to connect the potentiometer
int potpin2 = 1;  // analog pin used to connect the potentiometer
int val1;    // variable to read the value from the analog pin
int val2;

void setup() {
  uint8_t ver;

  // Initialize Serial port
  Serial.begin(9600);
  Serial.println();
  Serial.println("-----------------------------------");
  Serial.println("SparkFun/GestureSense - I2C ZX Demo");
  Serial.println("-----------------------------------");

  // Initialize ZX Sensor (configure I2C and read model ID)
  if ( zx_sensor.init() ) {
    Serial.println("ZX Sensor initialization complete");
  } else {
    Serial.println("Something went wrong during ZX Sensor init!");
  }

  // Read the model version number and ensure the library will work
  ver = zx_sensor.getModelVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading model version number");
  } else {
    Serial.print("Model version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_MODEL_VER ) {
    Serial.print("Model version needs to be ");
    Serial.print(ZX_MODEL_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }

  // Read the register map version and ensure the library will work
  ver = zx_sensor.getRegMapVersion();
  if ( ver == ZX_ERROR ) {
    Serial.println("Error reading register map version number");
  } else {
    Serial.print("Register Map Version: ");
    Serial.println(ver);
  }
  if ( ver != ZX_REG_MAP_VER ) {
    Serial.print("Register map version needs to be ");
    Serial.print(ZX_REG_MAP_VER);
    Serial.print(" to work with this library. Stopping.");
    while (1);
  }
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);  // attaches the servo on pin 10 to the servo object
  val1 = 90;
  myservo1.write(val1);                  // sets the servo position according to the scaled value

}

void loop() {
  // If there is position data available, read and print it
  if ( zx_sensor.positionAvailable() ) {
    x_pos = zx_sensor.readX();
    if ( x_pos != ZX_ERROR ) {
      Serial.print("X: ");
      Serial.println(x_pos);
      // val1 = constrain(map(x_pos, 50, 200, 160, 20), 0, 180);    // scale it to use it with the servo (value between 0 and 180)

      z_pos = zx_sensor.readZ();
      if ( z_pos != ZX_ERROR ) {
//        Serial.print("Z: ");
//        Serial.println(z_pos);
        if (z_pos < 250 && z_pos > 2) {

          if (x_pos > 125 && val1 > 1) {
            val1--;
            myservo1.write(val1);                  // sets the servo position according to the scaled value

            delay(1);
          }

          else if (x_pos < 115 && val1 < 179) {
            val1++;
            myservo1.write(val1);
            delay(1);

          }
          //          Serial.print(" pan: ");
          //          Serial.println(val1);
          val2 = map(z_pos, 0, 255, 120, 30);     // scale it to use it with the servo (value between 0 and 180)
          myservo2.write(val2);                  // sets the servo position according to the scaled value

        }


      }
    }

  }

}
