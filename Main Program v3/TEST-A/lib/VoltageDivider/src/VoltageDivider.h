#ifndef VOLTAGEDIVIDER_H
#define VOLTAGEDIVIDER_H

#include <Arduino.h>

class VoltageDivider
{
public:
    VoltageDivider(int pin, float R1, float R2, float offset, float vcc);
    void begin();
    float readVoltage();
    float readPercentage(float minVoltage, float maxVoltage);

private:
    int _pin;
    float _R1;
    float _R2;
    float _offset;
    float _vcc;
    float _factor;
};

#endif
