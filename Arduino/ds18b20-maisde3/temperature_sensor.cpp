#include "temperature_sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = 4;
OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

// Armazena os endereços dos sensores
DeviceAddress sensor1, sensor2;

// Inicializa os sensores e detecta seus endereços
void setup_temperature_sensors() {
    sensors.begin();
    if (sensors.getDeviceCount() < 2) {
        Serial.println("Erro: Menos de dois sensores detectados!");
        return;
    }
    sensors.getAddress(sensor1, 0);
    sensors.getAddress(sensor2, 1);

    Serial.print("Sensor 1: ");
    for (uint8_t i = 0; i < 8; i++) {
        Serial.print(sensor1[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    Serial.print("Sensor 2: ");
    for (uint8_t i = 0; i < 8; i++) {
        Serial.print(sensor2[i], HEX);
        Serial.print(" ");
    }
    Serial.println();
}

// Função para ler temperatura de um dos sensores
float readTemperature(int sensorIndex) {
    sensors.requestTemperatures();

    if (sensorIndex == 0) {
        return sensors.getTempC(sensor1);
    } else if (sensorIndex == 1) {
        return sensors.getTempC(sensor2);
    }
    
    return -127.0; // Erro
}
