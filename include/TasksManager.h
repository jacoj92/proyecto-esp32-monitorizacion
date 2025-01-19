#ifndef TASKSMANAGER_H
#define TASKSMANAGER_H

//cabeceras de FreeRTOS
#include <freertos/FreeRTOS.h>   // FreeRTOS base types
#include <freertos/task.h>      // Soporte para tareas
#include <freertos/semphr.h>    // Soporte para semáforos


class TasksManager {
public:
    void init();
};

// Declaración de las tareas
void TaskReadSensors(void *pvParameters);
void TaskUpdateLCD(void *pvParameters);
void TaskSendToUbidots(void *pvParameters);
void TaskManageWiFi(void *pvParameters);
void TaskControlFan(void *pvParameters);


#endif

