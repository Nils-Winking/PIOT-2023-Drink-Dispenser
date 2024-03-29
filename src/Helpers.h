//
// Created by Nils on 22/11/2023.
//

#ifndef HELPERS_H
#define HELPERS_H

#include "arduino_secrets.h"
#include <Arduino.h>
#include <ansi.h>

extern ANSI ansi;

void printTitle();
void printDivider();
void printHeading(const char heading[]);
void printColored(const String& text, uint8_t fgcolor);

#endif //HELPERS_H
