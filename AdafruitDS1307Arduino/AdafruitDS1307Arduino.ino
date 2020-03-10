//**************************************************************************************************
// ArduinoUNOExample1
// This example demonstrates how to connect and use the Adafruit DS1307 RTC Breakout.
//
// REVISIONS
// 02/29/2020   Bob Mixon
// Initial module creation and testing.
//**************************************************************************************************

#include <Arduino.h>

// The Adafruit RTC library.
#include "RTClib.h"

// These are the boards this code has been tested with. Other boards will be added as time permits.
#if defined(ARDUINO_AVR_UNO)       
  #define BOARD_NAME "Arduino UNO"
#else
  #error "UNKNOWN BOARD"
#endif

// DS1307 RTC Breakout.
RTC_DS1307 rtc;
bool rtcRunning = false;
#define RTC_INITIALIZE true

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

//--------------------------------------------------------------------------------------------------
// setup
// Called and run only once.
//--------------------------------------------------------------------------------------------------
void setup()
{
  // Initialize the serial communications. This is for displaying status and RTC values only.
  while(!Serial);
  Serial.begin(57600);
  Serial.print(F("Board: "));
  Serial.println(BOARD_NAME);

  // Initialize the RTC.
  Serial.print(F("RTC  : "));
  if(!rtc.begin()){
    Serial.println(F("Couldn't find RTC"));
    return;
  }
  if(!rtc.isrunning())
  {
    Serial.println(F("RTC is not running"));
    return;
  }
  Serial.println(F("RTC is running!"));
  rtcRunning = true;
  
  // If this is the first time you are running this, the RTC requires initialization or it will not
  // operate correctly. The following line sets the RTC to the date & time this sketch was compiled.
  if(RTC_INITIALIZE)
  {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  // If you'd like to set the RTC with an explicit date & time...
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));

}

//--------------------------------------------------------------------------------------------------
// loop
// Called continuously..
//--------------------------------------------------------------------------------------------------
void loop()
{
  // We won't do anything if the RTC is not available or running.
  if(!rtcRunning)
  {
    Serial.println(F("RTC is not running"));
    delay(1000);
    return;
  }

  // Return the date and time as a DateTime object.
  DateTime curDateTime = rtc.now();

  // Disply the date and time on the serial terminal.
  serialPrintDateTime(curDateTime);

  delay(500);
}

//--------------------------------------------------------------------------------------------------
// serialPrintDateTime
// Prints the specified date and time to the serial terminal.
//--------------------------------------------------------------------------------------------------
void serialPrintDateTime(DateTime dt)
{
  Serial.print(dt.month(), DEC);
  Serial.print('/');
  Serial.print(dt.day(), DEC);
  Serial.print('/');
  Serial.print(dt.year(), DEC);
  Serial.print(" (");
  Serial.print(daysOfTheWeek[dt.dayOfTheWeek()]);
  Serial.print(") ");
  Serial.print(dt.hour(), DEC);
  Serial.print(':');
  Serial.print(dt.minute(), DEC);
  Serial.print(':');
  Serial.print(dt.second(), DEC);
  Serial.println();
}
