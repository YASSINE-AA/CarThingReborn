#include "volume_control.hpp"
#include <Arduino.h>

PMVolumeControl::PMVolumeControl(uint8_t vccPin, uint8_t outPin, uint16_t maxValue)
    : vccPin(vccPin), outPin(outPin), maxValue(maxValue), previousVolumeValue(0) {}

void PMVolumeControl::init()
{
    pinMode(vccPin, OUTPUT);
    digitalWrite(vccPin, HIGH);
    volumeChanged = false;
}

uint8_t PMVolumeControl::getVolumePercentage()
{
    uint16_t value = smoothAnalogRead();
    return (uint8_t)roundf(((float)value / maxValue) * 100);
}

bool PMVolumeControl::isVolumeChanged() const
{
    return volumeChanged;
}
uint16_t PMVolumeControl::smoothAnalogRead()
{
    const uint8_t numSamples = 5;         // Number of samples for smoothing
    const uint8_t pmTolerance = 8;
    static uint16_t readings[numSamples]; // Circular buffer
    static bool initialized = false;
    static uint8_t index = 0;
    static uint16_t sum = 0; // Sum of last `numSamples` readings
    

    if (!initialized)
    {
        uint16_t initialValue = analogRead(outPin);
        for (uint8_t i = 0; i < numSamples; i++)
        {
            readings[i] = initialValue;
            sum += initialValue;
        }
        previousVolumeValue = initialValue;
        initialized = true;
    }

    uint16_t rawValue = analogRead(outPin);

    sum -= readings[index];

    readings[index] = rawValue;

    sum += rawValue;

    index = (index + 1) % numSamples;

    uint16_t smoothedValue = sum / numSamples;

    if (abs((int)smoothedValue - (int)previousVolumeValue) > pmTolerance)
    {
        volumeChanged = true;
    }
    else
    {
        volumeChanged = false;
    }

    previousVolumeValue = smoothedValue;
    return smoothedValue;
}
