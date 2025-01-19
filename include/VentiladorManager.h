#ifndef VENTILADOR_MANAGER_H
#define VENTILADOR_MANAGER_H

#include <Arduino.h>

class VentiladorManager {
public:
    VentiladorManager(uint8_t pin);  // Constructor que recibe el pin del relé
    bool init();                     // Inicializa el pin del ventilador
    bool turnOn();                   // Enciende el ventilador
    bool turnOff();                  // Apaga el ventilador
    void control(float indiceCalor); // Controla el estado del ventilador según el índice de calor

private:
    uint8_t pinRele; // Pin conectado al relé que controla el ventilador
};

#endif // VENTILADOR_MANAGER_H
