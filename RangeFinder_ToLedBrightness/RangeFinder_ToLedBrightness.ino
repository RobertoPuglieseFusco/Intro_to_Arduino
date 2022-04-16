#define trigPin 10
#define echoPin 12
#define ledPin 9    // LED connected to digital pin 9

int brightness = 31;    // how bright the LED is


void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;

  if (distance >= 400 || distance <= 2) {
    Serial.print("Distance = ");
    Serial.println("Out of range");
    brightness = 0;
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");

    // set the brightness of pin 9:
    brightness = map(distance, 50, 10, 0, 100);
    brightness = constrain(brightness, 0, 255);
    analogWrite(ledPin, brightness);

  }
  if (distance > 50) {
    digitalWrite(LED_BUILTIN, LOW);  //Turn led off
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH); //Turn led on
  }
  delay(50);
}
