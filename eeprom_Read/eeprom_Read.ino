#include <Wire.h>

const byte chip = B1010000; // 24LC512 I2C Address
unsigned int address = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  Serial.println("----------------------------------------");
  Serial.println("");
}

void loop() {
  Serial.print("Reading from Address Number: ");
  Serial.print(address);
  Serial.println("/65535");
  
  byte numRead = readData(chip,address);
  //Serial.print("Integer read, in DEC: ");
  //Serial.println(numRead,BIN);
  Serial.print("Integer read, in BIN: ");
  Serial.println(numRead,BIN);

  Serial.println("");
  Serial.println("----------------------------------------");
  Serial.println("");

  if (readData(chip,address)) ++address;
  
  delay(1000);
}

void writeData(byte deviceAddress, unsigned int memoryAddress, byte data) {
  Wire.beginTransmission(deviceAddress);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.write(data);
  Wire.endTransmission();
  delay(5);
}

byte readData(byte deviceAddress, unsigned int memoryAddress) {
  byte data = 0x00;
  
  Wire.beginTransmission(deviceAddress);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(deviceAddress,1);
  if (Wire.available()) data = Wire.read();

  return data;
}
