//
// Created by nils on 23.01.24.
//

#ifndef PUMPDRIVER_H
#define PUMPDRIVER_H

#include <Arduino.h>

class PumpDriver
{
public:
    explicit PumpDriver();
    explicit PumpDriver(int pin1, int pin2);
    void stop() const;
    /**
     * \brief Sets the pump to run forward by setting pin1 to HIGH
     */
    void forward() const;
    /**
     * \brief Sets the pump to run backward by setting pin2 to HIGH
     */
    void backward() const;

private:
    int pin1;
    int pin2;
    bool properInit = false;
};


#endif //PUMPDRIVER_H
