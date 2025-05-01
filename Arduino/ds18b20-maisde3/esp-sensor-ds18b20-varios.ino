#include <Arduino.h>
#include "wifi_setup.h"
#include "mqtt_setup.h"
#include "temperature_sensor.h"
#include "deep_sleep.h"

RTC_DATA_ATTR int bootCount = 0;

void setup() {
    Serial.begin(115200);
    delay(30000);

    bootCount++;
    Serial.println("BootCount: " + String(bootCount));

    setup_wifi();
    setup_mqtt();
    setup_temperature_sensors();  // Inicializa os sensores

    float temp1 = readTemperature(0);
    float temp2 = readTemperature(1);

    // Publica ambos os valores no MQTT
    String payload = "{ \"sensor1\": " + String(temp1) + ", \"sensor2\": " + String(temp2) + " }";
    Serial.println(payload);
    publish_mqtt(payload.c_str());

    setupDeepSleep();
}

void loop() {
    // Código vazio pois o ESP32 entra em deep sleep
}
