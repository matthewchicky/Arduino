#include <Wire.h>

// Register/Address Definitions
#define STATUS 0x00
#define OUT_P_MSB 0x01
#define OUT_P_CSB 0x02
#define OUT_P_LSB 0x03
#define WHO_AM_I 0x0C
#define PT_DATA_CFG 0x13
#define CTRL_REG_1 0x26
#define CTRL_REG_2 0x27
#define MPL3115A2_ADDRESS 0x60
#define EEPROM_ADDRESS 0x50

// Variable Declarations
byte sta = 0x02;
byte ctrl = 0x00;
byte msb = 0x00, csb = 0x00, lsb = 0x00;
byte data1 = 0x00, data2 = 0x00;
unsigned int address = 0;
byte page[128] = {0};
short int iterator = 0;

void twobyte(byte msb, byte csb, byte lsb, byte *d1, byte *d2)  {
  long pressure_whole = (long)msb << 16 | (long)csb << 8 | (long)lsb;
  pressure_whole >>= 6;
  pressure_whole -= 88616;    // Apply compression factor
  lsb &= B00110000;
  lsb >>= 4;
  long prePackage = pressure_whole << 2 | (long)lsb;

  *d1 = prePackage >> 8;
  *d2 = (prePackage & B11111111);
}

byte IIC_Read(byte address)
{
  Wire.beginTransmission(MPL3115A2_ADDRESS);
  Wire.write(address);
  Wire.endTransmission(false);
  Wire.requestFrom(MPL3115A2_ADDRESS, 1);
  return Wire.read();
}

void IIC_Write(byte address, byte data)
{
  Wire.beginTransmission(MPL3115A2_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission(true);
}

void renewTransmission(short int *piterator, unsigned int *paddress)  {
  Wire.endTransmission();
  delay(5);

  Serial.print("Page written to addresses ");
  Serial.print(*paddress);
  Serial.print(" to ");
  Serial.println(*paddress + 128);

  *piterator = 0;
  *paddress += 128;

  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(*paddress >> 8);
  Wire.write(*paddress & 0xFF);
}

byte readFromEEPROM(unsigned int memoryAddress) {
  byte data = 0x00;

  Wire.beginTransmission(EEPROM_ADDRESS);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDRESS, 1);
  if (Wire.available()) data = Wire.read();

  return data;
}

void setup() {
  Wire.begin();
  Serial.begin(57600);
  delay(5000);

  if (IIC_Read(WHO_AM_I) == 196)
    Serial.println("Pressure sensor online!");
  else
    Serial.println("No response - check connections");

  IIC_Write(CTRL_REG_1, 0x00); // 0x00: Standby, 1x Oversample, Barometer Mode
  if (IIC_Read(CTRL_REG_1)) Serial.println("Failure to set barometer mode, 1x oversample");
  IIC_Write(CTRL_REG_2, 0x0F); // Set the sampling frequency to once every 2^15 sec (0x0F)
  // Set the sampling frequency to once every second (0x00)
  if (IIC_Read(CTRL_REG_2) != 0x0F) Serial.println("Failure to set sampling frequency");
  IIC_Write(PT_DATA_CFG, 0x02); // Generate event flags for new pressure data ONLY
  if (IIC_Read(PT_DATA_CFG) != 0x02) Serial.println("Failure to set event flags");

  Wire.beginTransmission(EEPROM_ADDRESS);
  Wire.write(address >> 8);
  Wire.write(address & 0xFF);
}

void loop() {   // 65408    // 2 min, 27.91 sec for full EEPROM

  while (iterator < 128) {
    sta = IIC_Read(STATUS);
    if (sta == 0x00) {
      IIC_Write(CTRL_REG_1, 0x02);
      msb = IIC_Read(OUT_P_MSB);
      csb = IIC_Read(OUT_P_CSB);
      lsb = IIC_Read(OUT_P_LSB);
    }
    else if (sta & 0x04) {
      IIC_Write(CTRL_REG_1, 0x02);            // 0x02: Standby, OST, 1x Oversample, Barometer
      msb = IIC_Read(OUT_P_MSB);
      csb = IIC_Read(OUT_P_CSB);
      lsb = IIC_Read(OUT_P_LSB);
      ctrl = IIC_Read(CTRL_REG_1);

      twobyte(msb, csb, lsb, &data1, &data2);
      byte timestep = millis();

      Wire.write(timestep);
      Serial.print("Time: ");
      Serial.print(timestep, DEC);
      Serial.print("      Data: ");
      ++iterator;
      if (iterator > 127) renewTransmission(&iterator, &address);
      Wire.write(data1);
      Serial.print(data1,BIN);
      Serial.print(" ");
      ++iterator;
      if (iterator > 127) renewTransmission(&iterator, &address);
      Wire.write(data2);
      Serial.println(data2,BIN);
      ++iterator;
    }
  }

  renewTransmission(&iterator, &address);
  while (address == 65280)  {
    for (unsigned int j = 0; j < 65536; j+=3) {
      Serial.print("EEPROM Data:      ");
      Serial.print(readFromEEPROM(j), DEC);
      Serial.print(",");
      Serial.print(readFromEEPROM(j+1),BIN);
      Serial.print(",");
      Serial.println(readFromEEPROM(j+2),BIN);
    }
  }
}
