#ifndef ULTRASONICANEMOMETER_H
#define ULTRASONICANEMOMETER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class UltrasonicAnemometer
{
public:
    UltrasonicAnemometer(byte roPin, byte diPin, byte dePin, byte rePin, byte max485Pin, long baudRate = 4800);
    void begin();
    void setOffsetDirection(float offset);
    void update();
    float getWindSpeed_ms();
    float getWindSpeed_kph();
    float getWindDirectionDegrees();
    String getCompassDirection();

private:
    const byte *anemometerRequest;
    byte roPin;
    byte diPin;
    byte dePin;
    byte rePin;
    byte max485Pin;
    long baudRate;
    byte values[9];
    float windSpeed_ms;
    float windSpeed_kph;
    float windDirectionDegrees;
    float offsetDirection;
    bool dataReceived;
    SoftwareSerial *ultrasonicAnemometer;

    void sendAnemometerRequest();
    bool receiveAnemometerData();
    void parseAnemometerData();
    String calculateCompassDirection(float degrees);
};

#endif
