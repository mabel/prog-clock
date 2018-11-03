#define H1 12
#define H2 11
#define H3 10
#define H4 9
#define H5 8

#define M1 7
#define M2 6
#define M3 5
#define M4 A0
#define M5 A1
#define M6 A2

#define PAUSE 300


#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 RTC;

uint32_t minute_pins[] = {M1, M2, M3, M4, M5, M6};
uint32_t hour_pins[]   = {H1, H2, H3, H4, H5};

uint8_t hour_value;
uint8_t minute_value;

void setup () {
  //Serial.begin(9600);
  Wire.begin();
  RTC.begin();
  // Check to see if the RTC is keeping time.  If it is, load the time from your computer.
  if (! RTC.isrunning()) {
    //Serial.println("RTC is NOT running!");
    // This will reflect the time that your sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  for(int i = 0; i < 5; i++){
    pinMode(hour_pins[i], OUTPUT);
    digitalWrite(hour_pins[i], 1);
    delay(PAUSE);
  }
  for(int i = 0; i < 6; i++){
    pinMode(minute_pins[i], OUTPUT);
    digitalWrite(minute_pins[i], 1);
    delay(PAUSE);
  }
}
void loop () {
    DateTime now = RTC.now(); 
    hour_value = now.hour();   
    minute_value = now.minute();   
    for(int i = 0; i < 5; i++){
      bool state = bitRead(hour_value, i);
      digitalWrite(hour_pins[i], state);
    }
    for(int i = 0; i < 6; i++){
      bool state = bitRead(minute_value, i);
      digitalWrite(minute_pins[i], state);
    }
    delay(60000);
}
