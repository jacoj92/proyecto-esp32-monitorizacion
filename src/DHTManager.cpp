#include "DHTManager.h"
#include <Arduino.h>

DHTManager::DHTManager(int pin, uint8_t type) : dht(pin, type) {}

bool DHTManager::init() {
    dht.begin();
    Serial.println("DHT sensor inicializado");
    return true;
}

float DHTManager::readTemperature() {
    return dht.readTemperature();
}

float DHTManager::readHumidity() {
    return dht.readHumidity();
}

void DHTManager::readSensor() {
    float temperature = readTemperature();
    float humidity = readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Error al leer el sensor DHT");
    } else {
        Serial.print("Temperatura: ");
        Serial.println(temperature);
        Serial.print("Humedad: ");
        Serial.println(humidity);
    }
}
