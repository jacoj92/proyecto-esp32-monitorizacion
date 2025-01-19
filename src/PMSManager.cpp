#include "PMSManager.h"

PMSManager::PMSManager(HardwareSerial &serial, int rxPin, int txPin)
    : serialPort(serial), pms(serialPort) {
    serialPort.begin(9600, SERIAL_8N1, rxPin, txPin);
}

bool PMSManager::init() {
    Serial.println("Inicializando PMS5003...");
    // Configuración adicional si es necesario
    return true;
}

uint16_t PMSManager::getPM1_0() {
    if (pms.readUntil(data)) {
        return data.PM_AE_UG_1_0;
    }
    return 0; // Si no se leen datos, retornar 0
}

uint16_t PMSManager::getPM2_5() {
    if (pms.readUntil(data)) {
        return data.PM_AE_UG_2_5;
    }
    return 0; // Si no se leen datos, retornar 0
}

uint16_t PMSManager::getPM10() {
    if (pms.readUntil(data)) {
        return data.PM_AE_UG_10_0;
    }
    return 0; // Si no se leen datos, retornar 0
}
