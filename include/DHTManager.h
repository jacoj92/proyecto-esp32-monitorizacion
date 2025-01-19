#ifndef DHT_MANAGER_H
#define DHT_MANAGER_H

#include <DHT.h>

class DHTManager {
public:
    DHTManager(int pin, uint8_t type);
    bool init();
    float readTemperature();
    float readHumidity();
    void readSensor();

private:
    DHT dht; // Objeto DHT
};

#endif

