#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>

// the four lines of the LCD
String line0 = "Click on something!";
String line1;
String line2;
String line3;

// variables for the parts of the cell
int vacc = 11;
int mito = 2;
int chloro = 10;
int nuc = 9;
int cyto = 12;
int choose = 6;
int knob = A0;
int wall = 7;

// initialize the LCD
LiquidCrystal_I2C lcd(0x27,20,4);

void setup()
{
  Serial.begin(9600);

  pinMode(knob, INPUT);

  // cell wall button initialization
  pinMode(wall, INPUT);
  digitalWrite(wall, HIGH);

  // vaccuole button initialization
  pinMode(vacc, INPUT);
  digitalWrite(vacc, HIGH);

  // mitochondria button initialization
  pinMode(mito, INPUT);
  digitalWrite(mito, HIGH);

  // chloroplast button initialization
  pinMode(chloro, INPUT);
  digitalWrite(chloro, HIGH);

  // nucleus button initialization
  pinMode(nuc, INPUT);
  digitalWrite(nuc, HIGH);

  // cytoplasm button initialization
  pinMode(cyto, INPUT);
  digitalWrite(cyto, HIGH);

  // selection button initialization
  pinMode(choose, INPUT);
  digitalWrite(choose, HIGH);

  // start the LCD
  lcd.init();
  lcd.backlight();

  // start the serial monitor
  Serial.begin(9600);

  // clear the LCD and print some test on to the LCD
  lcd.write("               ");
  lcd.setCursor(0, 0);
  lcd.print("Click on something!");
}

void loop()
{
  // get values of the buttons and the knob
  int mitoVal = digitalRead(mito);
  int vaccVal = digitalRead(vacc);
  int chloroVal = digitalRead(chloro);
  int nucVal = digitalRead(nuc);
  int cytoVal = digitalRead(cyto);
  int chooseVal = digitalRead(choose);
  int wallVal = digitalRead(wall);
  int knobVal = analogRead(knob);

  // print on the screen based off what button has been pressed

  if (vaccVal == 0) {
    line0 = "Name: Vacuole";
    line1 = "-filled with cell sa";
    line2 = "p, a liquid containi";
    line3 = "ng salt and sugar.";
    write();
  }

  if (mitoVal == 0) {
    line0 = "Name: Mitochondria";
    line1 = "-creates energy for";
    line2 = "the cell with food";
    line3 = "from chloroplasts";

    write();

  }

  if (chloroVal == 0) {
    line0 = "Name: Chloroplast";
    line1 = "-creates food for";
    line2 = "the cell through";
    line3 = "photosyntheis";

    write();
  }

  if (nucVal == 0) {
    line0 = "Name: Nucleus";
    line1 = "-controles the";
    line2 = "cell and contains";
    line3 = "genetic information";

    write();

  }

  if (cytoVal == 0) {
    line0 = "Name: Cytoplasm";
    line1 = "-a jelly inside the";
    line2 = "cell and where chemi";
    line3 = "cal reactions happen";

    write();

  }

  // selection menu for the cell membrane and cell wall
  if (chooseVal == 0) {
    line0 = "Choose:";
    line1 = "Cell Wall";
    line2 = "Cell Membrane";
    line3 = "reclick to refresh";

    if (knobVal > 508) {
      line0 = "Choose:";
      line1 = "Cell Wall";
      line2 = "> Cell Membrane";
      line3 = "reclick to refresh";

      write();
    }

    if (knobVal < 509) {
      line0 = "Choose:";
      line1 = "> Cell Wall";
      line2 = "Cell Membrane";
      line3 = "reclick to refresh";

      write();
    }

    if (knobVal > 508 && btnVal == 0) {
      line0 = "Name: Cell Wall";
      line1 = "-stiff outer layer";
      line2 = "that gives the cell";
      line3 = "structure";

      write();
    }

    if (knobVal < 509 && wallVal == 0) {
      line0 = "Name: Cell Membrane";
      line1 = "-a thin skin around";
      line2 = "the cell that lets";
      line3 = "things in and out";

      write();
    }
    write();
  }
  lcd.setCursor(0,0);
}

// function to write to the LCD
// all it does is print the line variables at lines 5 to 8. It also sets the cursor position for those lines
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
