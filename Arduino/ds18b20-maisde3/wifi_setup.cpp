#include "wifi_setup.h"
#include <WiFi.h>

const char* ssid = "Amor Perfeito Lofts";
const char* password = "10061957M";

void setup_wifi() {
    Serial.print("Conectando a ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi conectado");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
}
