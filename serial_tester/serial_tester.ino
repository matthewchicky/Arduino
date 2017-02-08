unsigned int memoryAddress = 20000;

void setup() {
  // open the serial port at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  Serial.println(memoryAddress, BIN);
  Serial.println(memoryAddress >> 8, BIN);
  Serial.println((memoryAddress & 0xFF),BIN);

  delay(5000);
}
