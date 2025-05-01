#ifndef MQTT_SETUP_H
#define MQTT_SETUP_H

#include <PubSubClient.h>

extern PubSubClient client;
void setup_mqtt();
void publish_mqtt(const char* payload);

#endif
