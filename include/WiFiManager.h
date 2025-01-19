#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include <WebServer.h>

class WiFiManager {
public:
    WiFiManager(const char *apSsid, const char *apPassword);
    bool init(); // Cambiado a bool para retornar éxito o fallo
    void loop();
    bool lastRed();
    String leerStringDeEEPROM(int direccion);
    void escribirStringEnEEPROM(int direccion, String cadena);
    void intentoconexion(const char *apname, const char *appassword);

private:
    const char *apSsid;
    const char *apPassword;
    WebServer server; // Inicializado en el constructor con el puerto desde config.h
    int currentEEPROMPosition;

    //bool initAP(); // Cambiado a bool para verificar si el AP fue exitoso
    void handleRoot();
    void handleWifi();
};


#endif // WIFIMANAGER_H
