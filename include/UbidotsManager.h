#ifndef UBIDOTSMANAGER_H
#define UBIDOTSMANAGER_H

#include <UbidotsEsp32Mqtt.h>

class UbidotsManager {
public:
    UbidotsManager(const char* token);
    bool init();
    void sendData(const char* variableLabel, float value);
    void loop();

private:
    const char* token;
    Ubidots ubidots;
};

#endif
