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

int value = 0;                    // variable for reading the pin status
int nextPin = 2;
int prevPin = 3;
int volumePin = A0;
int playPin = 4;

int ledPin = 13;

bool playMode = false;

int fileToPlay = 3;
int numFiles = 4;
unsigned long timer = 0;
unsigned long timeOffset = 0;

uint8_t vol = 20;

void setup()
{

  pinMode(nextPin, INPUT_PULLUP);
  pinMode(prevPin, INPUT_PULLUP);
  pinMode(playPin, INPUT_PULLUP);

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

  myDFPlayer.volume(vol);  //Set volume value. From 0 to 30
  myDFPlayer.play(fileToPlay);  //Play the first mp3
}

void loop()
{

  if (myDFPlayer.available() && (millis() - timer > 4000)) {
    timer = millis();
    Serial.print(timer);
    Serial.print(" ");
    Serial.println(millis());
    printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
  }


  // NEXT
  value = digitalRead(nextPin);  // read input value
  if (value == false) {
    fileToPlay++;
    playMode = true;
    Serial.println("pressed next");
    if (fileToPlay > numFiles) {
      fileToPlay = 1;
    }
    playTrack(fileToPlay);
    delay(500);
  }

  // PREV
  value = digitalRead(prevPin);  // read input value
  if (value == false) {
    fileToPlay--;
    
    playMode = true;
    Serial.println("pressed previous");
    if (fileToPlay < 1) {
      fileToPlay = numFiles;
    }
    playTrack(fileToPlay);
    delay(500);
  }

  //PLAY / STOP
  value = digitalRead(playPin);  // read input value
  if (value == false) {
    Serial.println("pressed play button");
    if (playMode) {
      Serial.println("stop");
      myDFPlayer.pause();  //pause the mp3
      playMode = false;
      delay(500);
    }
    else {
      myDFPlayer.start();  //start the mp3 from the pause
      Serial.println("play");
      playMode = true;
      delay(500);
    }
  }
  if (playMode) {
    digitalWrite(ledPin, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }


  uint8_t nVol = map(analogRead(volumePin), 1023, 0, 0, 28);
  if (nVol != vol) {
    vol = nVol;
    myDFPlayer.volume(vol);
    Serial.println("volume changed");
  }

}


void playTrack(uint8_t track) {
   myDFPlayer.stop();
   delay(200);
   myDFPlayer.play(track);
   delay(200);
   int file = myDFPlayer.readCurrentFileNumber();

   Serial.print("Track:");Serial.println(track);
   Serial.print("File:");Serial.println(file);

   while (file != track) {
     myDFPlayer.play(track);
     delay(200);
     file = myDFPlayer.readCurrentFileNumber();
     fileToPlay = file;
   }
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
      fileToPlay++;
      delay(3000);      
      Serial.println(F(" Play next in cue"));
      playMode = true;
      if (fileToPlay > numFiles) {
        Serial.println(F("Play from the beginning!"));
        fileToPlay = 1;
      }
      playTrack(fileToPlay);
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
