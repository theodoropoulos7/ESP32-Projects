# 🚀 ESP-IDF Essentials: Key Functions & APIs

This document summarizes **must-know ESP-IDF components and functions** when building embedded and IoT apps using the ESP32 family (like the ESP32-S3).

---

## 📚 Categories

### 🔹 System & Utilities

| Header | Description |
|--------|-------------|
| `esp_system.h` | System info, chip reset, reboot, flash size |
| `esp_log.h` | Logging macros: `ESP_LOGI`, `ESP_LOGW`, `ESP_LOGE`, etc. |
| `esp_err.h` | Unified error codes: `ESP_OK`, `ESP_FAIL`, `ESP_ERR_*` |

#### Common Functions
```c
esp_restart();             // Restart the board
esp_chip_info_t chip_info;
esp_chip_info(&chip_info); // Get chip info
```
### 🔹 GPIO (General Purpose IO)
Header	driver/gpio.h

#### Common Functions
```c
gpio_set_direction(GPIO_NUM_5, GPIO_MODE_OUTPUT);
gpio_set_level(GPIO_NUM_5, 1);      // Set HIGH
gpio_get_level(GPIO_NUM_5);         // Read input
```

### 🔹 Timers and Delays
Header	freertos/FreeRTOS.h
Delay & Timing
```c
vTaskDelay(pdMS_TO_TICKS(1000));   // Delay 1 second
esp_timer_get_time();              // Get current time in µs
Periodic Timers
```c
esp_timer_create();
esp_timer_start_periodic();
```

### 🔹 FreeRTOS Multitasking
ESP-IDF apps run under FreeRTOS — use tasks, queues, semaphores, etc.

Common APIs
```c
xTaskCreate(my_task, "Task1", 2048, NULL, 5, NULL);
xQueueCreate(10, sizeof(int));
xSemaphoreCreateBinary();
```
Tasks allow you to create background loops or sensor reading threads.

### 🔹 Wi-Fi
| Headers | esp_wifi.h, esp_event.h, esp_netif.h |

Steps to Connect
Initialize NVS
Init TCP/IP and Wi-Fi driver
Configure Wi-Fi
Register event handler
Connect
Event Handling
```c
esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &handler, NULL);
esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &handler, NULL);
```

### 🔹 HTTP Server
| Header | esp_http_server.h |

Create web server with URI handlers:

```c
httpd_start();
httpd_register_uri_handler(&uri);
```

Serve HTML, JSON, sensor data, etc.

### 🔹 Non-Volatile Storage (NVS)
| Header | nvs_flash.h, nvs.h |

Persistent key-value storage in flash.

```c
nvs_open("storage", NVS_READWRITE, &handle);
nvs_set_i32(handle, "counter", 42);
nvs_get_i32(handle, "counter", &value);
nvs_commit(handle);
nvs_close(handle);
```

### 🔹 ADC – Analog Inputs
| Header | driver/adc.h |

```c
adc1_config_width(ADC_WIDTH_BIT_12);
adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);
int value = adc1_get_raw(ADC1_CHANNEL_0);
```

### 🔹 LED PWM (LEDC)
| Header | driver/ledc.h |

```c
ledc_timer_config();
ledc_channel_config();
ledc_set_duty();
ledc_update_duty();
```
Great for controlling brightness, motors, and LEDs.

### 🔹 I2C & SPI (Sensor Comm)
I2C: driver/i2c.h
SPI: driver/spi_master.h
Setup master mode and talk to peripherals like OLED, IMU, RTC, etc.

## 🔍 Debug Tips
Use ESP_LOGI(TAG, "...") to trace execution
Use idf.py monitor to watch logs
Call esp_restart() on serious errors to recover

## 📚 Additional Learning Resources
ESP-IDF Docs: https://docs.espressif.com
Examples: esp-idf/examples/
API Index: API Reference

## 🧠 Final Tip
Always check the return values of ESP-IDF functions. ESP_ERROR_CHECK() is your best friend.
```c
ESP_ERROR_CHECK(esp_wifi_start());
```
