int knobPin = A0;
int ledPin = 9;
int val;

void setup () {
  pinMode(ledPin, OUTPUT);
  pinMode(knobPin, INPUT);
}
void loop () {
  val = analogRead(knobPin);
  val = map(val, 0, 1023, 0, 100);
  val = constrain(val, 0, 255);
  analogWrite(ledPin, val);
}
// the analog input pin from the potentiometer // pin for LED (a PWM pin)
// Variable to hold light sensor value
// declare ledPin as output // knobPin is an (analog) input
//read the value from the pot // map to reasonable values
// Make sure it doesn’t go out of range // write it to the LED using PWM
