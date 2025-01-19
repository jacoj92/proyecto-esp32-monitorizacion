#include <Arduino.h> // Incluir la biblioteca para usar Serial y otras funcionalidades de Arduino
#include "VentiladorManager.h"

// Constructor
VentiladorManager::VentiladorManager(uint8_t pin)
    : pinRele(pin) {}

// Inicializa el pin del ventilador como salida
bool VentiladorManager::init() {
    pinMode(pinRele, OUTPUT);
    turnOff(); // Apaga el ventilador inicialmente
    Serial.println("Ventilador inicializado");
    return true; // Devuelve true porque la inicialización siempre debería ser exitosa
}

// Enciende el ventilador
bool VentiladorManager::turnOn() {
    digitalWrite(pinRele, LOW); // Activa el relé (depende de la configuración del módulo relé)
    Serial.println("Ventilador encendido");
    return true;
}

// Apaga el ventilador
bool VentiladorManager::turnOff() {
    digitalWrite(pinRele, HIGH); // Desactiva el relé
    Serial.println("Ventilador apagado");
    return true;
}

// Controla el estado del ventilador basado en el índice de calor
void VentiladorManager::control(float indiceCalor) {
    if (indiceCalor > 29) {
        turnOn(); // Enciende el ventilador si el índice de calor es mayor a 29
    } else {
        turnOff(); // Apaga el ventilador si el índice de calor es menor o igual a 29
    }
}
