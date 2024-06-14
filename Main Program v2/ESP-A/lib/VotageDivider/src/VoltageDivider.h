#ifndef VOLTAGEDIVIDER_H
#define VOLTAGEDIVIDER_H

#include <Arduino.h>

class VoltageDivider
{
public:
    // Constructor
    VoltageDivider(int pin);

    // Initialization method
    void begin(float R1 = 220000.0, float R2 = 10000.0);

    // Method to set voltage division factor manually
    void setDivisionFactor(float factor);

    // Method to read the input voltage
    float readVoltage();

    // Method to get the percentage based on min and max voltage
    float getPercentage(float minVoltage, float maxVoltage);

private:
    int _pin;
    float _R1;
    float _R2;
    float _divisionFactor;
    bool _customDivisionFactor;

    // Helper method to calculate the division factor
    float calculateDivisionFactor();
};

#endif // VOLTAGEDIVIDER_H
