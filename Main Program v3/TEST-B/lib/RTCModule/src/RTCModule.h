#ifndef RTCMODULE_H
#define RTCMODULE_H

#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>

class RTCModule
{
public:
    RTCModule(int timeZoneOffset = 0);
    void begin();
    String getCurrentDate();
    String getCurrentTime(bool amPmFormat = false);
    String getTimestamp();
    int getHour();

private:
    RTC_DS3231 rtc;
    int timeZoneOffset;
    String formatTwoDigits(int number);
};

#endif // RTCMODULE_H
