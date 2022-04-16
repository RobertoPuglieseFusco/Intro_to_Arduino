/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

const int ledPin = 13;       // the pin that the LED is attached to

int rotationMotor = 1;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(ledPin, OUTPUT);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue1 = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  int sensorValue3 = analogRead(A2);
  // print out the value you read:
  //  Serial.print("sensorValue1: ");
  //  Serial.println(sensorValue1);
  //  Serial.print("sensorValue2: ");
  //  Serial.println(sensorValue2);
  Serial.print("potentiometer: ");
  Serial.println(sensorValue3);

  int motorSpeed = map(sensorValue3, 1023, 0, 0, 128); // vaihda 128 > 255 lisätäksesi nopeutta, change value 128 to 255 for more speed

  if (motorSpeed < 20) {
    myMotor->run(RELEASE);
  }

  if (sensorValue1 < 600 && rotationMotor == 1) {
    rotationMotor = 2;

  }

  if (sensorValue2 < 600 && rotationMotor == 2) {
    rotationMotor = 1;
  }

  if (rotationMotor == 1) {

    myMotor->run(FORWARD);
    myMotor->setSpeed(motorSpeed);
    digitalWrite(ledPin, LOW);

  }
  else {
    myMotor->run(BACKWARD);
    myMotor->setSpeed(motorSpeed);
    digitalWrite(ledPin, HIGH);
  }

  delay(1);        // delay in between reads for stability

}
