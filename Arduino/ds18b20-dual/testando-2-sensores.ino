#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Configuração do pino de dados dos sensores
#define ONE_WIRE_BUS 4  // Defina o pino ao qual os sensores estão conectados

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Endereços dos sensores (serão detectados automaticamente)
DeviceAddress sensor1, sensor2;

// Configuração do Wi-Fi
const char* ssid = "Amor Perfeito Lofts";
const char* password = "10061957M";

// Configuração do MQTT
const char* mqtt_server = "192.168.1.5";  // Endereço do Broker MQTT
const char* topic_sensor1 = "sensor1/temperatura";
const char* topic_sensor2 = "sensor2/temperatura";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// Função para conectar ao Wi-Fi
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi");
}

// Função para conectar ao MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.println("Conectando ao MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao MQTT");
    } else {
      Serial.print("Falha na conexão MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5s");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);

  sensors.begin();

  // Verifica se há pelo menos dois sensores conectados
  if (sensors.getDeviceCount() < 2) {
    Serial.println("Erro: Menos de dois sensores encontrados!");
    while (true);
  }

  // Obtendo os endereços dos dois primeiros sensores encontrados
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

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensors.requestTemperatures(); // Comando para os sensores iniciarem a leitura

  float temp1 = sensors.getTempC(sensor1);
  float temp2 = sensors.getTempC(sensor2);

  Serial.print("Temperatura Sensor 1: ");
  Serial.print(temp1);
  Serial.println(" °C");

  Serial.print("Temperatura Sensor 2: ");
  Serial.print(temp2);
  Serial.println(" °C");

  // Publicando os dados no MQTT
  char msg1[8], msg2[8];
  dtostrf(temp1, 4, 2, msg1);
  dtostrf(temp2, 4, 2, msg2);

  client.publish(topic_sensor1, msg1);
  client.publish(topic_sensor2, msg2);

  delay(10000); // Aguarda 5 segundos antes da próxima leitura
}
