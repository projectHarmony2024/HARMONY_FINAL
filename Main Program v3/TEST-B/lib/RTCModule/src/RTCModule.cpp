#include "RTCModule.h"

RTCModule::RTCModule(int timeZoneOffset) : timeZoneOffset(timeZoneOffset) {}

void RTCModule::begin()
{
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

String RTCModule::getCurrentDate()
{
    DateTime now = rtc.now();
    now = now + TimeSpan(0, 1, 12, 34);

    String date = String(now.year()) + "-" +
                  formatTwoDigits(now.month()) + "-" +
                  formatTwoDigits(now.day());

    return date;
}

String RTCModule::getCurrentTime(bool amPmFormat)
{
    DateTime now = rtc.now();
    now = now + TimeSpan(0, 1, 12, 34);

    int hour = now.hour();
    String period = "";
    if (amPmFormat)
    {
        period = (hour >= 12) ? " PM" : " AM";
        hour = hour % 12;
        if (hour == 0)
            hour = 12; // Handle midnight and noon
    }

    String time = formatTwoDigits(hour) + ":" +
                  formatTwoDigits(now.minute()) + ":" +
                  formatTwoDigits(now.second());

    if (amPmFormat)
    {
        time += period;
    }

    return time;
}

String RTCModule::getTimestamp()
{
    DateTime now = rtc.now();
    now = now + TimeSpan(0, 1, 12, 34);

    String timestamp = String(now.year()) + "-" +
                       formatTwoDigits(now.month()) + "-" +
                       formatTwoDigits(now.day()) + "T" +
                       formatTwoDigits(now.hour()) + ":" +
                       formatTwoDigits(now.minute()) + ":" +
                       formatTwoDigits(now.second()) +
                       (timeZoneOffset >= 0 ? "+" : "") +
                       String(timeZoneOffset) + ":00";

    return timestamp;
}

int RTCModule::getHour()
{
    DateTime now = rtc.now();
    now = now + TimeSpan(0, 1, 12, 34);

    return now.hour();
}

String RTCModule::formatTwoDigits(int number)
{
    if (number < 10)
    {
        return "0" + String(number);
    }
    return String(number);
}
