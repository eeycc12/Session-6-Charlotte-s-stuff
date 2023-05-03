#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <string>
#include <list>
#include <MPU6050_tockn.h>
#define I2C_SLAVE_ADDR 0x04
#include <vector>


const byte ROWS = 4;  //four rows
const byte COLS = 3;  //three columns
char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

byte rowPins[ROWS] = { 26, 27, 32, 33 };  //connect to the row pinouts of the keypad
byte colPins[COLS] = { 13, 4, 25 };       //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

MPU6050 mpu6050(Wire);

int myArray[100];
int arrayPos = -1;

void setup() {
  Serial.begin(9600);
  pinMode(13, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(25, INPUT_PULLUP);
  Wire.begin();  // join i2c bus
  mpu6050.begin();
}

int TransmitValues(int x, int y, int z) {

  Wire.beginTransmission(I2C_SLAVE_ADDR);  // transmit to device #4

  Wire.write((byte)((x & 0x0000FF00) >> 8));  // first byte of x, containing bits 16 to 9
  Wire.write((byte)(x & 0x000000FF));         // second byte of x, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((y & 0x0000FF00) >> 8));  // first byte of y, containing bits 16 to 9
  Wire.write((byte)(y & 0x000000FF));         // second byte of y, containing the 8 LSB - bits 8 to 1
  Wire.write((byte)((z & 0x0000FF00) >> 8));  // first byte of z, containing bits 16 to 9
  Wire.write((byte)(z & 0x000000FF));         // second byte of z, containing the 8 LSB - bits 8 to 1

  Wire.endTransmission();  // stop transmitting
  return (0);
}

void loop() {
  Serial.println("Charlotte is the best :)");
  char keychar;
  int keyint, a;
  LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter");
  lcd.setCursor(0, 1);
  lcd.print("Command");

  do {
    keychar = keypad.getKey();
    if (keychar >= '0' && keychar <= '9') {  // check if key1 is a digit
      keyint = atoi(&keychar);              // convert the input to an int
      Serial.print(keyint);              // convert the input to an int and print it to Serial
      arrayPos = arrayPos + 1;
      myArray[arrayPos] = keyint;         // add the input to the array
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(keyint);
      lcd.setCursor(0, 1);
      lcd.print("selected");
      delay(100);
      a = 0;
    } else if (keychar == '#') {  // check if key1 is the '#' key
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Command");
      lcd.setCursor(0, 1);
      lcd.print("Complete");
      delay(100);
      a = 1;
    } else if (keychar == '*') {  // check if key1 is the '#' key
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("ALL HAIL");
      lcd.setCursor(0, 1);
      lcd.print("GAZZA");
      delay(100);
      a = 1;
    }
  } while (a != 1);

  for (int i= 0 ; i <= arrayPos; i++) {
    Serial.println(myArray[i]);
    if (i % 2 == 0){
      DirectionFunction(myArray[i]);
    }
    else{
      DistanceFunction(myArray[i]);
    }
  }
  arrayPos = -1;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Looping");
  lcd.setCursor(0, 1);
  lcd.print("again");
  delay(1000);
}

void DirectionFunction(int value) {
  int ang, x, y, z;
  float start, end;
  LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows
  lcd.clear();
  if (value == 2) {

    lcd.setCursor(0, 0);
    lcd.print("Forward");

    x = 0;
    y = 0;
    z = 79;
    TransmitValues(x, y, z);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turn");
    lcd.setCursor(0, 1);
    lcd.print("Complete");
    delay(1000);
  }

  else if (value == 4) {

    lcd.setCursor(0, 0);
    lcd.print("Left");

    ang = 90;
    mpu6050.update();
    start = mpu6050.getAngleZ();
    end = start + ang;

    x = 50;
    y = 150;
    z = 35;
    TransmitValues(x, y, z);

    while (mpu6050.getAngleZ() < end) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Turning");
      Serial.print("Angle is = ");
      mpu6050.update();
      Serial.print(mpu6050.getAngleZ());
    }
    x = 0;
    y = 0;
    z = 79;
    TransmitValues(x, y, z);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turn");
    lcd.setCursor(0, 1);
    lcd.print("Complete");
    delay(1000);
  }


  else if (value == 6) {

    lcd.setCursor(0, 0);
    lcd.print("Right");

    ang = -90;
    mpu6050.update();
    start = mpu6050.getAngleZ();
    end = start + ang;

    x = 150;
    y = 50;
    z = 135;
    TransmitValues(x, y, z);
    

    while (mpu6050.getAngleZ() > end) {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Turning");
      Serial.print("Angle is = ");
      mpu6050.update();
      Serial.print(mpu6050.getAngleZ());
    }
    x = 0;
    y = 0;
    z = 79;
    TransmitValues(x, y, z);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Turn");
    lcd.setCursor(0, 1);
    lcd.print("Complete");
    delay(1000);
  }
}

void DistanceFunction(int value) {
  int x,y,z;
  LiquidCrystal lcd(19, 23, 18, 17, 16, 15);
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows

  int d = value * 257;
  Serial.print("Delay is ");
  Serial.println(d);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moving");
  lcd.setCursor(0, 1);
  lcd.print(d);

  x = 150;
  y = 150;
  z = 79;

  TransmitValues(x, y, z);

  delay(d);

  x = 0;
  y = 0;
  z = 79;
  TransmitValues(x, y, z);
}