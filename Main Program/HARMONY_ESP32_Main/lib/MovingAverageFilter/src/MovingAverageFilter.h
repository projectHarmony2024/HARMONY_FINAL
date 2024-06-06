#ifndef MOVING_AVERAGE_FILTER_H
#define MOVING_AVERAGE_FILTER_H

#include <Arduino.h>

class MovingAverageFilter
{
public:
    // Constructor
    MovingAverageFilter(int size, int numChannels);

    // Destructor
    ~MovingAverageFilter();

    // Method to add a new reading for a specific channel
    void addReading(float newReading, int channel);

    // Method to get the current average for a specific channel
    float getAverage(int channel) const;

private:
    float **readings; // 2D array to store readings for multiple channels
    int size;         // Size of the array
    int numChannels;  // Number of channels
    int *index;       // Current index in the array for each channel
    int *count;       // Number of readings added for each channel
    float *sum;       // Sum of the readings for each channel
};

#endif // MOVING_AVERAGE_FILTER_H
