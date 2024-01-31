//
// Created by nils on 23.01.24.
//

#include "VL53L1XWrapper.h"

// #define DEBUG

void setupVL53L1X()
{
    printHeading("VL53L1X");

    Wire.begin();
    Serial.println("Wire initilized");
    if (!vl53.begin(0x29, &Wire, true))
    {
        Serial.print("..");
        Serial.print(F("Error on init of VL sensor: "));
        Serial.println(vl53.vl_status);
        while (1) delay(10);
    }
    Serial.println(F("VL53L1X sensor OK!"));

    Serial.print(F("Sensor ID: 0x"));
    Serial.println(vl53.sensorID(), HEX);

    if (!vl53.startRanging())
    {
        Serial.print(F("Couldn't start ranging: "));
        Serial.println(vl53.vl_status);
        while (1) delay(10);
    }
    Serial.println(F("Ranging started"));

    // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
    vl53.setTimingBudget(100);
    Serial.print(F("Timing budget (ms): "));
    Serial.println(vl53.getTimingBudget());

    // vl53.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
    // vl53.VL53L1X_SetInterruptPolarity(0);
}

int16_t readDistance(const boolean wait_for_data)
{
    do {
        if (vl53.dataReady())
        {
            // new measurement for the taking!
            const int16_t distance = vl53.distance();
            if (distance == -1)
            {
                // something went wrong!
#ifdef DEBUG
                Serial.print(F("Couldn't get distance: "));
                Serial.println(vl53.vl_status);
#endif
                return -1;
            }
#ifdef DEBUG
            Serial.print(F("Distance: "));
            Serial.print(distance);
            Serial.println(" mm");
#endif

            // data is read out, time for another reading!
            vl53.clearInterrupt();
            return distance;
        } else {
            Serial.println("No data ready");
        }
        delay(100);
    }
    while (wait_for_data);
    return -2;
}
