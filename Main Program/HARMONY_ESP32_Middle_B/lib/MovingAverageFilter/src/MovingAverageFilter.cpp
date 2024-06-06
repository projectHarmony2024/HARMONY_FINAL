#include "MovingAverageFilter.h"

// Constructor
MovingAverageFilter::MovingAverageFilter(int size, int numChannels) : size(size), numChannels(numChannels)
{
    readings = new float *[numChannels];
    index = new int[numChannels];
    count = new int[numChannels];
    sum = new float[numChannels];

    for (int i = 0; i < numChannels; i++)
    {
        readings[i] = new float[size];
        index[i] = 0;
        count[i] = 0;
        sum[i] = 0.0;
        for (int j = 0; j < size; j++)
        {
            readings[i][j] = 0.0;
        }
    }
}

// Destructor
MovingAverageFilter::~MovingAverageFilter()
{
    for (int i = 0; i < numChannels; i++)
    {
        delete[] readings[i];
    }
    delete[] readings;
    delete[] index;
    delete[] count;
    delete[] sum;
}

// Method to add a new reading for a specific channel
void MovingAverageFilter::addReading(float newReading, int channel)
{
    if (channel < 0 || channel >= numChannels)
    {
        return; // Invalid channel
    }
    // Subtract the oldest reading from the sum
    sum[channel] -= readings[channel][index[channel]];
    // Replace the oldest reading with the new one
    readings[channel][index[channel]] = newReading;
    // Add the new reading to the sum
    sum[channel] += newReading;
    // Move to the next index
    index[channel] = (index[channel] + 1) % size;
    // Increment count until it reaches the size
    if (count[channel] < size)
    {
        count[channel]++;
    }
}

// Method to get the current average for a specific channel
float MovingAverageFilter::getAverage(int channel) const
{
    if (channel < 0 || channel >= numChannels || count[channel] == 0)
    {
        return 0.0; // Invalid channel or no readings
    }
    return sum[channel] / count[channel];
}
