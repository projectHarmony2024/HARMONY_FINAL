#include "UltrasonicAnemometer.h"

UltrasonicAnemometer::UltrasonicAnemometer(uint8_t diPin, uint8_t dePin, uint8_t rePin, uint8_t roPin)
    : ultrasonicAnemometer(roPin, diPin, false), diPin(diPin), dePin(dePin), rePin(rePin), roPin(roPin)
{
    totalWindSpeed_ms = 0;
    totalWindSpeed_kph = 0;
    totalWindDirection = 0;
    windDirectionOffset = 0;
    lastUpdateTime = 0;
}

void UltrasonicAnemometer::begin()
{
    ultrasonicAnemometer.begin(4800);
    pinMode(rePin, OUTPUT);
    pinMode(dePin, OUTPUT);
}

void UltrasonicAnemometer::update()
{
    // Synchronization loop: Wait until the start of a new data frame is detected
    while (ultrasonicAnemometer.available())
    {
        ultrasonicAnemometer.read(); // Clear any existing data
    }

    // Transmit the request to the sensor
    transmitRequest();

    // Wait until we have the expected number of bytes or timeout
    unsigned long startTime = millis();
    while (ultrasonicAnemometer.available() < 9 && millis() - startTime < 1000)
    {
        // Wait for data to be available
    }

    if (ultrasonicAnemometer.available() >= 9)
    {
        // Read the response
        for (int index = 0; index < 9; index++)
        {
            values[index] = ultrasonicAnemometer.read();
        }

        // Parse the Wind Speed value
        int windSpeedInt = int(values[3] << 8 | values[4]);
        float windSpeed_m_s = windSpeedInt / 100.0;
        totalWindSpeed_ms = windSpeed_m_s;
        totalWindSpeed_kph = windSpeed_m_s * 3.6; // Conversion to km/h

        // Parse the Wind Direction value
        int windDirection = int(values[5] << 8 | values[6]);
        if (windDirection == 0)
        {
            totalWindDirection = 0; // No wind detected
        }
        else
        {
            totalWindDirection = windDirection + windDirectionOffset;
            if (totalWindDirection >= 360)
            {
                totalWindDirection -= 360;
            }
            else if (totalWindDirection < 0)
            {
                totalWindDirection += 360;
            }
        }
    }
    else
    {
        // Sensor timeout or incomplete frame
        totalWindSpeed_ms = 0;
        totalWindSpeed_kph = 0;
        totalWindDirection = 0;
    }
}

float UltrasonicAnemometer::getWindSpeed_ms()
{
    return totalWindSpeed_ms;
}

float UltrasonicAnemometer::getWindSpeed_kph()
{
    return totalWindSpeed_kph;
}

void UltrasonicAnemometer::setWindDirectionOffset(int offset)
{
    windDirectionOffset = offset;
}

int UltrasonicAnemometer::getWindDirection()
{
    return totalWindDirection;
}

void UltrasonicAnemometer::transmitRequest()
{
    digitalWrite(dePin, HIGH);
    digitalWrite(rePin, HIGH);
    delay(10);

    ultrasonicAnemometer.write(anemometer, sizeof(anemometer));

    digitalWrite(dePin, LOW);
    digitalWrite(rePin, LOW);
    delay(10);
}
