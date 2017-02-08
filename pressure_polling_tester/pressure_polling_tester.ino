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
#define MPL3115A2 0x60

// Variable Declarations
byte sta = 0x00;
byte ctrl = 0x00;
byte msb=0x00, csb=0x00, lsb=0x00;

void setup() {
  Wire.begin();
  Serial.begin(57600);

  if(IIC_Read(WHO_AM_I) == 196) 
    Serial.println("Pressure sensor online!");
  else
    Serial.println("No response - check connections");

  IIC_Write(CTRL_REG_1,0x00); // 0x00: Standby, 1x Oversample, Barometer Mode
  IIC_Write(CTRL_REG_2,0x0F); // Set the sampling frequency to once every 2^15 sec
  IIC_Write(PT_DATA_CFG,0x02); // Generate event flags for new pressure data ONLY

}

void loop() {
  sta = IIC_Read(STATUS);
  if (sta & 0x04) {
    IIC_Write(CTRL_REG_1,0x02); // 0x02: Standby, OST, 1x Oversample, Barometer
    msb = IIC_Read(OUT_P_MSB);
    csb = IIC_Read(OUT_P_CSB);
    lsb = IIC_Read(OUT_P_LSB);
    Serial.print(pressure(msb,csb,lsb));
    Serial.println("\n\n-------------------------------------------------\n");
  }

  ctrl = IIC_Read(CTRL_REG_1);
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
  Wire.beginTransmission(MPL3115A2);
  Wire.write(address);
  Wire.endTransmission(false); // Send data to I2C dev with option for a repeated start. THIS IS NECESSARY and not supported before Arduino V1.0.1!
  Wire.requestFrom(MPL3115A2,1); // Request the data...
  return Wire.read();
}

void IIC_Write(byte address, byte data)
{
  Wire.beginTransmission(MPL3115A2);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission(true);
}
