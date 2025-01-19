#include <Arduino.h>
#include <wifi.h>
#include "config.h"
#include "DHTManager.h"
#include "MQManager.h"
#include "PMSManager.h"
#include "VentiladorManager.h"
#include "LCDManager.h"
#include <EEPROM.h>
#include "WiFiManager.h"
#include "UbidotsManager.h"
#include "TasksManager.h"

// Semáforo para sincronizar el bus I2C
SemaphoreHandle_t i2cSemaphore;

// Definición de objetos globales
DHTManager dhtManager(DHT_PIN, DHT_TYPE);
MQManager mqManager(MQ_PIN);
PMSManager pmsManager(Serial2, PMS_RX_PIN, PMS_TX_PIN);
VentiladorManager ventiladorManager(PIN_RELAY);
LCDManager lcdManager(LCD_I2C_ADDR, LCD_COLUMNS, LCD_ROWS);
WiFiManager wifiManager(WIFI_SSID, WIFI_PASSWORD);
UbidotsManager ubidotsManager(UBIDOTS_TOKEN);

// Definir el mutex global
SemaphoreHandle_t i2cMutex;

// Crear instancia de TasksManager
TasksManager tasksManager;


void setup() {

    Serial.begin(115200);

    // Crear el semáforo para el bus I2C
    i2cMutex = xSemaphoreCreateMutex();
    if (i2cMutex == NULL) {
        Serial.println("Error al crear el semáforo I2C");
        while (1); // Detener si no se pudo crear el semáforo
    } else {
        Serial.println("Mutex I2C creado exitosamente");
    }

    i2cSemaphore = xSemaphoreCreateMutex();
    if (i2cSemaphore == NULL) {
        Serial.println("Error: No se pudo crear i2cSemaphore");
        while (1); // Detener ejecución si falla
    } else {
        Serial.println("i2cSemaphore creado exitosamente");
    }
    
    Wire.begin(21, 22);  // Inicializa el bus I2C con los pines SDA y SCL del ESP32

    // Inicializar módulos
    if (!dhtManager.init()) {
        Serial.println("Error al inicializar el DHT Manager. Continuando...");
    }
    if (!mqManager.init()) {
        Serial.println("Error al inicializar el MQ Manager. Continuando...");
    }
    if (!pmsManager.init()) {
        Serial.println("Error al inicializar el PMS Manager. Continuando...");
    }
    if (!ventiladorManager.init()) {
        Serial.println("Error al inicializar el Ventilador Manager. Continuando...");
    }
    if (!lcdManager.init()) {
        Serial.println("Error al inicializar el LCD Manager. Continuando...");
    }

     if (!EEPROM.begin(512)) { // inicializacion de la EEPROM
        Serial.println("Error inicializando EEPROM. Continuando...");
    }
    
    if (!wifiManager.lastRed()) {   //si falla conexion a ultima red 
        Serial.println("Error al intentar conectar a ultima red disponible. Continuando...");
        wifiManager.init();
        while (WiFi.status() != WL_CONNECTED) // mientras no se encuentre conectado a un red
        {
            wifiManager.loop();// genera una red wifi para que se configure desde la app movil
            
        }
    }
    if (!ubidotsManager.init()){
        Serial.println("Error al inicializar el UBIDOTS Manager. Continuando...");
    }

    // Inicializar tareas
    tasksManager.init();
}

void loop() {
    // No se utiliza, ya que FreeRTOS maneja el flujo principal
}
