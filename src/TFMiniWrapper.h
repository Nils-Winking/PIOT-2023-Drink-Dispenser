//
// Created by nils on 23.01.24.
//

#ifndef TFMINIWRAPPER_H
#define TFMINIWRAPPER_H

#include <Helpers.h>
#include <SoftwareSerial.h>

// #define IRQ_PIN 7
// #define XSHUT_PIN 6
constexpr int TFMINI_HEADER = 0x59; //frame header of data package

class TFMini {
public:
    explicit TFMini(int rx, int tx);

    explicit TFMini();

    int readDistance(boolean wait_for_data = false);

private:
    SoftwareSerial serial;
    boolean setup = false;
};

// void setupTFMini();

// int16_t readDistance(boolean wait_for_boolean = false);

#endif //TFMINIWRAPPER_H
