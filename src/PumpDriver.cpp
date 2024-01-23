//
// Created by nils on 23.01.24.
//

#include "PumpDriver.h"

PumpDriver::PumpDriver()
{
    this->pin1 = -1;
    this->pin2 = -1;
}

PumpDriver::PumpDriver(const int pin1, const int pin2)
{
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    this->properInit = true;
}

void PumpDriver::stop() const
{
    if (properInit)
    {
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, LOW);
    }
}

void PumpDriver::forward() const
{
    if (properInit)
    {
        digitalWrite(this->pin1, HIGH);
        digitalWrite(this->pin2, LOW);
    }
}

void PumpDriver::backward() const
{
    if (properInit)
    {
        digitalWrite(this->pin1, LOW);
        digitalWrite(this->pin2, HIGH);
    }
}
