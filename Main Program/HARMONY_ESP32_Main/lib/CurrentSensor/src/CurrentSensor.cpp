#include "CurrentSensor.h"

// Constructor with calibration parameters
CurrentSensor::CurrentSensor(byte pin, float voltage, int adcSteps, int mvPerAmp)
    : acs(pin, voltage, adcSteps, mvPerAmp) {}

CurrentSensor::~CurrentSensor() {}

// Separate setup function for ACS712 configuration
void CurrentSensor::begin()
{
    acs.autoMidPoint();
}

// Function to read current in mA
int CurrentSensor::readCurrent()
{
    return acs.mA_DC();
}
