#include "mqtt_setup.h"
#include <WiFi.h>
#include <PubSubClient.h>

const char* mqtt_server = "192.168.1.17";
const int mqtt_port = 1883;
const char* mqtt_topic = "teste";
const char* mqtt_user = "paulo";
const char* mqtt_password = "diana123";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_mqtt() {
    client.setServer(mqtt_server, mqtt_port);
    while (!client.connected()) {
        Serial.print("Tentando conexão MQTT...");
        if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
            Serial.println("Conectado");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("Falhou, estado=");
            Serial.print(client.state());
            Serial.println(" tente novamente em 5 segundos");
            delay(5000);
        }
    }
}

void publish_mqtt(const char* payload) {
    client.publish(mqtt_topic, payload);
}
