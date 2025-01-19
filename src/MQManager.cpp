#include "MQManager.h"

MQManager::MQManager(uint8_t pin)
    : mqSensor("ESP-32", 3.3, 12, pin, "MQ-135") {}

bool MQManager::init() {
    Serial.println("Iniciando MQ-2...");
    mqSensor.setRegressionMethod(1);  // Configura el modelo matemático
    mqSensor.setA(110.47);            // Parámetro 'A' para la curva de calibración
    mqSensor.setB(-2.862);            // Parámetro 'B' para la curva de calibración
    mqSensor.init();
    calibrate();                      // Calibración inicial

    return true;
}

void MQManager::calibrate() {
    Serial.println("Calibrando el sensor MQ...");
    float r0 = 0.0;

    for (int i = 0; i < 10; i++) {
        mqSensor.update();                  // Actualiza los datos del sensor
        r0 += mqSensor.calibrate(3.6);      // Calibra en aire limpio
        delay(1000);
    }

    r0 /= 10.0;  // Calcula el promedio
    mqSensor.setR0(r0);

    if (isinf(r0)) {
        Serial.println("Error: Circuito abierto detectado.");
        //while (1);
    } else if (r0 == 0) {
        Serial.println("Error: Cortocircuito detectado.");
       // while (1);
    } else {
        Serial.println("Calibración completada con éxito.");
    }
}

float MQManager::readCO2() {
    //lectura de C02
    mqSensor.setA(110.47);
    mqSensor.setB(-2.862);
    mqSensor.update();
    return mqSensor.readSensor();
}

float MQManager::readCO() {
    mqSensor.setA(605.18);
    mqSensor.setB(-3.937);
    mqSensor.update();
    return mqSensor.readSensor();
}

float MQManager::readAlcohol() {
    mqSensor.setA(77.255);
    mqSensor.setB(-3.18);
    mqSensor.update();
    return mqSensor.readSensor();
}
