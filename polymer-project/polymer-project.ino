#include <LedControl.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

String line0 = "Click on something!";
String line1;
String line2;
String line3;

int scroll = 0;

const int xPin = A1;
const int yPin = A0;

const int backBtnPin = 2;
const int nextBtnPin = 7;
LedControl lc1 = LedControl(8, 10, 9, 1);
LedControl lc2 = LedControl(13, 11, 12, 1);
LiquidCrystal_I2C lcd(0x27, 20, 4);
int slide = 1;

byte cleared[8] = { B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000 };
byte atomFrame1[8] = { 0b00000000, 0b10111010, 0b10000010, 0b00000000, 0b00000000, 0b00000000, 0b10000010, 0b10111010 };
byte atomFrame2[8] = { 0b00000000, 0b01011101, 0b01000001, 0b00000000, 0b00000000, 0b00000000, 0b01000001, 0b01011101 };
byte bondFrame1[8] = { 0b00000000, 0b00000000, 0b00000000, 0b00101000, 0b00101000, 0b00101000, 0b00000000, 0b00000000 };
byte bondFrame2[8] = { 0b00000000, 0b00000000, 0b00000000, 0b00010100, 0b00010100, 0b00010100, 0b00000000, 0b00000000 };
byte fullFrame1[8] = { 0b00000000, 0b10111010, 0b10000010, 0b00101000, 0b00101000, 0b00101000, 0b10000010, 0b10111010 };
byte fullFrame2[8] = { 0b00000000, 0b01011101, 0b01000001, 0b00010100, 0b00010100, 0b00010100, 0b01000001, 0b01011101 };
byte singleFrame1[8] = { 0b00001000, 0b01011101, 0b01000001, 0b00001000, 0b00001000, 0b00001000, 0b01000001, 0b01011101 };
byte singleFrame2[8] = { 0b10111010, 0b10000010, 0b00010000, 0b00010000, 0b00010000, 0b10000010, 0b10111010, 0b00010000 };
byte joinedFrame1[8] = { 0b00010000, 0b10111010, 0b10000010, 0b00010000, 0b00010000, 0b00010000, 0b10000010, 0b10111010 };
byte joinedFrame2[8] = { 0b10111010, 0b10000010, 0b00010000, 0b00010000, 0b00010000, 0b10000010, 0b10111010, 0b00010000 };

char* strongArr[] = { "Why are polymers so ", "strong?             ", "bonds between monome", "r chains are strong", "" };

void setup() {
  Serial.begin(9600);

  lc1.shutdown(0, false);
  lc1.setIntensity(0, 4);
  lc1.clearDisplay(0);
  lc2.shutdown(0, false);
  lc2.setIntensity(0, 4);
  lc2.clearDisplay(0);

  pinMode(backBtnPin, INPUT_PULLUP);
  pinMode(nextBtnPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
}

void loop() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  Serial.print("x value: ");
  Serial.print(xValue);
  Serial.print(" y value: ");
  Serial.println(yValue);

  if (xValue < 250 && slide > 0) {
    slide = slide - 1;
  }

  if (xValue > 900 && slide < 11) {
    Serial.println("slide on");
    slide++;
  }

  if (yValue < 250 && scroll > -1) {
    scroll = scroll + 1;
  }
  if (yValue > 900 && scroll < 2) {
    scroll = scroll - 1;
  }

  if (slide == 1) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, atomFrame1[i]);
      lc2.setRow(0, i, atomFrame2[i]);
    }
    line0 = "                    ";
    line1 = "     POLYMERS       ";
    line2 = "                    ";
    line3 = "                    ";
    write();
  }

  if (slide == 2) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, atomFrame1[i]);
      lc2.setRow(0, i, atomFrame2[i]);
    }
    line0 = "These are the atoms ";
    line1 = "of 2 monomers       ";
    line2 = "                    ";
    line3 = "                    ";
    write();
  }

  if (slide == 3) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, bondFrame1[i]);
      lc2.setRow(0, i, bondFrame2[i]);
    }
    line0 = "These are the bonds ";
    line1 = "in 2 monomers       ";
    line2 = "                    ";
    line3 = "                    ";
    write();
  }

  if (slide == 4) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, fullFrame1[i]);
      lc2.setRow(0, i, fullFrame2[i]);
    }
    line0 = "These are double bon";
    line1 = "ded monomers.This me";
    line2 = "ans they can't join ";
    line3 = "other monomers ";
    write();
  }

  if (slide == 5) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, singleFrame1[i]);
      lc2.setRow(0, i, singleFrame2[i]);
    }
    line0 = "The double bonds hav";
    line1 = "e broken down into s";
    line2 = "ingle bonds.        ";
    line3 = "                    ";
    write();
  }

  if (slide == 6) {
    for (int i = 0; i < 8; i++) {
      lc1.setRow(0, i, joinedFrame1[i]);
      lc2.setRow(0, i, joinedFrame2[i]);
    }
    line0 = "This allows the mono";
    line1 = "mers to join togethe";
    line2 = "r.                  ";
    line3 = "                    ";
    write();
  }

  if (slide == 7) {
    for (int i = 0; i < 8; i++) {
      lc1.clearDisplay(0);
      lc2.clearDisplay(0);
    }
    line0 = "                    ";
    line1 = " THERMOSETTING and  ";
    line2 = "   THERMOPLASTICS   ";
    line3 = "                    ";
    write();
  }

  if (slide == 8) {
    for (int i = 0; i < 8; i++) {
      lc1.clearDisplay(0);
      lc2.clearDisplay(0);
    }
    line0 = "THERMOSETTING       ";
    line1 = "-permenantly harden ";
    line2 = "when heated and are ";
    line3 = "more heat-resistant ";
    write();
  }

  if (slide == 9) {
    for (int i = 0; i < 8; i++) {
      lc1.clearDisplay(0);
      lc2.clearDisplay(0);
    }
    line0 = "THERMOPLASTICS      ";
    line1 = "-can be shaped and  ";
    line2 = "reshaped, but are   ";
    line3 = "less heat-resistant ";
    write();
  }

  if (slide == 10) {
    for (int i = 0; i < 8; i++) {
      lc1.clearDisplay(0);
      lc2.clearDisplay(0);
    }
    line0 = strongArr[scroll + 0];
    line1 = strongArr[scroll + 1];
    line2 = strongArr[scroll + 2];
    line3 = strongArr[scroll + 3];
    write();
  }

  delay(500);
  lcd.setCursor(0, 0);
}

void write() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(line0);

  lcd.setCursor(0, 1);
  lcd.print(line1);

  lcd.setCursor(0, 2);
  lcd.print(line2);

  lcd.setCursor(0, 3);
  lcd.print(line3);
}
