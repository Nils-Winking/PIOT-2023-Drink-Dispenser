//
// Created by Nils on 27/01/2024.
//

#include "DisplayWrapper.h"

#define LCD_ENABLED

void setupDisplay() {
#ifdef LCD_ENABLED
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("hello, world!");
#endif
}


void lcd_print(const char* line1, const char* line2) {
#ifdef LCD_ENABLED
    lcd.clear();
    lcd.print(line1);
    if (line2 != nullptr) {
        lcd.setCursor(0, 1);
        lcd.print(line2);
    }
#endif
}
