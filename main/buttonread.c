#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include "driver/gpio.h"
#include "iot_button.h"
#include "button_gpio.h"

#include "lantern.h"

static const char *TAG = "BUTTON";

static void button_single_click_event_cb(void *arg, void *data) {
    ESP_LOGI(TAG, "Button single click!");
    set_brightness((get_brightness() + 1)% 8);
}

static void button_double_click_event_cb(void *arg, void *data) {
    ESP_LOGI(TAG, "Button double click!");
    set_brightness(0);
}

static void button_long_press_event_cb(void *arg, void *data) {
    ESP_LOGI(TAG, "Button long press!");
    set_brightness(8); // or start bt pairing?
}

static void button_repeat_event_cb(void *arg, void *data) {
    ESP_LOGI(TAG, "Button press repeat!");
}

void start_buttonread() {
    const button_config_t btn_cfg = {
        .long_press_time = 5000,      // Long press time in milliseconds
        .short_press_time = 200,      // Short press time in milliseconds
    };

    const button_gpio_config_t btn_gpio_cfg = {
        .gpio_num = BUTTON_IO_NUM,
        .active_level = BUTTON_ACTIVE_LEVEL,
        .disable_pull = false,
    };

    // Button handle
    button_handle_t btn;
    // Create a new button device
    ESP_ERROR_CHECK(iot_button_new_gpio_device(&btn_cfg, &btn_gpio_cfg, &btn));

    // Register callback for button press
    ESP_ERROR_CHECK(iot_button_register_cb(btn, BUTTON_SINGLE_CLICK, NULL, button_single_click_event_cb, NULL));
    ESP_ERROR_CHECK(iot_button_register_cb(btn, BUTTON_DOUBLE_CLICK, NULL, button_double_click_event_cb, NULL));
    ESP_ERROR_CHECK(iot_button_register_cb(btn, BUTTON_LONG_PRESS_UP, NULL, button_long_press_event_cb, NULL));
    ESP_ERROR_CHECK(iot_button_register_cb(btn, BUTTON_PRESS_REPEAT, NULL, button_repeat_event_cb, NULL));
}

