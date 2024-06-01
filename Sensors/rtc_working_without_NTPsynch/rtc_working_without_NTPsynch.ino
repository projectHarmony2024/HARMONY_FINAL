//   DS3231 RTC MODULE PINOUTS
//    VCC   =    5V
//    GND   =    GND
//    SDA   =    PIN 21 
//    SCL   =    PIN 22

#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char* monthNames[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
const int timeZoneOffset = 8;  // Time zone offset in hours

void setup() {
  delay(1000);

  Serial.begin(115200);
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

void loop() {
  DateTime now = rtc.now();

  // Adjust time for time zone offset
  // now = now + TimeSpan(0, timeZoneOffset, 0, 0);

  String dateTime = "";
  dateTime += String(now.year(), DEC) + "-";

  String month = String(now.month());
  if (month.length() == 1) {
    month = "0" + month;
  }
  dateTime += month + "-";

  String day = String(now.day());
  if (day.length() == 1) {
    day = "0" + day;
  }
  dateTime += day + "-";

  String hour = String(now.hour());
  if (hour.length() == 1) {
    hour = "0" + hour;
  }
  dateTime += hour;

  String minute = String(now.minute());
  if (minute.length() == 1) {
    minute = "0" + minute;
  }
  dateTime += minute;

  String second = String(now.second());
  if (second.length() == 1) {
    second = "0" + second;
  }
  dateTime += second;

  Serial.println(dateTime);
  delay(1000);
}