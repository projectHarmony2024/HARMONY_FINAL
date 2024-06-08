#ifndef ULTRASONICANEMOMETER_H
#define ULTRASONICANEMOMETER_H

#include <SoftwareSerial.h>
#include <cmath> // For NAN constant

class UltrasonicAnemometer
{
public:
    UltrasonicAnemometer(int roPin, int diPin, int dePin, int rePin, int max485VCC_Pin);

    void begin();
    int readData(); // Return type: Integer (1/nan)

    float getWindSpeed_ms() const;
    float getWindSpeed_kph() const;
    int getWind_Direction() const;

    void setDirectionOffset(int offset);

private:
    int roPin, diPin, dePin, rePin, max485VCC_Pin;
    byte values[9];
    SoftwareSerial ultrasonicAnemometer;
    float windSpeedMs;
    int windDirection;
    int directionOffset;

    void synchronize();
    void transmitRequest();
    bool receiveResponse();
    void parseData();
    void parseWindSpeed();
    void parseWindDirection();
};

#endif // ULTRASONICANEMOMETER_H
