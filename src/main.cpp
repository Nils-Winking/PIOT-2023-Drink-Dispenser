//
// Created by Nils on 22/11/2023.
//

#include <Arduino.h>
#include <map>

#include "Helpers.h"
#include "NfcWrapper.h"
#include "WifiWrapper.h"
#include "VL53L1XWrapper.h"
#include "PumpDriver.h"
#include "Preference.h"

bool waiting_for_cup = true;

std::map<int, PumpDriver> pumps = {};
// PumpDriver pumps[20];

void setup()
{
    Serial.begin(115200);
    while (!Serial) delay(10); // for Leonardo/Micro/Zero
    printTitle();
    setupNfc();
    setupWifi();
    setupVL53L1X();

    pumps[1] = PumpDriver(8, 9);
    pumps[11] = PumpDriver(4, 5);
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
            const auto preference = new Preference(preferenceString);
            Serial.print("Preference Parsed with ");
            Serial.print(preference->getIngredientCount());
            Serial.println(" ingredients");

            // get cup height
            const int16_t height = 300; // 300 mm
            // get initial fill

            if (const int16_t initial_fill = readDistance(); initial_fill >= 0)
            {
                const int free = height - initial_fill;
                Serial.print("Cup has empty space of: ");
                Serial.println(free);
                int16_t fill;
                double filled = 0;
                for (int i = 0; i < preference->getIngredientCount(); ++i)
                {
                    Serial.print("Ingredient ID: ");
                    auto ingredient = preference->getIngredient(i);
                    Serial.print(ingredient.getId());
                    Serial.print(" Percentage: ");
                    Serial.print(ingredient.getAmount());
                    Serial.print("%");

                    const double this_height = free / 100.0 * ingredient.getAmount();
                    Serial.print(" Height: ");
                    Serial.print(this_height);
                    const double target = filled + this_height;
                    Serial.print(" Target Fill: ");
                    Serial.println(target);
                    filled = target;

                    while ((fill = readDistance()) < target)
                    {
                        if (fill < 0)
                        {
                            // sensor didn't provide a value
                            // waiting a bit then trying again
                            delay(100);
                            continue;
                        }
                        ansi.cursorBack(17);
                        ansi.print("Fill: ");
                        char f[5];
                        sprintf(f, "%4d", fill);
                        ansi.print(f);
                        // set pump to forward (dispense) and wait a bit
                        pumps[ingredient.getId()].forward();
                        delay(100);
                    }
                    // Just in case so that the next line is always printed properly
                    ansi.println();
                    ansi.println("Fill above target, stopping!");
                    // target for this ingredient is reached
                    // set pump to stop
                    pumps[ingredient.getId()].stop();
                }
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
