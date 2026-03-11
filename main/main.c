// #include <stdio.h>
// #include <esp_system.h>
// #include <esp_log.h>
// #include <nvs_flash.h>
// #include <esp_event.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sdkconfig.h"
#include "lantern.h"

// static const char *TAG = "lantern";

void app_main(void) {
    // run the lights on very-low-priority
    xTaskCreate(start_neopixel, "start_neopixel", 2048, NULL, tskIDLE_PRIORITY, NULL);

    start_buttonread();
}
