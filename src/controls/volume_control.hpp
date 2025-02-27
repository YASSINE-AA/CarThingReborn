#ifndef VOLUME_CONTROL_HPP
#define VOLUME_CONTROL_HPP

#include <Arduino.h>

class PMVolumeControl
{
public:
    PMVolumeControl(uint8_t vccPin, uint8_t outPin, uint16_t maxValue);

    void init();
    uint8_t getVolumePercentage();
    bool isVolumeChanged() const;

private:
    uint8_t vccPin;
    uint8_t outPin;
    uint16_t maxValue;
    uint16_t step;
    uint16_t previousVolumeValue;
    bool volumeChanged;
    uint16_t readStableValue(uint8_t pin);
    uint16_t smoothAnalogRead();
};

#endif // VOLUME_CONTROL_HPP