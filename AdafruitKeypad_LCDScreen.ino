#include "Adafruit_Keypad.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte ROWS = 4; // rows
const byte COLS = 4; // columns
//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Adafruit_Keypad customKeypad = Adafruit_Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

//0x27 is the device address.
LiquidCrystal_I2C lcd(0x27, 20, 4); // set the LCD address to 0x27 for a 16 chars and 2 line display
//If address 0x27 doesn't work, try address 0x3F (shown below...)
//LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x3F for a 16 chars and 2 line display

static unsigned int state;

void setup() {
  Serial.begin(9600);
  customKeypad.begin();
  lcd.init(); 
  lcd.clear();         
  lcd.backlight();      // Make sure backlight is on

  state = 0;

}

void loop() {
  customKeypad.tick();
  keypadEvent e = customKeypad.read();

  switch (state){ //Transitions
    case 0:
      while(customKeypad.available()){
        e = customKeypad.read();
        Serial.print((char)e.bit.KEY);
      }
      if((char)e.bit.KEY == '1'){
        state = 1;
      }
      else if((char)e.bit.KEY == '2'){
        state = 7;
      }
      break;
    // CALLIBRATION CASES
    case 1:
      while(customKeypad.available()){
        e = customKeypad.read();
        Serial.print((char)e.bit.KEY);
      }
      if((char)e.bit.KEY == 'A'){
        state = 2;
      }
      break;
    case 2:
      delay(3000);
      state = 3;
      break;
    case 3:
      delay(3000);
      state = 4;
      break;
    case 4:
      while(customKeypad.available()){
        e = customKeypad.read();
        Serial.print((char)e.bit.KEY);
      }
      if((char)e.bit.KEY == '1'){
        state = 5;
      }
      break;
    case 5:
      delay(3000);
      state = 6;
      break;
    case 6:
      delay(3000);
      state = 0;
      break;
    // RUNNING SAMPLE CASES
    case 7:
      delay(3000);
      state = 8;
      break;
    case 8:
      delay(3000);
      state = 9;
      break;
    case 9:
      delay(3000);
      state = 10;
      break;
    case 10:
      delay(3000);
      state = 11;
      break;
    case 11:
      while(customKeypad.available()){
        e = customKeypad.read();
        Serial.print((char)e.bit.KEY);
      }
      if((char)e.bit.KEY == 'A'){
        state = 12;
      }
      else if((char)e.bit.KEY == 'B'){
        state = 13;
      }
      break;
    case 12:
      delay(3000);
      state = 0;
      break;
    case 13:
      delay(3000);
      state = 0;
      break;
  }

  switch (state){ //Display
    case 0:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SELECT AN OPTION");
      lcd.setCursor(2,1);
      lcd.print("1. CALLIBRATE");
      lcd.setCursor(2,2);
      lcd.print("2. SAMPLE");
      break;
    // CALLIBRATION CASES
    case 1:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("CALLIBRATE");
      lcd.setCursor(2,1);
      lcd.print("A. TARE");
      break;
    case 2:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("TARING 0 KG");
      lcd.setCursor(2,1);
      lcd.print("REMOVE ALL WEIGHTS");
      break;
    case 3:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("TARING COMPLETE");
      break;
    case 4:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("PLACE WEIGHT");
      lcd.setCursor(2,1);
      lcd.print("ON THE");
      lcd.setCursor(2,2);
      lcd.print("LOAD CELL");
      lcd.setCursor(2,3);
      lcd.print("1. DONE");
      break;
    case 5:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("ENTER KNOWN");
      lcd.setCursor(2,1);
      lcd.print("WEIGHT (G)");
      break;
    case 6:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("CALLIBRATION");
      lcd.setCursor(2,1);
      lcd.print("COMPLETE");
      lcd.setCursor(2,2);
      lcd.print("RETURNING TO");
      lcd.setCursor(2,3);
      lcd.print("MAIN SCREEN...");
      break;
    // RUNNING SAMPLE CASES
    case 7:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SAMPLE");
      lcd.setCursor(2,1);
      lcd.print("ENTER PARAMETERS");
      lcd.setCursor(2,2);
      lcd.print("LENGTH (MM)");
      break;
    case 8:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SAMPLE");
      lcd.setCursor(2,1);
      lcd.print("ENTER PARAMETERS");
      lcd.setCursor(2,2);
      lcd.print("WIDTH (MM)");
      break;
    case 9:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SAMPLE");
      lcd.setCursor(2,1);
      lcd.print("ENTER PARAMETERS");
      lcd.setCursor(2,2);
      lcd.print("THICKNESS (uM)");
      break;
    case 10:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("RUNNING SAMPLE");
      break;
    case 11:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("FILE SAVED");
      lcd.setCursor(2,1);
      lcd.print("TO SD CARD");
      lcd.setCursor(2,2);
      lcd.print("A. RETURN TO MENU");
      lcd.setCursor(2,3);
      lcd.print("B. EJECT SD CARD");
      break;
    case 12:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("RETURNING TO");
      lcd.setCursor(2,1);
      lcd.print("MAIN SCREEN...");
      break;
    case 13:
      lcd.clear();
      lcd.setCursor(2,0);
      lcd.print("SD CARD EJECTED");
      lcd.setCursor(2,1);
      lcd.print("RETURNING TO");
      lcd.setCursor(2,2);
      lcd.print("MAIN SCREEN...");
      break;
  }

  delay(1000);
}
