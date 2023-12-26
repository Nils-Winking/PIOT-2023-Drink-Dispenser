//
// Created by Nils on 22/11/2023.
//

#include <Arduino.h>
#include "Helpers.h"
#include "NfcWrapper.h"
#include "WifiWrapper.h"

bool waiting_for_cup = true;

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(10); // for Leonardo/Micro/Zero
    printTitle();
    setupNfc();
    setupWifi();
}

void loop() {
    if (waiting_for_cup) {
        printColored("Insert Cup (Waiting for NFC tag)", ANSI::green);
        if (tagPresent()) {
            NfcTag tag = readAndPrintId();
            const bool onlineMode = isConnected();
            if (onlineMode) {
                // get preference from server
                const String uid = tag.getUidString();
                const String preferenceString = getPreferenceFromServer(uid);
            }
            else {
                // get preference from tag
                const String payload = getTagContent(tag);
                Serial.println(payload);
            }
            while (true) {
                // pour drink
                // e.g. check fill
                break;
            }
            if (onlineMode) {
                // save preference to tag
                savePreferenceToTag("");
            }
        }
    }
    delay(5000);
}
