#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

const char* ssid = "Amor Perfeito Lofts";
const char* password = "10061957M";

const char* mqtt_server = "192.168.1.18";
const int mqtt_port = 1883;

const char* mqtt_topic = "teste/teste";
const char* mqtt_user = "paulo";
const char* mqtt_password = "123qweasd";

WiFiClient espClient;
PubSubClient client(espClient);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  sensors.begin();
}

void setup_wifi() {
  delay(10);
  // Conectar-se à rede WiFi
  Serial.println();
  Serial.print("Conectando-se à rede WiFi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop até que estejamos reconectados
  while (!client.connected()) {
    Serial.print("Tentando se reconectar ao MQTT Broker...");
    
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado");
      client.subscribe(mqtt_topic);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  int temperatureInt = int(temperatureC); // Get integer part of temperature
  String payload = String(temperatureInt);
  Serial.println(payload);
  client.publish(mqtt_topic, (char*) payload.c_str());
//  delay(600000); 60 segundos
//  delay(1200000); // 20 minutos = 20 x 60s
  delay(10000);
}
