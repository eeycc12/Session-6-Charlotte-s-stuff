#include <Wire.h>
#define I2C_SLAVE_ADDR 0x04

void setup(){
  Serial.begin(9600);
  Wire.begin();  // join i2c bus
}

void loop(){

Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4

int x=150;
int y=150;
int z=77;

Wire.write((byte)((x & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
Wire.write((byte)(x & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
Wire.write((byte)((y & 0x0000FF00) >> 8));    // first byte of y, containing bits 16 to 9
Wire.write((byte)(y & 0x000000FF));           // second byte of y, containing the 8 LSB - bits 8 to 1
Wire.write((byte)((z & 0x0000FF00) >> 8));    // first byte of z, containing bits 16 to 9
Wire.write((byte)(z & 0x000000FF));           // second byte of z, containing the 8 LSB - bits 8 to 1

Wire.endTransmission();   // stop transmitting

delay(275);

Wire.beginTransmission(I2C_SLAVE_ADDR); // transmit to device #4

x=0;
y=0;
z=77;

Wire.write((byte)((x & 0x0000FF00) >> 8));    // first byte of x, containing bits 16 to 9
Wire.write((byte)(x & 0x000000FF));           // second byte of x, containing the 8 LSB - bits 8 to 1
Wire.write((byte)((y & 0x0000FF00) >> 8));    // first byte of y, containing bits 16 to 9
Wire.write((byte)(y & 0x000000FF));           // second byte of y, containing the 8 LSB - bits 8 to 1
Wire.write((byte)((z & 0x0000FF00) >> 8));    // first byte of z, containing bits 16 to 9
Wire.write((byte)(z & 0x000000FF));           // second byte of z, containing the 8 LSB - bits 8 to 1

Wire.endTransmission();   // stop transmitting
delay(1000);
}