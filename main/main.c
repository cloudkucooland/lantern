#include <string.h>
#include <esp_system.h>
#include <esp_log.h>
// #include <nvs_flash.h>
// #include <esp_event.h>

#include "lantern.h"

static const char *TAG = "lantern";

void app_main(void) {
    ESP_LOGI(TAG, "running...");
    start_neopixel();
}
