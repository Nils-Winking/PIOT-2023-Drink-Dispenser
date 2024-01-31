//
// Created by Nils on 22/11/2023.
//

#ifndef WIFIWRAPPER_H
#define WIFIWRAPPER_H

#include "arduino_secrets.h"
#include <WiFiTypes.h>
#include <Arduino.h>
#include <WiFiS3.h>
#include "Ingredient.h"
#include "Preference.h"
#include "DisplayWrapper.h"

void printWifiStatus();
void setupWifi();
int isConnected();
String getPreferenceFromServer(const String &uid);
void reportSpendAmountToServer(const String &uid, int amount);

#endif //WIFIWRAPPER_H
