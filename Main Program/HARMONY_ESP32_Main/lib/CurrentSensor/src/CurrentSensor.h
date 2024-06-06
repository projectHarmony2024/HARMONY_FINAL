#ifndef CURRENTSENSOR_H
#define CURRENTSENSOR_H

#include <Arduino.h>
#include <ACS712.h>

class CurrentSensor
{
private:
    ACS712 acs;

public:
    // Constructor with calibration parameters
    CurrentSensor(byte pin, float voltage, int adcSteps, int mvPerAmp);

    ~CurrentSensor();

    // Separate setup function for ACS712 configuration
    void begin();

    // Function to read current in mA
    int readCurrent();
};

#endif
