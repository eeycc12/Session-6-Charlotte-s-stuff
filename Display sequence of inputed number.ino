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

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

LiquidCrystal lcd(19, 23, 18, 17, 16, 15);


void setup(){
  Serial.begin(9600);

  pinMode(13, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);

  Wire.begin();  // join i2c bus
  lcd.begin(16, 2); // set up the LCD's number of columns and rows

}



long long getKeypadIntegerMulti()
{
  long long IC = 0;                                // the number accumulator
  long keyvalue;                              // the key pressed at current moment
  int isnum;
  do
  {
    keyvalue = kpd.getKey();                              // input the key
    isnum = (keyvalue >= '0' && keyvalue <= '9');        // is it a digit?
    if (isnum)                                          // if it is a digit then do this          
    {
      lcd.print(keyvalue - '0');
      IC = (IC * 10) + keyvalue - '0';               // accumulate the input number
    }
  } while (isnum || !keyvalue);                  // until not a digit or while no key pressed
  char digits[22];
  int index = 21;
  digits[index--] = '\0'; // Null terminator

  // Take the rightmost digit, even if it's 0;
  digits[index--] = (IC % 10) + '0';
  IC /= 10;

  // Take all the remaining digits
  while (IC != 0)
  {
    digits[index--] = (IC % 10) + '0';
    IC /= 10;
  }
  // Print the string from the buffer.
  Serial.print(&digits[index+1]); 
  lcd.clear();
  lcd.print("The value is: ");
  lcd.setCursor(1, 1);  //Set cursor to 2nd column and 2nd row (counting starts at 0)
  lcd.print(&digits[index+1]);
  return IC;
}

void loop() 
{
   int val= getKeypadIntegerMulti(); 
    Serial.println(" Value is");
    Serial.println(val);
   delay(2000);
   lcd.clear();
}  