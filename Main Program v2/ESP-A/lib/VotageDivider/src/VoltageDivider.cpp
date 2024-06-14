#include "VoltageDivider.h"

// Constructor implementation
VoltageDivider::VoltageDivider(int pin)
    : _pin(pin), _R1(220000.0), _R2(10000.0), _customDivisionFactor(false) {}

// Initialization method
void VoltageDivider::begin(float R1, float R2)
{
    _R1 = R1;
    _R2 = R2;
    pinMode(_pin, INPUT);
    _divisionFactor = calculateDivisionFactor();
}

// Method to set voltage division factor manually
void VoltageDivider::setDivisionFactor(float factor)
{
    _divisionFactor = factor;
    _customDivisionFactor = true;
}

// Method to read the input voltage
float VoltageDivider::readVoltage()
{
    int adcValue = analogRead(_pin);
    float referenceVoltage = 3.3; // ESP32 ADC reference voltage
    float pinVoltage = (adcValue / 4095.0) * referenceVoltage;
    return pinVoltage * _divisionFactor;
}

// Method to get the percentage based on min and max voltage
float VoltageDivider::getPercentage(float minVoltage, float maxVoltage)
{
    float inputVoltage = readVoltage();
    if (inputVoltage < minVoltage)
    {
        return 0.0;
    }
    else if (inputVoltage > maxVoltage)
    {
        return 100.0;
    }
    else
    {
        return ((inputVoltage - minVoltage) / (maxVoltage - minVoltage)) * 100.0;
    }
}

// Helper method to calculate the division factor
float VoltageDivider::calculateDivisionFactor()
{
    return (_R1 / _R2) + 1;
}
