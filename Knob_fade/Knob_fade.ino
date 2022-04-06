int knobPin = A0;
int ledPin = 9;
int ledPin2 = 10;
int val;

void setup () {
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(knobPin, INPUT);
  Serial.begin(9600);
}
void loop () {
  val = analogRead(knobPin);
  Serial.println(val);
  int sensorHighValue = 800;
  int sensorLowValue = 320;
  if (val > sensorHighValue) {
    // DO NOTHING

  }
  else {
    val = map(val, sensorLowValue, sensorHighValue, 100, 500);
    val = constrain(val, 100, 500);
    analogWrite(ledPin, 128);
    delay(val);
    analogWrite(ledPin, 0);
    delay(val);
    }

    //  int midValue = (sensorHighValue - sensorLowValue) / 2 + sensorLowValue;
    //
    //  Serial.println(midValue);
    //  if (val < midValue) {
    //
    //    val = map(val, sensorLowValue, midValue, 0, 255);
    //    val = constrain(val, 0, 255);
    //
    //    //do something
    //    analogWrite(ledPin, val);
    //    analogWrite(ledPin2, 0);
    //  }
    //  else {
    //    //do something else
    //    val = map(val, midValue, sensorHighValue, 0, 255);
    //    val = constrain(val, 0, 255);
    //    analogWrite(ledPin, 0);
    //    analogWrite(ledPin2, val);
    //  }
  }
  // the analog input pin from the potentiometer // pin for LED (a PWM pin)
  // Variable to hold light sensor value
  // declare ledPin as output // knobPin is an (analog) input
  //read the value from the pot // map to reasonable values
  // Make sure it doesn’t go out of range // write it to the LED using PWM
