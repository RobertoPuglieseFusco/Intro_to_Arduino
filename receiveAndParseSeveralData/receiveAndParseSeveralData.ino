
// Example 5 - Receive with start- and end-markers combined with parsing

const byte numChars = 32;
char receivedChars[numChars];
char tempChars[numChars];        // temporary array for use when parsing

// variables to hold the parsed data
char messageFromPC[numChars] = {0};
float floatFromPC1 = 0;
float floatFromPC2 = 0.0;

boolean newData = false;

const int ledPin = 13; // the pin that the LED is attached to

//============

void setup() {
  Serial.begin(9600);
  Serial.println("This demo expects 3 pieces of data - text, an integer and a floating point value");
  Serial.println("Enter data in this style <HelloWorld, 12, 24.7>  ");
  Serial.println();
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
}

//============

void loop() {
  recvWithStartEndMarkers();
  if (newData == true) {
    strcpy(tempChars, receivedChars);
    // this temporary copy is necessary to protect the original data
    //   because strtok() used in parseData() replaces the commas with \0
    parseData();
    showParsedData();
    newData = false;

    if (floatFromPC1 > 0.5) {
      digitalWrite(ledPin, HIGH); // turn the LED on
    }
    else {
      digitalWrite(ledPin, LOW); // turn the LED on
    }
  }
  
}

//============

void recvWithStartEndMarkers() {
  static boolean recvInProgress = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if (ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[ndx] = '\0'; // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

//============

void parseData() {      // split the data into its parts

  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(tempChars, ",");     // get the first part - the string
  strcpy(messageFromPC, strtokIndx); // copy it to messageFromPC

  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  floatFromPC1 = atof(strtokIndx);     // convert this part to a float



  strtokIndx = strtok(NULL, ",");
  floatFromPC2 = atof(strtokIndx);     // convert this part to a float

}

//============

void showParsedData() {
  Serial.print("Message ");
  Serial.println(messageFromPC);
  Serial.print("Integer ");
  Serial.println(floatFromPC1);
  Serial.print("Float ");
  Serial.println(floatFromPC2);
}
