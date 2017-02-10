#include <Wire.h>

#define MPL3115A2 0x60

void setup() {
  Wire.begin();
  Serial.begin(9600);
  

}

void loop() {
  

}

void writeToEEPROM(unsigned int memoryAddress, byte data) {
  Wire.beginTransmission(B1010000);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

byte readFromEEPROM(unsigned int memoryAddress) {
  byte data = 0x00;
  Wire.beginTransmission(B1010000);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();
  Wire.requestFrom(B1010000,1);
  if (Wire.available()) data = Wire.read();
  return data;
}

byte readPSensor(byte registerAddress)
{
  Wire.beginTransmission(B11000000);
  Wire.write(registerAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(MPL3115A2, 1);
  return Wire.read();
}

void writePSensor(byte registerAddress, byte value)
{
  Wire.beginTransmission(B11000000);
  Wire.write(registerAddress);
  Wire.write(value);
  Wire.endTransmission(true);
}
