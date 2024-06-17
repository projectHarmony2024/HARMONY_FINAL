#include "VoltageDivider.h"

VoltageDivider::VoltageDivider(int pin, float R1, float R2, float offset, float vcc)
    : _pin(pin), _R1(R1), _R2(R2), _offset(offset), _vcc(vcc)
{
    _factor = (_R1 / _R2) + _offset;
}

void VoltageDivider::begin()
{
    pinMode(_pin, INPUT);
}

float VoltageDivider::readVoltage()
{
    float voltageSensorVal = analogRead(_pin);
    float vOut = (voltageSensorVal / 4095.0) * _vcc;
    float vIn = vOut * _factor;
    return vIn;
}

float VoltageDivider::readPercentage(float minVoltage, float maxVoltage)
{
    float voltage = readVoltage();
    if (voltage <= minVoltage)
    {
        return 0.0;
    }
    else if (voltage >= maxVoltage)
    {
        return 100.0;
    }
    else
    {
        return ((voltage - minVoltage) / (maxVoltage - minVoltage)) * 100.0;
    }
}
