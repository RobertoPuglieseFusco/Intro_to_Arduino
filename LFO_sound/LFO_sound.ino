/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage
*/
int piezoPin = 8;
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(piezoPin, OUTPUT);
}
int i = 0;
// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0); // a value between 0 - 1023
  Serial.println(sensorValue);

  // it is a value between 0 - 255

  int period = map(sensorValue, 550, 850, 40, 400);

  
  if (i == 0) {
    tone(piezoPin, 440, 50);
    i++;
  }
  else {
    tone(piezoPin, 880, 50);
    i=0;
  }

  period = constrain(period, 0, 2000);
  delay(period);
  noTone(piezoPin);
  delay(period);

}
