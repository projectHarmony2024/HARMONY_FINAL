#ifndef RTCMANAGER_H
#define RTCMANAGER_H

#include <Wire.h>
#include "RTClib.h"

class RTCManager
{
public:
    RTCManager();
    void init();
    void setTimezoneOffset(int offset);
    String getTime(String format = "HH:MM");
    String getDate(String format = "DD:MM:YYYY");
    String getDateTime();
    String getTimestamp();

private:
    RTC_DS3231 rtc;
    int timeZoneOffset;
    String formatTime(DateTime now, String format);
    String formatDate(DateTime now, String format);
    String formatTimeZoneOffset();
};

#endif
