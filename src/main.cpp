//
// Created by Nils on 22/11/2023.
//

#include <Arduino.h>
#include "Helpers.h"
#include "NfcWrapper.h"
#include "WifiWrapper.h"
#include "Preference.h"

bool waiting_for_cup = true;

void setup()
{
    Serial.begin(115200);
    while (!Serial) delay(10); // for Leonardo/Micro/Zero
    printTitle();
    setupNfc();
    setupWifi();
}

void loop()
{
    if (waiting_for_cup)
    {
        printColored("Insert Cup (Waiting for NFC tag)", ANSI::green);
        if (tagPresent())
        {
            NfcTag tag = readAndPrintId();
            const bool onlineMode = isConnected();
            String preferenceString;
            if (onlineMode)
            {
                // get preference from server
                const String uid = tag.getUidString();
                preferenceString = getPreferenceFromServer(uid);
            }
            else
            {
                // get preference from tag
                preferenceString = getTagContent(tag);
            }
            Serial.println(preferenceString);
            auto preference = new Preference(preferenceString);
            Serial.print("Preference Parsed with ");
            Serial.print(preference->getIngredientCount());
            Serial.println(" ingredients");
            for (int i = 0; i < preference->getIngredientCount(); ++i){
                Serial.print("Ingredient ID: ");
                Serial.print(preference->getIngredient(i).getId());
                Serial.print(" Percentage: ");
                Serial.println(preference->getIngredient(i).getAmount());
            }

            while (true)
            {
                // pour drink
                // e.g. check fill
                break;
            }
            if (onlineMode)
            {
                // save preference to tag
                savePreferenceToTag(preferenceString);
            }
        }
    }
    delay(5000);
}
