

# Sistema de Monitorización y Control Ambiental Basado en ESP32

Este repositorio contiene el código y los recursos necesarios para implementar un sistema embebido de monitorización ambiental utilizando un ESP32. El proyecto está diseñado para medir parámetros como temperatura, humedad, calidad del aire y gases inflamables en tiempo real. Además, incluye integración con una plataforma IoT para almacenamiento y notificación remota de alertas.

---

## Características Principales

- **Sensores Utilizados:**
  - DHT22: Medición de temperatura y humedad.
  - PMS5003: Detección de partículas PM2.5.
  - MQ-2: Monitoreo de gases inflamables.

- **Pantalla LCD 16x2:** Visualización de datos en tiempo real.
- **Conectividad WiFi:** Enlace con Firebase para almacenamiento de datos.
- **Notificaciones Remotas:** Integración con Telegram para alertas críticas.
- **FreeRTOS:** Gestión eficiente de tareas concurrentes.

---

## Requisitos

### Hardware
- ESP32
- Sensor DHT22
- Sensor PMS5003
- Sensor MQ-2
- Pantalla LCD 16x2
- Módulo Relé
- Fuente de alimentación (baterías recargables de 3.7V)

### Software
- PlatformIO IDE (recomendado para Visual Studio Code)
- Librerías especificadas en `platformio.ini`:
  - `Adafruit_Sensor`
  - `LiquidCrystal_I2C`
  - `Firebase ESP32`
  - `FreeRTOS`

---

## Instalación

1. **Clona este repositorio:**
   ```bash
   git clone https://github.com/usuario/proyecto-esp32-monitorizacion.git
   cd proyecto-esp32-monitorizacion
   ```

2. **Abre el proyecto en PlatformIO:**
   - Asegúrate de tener instalado Visual Studio Code y la extensión de PlatformIO.
   - Abre la carpeta del proyecto.

3. **Configura los parámetros WiFi y Firebase:**
   - Modifica los valores en el archivo principal dentro de `src/` para incluir tus credenciales de red y configuración de Firebase.

4. **Compila y sube el código:**
   - Conecta tu ESP32 a la computadora.
   - Utiliza PlatformIO para compilar y cargar el código en el dispositivo.

---

## Uso

1. **Conexión a WiFi:** Configura las credenciales WiFi antes de cargar el código.
2. **Visualización de datos:** Los datos se mostrarán en la pantalla LCD en tiempo real.
3. **Plataforma IoT:** Los datos también se subirán a Firebase para monitoreo remoto.
4. **Notificaciones:** Recibirás alertas automáticas en Telegram cuando los parámetros superen los umbrales establecidos.

---

## Estructura del Repositorio

```
proyecto-esp32-monitorizacion/
├── include/         # Archivos de cabecera
├── src/             # Código fuente principal
└── README.md        # Documentación del proyecto
```

---

## Contribuciones

1. Realiza un fork de este repositorio.
2. Crea una nueva rama para tus cambios:
   ```bash
   git checkout -b feature-nueva-funcion
   ```
3. Realiza tus modificaciones y haz commit:
   ```bash
   git commit -m "Agregada nueva función de monitoreo"
   ```
4. Envía un pull request explicando los cambios realizados.

---

## Licencia
Este proyecto está licenciado bajo la [Licencia MIT](LICENSE).

---

## Contacto
Para preguntas o sugerencias, por favor contacta a [tu correo].

