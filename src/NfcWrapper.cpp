//
// Created by Nils on 22/11/2023.
//

#include "NfcWrapper.h"
#include <Helpers.h>

// #define DEBUG

/**
 * NFC related variables and functions
 */
Adafruit_PN532 nfc(10);
NfcAdapter nfcAdapter = NfcAdapter(nfc);

void setupNfc() {
    printHeading("NFC");
    Serial.println("Initializing NFC reader!");
    nfcAdapter.begin();
}

NfcTag readAndPrintId() {
    NfcTag tag = nfcAdapter.read();
    // Serial.println(tag.getTagType());
    Serial.print("UID: ");
    Serial.println(tag.getUidString());
    return tag;
}

const String uriPrefixes[] = {
    "http://www.", "https://www.", "http://", "https://", "tel:", "mailto:",
    "ftp://anonymous:anonymous@", "ftp://ftp.", "ftps://", "sftp://", "smb://", "nfs://", "ftp://", "dav://", "news:",
    "telnet://", "imap:", "rtsp://", "urn:", "pop:", "sip:", "sips:", "tftp:", "btspp://", "btl2cap://", "btgoep://",
    "tcpobex://", "irdaobex://", "file://", "urn:epc:id:", "urn:epc:tag:", "urn:epc:pat:", "urn:epc:raw:", "urn:epc:",
    "urn:nfc:"
};

String getTagContent(NfcTag&tag) {
    if (tag.hasNdefMessage()) // every tag won't have a message
    {
        NdefMessage message = tag.getNdefMessage();
#ifdef DEBUG
        Serial.print("\nThis NFC Tag contains an NDEF Message with ");
        Serial.print(message.getRecordCount());
        Serial.print(" NDEF Record");
        if (message.getRecordCount() != 1) {
            Serial.print("s");
        }
        Serial.println(".");
#endif
        // cycle through the records, printing some info from each
        int recordCount = message.getRecordCount();
        for (int i = 0; i < recordCount; i++) {
            NdefRecord record = message.getRecord(i);
#ifdef DEBUG
            Serial.print("\nNDEF Record ");
            Serial.println(i+1);
            Serial.print("  TNF: ");Serial.println(record.getTnf());
            Serial.print("  Type: ");Serial.println(record.getType()); // will be "" for TNF_EMPTY
#endif
            // The TNF and Type should be used to determine how your application processes the payload
            // There's no generic processing for the payload, it's returned as a byte[]
            int payloadLength = record.getPayloadLength();
            byte payload[payloadLength];
            record.getPayload(payload);

            // Print the Hex and Printable Characters
#ifdef DEBUG
            Serial.print("  Payload (HEX): ");
            PrintHexChar(payload, payloadLength);
#endif
            // Force the data into a String (might work depending on the content)
            // Real code should use smarter processing
            String payloadAsString = "";
            int first_usable_char = 0;

            String type = record.getType();
            if (type == "U") {
                // Type is a URI
                first_usable_char = 1;
                payloadAsString += uriPrefixes[payload[0]];
            }
            else if (type == "T") {
                // Type is text
                first_usable_char = 3;
            }
            else {
                continue;
            }

            for (int c = first_usable_char; c < payloadLength; c++) {
                if (payload[c] >= 32 && payload[c] <= 126) {
                    payloadAsString += (char)payload[c];
                }
            }
#ifdef DEBUG
            Serial.print("  Payload (as String): ");
            Serial.println(payloadAsString);
#endif
            // id is probably blank and will return ""
#ifdef DEBUG
            String uid = record.getId();
            if (uid != "") {
                Serial.print("  ID: ");Serial.println(uid);
            }
#endif
            return payloadAsString;
        }
    }
}


void savePreferenceToTag(const String &payload) {
    NdefMessage message = NdefMessage();
    message.addTextRecord(payload);
    nfcAdapter.write(message);
}
