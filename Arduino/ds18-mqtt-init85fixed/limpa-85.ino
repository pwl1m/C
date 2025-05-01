#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Arduino.h>

#define uS_TO_S_FACTOR 1000000ULL  /* Fator de conversão de microssegundos para segundos */
#define TIME_TO_SLEEP  3 * 3600       

// Configurações da rede Wi-Fi
const char* ssid = "Amor Perfeito Lofts";
const char* password = "10061957M";

// Configurações do broker MQTT
const char* mqtt_server = "192.168.1.5";
const int mqtt_port = 1883;
const char* mqtt_topic = "monitoramento/temperatura";

const char* mqtt_user = "paulo";
const char* mqtt_password = "senha123";

// Configurações do sensor DS18B20
const int oneWireBus = 4; // Pino onde o sensor está conectado

WiFiClient espClient;
PubSubClient client(espClient);

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

RTC_DATA_ATTR int bootCount = 0;

void setup() {
  // inicio
  Serial.begin(115200);
  delay(30000);

  // increment boot count
  bootCount++;
  Serial.println("BootCount: " + String(bootCount));

  // iniciando wifi
  setup_wifi();

  // setando mqtt
  client.setServer(mqtt_server, mqtt_port);

  // se não conectado pelo mqtt
  if (!client.connected()) {
    // tentar até conectar
    reconnect();
  }

  // inicializa o sensor de temperatura
  sensors.begin();

  float temperatureC = 85.0; // Valor inicial para entrar no loop

  // Faz leituras até que uma temperatura válida seja obtida
  while (temperatureC == 85.0 || temperatureC == DEVICE_DISCONNECTED_C) {
    sensors.requestTemperatures();
    temperatureC = sensors.getTempCByIndex(0);
    delay(1000); // Espera um segundo para estabilizar a leitura
  }

  // Converte para um valor inteiro
  int temperatureInt = int(temperatureC); 

  // enviando o formato necessario para o node-red
  String payload = String(temperatureInt);
  Serial.println(payload);
  client.publish(mqtt_topic, (char*) payload.c_str());

  // função deep sleep
  setupDeepSleep();
}

void setupDeepSleep(){
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println(TIME_TO_SLEEP); // Imprime o tempo total de sono em segundos
  Serial.println(TIME_TO_SLEEP/120); // Em Minutos
  // Serial.println(uS_TO_S_FACTOR);
  Serial.println("Indo dormir agora");
  // Serial.flush(); 
  esp_deep_sleep_start();
}

void setup_wifi() {
  delay(10);
  Serial.print("Conectando a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi conectado");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

// função mqtt
void reconnect() {
  while (!client.connected()) {
    Serial.print("(!client.connected) Tentando conexão MQTT...");
    
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado");
      client.subscribe(mqtt_topic);
    } 
    else {
      Serial.print("Falhou, estado=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      delay(5000);
    }
  }
}

void loop() {
}