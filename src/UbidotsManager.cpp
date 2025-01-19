#include "UbidotsManager.h"
#include <WiFi.h>
#include <Arduino.h>

// Constructor
UbidotsManager::UbidotsManager(const char* token)
    : token(token), ubidots(token) {}

// Inicializa la conexión con Ubidots
bool UbidotsManager::init() {
    Serial.println("Inicializando Ubidots...");
    ubidots.setup();
    while (!ubidots.connected()) {
        Serial.println("Intentando conectar a Ubidots...");
        ubidots.reconnect();
        delay(1000);
    }
    Serial.println("Conectado a Ubidots.");

    return true;
}

// Envía datos a Ubidots
void UbidotsManager::sendData(const char* variableLabel, float value) {
    ubidots.add(variableLabel, value);
    if (ubidots.publish()) {
        Serial.printf("Datos enviados: %s -> %.2f\n", variableLabel, value);
    } else {
        Serial.println("Error al enviar datos a Ubidots.");
    }
}

// Manejador del bucle principal de Ubidots
void UbidotsManager::loop() {
    ubidots.loop();
}
