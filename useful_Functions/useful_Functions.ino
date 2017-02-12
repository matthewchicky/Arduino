// useful functions

float pressure(byte msb, byte csb, byte lsb)
{
  long pressure_whole = (long)msb << 16 | (long)csb << 8 | (long)lsb;
  pressure_whole >>= 6;

  lsb &= B00110000;
  lsb >>= 4;
  float pressure_decimal = (float)lsb / 4.0;
  float pressure = (float)pressure_whole + pressure_decimal;
  return (pressure);
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
