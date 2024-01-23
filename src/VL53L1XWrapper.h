//
// Created by nils on 23.01.24.
//

#ifndef VL53L1XWRAPPER_H
#define VL53L1XWRAPPER_H

#include <Adafruit_VL53L1X.h>
#include <Helpers.h>

#define IRQ_PIN 7
#define XSHUT_PIN 6

inline Adafruit_VL53L1X vl53 = Adafruit_VL53L1X(XSHUT_PIN, IRQ_PIN);

void setupVL53L1X();

int16_t readDistance();

#endif //VL53L1XWRAPPER_H
