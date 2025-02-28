#include "power_button.hpp"
#include <Arduino.h>

PowerButton::PowerButton() : PB_PIN(19) {}

void PowerButton::init()
{
    pinMode(PB_PIN, INPUT);
}

bool PowerButton::getState()
{
    Serial.println(digitalRead(PB_PIN));
    return false;
}