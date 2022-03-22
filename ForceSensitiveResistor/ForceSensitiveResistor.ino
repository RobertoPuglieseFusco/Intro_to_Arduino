/* FSR testing sketch.

  Connect one end of FSR to 5V, the other end to Analog 0.
  Then connect one end of a 10K resistor from Analog 0 to ground
  Connect LED from pin 11 through a resistor to ground

  For more information see www.ladyada.net/learn/sensors/fsr.html */

int sensor = 0; // FSR is connected to analog 0
int readingValue;      // connect Red LED to pin 11 (PWM pin)

int pinLed1 = 11;
int pinLed2 = 3;

int ledBrightness_1;
int ledBrightness_2;

void setup() {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}

void loop() {
  readingValue = analogRead(sensor);

  Serial.println(readingValue);

  if (readingValue < 400) {
    ledBrightness_1 = map(readingValue, 0, 400, 0, 255);
    analogWrite(pinLed1, ledBrightness_1);
    analogWrite(pinLed2, 0);
  }
  else {
    ledBrightness_2 = map(readingValue, 400, 800, 0, 255);
    analogWrite(pinLed2, ledBrightness_2);
    analogWrite(pinLed1, 0);
  }
}
