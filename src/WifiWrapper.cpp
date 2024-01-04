//
// Created by Nils on 22/11/2023.
//

#include "WifiWrapper.h"

#include "Helpers.h"

#define WIFI_MAX_ATTEMPTS 2

#define forceConnection

/**
 * WiFi related variables and functions
 */
int status = WL_IDLE_STATUS;
char ssid[] = SECRET_SSID; // Both the SSID and PASS are loaded from an external file (arduino_secrets.h)
char pass[] = SECRET_PASS;
IPAddress server(SERVER_IP);
WiFiClient client;

void printWifiStatus() {
    // print the SSID of the network you're attached to:
    ansi.foreground(ANSI::cyan);
    Serial.print("                  SSID: ");
    Serial.println(WiFi.SSID());

    // print your board's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("            IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("Signal Strength (RSSI): ");
    Serial.print(rssi);
    Serial.println(" dBm");
    ansi.normal();
}

void setupWifi() {
    printHeading("WiFi");
    Serial.println("Initializing WiFi!");
    delay(1000);
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
        Serial.println("Communication with WiFi module failed!");
        // don't continue
        while (true);
    }

    if (String fv = CWifi::firmwareVersion(); fv < WIFI_FIRMWARE_LATEST_VERSION) {
        Serial.println("Please upgrade the firmware");
    }

    Serial.print("Attempting to connect to WiFi with SSID: ");
    Serial.println(ssid);

    uint8_t connectionAttempts = 0;

    // attempt to connect to WiFi network:
#ifdef forceConnection
    while (status != WL_CONNECTED) {
#else
        while (connectionAttempts < WIFI_MAX_ATTEMPTS && status != WL_CONNECTED) {
#endif
        uint8_t status1 = WiFi.status();
        if (status1 == WL_CONNECTED) {
            Serial.print("f1");
        }
        if (status1 == WL_CONNECT_FAILED) {
            Serial.print("f2");
        }
        if (status1 == WL_CONNECTION_LOST) {
            Serial.print("f3");
        }
        if (status1 == WL_DISCONNECTED){
            Serial.print("f4");
        }
        if (status1 == WL_NO_SSID_AVAIL){
            Serial.print("f5");
        }

        if (status1 == WL_AP_CONNECTED){
            Serial.print("f6");
        }

        if (status1 == WL_AP_FAILED){
            Serial.print("f7");
        }

        if (status1 == WL_AP_LISTENING){
            Serial.print("f8");
        }

        if (status1 == WL_IDLE_STATUS){
            Serial.print("f9");
        }

        if (status1 == WL_NO_MODULE){
            Serial.print("f10");
        }

        if (status1 == WL_NO_SHIELD){
            Serial.print("f11");
        }

        if (status1 == WL_SCAN_COMPLETED){
            Serial.print("f12");
        }
        Serial.print(".");
        connectionAttempts++;
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        status = WiFi.begin(ssid);
    }
    Serial.println();
    if (connectionAttempts == WIFI_MAX_ATTEMPTS && status != WL_CONNECTED) {
        ansi.color(ANSI::white, ANSI::red);
        ansi.bold();
        Serial.println("Failed to connect to WiFi!");
        Serial.print("Continuing in offline mode!");
        ansi.normal();
        ansi.clearLine();
        Serial.println();
    } else {
        printWifiStatus();
    }
}


int isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

String getPreferenceFromServer(const String &uid) {
    printColored("Fetching from Server", ANSI::green);
    if (!client.connect(server, SERVER_PORT)) {
        printColored("Could not connect to server", ANSI::red);
        return "99";
    }
    client.println("GET /search?q=arduino HTTP/1.1");
    client.println("Host: drinkserver.io");
    client.println("Connection: close");
    client.println();
    uint32_t received_data_num = 0;
    printColored("PrintingDATA:", ANSI::blue);

    while (client.available()) {
        /* actual data reception */
        char c = client.read();
        /* print data to serial port */
        Serial.print(c);
        /* wrap data to 80 columns */
        received_data_num++;
        if (received_data_num % 80 == 0) {
            Serial.println();
        }
    }
    printColored("DataPrintFinished:", ANSI::blue);

    return "";
}

void reportSpendAmountToServer(const String &uid, int amount) {
    //TODO: report spent amount to server
}
