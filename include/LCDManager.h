#ifndef LCDMANAGER_H
#define LCDMANAGER_H

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

class LCDManager {
public:
    LCDManager(uint8_t lcdAddr, uint8_t cols, uint8_t rows); // Constructor
    bool init();                                            // Inicializa el LCD
    void print(const String &line1, const String &line2);   // Muestra dos líneas en el LCD

private:
    LiquidCrystal_I2C lcd;                                  // Objeto para manejar el LCD
    uint8_t columns;
    uint8_t rows;
    String currentLine1;                                    // Línea actual 1 en el LCD
    String currentLine2;                                    // Línea actual 2 en el LCD
};

#endif
