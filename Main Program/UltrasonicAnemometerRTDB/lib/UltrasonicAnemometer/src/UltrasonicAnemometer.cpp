#include "UltrasonicAnemometer.h"

const byte defaultAnemometerRequest[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

UltrasonicAnemometer::UltrasonicAnemometer(byte roPin, byte diPin, byte dePin, byte rePin, byte max485Pin, long baudRate)
    : roPin(roPin), diPin(diPin), dePin(dePin), rePin(rePin), max485Pin(max485Pin), baudRate(baudRate),
      anemometerRequest(defaultAnemometerRequest), windSpeed_ms(0), windSpeed_kph(0), windDirectionDegrees(0),
      offsetDirection(0), dataReceived(false)
{
    ultrasonicAnemometer = new SoftwareSerial(roPin, diPin, false);
}

void UltrasonicAnemometer::begin()
{
    pinMode(max485Pin, OUTPUT);
    pinMode(rePin, OUTPUT);
    pinMode(dePin, OUTPUT);
    digitalWrite(max485Pin, HIGH);
    ultrasonicAnemometer->begin(baudRate);
}

void UltrasonicAnemometer::setOffsetDirection(float offset)
{
    offsetDirection = offset;
}

void UltrasonicAnemometer::update()
{
    dataReceived = false;
    sendAnemometerRequest();
    if (receiveAnemometerData())
    {
        parseAnemometerData();
    }
}

float UltrasonicAnemometer::getWindSpeed_ms()
{
    return windSpeed_ms;
}

float UltrasonicAnemometer::getWindSpeed_kph()
{
    return windSpeed_kph;
}

float UltrasonicAnemometer::getWindDirectionDegrees()
{
    return windDirectionDegrees;
}

String UltrasonicAnemometer::getCompassDirection()
{
    return calculateCompassDirection(windDirectionDegrees);
}

void UltrasonicAnemometer::sendAnemometerRequest()
{
    digitalWrite(dePin, HIGH);
    digitalWrite(rePin, HIGH);
    delay(10);
    ultrasonicAnemometer->write(anemometerRequest, sizeof(defaultAnemometerRequest));
    digitalWrite(dePin, LOW);
    digitalWrite(rePin, LOW);
}

bool UltrasonicAnemometer::receiveAnemometerData()
{
    unsigned long startTime = millis();
    while (ultrasonicAnemometer->available() < 9 && millis() - startTime < 1000)
    {
        if (millis() - startTime >= 1000)
        {
            return false;
        }
    }

    if (ultrasonicAnemometer->available() >= 9)
    {
        for (int i = 0; i < 9; i++)
        {
            values[i] = ultrasonicAnemometer->read();
        }
        dataReceived = true;
        return true;
    }
    else
    {
        return false;
    }
}

void UltrasonicAnemometer::parseAnemometerData()
{
    // Parse Wind Speed
    int windSpeedInt = int(values[3] << 8 | values[4]);
    windSpeed_ms = windSpeedInt / 100.0;
    windSpeed_kph = windSpeed_ms * 3.6;

    // Parse Wind Direction
    int windDirectionInt = int(values[5] << 8 | values[6]);
    windDirectionDegrees = (windSpeed_ms == 0) ? 0 : windDirectionInt;

    // Adjust wind direction by the offset
    windDirectionDegrees += offsetDirection;
    if (windDirectionDegrees >= 360)
    {
        windDirectionDegrees -= 360;
    }
    else if (windDirectionDegrees < 0)
    {
        windDirectionDegrees += 360;
    }
}

String UltrasonicAnemometer::calculateCompassDirection(float degrees)
{
    if (degrees >= 337.5 || degrees < 22.5)
        return "N";
    else if (degrees >= 22.5 && degrees < 67.5)
        return "NE";
    else if (degrees >= 67.5 && degrees < 112.5)
        return "E";
    else if (degrees >= 112.5 && degrees < 157.5)
        return "SE";
    else if (degrees >= 157.5 && degrees < 202.5)
        return "S";
    else if (degrees >= 202.5 && degrees < 247.5)
        return "SW";
    else if (degrees >= 247.5 && degrees < 292.5)
        return "W";
    else
        return "NW";
}
