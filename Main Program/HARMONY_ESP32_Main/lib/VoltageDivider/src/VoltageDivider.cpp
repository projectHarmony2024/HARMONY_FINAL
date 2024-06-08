#include "VoltageDivider.h"

// Constructor implementation
VoltageDivider::VoltageDivider(uint8_t pin, float R1, float R2, int adcResolution, float vRef)
    : _pin(pin), _R1(R1), _R2(R2), _adcResolution(adcResolution), _vRef(vRef), _minVoltage(0), _maxVoltage(vRef)
{
}

// Method to read raw ADC value
int VoltageDivider::readRaw()
{
    return analogRead(_pin);
}

// Method to read the voltage
float VoltageDivider::readVoltage()
{
    int rawValue = readRaw();
    float voltage = (rawValue / (float)_adcResolution) * _vRef;
    float actualVoltage = voltage * ((_R1 + _R2) / _R2);
    return actualVoltage;
}

// Method to set battery voltage range
void VoltageDivider::setBatteryVoltageRange(float minVoltage, float maxVoltage)
{
    _minVoltage = minVoltage;
    _maxVoltage = maxVoltage;
}

// Method to read battery percentage
float VoltageDivider::readBatteryPercentage()
{
    float voltage = readVoltage();
    if (voltage <= _minVoltage)
    {
        return 0.0;
    }
    if (voltage >= _maxVoltage)
    {
        return 100.0;
    }
    return ((voltage - _minVoltage) / (_maxVoltage - _minVoltage)) * 100.0;
}
