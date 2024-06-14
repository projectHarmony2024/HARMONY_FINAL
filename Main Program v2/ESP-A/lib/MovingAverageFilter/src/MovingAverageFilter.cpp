#include "MovingAverageFilter.h"

MovingAverageFilter::MovingAverageFilter(uint8_t numSamples)
{
    _numSamples = numSamples;
    _readings = new float[_numSamples]; // Dynamically allocate memory for readings
    _readIndex = 0;
    _total = 0.0;

    // Initialize all readings to 0
    for (uint8_t i = 0; i < _numSamples; i++)
    {
        _readings[i] = 0.0;
    }
}

MovingAverageFilter::~MovingAverageFilter()
{
    delete[] _readings; // Clean up dynamically allocated memory
}

float MovingAverageFilter::addReading(float newReading)
{
    // Subtract the last reading from the total
    _total = _total - _readings[_readIndex];

    // Add the new reading to the array and total
    _readings[_readIndex] = newReading;
    _total = _total + newReading;

    // Advance to the next position in the array
    _readIndex = _readIndex + 1;

    // If we're at the end of the array, wrap around to the beginning
    if (_readIndex >= _numSamples)
    {
        _readIndex = 0;
    }

    // Calculate and return the average
    return _total / _numSamples;
}
