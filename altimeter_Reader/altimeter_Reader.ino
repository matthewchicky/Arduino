#include <SPI.h>
#include <SD.h>
#include <Wire.h>

const int chipSelect = 10;
const byte chip = B1010000; // 24LC512 I2C Address
unsigned int address = 0;
byte data = 0x00;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  Wire.begin();
}

void loop() {
  // make a string for assembling the data to log:
  String dataString = "";

  dataString += String(address);
  dataString += ",";
  data = readData(chip,address);
  dataString += String(data);
  ++address;
  dataString += ",";
  data = readData(chip,address);
  dataString += String(data);
  ++address;
  dataString += ",";
  data = readData(chip,address);
  dataString += String(data);
  ++address;

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("pressures.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    Serial.println(dataString);
  }
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
