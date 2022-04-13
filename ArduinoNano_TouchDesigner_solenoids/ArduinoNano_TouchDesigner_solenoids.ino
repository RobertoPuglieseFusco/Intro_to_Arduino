#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
int Steps = 0;
boolean Direction = true;

char inChar;

void setup() {
  Serial.begin(19200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
void loop() {

  if (Serial.available()) {
   // inChar = (char)Serial.read();
    int valA = Serial.parseInt();
    Serial.println(valA);
    int someInt = inChar;

    digitalWrite(valA, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(50);                       // wait for a second
    //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(valA, LOW);    // turn the LED off by making the voltage LOW
    delay(50);
  }


}
