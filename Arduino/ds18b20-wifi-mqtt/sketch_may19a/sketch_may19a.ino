#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Configurações da rede Wi-Fi
const char* ssid = "Amor Perfeito Lofts";
const char* password = "10061957M";

// Configurações do broker MQTT
const char* mqtt_server = "192.168.1.";
const int mqtt_port = 1883;
const char* mqtt_topic = "temperatura/teste";

// Configurações do sensor DS18B20
const int oneWireBus = 19; // Pino onde o sensor está conectado

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  sensors.begin();
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Conectando a ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  sensors.requestTemperatures(); // Envia comando para ler temperatura
  float temperatureC = sensors.getTempCByIndex(0); // Obtém a temperatura em Celsius

  // Captura o timestamp atual (em segundos desde o início do programa)
  unsigned long timestamp = millis() / 1000;

  String payload = String(temperatureC) + "," + String(timestamp);

  Serial.print("Enviando mensagem: ");
  Serial.println(payload);

  client.publish(mqtt_topic, (char*) payload.c_str());

  delay(5000); // Aguarda 5 segundos antes de enviar a próxima leitura
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("conectado");
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      delay(5000);
    }
  }
}
