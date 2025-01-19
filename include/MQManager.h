#ifndef MQ_MANAGER_H
#define MQ_MANAGER_H

#include <MQUnifiedsensor.h>

class MQManager {
public:
    MQManager(uint8_t pin);
    bool init();
    float readCO2();
    float readCO();
    float readAlcohol();
    void calibrate();
private:
    MQUnifiedsensor mqSensor; // Objeto para manejar el sensor MQ
};

#endif
