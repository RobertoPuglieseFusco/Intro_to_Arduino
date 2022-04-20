/*
  Fading

  This example shows how to fade an LED using the analogWrite() function.

  The circuit:
  - LED attached from digital pin 9 to ground.

  created 1 Nov 2008
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fading
*/

int motor1 = 9;    // LED connected to digital pin 9
int motor2 = 10;    // LED connected to digital pin 9


void setup() {
  // nothing happens in setup
  pinMode(motor1,OUTPUT);
  pinMode(motor2,OUTPUT);
}

void loop() {
  
motorBF();
//analogWrite(motor1, 255);
//  analogWrite(motor2, 0);

//digitalWrite(motor1, LOW);
//  digitalWrite(motor2, HIGH);


}

void motorBF(){
  // fade in from min to max in increments of 5 points:
  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
    // sets the value (range from 0 to 255):
    analogWrite(motor1, fadeValue);
    analogWrite(motor2, 0);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
    // sets the value (range from 0 to 255):
    analogWrite(motor1, fadeValue);
    analogWrite(motor2, 0);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 1) {
    // sets the value (range from 0 to 255):
    analogWrite(motor2, fadeValue);
    analogWrite(motor1, 0);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 1) {
    // sets the value (range from 0 to 255):
    analogWrite(motor2, fadeValue);
    analogWrite(motor1, 0);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  
  
  
  }
