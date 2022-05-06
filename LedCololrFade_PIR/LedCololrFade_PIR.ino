// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 12 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

int ledPin = 13;                // choose the pin for the LED
int inputPin = 3;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();
  pinMode(inputPin, INPUT);     // declare sensor as input

  Serial.begin(9600);
}

void loop() {
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();
  val = digitalRead(inputPin);  // read input value
  Serial.println(val);
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
      for (int j = 0; j < 255; j++) {
        for (int i = 0; i < pixels.numPixels(); i++) { // For each pixel in strip...
          pixels.setPixelColor(i, pixels.Color(j,   j,   j));         //  Set pixel's color (in RAM)

        }
        pixels.show();
        delay(50);
      }
    }
    delay(1000);
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    if (pirState == HIGH) {
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
      for (int j = 255; j > 0; j--) {
        for (int i = 0; i < pixels.numPixels(); i++) { // For each pixel in strip...
          pixels.setPixelColor(i, pixels.Color(j,   j,   j));         //  Set pixel's color (in RAM)
        }
        pixels.show();
        delay(50);
      }
      pixels.clear(); // Set all pixel colors to 'off'
      delay(1000);
    }
  }


}
