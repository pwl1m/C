// *** WIFI *** //
#include <WiFi.h>

#define WIFI_SSID "Amor Perfeito Lofts"
#define WIFI_PASSWORD "10061957M"
int status = WL_IDLE_STATUS; 

// void conectawifi(){
//     WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
//       Serial.print("Conectando ao WiFi ");
//       Serial.print(WIFI_SSID);
  
//   while (WiFi.status() != WL_CONNECTED) {// Wait for connection
//     delay(100);
//     Serial.print(".");
//   }
//   Serial.println(" Conectado!");
//   Serial.print("IP address: ");
//   Serial.println(WiFi.localIP());
// }
// *** WIFI *** //

const int ledBlinkIntervalConnecting = 500; // Intervalo de piscar durante a conexão (500 ms)
const int ledBlinkIntervalConnected = 1000; // Intervalo de piscar quando conectado (1000 ms)
const int ledSolidIntervalDisconnected = 0; // Intervalo sólido quando desconectado (0 ms)


const byte led_gpio = 33;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32!");
  // conectawifi();
  pinMode(led_gpio, OUTPUT);

    // Conectar-se à rede WiFi
  Serial.println();
  Serial.println("Conectando-se à rede WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  // Aguardar até que a conexão seja bem-sucedida
  while (WiFi.status() != WL_CONNECTED) {
    blinkLed(ledBlinkIntervalConnecting);
  }
  
  // Mostrar endereço IP após a conexão bem-sucedida
  Serial.println("Conectado à rede WiFi");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  // digitalWrite(led_gpio, HIGH);   // turn the LED on (HIGH is the voltage level)
  // delay(2500);                       // wait for a second
  // digitalWrite(led_gpio, LOW);    // turn the LED off by making the voltage LOW
  // delay(1250);        
  
  if (WiFi.status() != WL_CONNECTED) {
    // Se desconectado, manter o LED aceso
    digitalWrite(led_gpio, HIGH);
    delay(ledSolidIntervalDisconnected);
  } else {
    // Se conectado, piscar o LED lentamente
    blinkLed(ledBlinkIntervalConnected);
  }

}

// Função para fazer o LED piscar com um determinado intervalo
void blinkLed(int interval) {
  digitalWrite(led_gpio, HIGH);
  delay(interval / 2);
  digitalWrite(led_gpio, LOW);
  delay(interval / 2);
}
