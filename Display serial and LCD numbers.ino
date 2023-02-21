#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#define I2C_SLAVE_ADDR 0x04

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};


byte rowPins[ROWS] = {26, 27, 32, 33}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {13, 4, 25}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);


void setup(){
  Serial.begin(9600);

  pinMode(13, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);

  Wire.begin();  // join i2c bus
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

}

 

void loop(){
  char key = keypad.getKey();

  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4

  int x, y, z;
  if (key){
    Serial.println(key);
    lcd.clear();

    if (key == '#'){
      x=150;
      y=70;
      z=50;
      lcd.setCursor(0, 0);  // Set the cursor on the first column and first row.
      lcd.print("Symbol selected");
      lcd.setCursor(1, 1);  //Set cursor to 2nd column and 2nd row (counting starts at 0)
      lcd.write(key);  
    }

    else if (key == '*'){
      x=100;
      y=200;
      z=105;
      lcd.setCursor(0, 0);  // Set the cursor on the first column and first row.
      lcd.print("Symbol selected");
      lcd.setCursor(1, 1);  //Set cursor to 2nd column and 2nd row (counting starts at 0)
      lcd.write(key);  
    }

    else {
      x=0;
      y=0;
      z=78; 
      lcd.setCursor(0, 0);  // Set the cursor on the first column and first row.
      lcd.print("Number selected");
      lcd.setCursor(1, 1);  //Set cursor to 2nd column and 2nd row (counting starts at 0)
      lcd.write(key);   
    }

    Wire.write((byte)((x & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
    Wire.write((byte)(x & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((y & 0x0000FF00) >> 8));    // first byte of y, containing bits 16 to 9
    Wire.write((byte)(y & 0x000000FF));           // second byte of y, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((z & 0x0000FF00) >> 8));    // first byte of z, containing bits 16 to 9
    Wire.write((byte)(z & 0x000000FF));           // second byte of z, containing the 8 LSB - bits 8 to 1


    Wire.endTransmission();   // stop transmitting
  }
}
