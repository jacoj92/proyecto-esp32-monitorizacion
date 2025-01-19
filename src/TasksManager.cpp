#include "TasksManager.h"
#include "DHTManager.h"
#include "MQManager.h"
#include "PMSManager.h"
#include "LCDManager.h"
#include "UbidotsManager.h"
#include "WiFiManager.h"
#include "VentiladorManager.h"
#include "Config.h"

// FreeRTOS include
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

// Declarar las instancias con extern
extern DHTManager dhtManager;
extern MQManager mqManager;
extern PMSManager pmsManager;
extern VentiladorManager ventiladorManager;  
extern LCDManager lcdManager;
extern WiFiManager wifiManager;
extern UbidotsManager ubidotsManager;

// Declarar mutex
extern SemaphoreHandle_t i2cMutex;

void TasksManager::init() {
    // Crear las tareas
    xTaskCreatePinnedToCore(TaskReadSensors, "TaskReadSensors", 4096, nullptr, 2, NULL, 1);
    xTaskCreatePinnedToCore(TaskUpdateLCD, "TaskUpdateLCD", 8196, &lcdManager, 1, NULL, 1);
    xTaskCreatePinnedToCore(TaskControlFan, "TaskControlFan", 4096, nullptr, 1, NULL, 1);
    xTaskCreatePinnedToCore(TaskSendToUbidots, "Send to Ubidots", 4096, &ubidotsManager, 1, NULL, 1);
    xTaskCreatePinnedToCore(TaskManageWiFi, "Manage WiFi", 16384, &wifiManager, 1, NULL, 1);
}

void TaskReadSensors(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) { // Proteger acceso al bus I2C
            dhtManager.readHumidity();
            dhtManager.readTemperature();

            mqManager.readCO2();
            mqManager.readCO();
            mqManager.readAlcohol();
            
            pmsManager.getPM1_0();
            pmsManager.getPM10();
            pmsManager.getPM2_5();
            xSemaphoreGive(i2cMutex); // Liberar el mutex
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void TaskUpdateLCD(void *pvParameters) {
    // Convertir el parámetro en un puntero a LCDManager
    LCDManager *lcdManager = static_cast<LCDManager *>(pvParameters);

    int sensorIndex = 0; // Contador para alternar entre los sensores
    while (1) {
        if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) { // Proteger acceso al bus I2C
            char line1[16], line2[16]; // Líneas para mostrar en el LCD
            switch (sensorIndex) {
                case 0:
                    snprintf(line1, sizeof(line1), "Temp: %.1f C", dhtManager.readTemperature());
                    snprintf(line2, sizeof(line2), "Hum: %.1f %%", dhtManager.readHumidity());
                    break;
                case 1:
                    snprintf(line1, sizeof(line1), "Alcohol: %.1f", mqManager.readAlcohol());
                    snprintf(line2, sizeof(line2), "CO: %.1f CO2: %.1f", mqManager.readCO(), mqManager.readCO2());
                    break;
                case 2:
                    snprintf(line1, sizeof(line1), "PM1.0: %.1f", (float)pmsManager.getPM1_0());
                    snprintf(line2, sizeof(line2), "PM2.5: %.1f PM10: %.1f", (float)pmsManager.getPM2_5(), (float)pmsManager.getPM10());
                    break;
            }
            lcdManager->print(line1, line2);
            xSemaphoreGive(i2cMutex); // Liberar el mutex
            sensorIndex = (sensorIndex + 1) % 3;
        }else {
            Serial.println("Error al acceder al LCD");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void TaskSendToUbidots(void *pvParameters) {
    // Convertir el parámetro en un puntero a UbidotsManager
    UbidotsManager *ubidotsManager = static_cast<UbidotsManager *>(pvParameters);
    while (1) {
        ubidotsManager->sendData("temperature", dhtManager.readTemperature());
        ubidotsManager->sendData("humidity", dhtManager.readHumidity());
        ubidotsManager->sendData("alcohol", mqManager.readAlcohol());
        ubidotsManager->sendData("CO", mqManager.readCO());
        ubidotsManager->sendData("CO2", mqManager.readCO2());
        ubidotsManager->sendData("PM1_0", pmsManager.getPM1_0());
        ubidotsManager->sendData("PM2_5", pmsManager.getPM2_5());
        ubidotsManager->sendData("PM10", pmsManager.getPM10());
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void TaskManageWiFi(void *pvParameters) {
    WiFiManager *wifiManager = (WiFiManager *)pvParameters;

    while (1) {
        wifiManager->loop();
        vTaskDelay(pdMS_TO_TICKS(10));
        //Serial.printf("Free Stack for TaskManageWiFi: %u bytes\n", uxTaskGetStackHighWaterMark(NULL));

    }
}

void TaskControlFan(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(i2cMutex, portMAX_DELAY)) { // Proteger acceso al bus I2C
            float temperature = dhtManager.readTemperature();
            float humidity = dhtManager.readHumidity();
            float airQuality = mqManager.readCO2();
            float heatIndex = temperature /*+ (0.1 * humidity)*/;
            if (heatIndex > 27.0 /*|| airQuality > 1000.0*/) {
                ventiladorManager.turnOn();
            } else {
                ventiladorManager.turnOff();
            }
            xSemaphoreGive(i2cMutex); // Liberar el mutex
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
