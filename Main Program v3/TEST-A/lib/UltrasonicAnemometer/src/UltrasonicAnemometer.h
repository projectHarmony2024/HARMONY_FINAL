#ifndef ULTRASONIC_ANEMOMETER_H
#define ULTRASONIC_ANEMOMETER_H

#include <Arduino.h>
#include <SoftwareSerial.h>

class UltrasonicAnemometer {
public:
    UltrasonicAnemometer(uint8_t diPin, uint8_t dePin, uint8_t rePin, uint8_t roPin);
    void begin();
    void update();
    float getWindSpeed_ms();
    float getWindSpeed_kph();
    void setWindDirectionOffset(int offset);
    int getWindDirection();

private:
    SoftwareSerial ultrasonicAnemometer;
    uint8_t roPin;
    uint8_t diPin;
    uint8_t dePin;
    uint8_t rePin;
    const byte anemometer[8] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B };
    byte values[9];
    int windDirectionOffset;
    unsigned long lastUpdateTime;
    float totalWindSpeed_ms;
    float totalWindSpeed_kph;
    int totalWindDirection;

    void transmitRequest();
};

#endif
