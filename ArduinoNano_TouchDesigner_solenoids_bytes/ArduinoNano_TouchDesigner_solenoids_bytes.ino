#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11
int Steps = 0;

int inChar;

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}
void loop() {
    if (Serial.available()) {

      inChar = Serial.read();

      Serial.println(inChar);

      digitalWrite(inChar, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(50);                       // wait for a second
      //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      digitalWrite(inChar, LOW);    // turn the LED off by making the voltage LOW
      
    }
}
