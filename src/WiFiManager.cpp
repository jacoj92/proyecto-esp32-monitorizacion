#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <Wire.h>
#include <ciso646> //para manejo de expresiones booleaas como "A and B"
//mis includes
#include "WiFiManager.h"
#include "config.h"


WiFiManager::WiFiManager(const char *apSsid, const char *apPassword)
    : apSsid(apSsid), apPassword(apPassword), server(SERVER_PORT), currentEEPROMPosition(50) {}

bool WiFiManager::init() 
{
    Serial.begin(115200);
    Serial.println("Inicializando WiFi...");

    /*
    // Inicializa el Access Point y verifica si fue exitoso
    if (!initAP()) {
        Serial.println("Error al inicializar el modo AP.");
        return false; // Si falla, retorna false
    }
    */

    WiFi.mode(WIFI_AP);
    WiFi.softAP(apSsid, apPassword);


    server.on("/", [this]() { handleRoot(); });
    server.on("/wifi", [this]() { handleWifi(); });

    server.begin(); // Inicia el servidor en el puerto especificado
    Serial.printf("Servidor iniciado en el puerto %d\n", SERVER_PORT);

    return true; // Inicialización exitosa
}


/*
bool WiFiManager::initAP() {
    Serial.println("Configurando modo AP...");
    WiFi.mode(WIFI_AP);
    bool apStarted = WiFi.softAP(apSsid, apPassword);

    if (apStarted) {
        Serial.printf("AP iniciado con SSID: %s\n", apSsid);
    } else {
        Serial.println("Error al iniciar el AP.");
    }

    return apStarted; // Retorna true si el AP se inició correctamente
}
*/


void WiFiManager::loop() 
{
    server.handleClient();
    vTaskDelay(pdMS_TO_TICKS(10)); // Pequeño delay para evitar watchdog resets
}

void WiFiManager::handleRoot() 
{
    String html = "<html><body>";
    html += "<form method='POST' action='/wifi'>";
    html += "Red Wi-Fi: <input type='text' name='ssid'><br>";
    html += "Contraseña: <input type='password' name='password'><br>";
    html += "<input type='submit' value='Conectar'>";
    html += "</form></body></html>";
    server.send(200, "text/html", html);
}

String WiFiManager::leerStringDeEEPROM(int direccion)
{
    String cadena = "";
    char caracter = EEPROM.read(direccion);
    int i = 0;
    while (caracter != '\0' && i < 100)
    {
        cadena += caracter;
        i++;
        caracter = EEPROM.read(direccion + i);
    }
    return cadena;
}


void WiFiManager::escribirStringEnEEPROM(int direccion, String cadena)
{
    int longitudCadena = cadena.length();
    for (int i = 0; i < longitudCadena; i++)
    {
        EEPROM.write(direccion + i, cadena[i]);
    }
    EEPROM.write(direccion + longitudCadena, '\0'); // Null-terminated string
    EEPROM.commit();                                // Guardamos los cambios en la memoria EEPROM
}


void WiFiManager::handleWifi() 
{
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    Serial.printf("Conectando a red Wi-Fi: %s\n", ssid.c_str());

    WiFi.disconnect();
    WiFi.begin(ssid.c_str(), password.c_str());


    int attempts = 10;
    while (WiFi.status() != WL_CONNECTED && attempts-- > 0) {
        delay(1000);
        Serial.print(".");
    }


    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nConexión establecida.");

        // guardar en memoria eeprom la ultima red conectada
        String varsave = leerStringDeEEPROM(300);
        if (varsave == "a") {
            currentEEPROMPosition = 0;
            escribirStringEnEEPROM(300, "b");
        }
        else{
            currentEEPROMPosition=50;
            escribirStringEnEEPROM(300, "a");
        }
        
        escribirStringEnEEPROM(0 + currentEEPROMPosition, ssid);
        escribirStringEnEEPROM(100 + currentEEPROMPosition, password);
        // guardar en memoria eeprom la ultima red conectada

        server.send(200, "text/plain", "Conexión establecida");

    } else {
        Serial.println("\nNo se pudo establecer la conexión.");
        server.send(200, "text/plain", "Conexión no establecida");
    }
}

void WiFiManager::intentoconexion(const char *apname, const char *appassword)
{
    Serial.begin(115200);
    EEPROM.begin(512);
    Serial.println("ingreso a intentoconexion");
    
    // redirige a la funcion    
    Serial.println("Conectarse desde su celular a la red creada");
    Serial.println("en el navegador colocar la ip:");
    Serial.println("192.168.4.1");
    init(); // nombre de wifi a generarse y contrasena
    
    while (WiFi.status() != WL_CONNECTED) // mientras no se encuentre conectado a un red
    {
        loop(); // genera una red wifi para que se configure desde la app movil
    }
}


bool WiFiManager::lastRed()
{   
    // verifica si una de las 2 redes guardadas en la memoria eeprom se encuentra disponible
    // para conectarse en ese momento
    for (int psW = 0; psW <= 50; psW += 50)
    {
        String usu = leerStringDeEEPROM(0 + psW);   //lectura desde la eprom del ssid almacenado 
        String cla = leerStringDeEEPROM(100 + psW); //lectura desde la eprom del password almacenado 
        Serial.println(usu);
        Serial.println(cla);
        WiFi.disconnect();
        WiFi.begin(usu.c_str(), cla.c_str(), 6);
        int cnt = 0;
        while (WiFi.status() != WL_CONNECTED and cnt < 10)  //
        {
            delay(1000);
            Serial.print(".");
            cnt++;
        }
        if (WiFi.status() == WL_CONNECTED){
            Serial.println("Conectado a Red Wifi");
            Serial.println(WiFi.localIP());
            break;
        }
    }
    if (WiFi.status() == WL_CONNECTED)
        return true;
    else
        return false;
}
