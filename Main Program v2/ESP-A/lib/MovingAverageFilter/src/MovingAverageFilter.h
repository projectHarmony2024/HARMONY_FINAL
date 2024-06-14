#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include <Arduino.h>

class MovingAverageFilter
{
public:
    // Constructor to initialize the filter with the number of samples
    MovingAverageFilter(uint8_t numSamples);

    // Destructor to clean up dynamically allocated memory
    ~MovingAverageFilter();

    // Add a new reading and get the filtered value
    float addReading(float newReading);

private:
    uint8_t _numSamples; // Number of samples in the moving average
    float *_readings;    // Array to hold the sensor readings (floats)
    uint8_t _readIndex;  // Current position in the array
    float _total;        // Total of all readings
};

#endif
