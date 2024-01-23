//
// Created by Nils on 22/11/2023.
//

#include "Helpers.h"

ANSI ansi(&Serial);

void printTitle() {
    Serial.println(R"(
$$$$$$$\            $$\           $$\             $$$$$$$\  $$\
$$  __$$\           \__|          $$ |            $$  __$$\ \__|
$$ |  $$ | $$$$$$\  $$\ $$$$$$$\  $$ |  $$\       $$ |  $$ |$$\  $$$$$$$\  $$$$$$\   $$$$$$\  $$$$$$$\   $$$$$$$\  $$$$$$\   $$$$$$\
$$ |  $$ |$$  __$$\ $$ |$$  __$$\ $$ | $$  |      $$ |  $$ |$$ |$$  _____|$$  __$$\ $$  __$$\ $$  __$$\ $$  _____|$$  __$$\ $$  __$$\
$$ |  $$ |$$ |  \__|$$ |$$ |  $$ |$$$$$$  /       $$ |  $$ |$$ |\$$$$$$\  $$ /  $$ |$$$$$$$$ |$$ |  $$ |\$$$$$$\  $$$$$$$$ |$$ |  \__|
$$ |  $$ |$$ |      $$ |$$ |  $$ |$$  _$$<        $$ |  $$ |$$ | \____$$\ $$ |  $$ |$$   ____|$$ |  $$ | \____$$\ $$   ____|$$ |
$$$$$$$  |$$ |      $$ |$$ |  $$ |$$ | \$$\       $$$$$$$  |$$ |$$$$$$$  |$$$$$$$  |\$$$$$$$\ $$ |  $$ |$$$$$$$  |\$$$$$$$\ $$ |
\_______/ \__|      \__|\__|  \__|\__|  \__|      \_______/ \__|\_______/ $$  ____/  \_______|\__|  \__|\_______/  \_______|\__|
                                                                          $$ |
                                                                          $$ |
                                                                          \__|)");
}

void printDivider() {
    Serial.println("--------------------------------------------------------------------------------");
}

void printHeading(const char heading[]) {
    printDivider();
    Serial.print("|");
    // Determine heading length
    size_t headingLendth = strlen(heading);
    if (headingLendth >= 78) {
        dprintf(Serial, "%.*s", 78, heading);
    }
    else {
        // Fill the rest of the line with spaces
        for (int i = 0; i < (78 - headingLendth) / 2; i++) {
            Serial.print(" ");
        }
        Serial.print(heading);
        for (int i = 0; i < (78 - headingLendth) / 2; i++) {
            Serial.print(" ");
        }
    }
    Serial.println("|");
    printDivider();
}

void printColored(const String& text, uint8_t fgcolor) {
    ansi.foreground(fgcolor);
    Serial.print(text);
    ansi.normal();
    ansi.clearLine();
    Serial.println();
    _UART1_.print("");
}