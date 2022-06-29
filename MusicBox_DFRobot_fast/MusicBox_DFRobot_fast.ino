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

#include <DFPlayerMini_Fast.h>

#if !defined(UBRR1H)
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX
#endif

DFPlayerMini_Fast myDFPlayer;

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

void setup()
{

  pinMode(nextPin, INPUT_PULLUP);
  pinMode(prevPin, INPUT_PULLUP);
  pinMode(playPin, INPUT_PULLUP);

  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
#if !defined(UBRR1H)
  mySerial.begin(9600);
  myDFPlayer.begin(mySerial, true);
#else
  Serial1.begin(9600);
  myDFPlayer.begin(Serial1, true);
#endif

  delay(5000);

  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
  myDFPlayer.play(fileToPlay);  //Play the first mp3
}

void loop()
{

  //if (myDFPlayer.isPlaying() == false && (millis - timer > 2000)) {
     if (myDFPlayer.isPlaying() == false) {
    timer += millis();
    Serial.print(F("Number:"));
    Serial.print(value);
    Serial.println(F(" Play Finished!"));
    fileToPlay++;
    delay(2000);
    myDFPlayer.playNext();
    Serial.println(F(" Play next in cue"));
    playMode = true;
    if (fileToPlay > numFiles) {
      Serial.println(F("Play from the beginning!"));
      fileToPlay = 1;
    }

  }


  // NEXT
  value = digitalRead(nextPin);  // read input value
  if (value == false) {
    fileToPlay++;
    myDFPlayer.playNext();
    playMode = true;
    Serial.println("pressed next");
    if (fileToPlay > numFiles) {
      fileToPlay = 1;
    }
    delay(500);
  }

  // PREV
  value = digitalRead(prevPin);  // read input value
  if (value == false) {
    fileToPlay--;
    myDFPlayer.playPrevious();
    playMode = true;
    Serial.println("pressed previous");
    if (fileToPlay < 1) {
      fileToPlay = numFiles;
    }
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
      myDFPlayer.resume();  //start the mp3 from the pause
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

//  value = analogRead(volumePin);
//  myDFPlayer.volume(map(value, 1023, 0, 0, 28));

}
