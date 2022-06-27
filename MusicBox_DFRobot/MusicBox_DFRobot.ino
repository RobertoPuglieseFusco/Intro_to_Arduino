/***************************************************
  DFPlayer - A Mini MP3 Player For Arduino
  <https://www.dfrobot.com/product-1121.html>

 ***************************************************
  This example shows the basic function of library for DFPlayer.

  Created 2016-12-07
  By [Angelo qiao](Angelo.qiao@dfrobot.com)

  GNU Lesser General Public License.
  See <http://www.gnu.org/licenses/> for details.
  All above must be included in any redistribution
 ****************************************************/

/***********Notice and Trouble shooting***************
  1.Connection and Diagram can be found here
  <https://www.dfrobot.com/wiki/index.php/DFPlayer_Mini_SKU:DFR0299#Connection_Diagram>
  2.This code is tested on Arduino Uno, Leonardo, Mega boards.
 ****************************************************/

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);

int inputPin = 2;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int value = 0;                    // variable for reading the pin status
int nextPin = 2;
int prevPin = 3;
int volumePin = A0;
int playPin = 4;

int ledPin = 5;

bool playMode = false;

int fileToPlay = 1;
int numFiles = 4;

void setup()
{

  pinMode(inputPin, INPUT);
  pinMode(nextPin, INPUT);
  pinMode(prevPin, INPUT);
  pinMode(playPin, INPUT);

  pinMode(ledPin, OUTPUT);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.enableLoopAll(); //loop all mp3 files.

  myDFPlayer.volume(17);  //Set volume value. From 0 to 30
  myDFPlayer.play(fileToPlay);  //Play the first mp3
}

void loop()
{

  if (myDFPlayer.available()) {
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }


  // NEXT
  value = digitalRead(nextPin);  // read input value
  if (value == true) {
    fileToPlay++;
    myDFPlayer.next();
    playMode = true;
    if (fileToPlay > numFiles) {
      fileToPlay = 1;
    }
    delay(500);
  }

  // PREV
  value = digitalRead(prevPin);  // read input value
  if (value == true) {
    fileToPlay--;
    myDFPlayer.previous();
    playMode = true;
    if (fileToPlay < 1) {
      fileToPlay = numFiles;
    }
    delay(500);
  }

  //PLAY / STOP
  value = digitalRead(playPin);  // read input value
  if (value == true) {
    if (playMode) {
      myDFPlayer.pause();  //pause the mp3
      playMode = false;
      delay(500);
    }
    else {
      myDFPlayer.start();  //start the mp3 from the pause
      playMode = true;
      delay(500);
    }
  }
  if (playMode) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }

  value = analogRead(volumePin);
  myDFPlayer.volume(map(value, 0, 1023, 0, 28));

}

void printDetail(uint8_t type, int value) {
  switch (type) {
    case TimeOut:
      Serial.println(F("Time Out!"));
      break;
    case WrongStack:
      Serial.println(F("Stack Wrong!"));
      break;
    case DFPlayerCardInserted:
      Serial.println(F("Card Inserted!"));
      break;
    case DFPlayerCardRemoved:
      Serial.println(F("Card Removed!"));
      break;
    case DFPlayerCardOnline:
      Serial.println(F("Card Online!"));
      break;
    case DFPlayerUSBInserted:
      Serial.println("USB Inserted!");
      break;
    case DFPlayerUSBRemoved:
      Serial.println("USB Removed!");
      break;
    case DFPlayerPlayFinished:
      Serial.print(F("Number:"));
      Serial.print(value);
      Serial.println(F(" Play Finished!"));
      break;
    case DFPlayerError:
      Serial.print(F("DFPlayerError:"));
      switch (value) {
        case Busy:
          Serial.println(F("Card not found"));
          break;
        case Sleeping:
          Serial.println(F("Sleeping"));
          break;
        case SerialWrongStack:
          Serial.println(F("Get Wrong Stack"));
          break;
        case CheckSumNotMatch:
          Serial.println(F("Check Sum Not Match"));
          break;
        case FileIndexOut:
          Serial.println(F("File Index Out of Bound"));
          break;
        case FileMismatch:
          Serial.println(F("Cannot Find File"));
          break;
        case Advertise:
          Serial.println(F("In Advertise"));
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

}