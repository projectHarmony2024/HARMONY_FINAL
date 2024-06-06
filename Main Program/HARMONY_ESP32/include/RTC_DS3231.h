// Date and time functions using a DS3231 RTC connected via I2C and Wire lib
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
const char* monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const int timeZoneOffset = 8; // Time zone offset in hours, adjust as needed

void init_RTC () {
  delay(1000);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (1) delay(10);
  }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}

String RTCcurrentDateTime(){
  DateTime now = rtc.now();
  now = now + TimeSpan(0, 0, 0, 36);

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
  dateTime += day + "T";

  String hour = String(now.hour());
  if (hour.length() == 1) {
    hour = "0" + hour;
  }
  dateTime += hour + ":";

  String minute = String(now.minute());
  if (minute.length() == 1) {
    minute = "0" + minute;
  }
  dateTime += minute + ":";

  String second = String(now.second());
  if (second.length() == 1) {
    second = "0" + second;
  }
  dateTime += second;

  debugln(dateTime);

  return dateTime;
}

String RTCgetTimestamp(){
  DateTime now = rtc.now();
  now = now + TimeSpan(0, 0, 0, 36);

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
  dateTime += day + "T";

  String hour = String(now.hour());
  if (hour.length() == 1) {
    hour = "0" + hour;
  }
  dateTime += hour + ":";

  String minute = String(now.minute());
  if (minute.length() == 1) {
    minute = "0" + minute;
  }
  dateTime += minute + ":";

  String second = String(now.second());
  if (second.length() == 1) {
    second = "0" + second;
  }
  dateTime += second + "+08:00";

  debugln(dateTime);

  return dateTime;
}

