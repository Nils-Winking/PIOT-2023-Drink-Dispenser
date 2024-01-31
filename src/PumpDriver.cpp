//
// Created by nils on 23.01.24.
//

#include "PumpDriver.h"

#define PUMP_HIGH 100

PumpDriver::PumpDriver() {
    this->pin1 = -1;
    this->pin2 = -1;
}

PumpDriver::PumpDriver(const int pin1, const int pin2) {
    this->pin1 = pin1;
    this->pin2 = pin2;
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    this->properInit = true;
}

PumpDriver::PumpDriver(const int pin1) {
    this->pin1 = pin1;
    this->pin2 = -1;
    pinMode(pin1, OUTPUT);
    this->properInit = true;
}

void PumpDriver::stop() const {
    if (properInit) {
        analogWrite(this->pin1, LOW);
        if (this->pin2 >= 0) {
            analogWrite(this->pin2, LOW);
        }
    }
}

void PumpDriver::forward() const {
    if (properInit) {
        analogWrite(this->pin1, PUMP_HIGH);
        if (this->pin2 >= 0) {
            analogWrite(this->pin2, LOW);
        }
    }
}

void PumpDriver::backward() const {
    if (properInit) {
        analogWrite(this->pin1, LOW);
        if (this->pin2 >= 0) {
            analogWrite(this->pin2, PUMP_HIGH);
        }
    }
}
