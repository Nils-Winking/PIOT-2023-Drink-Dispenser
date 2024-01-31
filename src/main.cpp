//
// Created by Nils on 22/11/2023.
//

#include <Arduino.h>
#include <DisplayWrapper.h>
#include <map>
#include "TFMiniWrapper.h"
#include "VL53L1XWrapper.h"

#include "Helpers.h"
#include "NfcWrapper.h"
#include "WifiWrapper.h"
#include "TFMiniWrapper.h"
#include "PumpDriver.h"
#include "Preference.h"

bool waiting_for_cup = true;

std::map<int, PumpDriver> pumps = {};

int height;
constexpr int16_t cup_height = 80;
// PumpDriver pumps[20];

// TFMini tfMini(2, 3);

void setup() {
    Serial.begin(115200);
    while (!Serial) delay(10); // for Leonardo/Micro/Zero
    printTitle();
    // Setting up the lcd display, needed for lcd_print
    setupDisplay();
    lcd_print("Starting up...");
    // Setting up the NFC reader
    setupNfc();
    lcd_print("NFC setup done!");
    // Setting up the TOF sensor
    setupVL53L1X();
    lcd_print("VL53L1X setup done!");

    // Getting the height of the empty dispenser and printing it
    delay(100);
    height = readDistance(true);
    if (height < 0) {
        printColored("Couldn't get height, aborting!", ANSI::red);
        while (true);
    }
    Serial.print("Calibrated height: ");
    Serial.println(height);
    char l1[16];
    char l2[16];
    sprintf(l1, "Calibrated");
    sprintf(l2, "height: %4d", height);
    lcd_print(l1, l2);

    // Setting up the wifi connection
    setupWifi();

    // Setting up the pumps
    pumps[1] = PumpDriver(5);
    pumps[11] = PumpDriver(6);
    delay(1000);
}

void loop() {
    if (waiting_for_cup) {
        printColored("Insert Cup (Waiting for NFC tag)", ANSI::green);
        lcd_print("Insert Cup!");
        if (tagPresent()) {
            NfcTag tag = readAndPrintId();
            const bool onlineMode = isConnected();
            String preferenceString;
            lcd_print("Tag found!");
            if (onlineMode) {
                // get preference from server
                lcd_print("Fetching prefere","nce from server...");
                const String uid = tag.getUidString();
                preferenceString = getPreferenceFromServer(uid);
            }
            else {
                // get preference from tag
                preferenceString = getTagContent(tag);
            }
            // auto substring = preferenceString.substring(3, preferenceString.length() - 7);
            // lcd_print(substring.c_str());
            // Serial.println(substring);
            const auto preference = new Preference(preferenceString);
            Serial.print("Preference Parsed with ");
            Serial.print(preference->getIngredientCount());
            Serial.println(" ingredients");
            const int initial_fill = height - readDistance();
            Serial.print("Initial fill: ");
            Serial.println(initial_fill);
            const int free = cup_height - initial_fill;
            Serial.print("Cup has empty space of: ");
            Serial.println(free);
            int fill;
            int raw;
            double filled = 0;
            delay(1000);
            char l1[16];
            char l2[16];
            for (int i = 0; i < preference->getIngredientCount(); ++i) {
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
                while ((raw = readDistance(true)) > 0 && (fill = height - raw) < target) {
                    // printing the current fill level and replacing the old one
                    ansi.cursorBack(17);
                    ansi.print("Fill: ");
                    char f[5];
                    sprintf(f, "%4d", fill);
                    ansi.print(f);
                    sprintf(l1, "Ingr.: %2d (%3d%%)", ingredient.getId(), ingredient.getAmount());
                    sprintf(l2, "Fill: %4d/%4f", fill, target);
                    lcd_print(l1, l2);
                    // set pump to forward (dispense) and wait a bit
                    pumps[ingredient.getId()].forward();
                    delay(110);
                }
                // Just in case so that the next line is always printed properly
                ansi.println();
                ansi.print("Fill: ");
                char f[5];
                sprintf(f, "%4d", fill);
                ansi.println(f);
                ansi.println("Fill above target, stopping!");
                sprintf(l1, "Ingr.: %2d (%3d%%)", ingredient.getId(), ingredient.getAmount());
                sprintf(l2, "Fill: %4d/%4f", fill, target);
                lcd_print(l1, l2);

                // target for this ingredient is reached
                // set pump to stop
                pumps[ingredient.getId()].stop();
                filled = target;
            }
            lcd_print("Finished! :)");
            if (onlineMode) {
                // save preference to tag
                savePreferenceToTag(preferenceString);
            }
        }
    }
    delay(5000);
}
