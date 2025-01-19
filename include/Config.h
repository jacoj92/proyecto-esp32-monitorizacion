// Config.h
#ifndef CONFIG_H
#define CONFIG_H

#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

// Extern para el mutex global
extern SemaphoreHandle_t i2cMutex;
extern SemaphoreHandle_t i2cSemaphore;

// Configuración de Ubidots
#define UBIDOTS_TOKEN "BBUS-nyq87myIyRcfx0CewWuwTeVc9ffo1D"  

// Configuración de red_wifi_webServer
#define WIFI_SSID "ESP32_AP"
#define WIFI_PASSWORD "moreiravera2024"
#define SERVER_PORT 80 // Puerto del servidor web

// Configuración de Pines y Sensores
#define DHT_PIN 14
#define DHT_TYPE DHT22
#define MQ_PIN 36
#define PMS_RX_PIN 16
#define PMS_TX_PIN 17
#define PIN_RELAY 26
#define LCD_I2C_ADDR 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

#endif
