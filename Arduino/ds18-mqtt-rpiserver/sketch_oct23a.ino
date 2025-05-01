#include <WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define uS_TO_S_FACTOR 1000000  /* Fator de conversão de microssegundos para segundos */
//#define TIME_TO_SLEEP  45        /* Tempo que o ESP32 irá dormir (em minutos) */

// Configurações da rede Wi-Fi
const char* ssid = "TP-Link_FB40";
const char* password = "amoros4321";

// Configurações do broker MQTT
const char* mqtt_server = "pi.local";
const int mqtt_port = 1883;
const char* mqtt_topic = "teste";

const char* mqtt_user = "esp";
const char* mqtt_password = "amorosa";

// Configurações do sensor DS18B20
const int oneWireBus = 4; // Pino onde o sensor está conectado

WiFiClient espClient;
PubSubClient client(espClient);

OneWire oneWire(oneWireBus);
DallasTemperature sensors(&oneWire);

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
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  int temperatureInt = int(temperatureC); // Obter a parte inteira da temperatura
  String payload = String(temperatureInt);
  Serial.println(payload);
  client.publish(mqtt_topic, (char*) payload.c_str());

//  // Configurar para dormir por 45 minutos
//  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * 60 * uS_TO_S_FACTOR);
//  Serial.println("Configurar ESP32 para dormir por " + String(TIME_TO_SLEEP) + " minutos");

  Serial.println("Indo dormir agora");
  Serial.flush(); 
  // Entrar em deep sleep
  // esp_deep_sleep_start();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conectado");
      client.subscribe(mqtt_topic);
    } 
    else {
      Serial.print("Falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tente novamente em 5 segundos");
      delay(5000);
    }
  }
}
