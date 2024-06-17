#include "VoltageDivider.h"

VoltageDivider::VoltageDivider(int sensorPin, float conversionFactor, float referenceVoltage)
    : _sensorPin(sensorPin), _conversionFactor(conversionFactor), _referenceVoltage(referenceVoltage) {}

void VoltageDivider::begin()
{
    pinMode(_sensorPin, INPUT);
}

float VoltageDivider::readVoltage()
{
    _sensorValue = analogRead(_sensorPin);
    _vOut = (_sensorValue / 4095.0) * _referenceVoltage;
    return _vOut * _conversionFactor;
}
