// Libraries included in the sketch
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "RTClib.h"

// Define power and chip select pins
const int CS_pin = 10;
const int POWER_pin = 8;

int refresh_rate = 5000;          // default refresh rate 5 sec
RTC_DS1307 RTC;                  // define an RTC object
String years, months, days, hours, minutes, seconds, date, time;            // initialize strings

void setup() {
  
  // Initialize chip select and power pin modes
  pinMode(CS_pin, OUTPUT);
  pinMode(POWER_pin,OUTPUT);
  digitalWrite(POWER_pin,HIGH);
  
  // Begin serial communications
  Serial.begin(9600);
  while(!Serial);
  
  // Initialize card for write
  Serial.println(F("Initializing Card..."));
  if (!SD.begin(CS_pin))
  {
    Serial.println(F("Card not found. Please insert card."));
    while (!SD.begin(CS_pin));
  }
  Serial.println(F("Card Ready"));
  
  // Initiate the I2C bus and the RTC library
  Wire.begin();
  RTC.begin();
  
  // Set RTC if not already running
  if (! RTC.isrunning())
  {
    Serial.println(F("RTC is not running."));
    RTC.adjust(DateTime(__DATE__,__TIME__));
  }
  
  // Column Headers for each new logging instance
  File dataFile = SD.open("log.csv", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(F("\nNew Log Started."));
    dataFile.println(F("Date,Time,Phrase"));
    dataFile.close();                  // data is written upon close of file
    
    // For debugging purposes
    Serial.println(F("\nNew Log Started."));
    Serial.println(F("Date,Time,Phrase"));
  }
  else
  {
    Serial.println(F("Couldn't open the log file..."));
  }

}

void loop() {
  
  // Store current date and time info in strings
  DateTime datetime = RTC.now();
  years = String(datetime.year(), DEC);
  months = String(datetime.month(), DEC);
  days = String(datetime.day(), DEC);
  hours = String(datetime.hour(), DEC);
  minutes = String(datetime.minute(), DEC);
  seconds = String(datetime.second(), DEC);
  
  // Concatenation
  date = years + "/" + months + "/" + days;
  time = hours + ":" + minutes + ":" + seconds;
  
  String dataString = "chicky";            // data string to print
  
  // Create/Open a file and write to it
  File dataFile = SD.open("log.csv",FILE_WRITE);
  if (dataFile)
  {
    dataFile.print(date);
    dataFile.print(F(","));
    dataFile.print(time);
    dataFile.print(F(","));
    dataFile.println(dataString);
    dataFile.close();            // Data written after file is closed
    
    Serial.print(date);          // Serial printout for debugging
    Serial.print(F(","));
    Serial.print(time);
    Serial.print(F(","));
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open the log file...");
  }
  
  delay(refresh_rate);          // delay refresh rate length

}
  
  
