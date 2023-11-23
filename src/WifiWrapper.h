//
// Created by Nils on 22/11/2023.
//

#ifndef WIFIWRAPPER_H
#define WIFIWRAPPER_H

#include <arduino_secrets.h>
#include <WiFiTypes.h>
#include <Arduino.h>
#include <WiFiS3.h>

void printWifiStatus();
void setupWifi();
int isConnected();

#endif //WIFIWRAPPER_H
