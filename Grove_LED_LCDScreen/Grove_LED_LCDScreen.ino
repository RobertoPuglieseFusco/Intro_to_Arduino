// Demo for Grove - Starter V2.0
// Author: Loovee  2013-3-10
// Pulses the Grove - LED with a "breathing" effect.
// Connect the Grove - LED to the socket marked D3

// Defines the pin to which the LED is connected.
// Any pin that supports PWM can also be used:
// 3, 5, 6, 9, 10, 11


#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

const int colorR = 255;
const int colorG = 0;
const int colorB = 0;

const int pinLed    = 3;

// Define the delay for the "breathing" effect; change this
// to a smaller value for a faster effect, larger for slower.
const int BREATH_DELAY = 5; // milliseconds

void setup()
{
    // Configure the LED's pin for output signals.
    pinMode(pinLed, OUTPUT);
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    
    lcd.setRGB(colorR, colorG, colorB);
    
    // Print a message to the LCD.
    lcd.print("brighness value");

    delay(1000);
}

void loop()
{
    for(int i=0; i<256; i++)
    {
        analogWrite(pinLed, i);
        delay(BREATH_DELAY);
        // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(i);
    }
    delay(100);
    
    for(int i=254; i>=0; i--)
    {
        analogWrite(pinLed, i);
        delay(BREATH_DELAY);
            // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    lcd.print(i);
    }
    delay(500);
}
