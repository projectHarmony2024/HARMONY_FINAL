#ifndef VOLTAGE_DIVIDER_H
#define VOLTAGE_DIVIDER_H

#include <Arduino.h>

class VoltageDivider
{
public:
    // Constructor
    VoltageDivider(uint8_t pin, float R1, float R2, int adcResolution = 1023, float vRef = 5.0);

    // Method to read raw ADC value
    int readRaw();

    // Method to read the voltage
    float readVoltage();

    // Methods to set battery voltage range
    void setBatteryVoltageRange(float minVoltage, float maxVoltage);

    // Method to read battery percentage
    float readBatteryPercentage();

private:
    uint8_t _pin;
    float _R1;
    float _R2;
    int _adcResolution;
    float _vRef;
    float _minVoltage;
    float _maxVoltage;
};

#endif
