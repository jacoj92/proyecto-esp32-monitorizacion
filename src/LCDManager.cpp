#include "LCDManager.h"
#include <Arduino.h>
#include "TasksManager.h"
#include "config.h"

LCDManager::LCDManager(uint8_t lcdAddr, uint8_t cols, uint8_t rows)
    : lcd(lcdAddr, cols, rows), columns(cols), rows(rows) {
    currentLine1 = "";
    currentLine2 = "";
}

// Inicializa el LCD
bool LCDManager::init() {
    if (xSemaphoreTake(i2cSemaphore, portMAX_DELAY) == pdTRUE) {
        lcd.begin(columns, rows);
        lcd.backlight();             //encendido de la luz de fondo del display
        xSemaphoreGive(i2cSemaphore);
    } else {
        Serial.println("Error al tomar el semáforo I2C para inicializar LCD");
        return false;
    } // Configura el LCD
    if (xSemaphoreTake(i2cSemaphore, portMAX_DELAY) == pdTRUE) {
        lcd.clear();
        xSemaphoreGive(i2cSemaphore);
    } else {
        Serial.println("Error al tomar el semáforo I2C para limpiar LCD");
    }
    lcd.print("LCD Initialized"); // Mensaje de prueba
    delay(2000);                  // Muestra el mensaje por 2 segundos
    if (xSemaphoreTake(i2cSemaphore, portMAX_DELAY) == pdTRUE) {
        lcd.clear();
        xSemaphoreGive(i2cSemaphore);
    } else {
        Serial.println("Error al tomar el semáforo I2C para limpiar LCD");
    }

    Serial.println("LCD initialized successfully");
    return true; // Retorna true ya que no hay forma de verificar errores explícitos
}

// Muestra dos líneas de texto en el LCD
void LCDManager::print(const String &line1, const String &line2) {
    if (line1 != currentLine1 || line2 != currentLine2) { // Actualiza solo si el contenido ha cambiado
        if (xSemaphoreTake(i2cSemaphore, portMAX_DELAY) == pdTRUE) {
        lcd.clear();
        xSemaphoreGive(i2cSemaphore);
    } else {
        Serial.println("Error al tomar el semáforo I2C para limpiar LCD");
    }
        lcd.setCursor(0, 0); // Primera línea
        lcd.print(line1);
        lcd.setCursor(0, 1); // Segunda línea
        lcd.print(line2);
        currentLine1 = line1;
        currentLine2 = line2;
    }
}
