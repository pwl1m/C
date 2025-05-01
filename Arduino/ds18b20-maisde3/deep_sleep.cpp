#include "deep_sleep.h"
#include <esp_sleep.h>

#define uS_TO_S_FACTOR 1000000ULL  // Fator de conversão de microssegundos para segundos
#define TIME_TO_SLEEP  15 * 60     // Tempo de sleep em segundos (15 minutos)

void setupDeepSleep() {
    // Habilita o wakeup por timer
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    
    // Mensagem indicando que o dispositivo está indo dormir
    Serial.println("Indo dormir agora");
    
    // Inicia o deep sleep
    esp_deep_sleep_start();
}