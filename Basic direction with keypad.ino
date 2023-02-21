/* @file HelloKeypad.pde
|| @version 1.0
|| @author Alexander Brevig
|| @contact alexanderbrevig@gmail.com
||
|| @description
|| | Demonstrates the simplest use of the matrix Keypad library.
|| #
*/
#include <Keypad.h>
#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};


byte rowPins[ROWS] = {18, 5, 17, 16}; //GIOP18, GIOP5, GIOP17, GIOP16 connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 0, 2}; //GIOP4, GIOP0, GIOP2 connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
  Serial.begin(9600);
  Wire.begin();  // join i2c bus
}

 

void loop(){
  char key = keypad.getKey();

  Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4

  int x, y, z;
  if (key){
    Serial.println(key);

    if (key == '#'){
      x=150;
      y=70;
      z=50;
    }

    else if (key == '*'){
      x=100;
      y=200;
      z=105;
    }

    else {
      x=0;
      y=0;
      z=78;    
    }

    Wire.write((byte)((x & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
    Wire.write((byte)(x & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((y & 0x0000FF00) >> 8));    // first byte of y, containing bits 16 to 9
    Wire.write((byte)(y & 0x000000FF));           // second byte of y, containing the 8 LSB - bits 8 to 1
    Wire.write((byte)((z & 0x0000FF00) >> 8));    // first byte of z, containing bits 16 to 9
    Wire.write((byte)(z & 0x000000FF));           // second byte of z, containing the 8 LSB - bits 8 to 1


    Wire.endTransmission();   // stop transmitting
    //delay(100); // delay between loops
  }
}
