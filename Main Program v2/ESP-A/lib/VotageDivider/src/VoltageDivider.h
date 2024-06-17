#ifndef VOLTAGE_DIVIDER_H
#define VOLTAGE_DIVIDER_H

#include <Arduino.h>

class VoltageDivider
{
public:
    VoltageDivider(int sensorPin, float conversionFactor, float referenceVoltage);
    void begin();
    float readVoltage();

private:
    int _sensorPin;
    float _conversionFactor;
    float _referenceVoltage;
    float _sensorValue;
    float _vOut;
};

#endif
