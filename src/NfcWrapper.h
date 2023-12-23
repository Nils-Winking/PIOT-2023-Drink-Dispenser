//
// Created by Nils on 22/11/2023.
//

#ifndef NFCWRAPPER_H
#define NFCWRAPPER_H
#include <Adafruit_PN532.h>
#include <NfcAdapter.h>

/**
 * NFC related variables and functions
 */
extern Adafruit_PN532 nfc;
extern NfcAdapter nfcAdapter;

void setupNfc();

NfcTag readAndPrintId();
String getTagContent(NfcTag &tag);
void savePreferenceToTag(const String &payload);
bool tagPresent();

#endif //NFCWRAPPER_H
