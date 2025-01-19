#ifndef PMS_MANAGER_H
#define PMS_MANAGER_H

#include <Arduino.h>
#include <PMS.h>

class PMSManager {
public:
    PMSManager(HardwareSerial &serial, int rxPin, int txPin);
    bool init();
    uint16_t getPM1_0();
    uint16_t getPM2_5();
    uint16_t getPM10();

private:
    HardwareSerial &serialPort; // Referencia al puerto serial
    PMS pms;                    // Objeto PMS
    PMS::DATA data;             // Estructura para almacenar los datos
};

#endif
