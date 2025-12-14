#include "SevSeg.h"

int workTimerLength = 50;
int breakTimerLength = 10;
unsigned long previousTime = 0;  // the time that happened. is set to currentTime when a time loop cycle is completed
long interval = 60000;           // 1 minute in milliseconds. whenever previousTime goes over by currentTime by this amount it updates. default is 60000
long mins = 0;                   // the amount of updates previousTime had (minutes)
String timerType = "work";       // used to keep track of whether the timer should be 10 or 50 minutes (work or break)

SevSeg sevseg;

void setup() {
  Serial.begin(9600);
  pinMode(A0, OUTPUT);

  byte numDigits = 4;  // 4 digit 7 Segment Display is used, we define it here
  // D1 D2 D3 D4
  byte digitPins[] = { 2, 5, 6, 8 };  //PIN NUMBERS OF the digit pins
  //a b c d e f g DP
  byte segmentPins[] = { 3, 7, 10, 12, 13, 4, 9, 11 };  //respective pins for 7 segment led pins
  bool resistorsOnSegments = false;                     // 'false' means resistors are on digit pins
  byte hardwareConfig = COMMON_CATHODE;                 // Need to check against your datasheet whether it is COMMON_ANODE or COMMON_CATHODE
  bool updateWithDelays = false;                        // Default. Recommended
  bool leadingZeros = true;                             // Use 'true' if you'd like to keep the leading zeros

  //passing the relevant variables to the Sevseg class, refer to the header and .cpp file for more info
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(10);  //brightness can range from 0 to 100
}

void loop() {
  unsigned long currentTime = millis();  // time since currentTime was updated

  if (mins == 0) {
    sevseg.setNumber(0000);
  }

  if (currentTime - previousTime > interval) {  // updates currentTime every interval (1 minute)
    previousTime = currentTime;
    mins++;                                 // increases the minutes
    sevseg.setNumber(minsToDisplay(mins));  //display the time on the 4 digit array
  }
  sevseg.refreshDisplay();  // idk what it does but it's important

  if (mins > workTimerLength && timerType == "work") {  // whenever the amount of times previousTime has been updated goes over workTimerLength variable and the timer type is work, the timer type switches to break.
    currentTime = 0;
    previousTime = 0;
    mins = 0;
    timerType = "break";
  }
  if (mins > breakTimerLength && timerType == "break") {  // same as the top one
    currentTime = 0;
    previousTime = 0;
    mins = 0;
    timerType = "work";
  }
}

int minsToDisplay(int minutes) {
  int extraMins = minutes % 60;
  int hoursInMinutes = minutes - mins;
  int hours = hoursInMinutes / 60;

  int fulltime = hours * 100 + extraMins;

  return fulltime;
}
