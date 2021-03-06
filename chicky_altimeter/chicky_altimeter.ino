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
byte sta = 0x00;
byte ctrl = 0x00;
byte msb=0x00, csb=0x00, lsb=0x00;
byte data1 = 0x00, data2 = 0x00;
unsigned int address = 0;
byte page[128] = {0};
short int iterator = 0;

void twobyte(byte msb, byte csb, byte lsb, byte *d1, byte *d2)  {
  long pressure_whole = (long)msb<<16 | (long)csb<<8 | (long)lsb; 
  pressure_whole >>= 6;                                           
  pressure_whole -= 88616;    // Apply compression factor         
  lsb &= B00110000;                                               
  lsb >>= 4;                                                      
  long prePackage = pressure_whole<<2 | (long)lsb;
  
  *d1 = prePackage>>8;
  *d2 = (prePackage & B11111111);
}

float pressure(byte msb, byte csb, byte lsb)
{
  long pressure_whole = (long)msb<<16 | (long)csb<<8 | (long)lsb;
  pressure_whole >>= 6;

  lsb &= B00110000;
  lsb >>= 4;
  float pressure_decimal = (float)lsb/4.0;
  float pressure = (float)pressure_whole + pressure_decimal;
  return(pressure);
}

byte IIC_Read(byte address)
{
  Wire.beginTransmission(MPL3115A2_ADDRESS);
  Wire.write(address);
  Wire.endTransmission(false);
  Wire.requestFrom(MPL3115A2_ADDRESS,1);
  return Wire.read();
}

void IIC_Write(byte address, byte data)
{
  Wire.beginTransmission(MPL3115A2_ADDRESS);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission(true);
}

void writeToEEPROM(unsigned int memoryAddress, byte data[], const byte length = 128) {
  Wire.beginTransmission(EEPROM_ADDRESS);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  for (int i = 0; i<length; ++i)  {
    Wire.write(data[i]);
    Serial.println(data[i],BIN);
  }
  Wire.endTransmission();
  delay(10);
}

byte readFromEEPROM(unsigned int memoryAddress) {
  byte data = 0x00;
  
  Wire.beginTransmission(EEPROM_ADDRESS);  // begin transmission with device
  Wire.write(memoryAddress >> 8);
  Wire.write(memoryAddress & 0xFF);
  Wire.endTransmission();

  Wire.requestFrom(EEPROM_ADDRESS,1);
  if (Wire.available()) data = Wire.read();

  return data;
}

void setup() {
  Wire.begin();
  Serial.begin(57600);
  delay(5000);
  
  if(IIC_Read(WHO_AM_I) == 196) 
    Serial.println("Pressure sensor online!");
  else
    Serial.println("No response - check connections");

  IIC_Write(CTRL_REG_1,0x00); // 0x00: Standby, 1x Oversample, Barometer Mode
    if (IIC_Read(CTRL_REG_1)) Serial.println("Failure to set barometer mode, 1x oversample");
  IIC_Write(CTRL_REG_2,0x0F); // Set the sampling frequency to once every 2^15 sec (0x0F)
                              // Set the sampling frequency to once every second (0x00)
    if (IIC_Read(CTRL_REG_2) != 0x0F) Serial.println("Failure to set sampling frequency");
  IIC_Write(PT_DATA_CFG,0x02); // Generate event flags for new pressure data ONLY
    if (IIC_Read(PT_DATA_CFG) != 0x02) Serial.println("Failure to set event flags");
}

void loop() {
  sta = IIC_Read(STATUS);

  if (sta & 0x04){
    IIC_Write(CTRL_REG_1,0x02);             // 0x02: Standby, OST, 1x Oversample, Barometer
    msb = IIC_Read(OUT_P_MSB);
    csb = IIC_Read(OUT_P_CSB);
    lsb = IIC_Read(OUT_P_LSB);

    twobyte(msb,csb,lsb,&data1,&data2);
    byte timestep = millis();

    page[iterator] = timestep;
    Serial.println(timestep,DEC);
      if (iterator == 127)  {
        iterator = -1;
        writeToEEPROM(address,page);
        while (address == 65408);
        address += 128;
      }
    page[++iterator] = data1;
    Serial.println(data1,BIN);
      if (iterator == 127)  {
        iterator = -1;
        writeToEEPROM(address,page);
        while (address == 65408);
        address += 128;
      }
    page[++iterator] = data2;
    Serial.println(data2,BIN);
      if (iterator == 127)  {
        iterator = -1;
        writeToEEPROM(address,page);
        while (address == 65408);
        address += 128;
      }
    ++iterator;
  }

  ctrl = IIC_Read(CTRL_REG_1);
}
