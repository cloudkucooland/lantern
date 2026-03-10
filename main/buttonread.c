#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include "sdkconfig.h"

#include "lantern.h"

void start_buttonread(void *) {
    // Configure GPIO
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << BUTTON_PIN),   // Select GPIO 4
        .mode = GPIO_MODE_INPUT,                // Set as input
        .pull_up_en = GPIO_PULLUP_ENABLE,       // Enable internal pull-up
        .pull_down_en = GPIO_PULLDOWN_DISABLE,  // Disable pull-down
        .intr_type = GPIO_INTR_DISABLE          // Disable interrupts
    };
    gpio_config(&io_conf);

    while (1) {
        // Read GPIO level (current state)
        int level = gpio_get_level(BUTTON_PIN);
        if (level == 0) {
            printf("Button Pressed!\n");
        } else {
            printf("Button Released...\n");
            set_brightness(get_brightness() % 8);
        }
        vTaskDelay(pdMS_TO_TICKS(200)); // Delay 200ms
    }
}

