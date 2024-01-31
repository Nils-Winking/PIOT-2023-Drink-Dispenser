//
// Created by Nils on 27/01/2024.
//

#ifndef DISPLAYWRAPPER_H
#define DISPLAYWRAPPER_H

#include <LiquidCrystal.h>

constexpr int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 7;

inline LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setupDisplay();

void lcd_print(const char* line1, const char* line2 = nullptr);

#endif //DISPLAYWRAPPER_H
