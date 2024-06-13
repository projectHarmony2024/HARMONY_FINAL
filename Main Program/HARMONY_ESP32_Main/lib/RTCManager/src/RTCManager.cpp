#include "RTCManager.h"

RTCManager::RTCManager() : timeZoneOffset(0) {}

void RTCManager::init()
{
    delay(1000);
    if (!rtc.begin())
    {
        while (1)
            delay(10);
    }
    if (rtc.lostPower())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

void RTCManager::setTimezoneOffset(int offset)
{
    timeZoneOffset = offset;
}

String RTCManager::getTime(String format)
{
    DateTime now = rtc.now() + TimeSpan(0, timeZoneOffset, 0, 0);
    return formatTime(now, format);
}

// FOR GETTING TIME AS INT
int RTCManager::getTimeInt(int offset)
{
    DateTime now = rtc.now();
    int adjustedHour = (now.hour() + offset) % 24;
    int currentTime = adjustedHour * 100 + now.minute();
    return currentTime;
}

String RTCManager::getDate(String format)
{
    DateTime now = rtc.now() + TimeSpan(0, timeZoneOffset, 0, 0);
    return formatDate(now, format);
}

String RTCManager::getDateTime()
{
    DateTime now = rtc.now() + TimeSpan(0, timeZoneOffset, 0, 0);
    return formatDate(now, "YYYY:DD:MM") + "T" + formatTime(now, "HH:MM");
}

String RTCManager::getTimestamp()
{
    DateTime now = rtc.now() + TimeSpan(0, timeZoneOffset, 0, 0);
    return formatDate(now, "YYYY:DD:MM") + "T" + formatTime(now, "HH:MM") + formatTimeZoneOffset();
}

String RTCManager::formatTime(DateTime now, String format)
{
    String hour = String(now.hour());
    String minute = String(now.minute());
    if (format == "HH:MMp")
    {
        bool isPM = now.hour() >= 12;
        int hour12 = now.hour() % 12;
        if (hour12 == 0)
            hour12 = 12;
        hour = String(hour12);
        if (hour.length() == 1)
            hour = "0" + hour;
        minute = String(now.minute());
        if (minute.length() == 1)
            minute = "0" + minute;
        return hour + ":" + minute + (isPM ? "PM" : "AM");
    }
    if (hour.length() == 1)
        hour = "0" + hour;
    if (minute.length() == 1)
        minute = "0" + minute;
    return hour + ":" + minute;
}

String RTCManager::formatDate(DateTime now, String format)
{
    String day = String(now.day());
    String month = String(now.month());
    String year = String(now.year());
    if (day.length() == 1)
        day = "0" + day;
    if (month.length() == 1)
        month = "0" + month;
    if (format == "DD:MM:YYYY")
    {
        return day + ":" + month + ":" + year;
    }
    else if (format == "MM:DD:YYYY")
    {
        return month + ":" + day + ":" + year;
    }
    else if (format == "YYYY:MM:DD")
    {
        return year + ":" + month + ":" + day;
    }
    else if (format == "YYYY:DD:MM")
    {
        return year + ":" + day + ":" + month;
    }
    return "";
}

String RTCManager::formatTimeZoneOffset()
{
    int hours = timeZoneOffset;
    int minutes = (timeZoneOffset - hours) * 60;
    char buffer[7];
    snprintf(buffer, sizeof(buffer), "%+03d:%02d", hours, abs(minutes));
    return String(buffer);
}
