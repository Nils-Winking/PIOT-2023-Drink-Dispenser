//
// Created by nils on 23.01.24.
//

#include "TFMiniWrapper.h"

#define DEBUG

TFMini::TFMini(const int uart, const int tx) : serial(uart, tx) {
    setup = true;
}

int TFMini::readDistance(const boolean wait_for_data) {
    int dist; //actual distance measurements of LiDAR
    int strength; //signal strength of LiDAR
    int check = 0; //save check value
    int i = 0;
    char j = 0;
    int uart[9]; //save data measured by LiDAR
    do {
        if(Serial.available()) {
            uart[i] = Serial.read();
            if(uart[0] != 0x59) {
                i = 0;
            } else if(i == 1 && uart[1] != 0x59) {
                i = 0;
            } else if(i == 8) {
                for(j = 0; j < 8; j++) {
                    check += uart[j];
                }
                if(uart[8] == (check % 256)) {
                    dist = uart[2] + uart[3] * 256;
                    strength = uart[4] + uart[5] * 256;
                    return dist;
                }
                i = 0;
            } else {
                i++;
            }
        }
//         if (serial.available()) {
//             //check if serial port has data input
//             if (serial.read() == TFMINI_HEADER) {
//                 //assess data package frame TFMINI_HEADER 0x59
//                 uart[0] = TFMINI_HEADER;
//                 if (serial.read() == TFMINI_HEADER) {
//                     //assess data package frame TFMINI_HEADER 0x59
//                     uart[1] = TFMINI_HEADER;
//                     for (i = 2; i < 9; i++) {
//                         //save data in array
//                         uart[i] = serial.read();
//                     }
//                     check = uart[0] + uart[1] + uart[2] + uart[3] + uart[4] + uart[5] + uart[6] + uart[7];
//                     if (uart[8] == (check & 0xff)) {
//                         //verify the received data as per protocol
//                         dist = uart[2] + uart[3] * 256; //calculate distance value
//                         strength = uart[4] + uart[5] * 256; //calculate signal strength value
// #ifdef DEBUG
//                         Serial.print("dist = ");
//                         Serial.print(dist); //output measure distance value of LiDAR
//                         Serial.print('\t');
//                         Serial.print("strength = ");
//                         Serial.print(strength); //output signal strength value
//                         Serial.print('\n');
// #endif
//
//                         return dist;
//                     }
//                 }
//             }
//         }
#ifdef DEBUG
        Serial.print(".");
#endif
        delay(100);
    }
    while (wait_for_data);
    return -2;
}
