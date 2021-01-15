/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;  // create servo object to control a servo

int potpin1 = 0;  // analog pin used to connect the potentiometer
int potpin2 = 1;  // analog pin used to connect the potentiometer
int val1;    // variable to read the value from the analog pin
int val2;

void setup() {
  myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
   myservo2.attach(10);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  val1 = analogRead(potpin1);            // reads the value of the potentiometer (value between 0 and 1023)
  val1 = map(val1, 0, 1023, 10, 170);     // scale it to use it with the servo (value between 0 and 180)
  myservo1.write(val1);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
  val2 = analogRead(potpin2);            // reads the value of the potentiometer (value between 0 and 1023)
  val2 = map(val2, 0, 1023, 20, 100);     // scale it to use it with the servo (value between 0 and 180)
  myservo2.write(val2);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
