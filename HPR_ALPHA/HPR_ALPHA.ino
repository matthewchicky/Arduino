#include <SPI.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <avr/sleep.h>

SoftwareSerial mySerial(3, 2);
Adafruit_GPS GPS(&mySerial);

#define GPSECHO  false
#define LOG_FIXONLY false
#define PMTK_SET_NMEA_OUTPUT_GGA "$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29"
#define PMTK_API_SET_FIX_CTL_10HZ "$PMTK300,100,0,0,0,0*2C"

boolean usingInterrupt = false;
void useInterrupt(boolean);

#define chipSelect 10

File logfile;

void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
  }
  char filename[15];
  strcpy(filename, "GPSLOG00.CSV");
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = '0' + i / 10;
    filename[7] = '0' + i % 10;
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if ( ! logfile ) {
    Serial.print("Couldnt create ");
    Serial.println(filename);
  }
  Serial.print("Writing to ");
  Serial.println(filename);

  GPS.begin(9600);

  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_GGA);
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_10HZ);
  GPS.sendCommand(PMTK_API_SET_FIX_CTL_10HZ);
  GPS.sendCommand(PGCMD_NOANTENNA);

  useInterrupt(true);
  Serial.println("Ready!");
}

SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;
#endif
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  }
  else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void loop() {
  if (! usingInterrupt) {
    char c = GPS.read();
    if (GPSECHO)
      if (c) Serial.print(c);
  }

  if (GPS.newNMEAreceived()) {
    char *stringptr = GPS.lastNMEA();
    if (!GPS.parse(stringptr))
      return;

    uint8_t stringsize = strlen(stringptr);
    logfile.write((uint8_t *)stringptr, stringsize);
    logfile.flush();
  }
}
