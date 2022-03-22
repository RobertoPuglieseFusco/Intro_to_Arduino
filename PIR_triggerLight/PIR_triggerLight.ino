/*
   PIR sensor tester
*/
#define ledPin 9    // LED connected to digital pin 9


int minimumBrightness = 20;
int maximumBrightness = 200; // do not use more than 255
int fadeAmount = 1;    // how many points to fade the LED by


int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

int brightness = minimumBrightness;    // how bright the LED is
boolean rampUp = false;

void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  val = digitalRead(inputPin);  // read input value
  // set the brightness of pin 9:


  if (brightness < maximumBrightness && rampUp) {
    brightness = brightness + fadeAmount;
  }

  if (brightness >= maximumBrightness && val == LOW) {
    rampUp = false;

  }

  if (brightness > minimumBrightness && !rampUp) {

    brightness = brightness - fadeAmount;
  }

  brightness = constrain(brightness, 0, 255);
  Serial.println(brightness);
  analogWrite(ledPin, brightness);

  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(LED_BUILTIN, HIGH);  // turn LED ON
    // change the brightness for next time through the loop:

    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      rampUp = true;
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW); // turn LED OFF
    
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
// change delay time to slow down or speed up the fade in/out of the light
  delay(50);
}
